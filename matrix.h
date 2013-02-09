
/*
sos - SDL OpenGL Skeleton
Written in 2013 by <Ahmet Inan> <xdsopl@googlemail.com>
To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

#ifndef MATRIX_H
#define MATRIX_H
#include <math.h>

struct m4f
{
	float _00, _01, _02, _03;
	float _10, _11, _12, _13;
	float _20, _21, _22, _23;
	float _30, _31, _32, _33;
};

struct m4f m4f_ident()
{
	return (struct m4f){
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
}

struct m4f m4f_mul(struct m4f a, struct m4f b)
{
	float t[16], *l = (float *)&a, *r = (float *)&b;
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 4; k++) {
			t[4*i+k] = 0;
			for (int j = 0; j < 4; j++) {
				t[4*i+k] += l[4*i+j] * r[4*j+k];
			}
		}
	}
	return *(struct m4f *)t;
}
struct m4f m4f_rot(float a, struct v3f v)
{
	float c = cos(a);
	float s = sin(a);
	return (struct m4f){
		v.x*v.x*(1-c)+c,	v.x*v.y*(1-c)-v.z*s,	v.x*v.z*(1-c)+v.y*s,	0,
		v.y*v.x*(1-c)+v.z*s,	v.y*v.y*(1-c)+c,	v.y*v.z*(1-c)-v.x*s,	0,
		v.x*v.z*(1-c)-v.y*s,	v.y*v.z*(1-c)+v.x*s,	v.z*v.z*(1-c)+c,	0,
		0,			0,			0,			1
	};
}
#endif

