
/*
sos - SDL OpenGL Skeleton
Written in 2013 by <Ahmet Inan> <xdsopl@googlemail.com>
To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

#include <math.h>
#include <stdlib.h>
#include <SDL.h>
#include <GL/gl.h>
#include "vector.h"
#include "matrix.h"
#include "ray.h"
#include "aabb.h"
#include "voxel.h"

struct aabb big_box = {{ -1, -1, -1, 0 }, { 1, 1, 1, 0 }};
v4si cells = { 10, 10, 10, 0 };

m4sf rotation;
float zoom;

float mouse_x;
float mouse_y;
int focus;
GLint static_objects_list;
SDL_Surface *screen;

void draw_box(v4sf color, struct aabb box)
{
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_LINE_LOOP);
		glVertex3f(box.c0[0], box.c0[1], box.c0[2]);
		glVertex3f(box.c0[0], box.c1[1], box.c0[2]);
		glVertex3f(box.c1[0], box.c1[1], box.c0[2]);
		glVertex3f(box.c1[0], box.c0[1], box.c0[2]);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3f(box.c0[0], box.c0[1], box.c0[2]);
		glVertex3f(box.c1[0], box.c0[1], box.c0[2]);
		glVertex3f(box.c1[0], box.c0[1], box.c1[2]);
		glVertex3f(box.c0[0], box.c0[1], box.c1[2]);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3f(box.c0[0], box.c0[1], box.c0[2]);
		glVertex3f(box.c0[0], box.c0[1], box.c1[2]);
		glVertex3f(box.c0[0], box.c1[1], box.c1[2]);
		glVertex3f(box.c0[0], box.c1[1], box.c0[2]);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3f(box.c0[0], box.c0[1], box.c1[2]);
		glVertex3f(box.c1[0], box.c0[1], box.c1[2]);
		glVertex3f(box.c1[0], box.c1[1], box.c1[2]);
		glVertex3f(box.c0[0], box.c1[1], box.c1[2]);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3f(box.c0[0], box.c1[1], box.c0[2]);
		glVertex3f(box.c0[0], box.c1[1], box.c1[2]);
		glVertex3f(box.c1[0], box.c1[1], box.c1[2]);
		glVertex3f(box.c1[0], box.c1[1], box.c0[2]);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3f(box.c1[0], box.c0[1], box.c0[2]);
		glVertex3f(box.c1[0], box.c1[1], box.c0[2]);
		glVertex3f(box.c1[0], box.c1[1], box.c1[2]);
		glVertex3f(box.c1[0], box.c0[1], box.c1[2]);
	glEnd();
}

void draw_cell(v4sf color, v4si g)
{
	v4sf cell_len = (big_box.c1 - big_box.c0) / v4si_cvt(cells);
	struct aabb box = {
		cell_len * v4si_cvt(g) + big_box.c0,
		cell_len * v4si_cvt(v4si_set1(1) + g) + big_box.c0
	};
	draw_box(color, box);
}

void line(v4sf color, v4sf p0, v4sf p1)
{
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_LINES);
		glVertex3f(p0[0], p0[1], p0[2]);
		glVertex3f(p1[0], p1[1], p1[2]);
	glEnd();
}

void static_objects()
{
	v4si g;
	for (g[0] = 0; g[0] < cells[0]; g[0]++)
	for (g[1] = 0; g[1] < cells[1]; g[1]++)
	for (g[2] = 0; g[2] < cells[2]; g[2]++) {
		v4sf color = { 0.1, 0.1, 0.1 };
		draw_cell(color, g);
	}
}

void make_list()
{
	static_objects_list = glGenLists(1);
	glNewList(static_objects_list, GL_COMPILE);
	static_objects();
	glEndList();
}

void dynamic_objects()
{
	struct ray ray = init_ray(v4sf_set(2, 2, 5, 0), v4sf_normal3(v4sf_set(0.1 * mouse_x, 0.1 * mouse_y, -1, 0)));
	v4sf p0 = ray.o;
	v4sf p1 = v4sf_set1(40) * ray.d + ray.o;
	v4sf red = { 1, 0, 0, 0 };
	v4sf cyan = { 0, 1, 1, 0 };

	struct grid grid;
	if (!init_traversal(&grid, ray, big_box, cells)) {
		line(cyan, p0, p1);
		return;
	}

	v4sf pl0 = v4sf_set1(grid.l[0]) * ray.d + ray.o;
	v4sf pl1 = v4sf_set1(grid.l[1]) * ray.d + ray.o;

	line(cyan, p0, pl0);
	line(red, pl0, pl1);
	line(cyan, pl1, p1);

	for (first_voxel(&grid); inside_grid(&grid); next_voxel(&grid))
		draw_cell(red, grid.g);
}

void draw()
{
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.0);
	glMultMatrixf((float *)&rotation);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glCallList(static_objects_list);
	dynamic_objects();
	glFlush();
	SDL_GL_SwapBuffers();
}

void init_gl()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glLineWidth(1.0);
	glMatrixMode(GL_MODELVIEW);
}

void recalc_projection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (screen->w > screen->h) {
		float f = (float)screen->h / (float)screen->w;
		glFrustum(-zoom, zoom, -f * zoom, f * zoom, 5, 20);
	} else {
		float f = (float)screen->w / (float)screen->h;
		glFrustum(-f * zoom, f * zoom, - zoom, zoom, 5, 20);
	}
	glMatrixMode(GL_MODELVIEW);

}

void resize_screen(int w, int h)
{
	screen = SDL_SetVideoMode(w, h, 32, SDL_OPENGL|SDL_DOUBLEBUF|SDL_RESIZABLE);
	if (NULL == screen)
		exit(1);
	if (screen->format->BytesPerPixel != 4)
		exit(1);
	glViewport(0, 0, screen->w, screen->h);
	recalc_projection();
}

void handle_events()
{
	int w = 0, h = 0;
	static int button_left = 0;
	static int button_right = 0;
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_ACTIVEEVENT:
				focus = event.active.gain;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_r:
						rotation = m4sf_identity();
						break;
					case SDLK_q:
					case SDLK_ESCAPE:
						exit(0);
						break;
					default:
						break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button) {
					case SDL_BUTTON_LEFT:
						button_left = 1;
						break;
					case SDL_BUTTON_RIGHT:
						button_right = 1;
						break;
					case SDL_BUTTON_WHEELUP:
						zoom += 0.01;
						recalc_projection();
						break;
					case SDL_BUTTON_WHEELDOWN:
						zoom -= 0.01;
						recalc_projection();
						break;
					default:
						break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				switch (event.button.button) {
					case SDL_BUTTON_LEFT:
						button_left = 0;
						break;
					case SDL_BUTTON_RIGHT:
						button_right = 0;
						break;
					default:
						break;
				}
				break;
			case SDL_MOUSEMOTION:
				if (button_left) {
					rotation = m4sf_mul(rotation, m4sf_rot(v4sf_set(1, 0, 0, 0), -M_PI * (float)event.motion.yrel / (float)screen->h));
					rotation = m4sf_mul(rotation, m4sf_rot(v4sf_set(0, 1, 0, 0), -M_PI * (float)event.motion.xrel / (float)screen->w));
				}
				if (button_right) {
					mouse_x += (float)event.motion.xrel / (float)screen->w;
					mouse_y += -(float)event.motion.yrel / (float)screen->h;
				}
				break;
			case SDL_VIDEORESIZE:
				w = event.resize.w;
				h = event.resize.h;
				break;
			case SDL_QUIT:
				exit(0);
				break;
			default:
				break;
		}
	}
	if (w && h)
		resize_screen(w, h);

}

int main(int argc, char **argv)
{
	(void)argc; (void)argv;
	zoom = 1.0;
	mouse_x = -4.0;
	mouse_y = -4.0;
	focus = 1;
	rotation = m4sf_identity();
	atexit(SDL_Quit);
	SDL_Init(SDL_INIT_VIDEO);
	resize_screen(640, 480);
	SDL_WM_SetCaption("SDL OpenGL Skeleton", "sos");
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	init_gl();
	make_list();
	for (;;) {
		draw();
		if (focus)
			SDL_Delay(10);
		else
			SDL_Delay(100);
		handle_events();
	}
	return 0;
}

