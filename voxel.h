
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
	v4si cells;
	v4si g;
	v4sf fp;
	v4sf step;
	v4si sign;
	float l[2];
};

void first_voxel(struct grid *grid)
{
	v4sf cell_len = (grid->box.c1 - grid->box.c0) / v4si_cvt(grid->cells);
	float epsilon = 0.001;
	v4sf inside = v4sf_set1(grid->l[0] + epsilon) * grid->ray.d + grid->ray.o;
	grid->g = v4sf_cvt((inside - grid->box.c0) / cell_len);
	v4si far_planes = (v4si)(grid->ray.sign & (v4su)v4si_set(1, 1, 1, 0));
	grid->fp = cell_len * v4si_cvt(grid->g + far_planes) + grid->box.c0;
	grid->step = v4sf_select(grid->ray.sign, cell_len, -cell_len);
	grid->sign = v4si_select(grid->ray.sign, v4si_set(1, 1, 1, 0), v4si_set(-1, -1, -1, 0));
}

int init_traversal(struct grid *grid, struct ray ray, struct aabb box, v4si cells)
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
	v4sf max = (grid->fp - grid->ray.o) * grid->ray.inv_d;
	v4su s = v4sf_eq(v4sf_hmin3(max), max);
	grid->fp += (v4sf)(s & (v4su)grid->step);
	grid->g += (v4si)(s & (v4su)grid->sign);
}

int inside_grid(struct grid *grid)
{
	return v4si_inside3(grid->g, grid->cells);
}
#endif

