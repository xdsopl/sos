
/*
sos - SDL OpenGL Skeleton
Written in 2013 by <Ahmet Inan> <xdsopl@googlemail.com>
To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

#ifndef VOXEL_H
#define VOXEL_H

#include "vector.h"
#include "ray.h"
#include "aabb.h"

struct grid {
	struct aabb box;
	struct ray ray;
	struct v3i cells;
	struct v3i g;
	struct v3f fp;
	struct v3f step;
	struct v3i sign;
	float l[2];
};

void first_voxel(struct grid *grid)
{
	struct v3f cell_len = v3f_sub_cdiv(grid->box.c1, grid->box.c0, v3i2f(grid->cells));
	float epsilon = 0.001;
	struct v3f inside = v3f_mul_add(grid->l[0] + epsilon, grid->ray.d, grid->ray.o);
	grid->g = v3f2i(v3f_sub_cdiv(inside, grid->box.c0, cell_len));
	struct v3i far_planes = v3i_and(grid->ray.sign, v3i(1, 1, 1));
	grid->fp = v3f_cmul_add(cell_len, v3i2f(v3i_add(grid->g, far_planes)), grid->box.c0);
	grid->step = v3f_select(grid->ray.sign, cell_len, v3f_neg(cell_len));
	grid->sign = v3i_select(grid->ray.sign, v3i(1, 1, 1), v3i(-1, -1, -1));
}

int init_traversal(struct grid *grid, struct ray ray, struct aabb box, struct v3i cells)
{

	float l[2];
	if (!aabb_ray(l, box, ray))
		return 0;

	grid->box = box;
	grid->ray = ray;
	grid->cells = cells;
	grid->l[0] = l[0];
	grid->l[1] = l[1];
	return 1;
}

void next_voxel(struct grid *grid)
{
	struct v3f max = v3f_sub_cmul(grid->fp, grid->ray.o, grid->ray.inv_d);
	struct v3u s = v3f_seq(v3f_hmin(max), max);
	grid->fp = v3f_add(grid->fp, v3f_and(s, grid->step));
	grid->g = v3i_add(grid->g, v3i_and(s, grid->sign));
}

int inside_grid(struct grid *grid)
{
	return v3i_inside(grid->g, grid->cells);
}
#endif

