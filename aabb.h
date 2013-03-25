
/*
sos - SDL OpenGL Skeleton
Written in 2013 by <Ahmet Inan> <xdsopl@googlemail.com>
To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

#ifndef AABB_H
#define AABB_H
#include "vector.h"
#include "ray.h"

struct aabb
{
	v4sf c0, c1;
};

int aabb_ray(float l[2], struct aabb box, struct ray ray)
{
	v4sf a = (box.c0 - ray.o) * ray.inv_d;
	v4sf b = (box.c1 - ray.o) * ray.inv_d;
	l[0] = v4sf_hmax3_float(v4sf_min(a, b));
	l[1] = v4sf_hmin3_float(v4sf_max(a, b));
	return l[0] < l[1];
}
#endif
