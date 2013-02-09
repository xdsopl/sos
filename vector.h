
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

struct v3f v3f(float x, float y, float z)
{
	return (struct v3f){ x, y, z };
}

struct v3i v3i(int x, int y, int z)
{
	return (struct v3i){ x, y, z };
}

struct v3f v3f_mul(float a, struct v3f b)
{
	return (struct v3f){ a * b.x, a * b.y, a * b.z };
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

struct v3i v3f2i(struct v3f a)
{
	return (struct v3i){ a.x, a.y, a.z };
}

struct v3f v3i2f(struct v3i a)
{
	return (struct v3f){ a.x, a.y, a.z };
}

#endif
