
/*
sos - SDL OpenGL Skeleton
Written in 2013 by <Ahmet Inan> <xdsopl@googlemail.com>
To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

#ifndef MATRIX_H
#define MATRIX_H
#include <math.h>
#include <emmintrin.h>
#include "vector.h"

typedef struct {
	v4sf v0;
	v4sf v1;
	v4sf v2;
	v4sf v3;
} m4sf;

m4sf m4sf_identity()
{
	return (m4sf) {
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	};
}

m4sf m4sf_mul(m4sf l, m4sf r)
{
	return (m4sf) {
		v4sf_splat0(l.v0) * r.v0 + v4sf_splat1(l.v0) * r.v1 + v4sf_splat2(l.v0) * r.v2 + v4sf_splat3(l.v0) * r.v3,
		v4sf_splat0(l.v1) * r.v0 + v4sf_splat1(l.v1) * r.v1 + v4sf_splat2(l.v1) * r.v2 + v4sf_splat3(l.v1) * r.v3,
		v4sf_splat0(l.v2) * r.v0 + v4sf_splat1(l.v2) * r.v1 + v4sf_splat2(l.v2) * r.v2 + v4sf_splat3(l.v2) * r.v3,
		v4sf_splat0(l.v3) * r.v0 + v4sf_splat1(l.v3) * r.v1 + v4sf_splat2(l.v3) * r.v2 + v4sf_splat3(l.v3) * r.v3
	};
}

v4sf m4sf_vmul(m4sf l, v4sf r)
{
	return (v4sf) {
		v4sf_dot(l.v0, r),
		v4sf_dot(l.v1, r),
		v4sf_dot(l.v2, r),
		v4sf_dot(l.v3, r),
	};
}

m4sf m4sf_rot(v4sf v, float a)
{
	float c = cosf(a);
	float s = sinf(a);
	return (m4sf) {
		{ v[0]*v[0]*(1-c)+c,		v[0]*v[1]*(1-c)-v[2]*s,	v[0]*v[2]*(1-c)+v[1]*s,	0 },
		{ v[1]*v[0]*(1-c)+v[2]*s,	v[1]*v[1]*(1-c)+c,	v[1]*v[2]*(1-c)-v[0]*s,	0 },
		{ v[2]*v[0]*(1-c)-v[1]*s,	v[2]*v[1]*(1-c)+v[0]*s,	v[2]*v[2]*(1-c)+c,	0 },
		{ 0,				0,			0,			1 }
	};
}
#endif

