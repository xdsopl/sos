
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

struct aabb big_box = {{ -1, -1, -1 }, { 1, 1, 1 }};
struct v3i cells = { 10, 10, 10 };

struct m4f rotation;
float zoom;

float mouse_x;
float mouse_y;
int focus;
GLint static_objects_list;
SDL_Surface *screen;

void draw_box(struct v3f color, struct aabb box)
{
	glColor3f(color.x, color.y, color.z);
	glBegin(GL_LINE_LOOP);
		glVertex3d(box.c0.x, box.c0.y, box.c0.z);
		glVertex3d(box.c0.x, box.c1.y, box.c0.z);
		glVertex3d(box.c1.x, box.c1.y, box.c0.z);
		glVertex3d(box.c1.x, box.c0.y, box.c0.z);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3d(box.c0.x, box.c0.y, box.c0.z);
		glVertex3d(box.c1.x, box.c0.y, box.c0.z);
		glVertex3d(box.c1.x, box.c0.y, box.c1.z);
		glVertex3d(box.c0.x, box.c0.y, box.c1.z);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3d(box.c0.x, box.c0.y, box.c0.z);
		glVertex3d(box.c0.x, box.c0.y, box.c1.z);
		glVertex3d(box.c0.x, box.c1.y, box.c1.z);
		glVertex3d(box.c0.x, box.c1.y, box.c0.z);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3d(box.c0.x, box.c0.y, box.c1.z);
		glVertex3d(box.c1.x, box.c0.y, box.c1.z);
		glVertex3d(box.c1.x, box.c1.y, box.c1.z);
		glVertex3d(box.c0.x, box.c1.y, box.c1.z);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3d(box.c0.x, box.c1.y, box.c0.z);
		glVertex3d(box.c0.x, box.c1.y, box.c1.z);
		glVertex3d(box.c1.x, box.c1.y, box.c1.z);
		glVertex3d(box.c1.x, box.c1.y, box.c0.z);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3d(box.c1.x, box.c0.y, box.c0.z);
		glVertex3d(box.c1.x, box.c1.y, box.c0.z);
		glVertex3d(box.c1.x, box.c1.y, box.c1.z);
		glVertex3d(box.c1.x, box.c0.y, box.c1.z);
	glEnd();
}

void draw_cell(struct v3f color, struct v3i g)
{
	struct v3f cell_len = v3f_sub_cdiv(big_box.c1, big_box.c0, v3i2f(cells));
	struct aabb box = {
		v3f_cmul_add(cell_len, v3i2f(g), big_box.c0),
		v3f_cmul_add(cell_len, v3i2f(v3i_sadd(1, g)), big_box.c0)
	};
	draw_box(color, box);
}

void line(struct v3f color, struct v3f p0, struct v3f p1)
{
	glColor3f(color.x, color.y, color.z);
	glBegin(GL_LINES);
		glVertex3d(p0.x, p0.y, p0.z);
		glVertex3d(p1.x, p1.y, p1.z);
	glEnd();
}

void static_objects()
{
	struct v3i g;
	for (g.x = 0; g.x < cells.x; g.x++)
	for (g.y = 0; g.y < cells.y; g.y++)
	for (g.z = 0; g.z < cells.z; g.z++) {
		struct v3f color = { 0.1, 0.1, 0.1 };
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
	struct ray ray = init_ray(v3f(2, 2, 5), v3f_normal(v3f(0.1 * mouse_x, 0.1 * mouse_y, -1)));
	struct v3f p0 = ray.o;
	struct v3f p1 = v3f_mul_add(40, ray.d, ray.o);
	float l[2];
	struct v3f red = { 1, 0, 0 };
	struct v3f cyan = { 0, 1, 1 };

	if (!aabb_ray(l, big_box, ray)) {
		line(cyan, p0, p1);
		return;
	}

	struct v3f pl0 = v3f_mul_add(l[0], ray.d, ray.o);
	struct v3f pl1 = v3f_mul_add(l[1], ray.d, ray.o);

	line(cyan, p0, pl0);
	line(red, pl0, pl1);
	line(cyan, pl1, p1);

	struct v3f cell_len = v3f_sub_cdiv(big_box.c1, big_box.c0, v3i2f(cells));
	float epsilon = 0.001;
	struct v3f inside = v3f_mul_add(l[0] + epsilon, ray.d, ray.o);
	struct v3i g = v3f2i(v3f_sub_cdiv(inside, big_box.c0, cell_len));
	struct v3i far_planes = v3i(ray.d.x >= 0 ? 1 : 0, ray.d.y >= 0 ? 1 : 0, ray.d.z >= 0 ? 1 : 0);
	struct v3f fp = v3f_cmul_add(cell_len, v3i2f(v3i_add(g, far_planes)), big_box.c0);
	struct v3f step = v3f_cmul(v3i2f(ray.sign), cell_len);

	while (g.x >= 0 && g.y >= 0 && g.z >= 0 && g.x < cells.x && g.y < cells.y && g.z < cells.z) {
		draw_cell(red, g);
		struct v3f max = v3f_sub_cmul(fp, ray.o, ray.inv_d);
		struct v3u s = v3f_seq(v3f_hmin(max), max);
		g = v3i_add(g, v3u2i(v3u_and(s, v3i2u(ray.sign))));
		fp = v3f_add(fp, v3u2f(v3u_and(s, v3f2u(step))));
	}
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
	float f;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (screen->w > screen->h) {
		f = (float)screen->h / (float)screen->w;
		glFrustum(-zoom, zoom, -f * zoom, f * zoom, 5, 20);
	} else {
		f = (float)screen->w / (float)screen->h;
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
						rotation = m4f_ident();
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
					rotation = m4f_mul(rotation, m4f_rot(-M_PI * (float)event.motion.yrel / (float)screen->h, v3f(1, 0, 0)));
					rotation = m4f_mul(rotation, m4f_rot(-M_PI * (float)event.motion.xrel / (float)screen->w, v3f(0, 1, 0)));
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
	rotation = m4f_ident();
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

