
/*
sos - SDL OpenGL Skeleton
Written in 2013 by <Ahmet Inan> <xdsopl@googlemail.com>
To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

#ifndef VECTOR_H
#define VECTOR_H
#include <math.h>
#include <emmintrin.h>

typedef float v4sf __attribute__ ((__vector_size__ (16)));
typedef int v4si __attribute__ ((__vector_size__ (16)));
typedef unsigned int v4su __attribute__ ((__vector_size__ (16)));

v4sf v4sf_set1(float a)
{
	return (v4sf){ a, a, a, a };
}

v4sf v4sf_set(float a, float b, float c, float d)
{
	return (v4sf){ a, b, c, d };
}

v4si v4si_set1(int a)
{
	return (v4si){ a, a, a, a };
}

v4si v4si_set(int a, int b, int c, int d)
{
	return (v4si){ a, b, c, d };
}

v4su v4su_set1(unsigned int a)
{
	return (v4su){ a, a, a, a };
}

v4su v4su_set(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
{
	return (v4su){ a, b, c, d };
}

v4sf v4sf_splat0(v4sf a)
{
	return (v4sf)_mm_shuffle_ps(a, a, _MM_SHUFFLE(0,0,0,0));
}

v4sf v4sf_splat1(v4sf a)
{
	return (v4sf)_mm_shuffle_ps(a, a, _MM_SHUFFLE(1,1,1,1));
}

v4sf v4sf_splat2(v4sf a)
{
	return (v4sf)_mm_shuffle_ps(a, a, _MM_SHUFFLE(2,2,2,2));
}

v4sf v4sf_splat3(v4sf a)
{
	return (v4sf)_mm_shuffle_ps(a, a, _MM_SHUFFLE(3,3,3,3));
}

v4si v4sf_cvt(v4sf a)
{
	return (v4si)_mm_cvttps_epi32(a);
}

v4sf v4si_cvt(v4si a)
{
	return (v4sf)_mm_cvtepi32_ps((__m128i)a);
}

v4su v4sf_eq(v4sf a, v4sf b)
{
	return (v4su)_mm_cmpeq_ps(a, b);
}

v4su v4sf_lt(v4sf a, v4sf b)
{
	return (v4su)_mm_cmplt_ps(a, b);
}

v4su v4sf_le(v4sf a, v4sf b)
{
	return (v4su)_mm_cmple_ps(a, b);
}

v4su v4sf_gt(v4sf a, v4sf b)
{
	return (v4su)_mm_cmpgt_ps(a, b);
}

v4su v4sf_ge(v4sf a, v4sf b)
{
	return (v4su)_mm_cmpge_ps(a, b);
}

v4su v4si_eq(v4si a, v4si b)
{
	return (v4su)_mm_cmpeq_epi32((__m128i)a, (__m128i)b);
}

v4su v4si_lt(v4si a, v4si b)
{
	return (v4su)_mm_cmplt_epi32((__m128i)a, (__m128i)b);
}

v4su v4si_gt(v4si a, v4si b)
{
	return (v4su)_mm_cmpgt_epi32((__m128i)a, (__m128i)b);
}

v4sf v4sf_min(v4sf a, v4sf b)
{
	return _mm_min_ps(a, b);
}

v4sf v4sf_max(v4sf a, v4sf b)
{
	return _mm_max_ps(a, b);
}

v4su v4sf_eq1(v4sf a, v4sf b)
{
	return (v4su)_mm_cmpeq_ss(a, b);
}

v4su v4sf_lt1(v4sf a, v4sf b)
{
	return (v4su)_mm_cmplt_ss(a, b);
}

v4su v4sf_le1(v4sf a, v4sf b)
{
	return (v4su)_mm_cmple_ss(a, b);
}

v4su v4sf_gt1(v4sf a, v4sf b)
{
	return (v4su)_mm_cmpgt_ss(a, b);
}

v4su v4sf_ge1(v4sf a, v4sf b)
{
	return (v4su)_mm_cmpge_ss(a, b);
}

v4sf v4sf_min1(v4sf a, v4sf b)
{
	return _mm_min_ss(a, b);
}

v4sf v4sf_max1(v4sf a, v4sf b)
{
	return _mm_max_ss(a, b);
}
v4sf v4sf_hmin3(v4sf a)
{
	return (v4sf)_mm_min_ps(_mm_min_ps(a, (__m128)_mm_shuffle_epi32((__m128i)a, _MM_SHUFFLE(3,0,2,1))), (__m128)_mm_shuffle_epi32((__m128i)a, _MM_SHUFFLE(3,1,0,2)));
}

float v4sf_hmin3_float(v4sf a)
{
	return fminf(fminf(a[0], a[1]), a[2]);
}

v4sf v4sf_hmax3(v4sf a)
{
	return (v4sf)_mm_max_ps(_mm_max_ps(a, (__m128)_mm_shuffle_epi32((__m128i)a, _MM_SHUFFLE(3,0,2,1))), (__m128)_mm_shuffle_epi32((__m128i)a, _MM_SHUFFLE(3,1,0,2)));
}

float v4sf_hmax3_float(v4sf a)
{
	return fmaxf(fmaxf(a[0], a[1]), a[2]);
}

v4sf v4sf_cross3(v4sf a, v4sf b)
{
	return (v4sf)_mm_sub_ps(
		_mm_mul_ps(_mm_shuffle_ps(a, a, _MM_SHUFFLE(3,0,2,1)), _mm_shuffle_ps(b, b, _MM_SHUFFLE(3,1,0,2))),
		_mm_mul_ps(_mm_shuffle_ps(a, a, _MM_SHUFFLE(3,1,0,2)), _mm_shuffle_ps(b, b, _MM_SHUFFLE(3,0,2,1)))
	);
}

float v4sf_dot(v4sf a, v4sf b)
{
	v4sf c = a * b;
	return c[0] + c[1] + c[2] + c[3];
}

v4sf v4sf_normal3(v4sf a)
{
	float f = 1.0f / sqrtf(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	return (v4sf){a[0] * f, a[1] * f, a[2] * f, 0};
}

v4sf v4sf_clamp(v4sf a, v4sf b, v4sf c)
{
	return (v4sf)_mm_min_ps(_mm_max_ps(a, b), c);
}

v4sf v4sf_select(v4su a, v4sf b, v4sf c)
{
//	return (v4sf)_mm_xor_si128(_mm_and_si128((__m128i)a, _mm_xor_si128((__m128i)b, (__m128i)c)), (__m128i)c);
//	return (v4sf)_mm_or_ps(_mm_and_ps((__m128)a, b), _mm_andnot_ps((__m128)a, c));
	return (v4sf)_mm_xor_ps(_mm_and_ps((__m128)a, _mm_xor_ps(b, c)), c);
}

v4si v4si_select(v4su a, v4si b, v4si c)
{
//	return (v4si)_mm_xor_si128(_mm_and_si128((__m128i)a, _mm_xor_si128((__m128i)b, (__m128i)c)), (__m128i)c);
//	return (v4si)_mm_or_ps(_mm_and_ps((__m128)a, (__m128)b), _mm_andnot_ps((__m128)a, (__m128)c));
	return (v4si)_mm_xor_ps(_mm_and_ps((__m128)a, _mm_xor_ps((__m128)b, (__m128)c)), (__m128)c);
}

v4su v4su_select(v4su a, v4su b, v4su c)
{
//	return (v4su)_mm_xor_si128(_mm_and_si128((__m128i)a, _mm_xor_si128((__m128i)b, (__m128i)c)), (__m128i)c);
//	return (v4su)_mm_or_ps(_mm_and_ps((__m128)a, (__m128)b), _mm_andnot_ps((__m128)a, (__m128)c));
	return (v4su)_mm_xor_ps(_mm_and_ps((__m128)a, _mm_xor_ps((__m128)b, (__m128)c)), (__m128)c);
}

int v4si_inside3(v4si a, v4si b)
{
	return (a[0] >= 0) & (a[1] >= 0) & (a[2] >= 0) & (a[0] < b[0]) & (a[1] < b[1]) & (a[2] < b[2]);
}
#endif

