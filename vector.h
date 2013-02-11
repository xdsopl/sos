
/*
sos - SDL OpenGL Skeleton
Written in 2013 by <Ahmet Inan> <xdsopl@googlemail.com>
To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

#ifndef VECTOR_H
#define VECTOR_H
#include <math.h>

struct v3f {
	float x, y, z;
};

struct v3i {
	int x, y, z;
};

struct v3u {
	unsigned int x, y, z;
};

struct v3f v3f(float x, float y, float z)
{
	return (struct v3f){ x, y, z };
}

struct v3i v3i(int x, int y, int z)
{
	return (struct v3i){ x, y, z };
}

struct v3u v3u(unsigned int x, unsigned int y, unsigned int z)
{
	return (struct v3u){ x, y, z };
}

struct v3i v3f2i(struct v3f a)
{
	return (struct v3i){ a.x, a.y, a.z };
}

struct v3f v3i2f(struct v3i a)
{
	return (struct v3f){ a.x, a.y, a.z };
}

struct v3u v3i2u(struct v3i a)
{
	union {
		struct v3i in;
		struct v3u out;
	} fu;
	fu.in = a;
	return fu.out;
}

struct v3u v3f2u(struct v3f a)
{
	union {
		struct v3f in;
		struct v3u out;
	} fu;
	fu.in = a;
	return fu.out;
}

struct v3f v3u2f(struct v3u a)
{
	union {
		struct v3u in;
		struct v3f out;
	} fu;
	fu.in = a;
	return fu.out;
}

struct v3i v3u2i(struct v3u a)
{
	union {
		struct v3u in;
		struct v3i out;
	} fu;
	fu.in = a;
	return fu.out;
}

struct v3f v3f_neg(struct v3f a)
{
	return (struct v3f){ - a.x, - a.y, - a.z };
}

struct v3f v3f_mul(float a, struct v3f b)
{
	return (struct v3f){ a * b.x, a * b.y, a * b.z };
}

struct v3f v3f_cmul(struct v3f a, struct v3f b)
{
	return (struct v3f){ a.x * b.x, a.y * b.y, a.z * b.z };
}

struct v3f v3f_cdiv(struct v3f a, struct v3f b)
{
	return (struct v3f){ a.x / b.x, a.y / b.y, a.z / b.z };
}

struct v3i v3i_sadd(int a, struct v3i b)
{
	return (struct v3i){ a + b.x, a + b.y, a + b.z };
}

struct v3f v3f_sadd(float a, struct v3f b)
{
	return (struct v3f){ a + b.x, a + b.y, a + b.z };
}

struct v3f v3f_add(struct v3f a, struct v3f b)
{
	return (struct v3f){ a.x + b.x, a.y + b.y, a.z + b.z };
}

struct v3f v3f_sub(struct v3f a, struct v3f b)
{
	return (struct v3f){ a.x - b.x, a.y - b.y, a.z - b.z };
}

struct v3i v3i_add(struct v3i a, struct v3i b)
{
	return (struct v3i){ a.x + b.x, a.y + b.y, a.z + b.z };
}

struct v3f v3f_mul_sadd(float a, struct v3f b, float c)
{
	return (struct v3f){ a * b.x + c, a * b.y + c, a * b.z + c };
}

struct v3f v3f_mul_add(float a, struct v3f b, struct v3f c)
{
	return (struct v3f){ a * b.x + c.x, a * b.y + c.y, a * b.z + c.z };
}

struct v3f v3f_cmul_add(struct v3f a, struct v3f b, struct v3f c)
{
	return (struct v3f){ a.x * b.x + c.x, a.y * b.y + c.y, a.z * b.z + c.z };
}

struct v3f v3f_sub_cmul(struct v3f a, struct v3f b, struct v3f c)
{
	return (struct v3f){ (a.x - b.x) * c.x, (a.y - b.y) * c.y, (a.z - b.z) * c.z };
}

struct v3f v3f_sub_cdiv(struct v3f a, struct v3f b, struct v3f c)
{
	return (struct v3f){ (a.x - b.x) / c.x, (a.y - b.y) / c.y, (a.z - b.z) / c.z };
}

struct v3f v3f_normal(struct v3f a)
{
	float f = 1.0f / sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	return v3f(a.x * f, a.y * f, a.z * f);
}

struct v3f v3f_cmin(struct v3f a, struct v3f b)
{
	return (struct v3f){ fminf(a.x, b.x), fminf(a.y, b.y), fminf(a.z, b.z) };
}

struct v3f v3f_cmax(struct v3f a, struct v3f b)
{
	return (struct v3f){ fmaxf(a.x, b.x), fmaxf(a.y, b.y), fmaxf(a.z, b.z) };
}

float v3f_hmin(struct v3f a)
{
	return fminf(fminf(a.x, a.y), a.z);
}

float v3f_hmax(struct v3f a)
{
	return fmaxf(fmaxf(a.x, a.y), a.z);
}

struct v3u v3u_and(struct v3u a, struct v3u b)
{
	return (struct v3u){ a.x & b.x, a.y & b.y, a.z & b.z };
}

struct v3f v3f_and(struct v3u a, struct v3f b)
{
	return v3u2f(v3u_and(a, v3f2u(b)));
}

struct v3i v3i_and(struct v3u a, struct v3i b)
{
	return v3u2i(v3u_and(a, v3i2u(b)));
}

unsigned int v3u_hand(struct v3u a)
{
	return a.x & a.y & a.z;
}

struct v3u v3u_or(struct v3u a, struct v3u b)
{
	return (struct v3u){ a.x | b.x, a.y | b.y, a.z | b.z };
}

unsigned int v3u_hor(struct v3u a)
{
	return a.x | a.y | a.z;
}

struct v3u v3u_xor(struct v3u a, struct v3u b)
{
	return (struct v3u){ a.x ^ b.x, a.y ^ b.y, a.z ^ b.z };
}

struct v3u v3u_not(struct v3u a)
{
	return (struct v3u){ ~a.x, ~a.y, ~a.z };
}

struct v3u v3u_select(struct v3u a, struct v3u b, struct v3u c)
{
	return (struct v3u){ (a.x & b.x) | ((~a.x) & c.x), (a.y & b.y) | ((~a.y) & c.y), (a.z & b.z) | ((~a.z) & c.z) };
}

struct v3f v3f_select(struct v3u a, struct v3f b, struct v3f c)
{
	return v3u2f(v3u_select(a, v3f2u(b), v3f2u(c)));
}

struct v3i v3i_select(struct v3u a, struct v3i b, struct v3i c)
{
	return v3u2i(v3u_select(a, v3i2u(b), v3i2u(c)));
}

struct v3u v3f_ge(struct v3f a, struct v3f b)
{
	return (struct v3u){ (a.x >= b.x) ? ~0 : 0, (a.y >= b.y) ? ~0 : 0, (a.z >= b.z) ? ~0 : 0 };
}

struct v3u v3i_ge(struct v3i a, struct v3i b)
{
	return (struct v3u){ (a.x >= b.x) ? ~0 : 0, (a.y >= b.y) ? ~0 : 0, (a.z >= b.z) ? ~0 : 0 };
}

struct v3u v3f_lt(struct v3f a, struct v3f b)
{
	return (struct v3u){ (a.x < b.x) ? ~0 : 0, (a.y < b.y) ? ~0 : 0, (a.z < b.z) ? ~0 : 0 };
}

struct v3u v3i_lt(struct v3i a, struct v3i b)
{
	return (struct v3u){ (a.x < b.x) ? ~0 : 0, (a.y < b.y) ? ~0 : 0, (a.z < b.z) ? ~0 : 0 };
}

struct v3u v3f_eq(struct v3f a, struct v3f b)
{
	return (struct v3u){ (a.x == b.x) ? ~0 : 0, (a.y == b.y) ? ~0 : 0, (a.z == b.z) ? ~0 : 0 };
}

struct v3u v3f_seq(float a, struct v3f b)
{
	return (struct v3u){ (a == b.x) ? ~0 : 0, (a == b.y) ? ~0 : 0, (a == b.z) ? ~0 : 0 };
}

unsigned int v3i_inside(struct v3i a, struct v3i b)
{
	return (a.x >= 0) & (a.y >= 0) & (a.z >= 0) & (a.x < b.x) & (a.y < b.y) & (a.z < b.z);
}
#endif
