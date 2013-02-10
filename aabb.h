
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
	struct v3f c0, c1;
};

struct v3u aabb_ray_step(struct v3f fp, struct ray ray)
{
	struct v3f max = v3f_sub_cmul(fp, ray.o, ray.inv_d);
	return v3f_seq(v3f_hmin(max), max);
}

int aabb_ray(float l[2], struct aabb box, struct ray ray)
{
	struct v3f a = v3f_sub_cmul(box.c0, ray.o, ray.inv_d);
	struct v3f b = v3f_sub_cmul(box.c1, ray.o, ray.inv_d);
	l[0] = v3f_hmax(v3f_cmin(a, b));
	l[1] = v3f_hmin(v3f_cmax(a, b));
	return l[0] < l[1];
}
#endif
