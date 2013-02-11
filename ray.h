
/*
sos - SDL OpenGL Skeleton
Written in 2013 by <Ahmet Inan> <xdsopl@googlemail.com>
To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

#ifndef RAY_H
#define RAY_H
#include "vector.h"

struct ray
{
	struct v3f o, d;
	struct v3f inv_d;
	struct v3u sign;
};

struct ray init_ray(struct v3f o, struct v3f d)
{
	struct ray ray;
	ray.o = o;
	ray.d = d;
	ray.inv_d = v3f_cdiv(v3f(1, 1, 1), d);
	ray.sign = v3f_ge(d, v3f(0, 0, 0));
	return ray;
}

#endif
