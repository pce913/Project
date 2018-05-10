//----------------------
#ifndef _VMGMATH_H_
#define _VMGMATH_H_
//----------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;

#define PIF 3.141592653589793238462643383279f

typedef struct {
	float a;
	int b;
} V2DFI;

//	Vector
typedef float V2DF[2];
typedef int V2DI[2];
typedef double V2DD[2];

typedef float V3DF[3];
typedef int V3DI[3];
typedef double V3DD[3];

typedef float V4DF[4];
typedef int V4DI[4];
typedef double V4DD[4];


//	Matrix
typedef float M2DF[2][2];
typedef int M2DI[2][2];
typedef double M2DD[2][2];

typedef float M3DF[3][3];
typedef int M3DI[3][3];
typedef double M3DD[3][3];

typedef float M4DF[4][4];
typedef int M4DI[4][4];
typedef double M4DD[4][4];

typedef float Matrix2DF[2][2];
typedef float Matrix3DF[3][3];
typedef float Matrix4DF[4][4];
typedef double Matrix2DD[2][2];
typedef double Matrix3DD[3][3];
typedef double Matrix4DD[4][4];

//Èñ°æÃß°¡

typedef unsigned char V3DUC[3];

void vzero2(V2DF v);
void vzero(V3DI v);
void vzero(V3DD v);
void vzero(V3DF v);

//	Vector Operation

void vector2(V2DI v, int v1, int v2);
void vector2(V2DF v, float v1, float v2);
void vector2(V2DD v, double v1, double v2);

void vector3(V3DI v, int v1, int v2, int v3);
void vector3(V3DF v, float v1, float v2, float v3);
void vector3(V3DD v, double v1, double v2, double v3);

void vector4(V4DI v, int v1, int v2, int v3, int v4);
void vector4(V4DF v, float v1, float v2, float v3, float v4);
void vector4(V4DD v, double v1, double v2, double v3, double v4);


// dest = src
void vassign(V2DI dest, V2DI src);
void vassign2(V2DF dest, V2DF src);
void vassign2(V2DD dest, V2DD src);

void vcopy(V3DI dest, V3DI src);
void vcopy(V3DF des, V3DF src);
void vassign(V3DF dest, V3DF src);
void vassign(V3DD dest, V3DD src);

void vassign(V4DI dest, V4DI src);
void vassign(V4DF dest, V4DF src);
void vassign(V4DD dest, V4DD src);


// dest += src
void vadd(V2DI dest, V2DI src);
void vadd2(V2DF dest, V2DF src);
void vadd(V2DD dest, V2DD src);

void vadd(V3DI dest, V3DI src);
void vadd(V3DF dest, V3DF src);
void vadd(V3DD dest, V3DD src);

void vadd(V4DI dest, V4DI src);
void vadd(V4DF dest, V4DF src);
void vadd(V4DD dest, V4DD src);

// dest -=src
void vsub(V2DI dest, V2DI src);
void vsub(V2DF dest, V2DF src);
void vsub(V2DD dest, V2DD src);

void vsub(V3DI dest, V3DI src);
void vsub(V3DF dest, V3DF src);
void vsub(V3DD dest, V3DD src);

void vsub(V4DI dest, V4DI src);
void vsub(V4DF dest, V4DF src);
void vsub(V4DD dest, V4DD src);


// dest = src1 + src2
void vadd(V2DI dest, V2DI src1, V2DI src2);
void vadd(V2DF dest, V2DF src1, V2DF src2);
void vadd(V2DD dest, V2DD src1, V2DD src2);

void vadd(V3DI dest, V3DI src1, V3DI src2);
void vadd(V3DF dest, V3DF src1, V3DF src2);
void vadd(V3DD dest, V3DD src1, V3DD src2);

void vadd(V4DI dest, V4DI src1, V4DI src2);
void vadd(V4DF dest, V4DF src1, V4DF src2);
void vadd(V4DD dest, V4DD src1, V4DD src2);

// dest = src1 - src2
void vsub(V2DI dest, V2DI src1, V2DI src2);
void vsub(V2DF dest, V2DF src1, V2DF src2);
void vsub(V2DD dest, V2DD src1, V2DD src2);

void vsub(V3DI dest, V3DI src1, V3DI src2);
void vsub(V3DF dest, V3DF src1, V3DF src2);
void vsub(V3DD dest, V3DD src1, V3DD src2);

void vsub(V4DI dest, V4DI src1, V4DI src2);
void vsub(V4DF dest, V4DF src1, V4DF src2);
void vsub(V4DD dest, V4DD src1, V4DD src2);


bool viszero(V3DF v);

bool vsame(V3DF v1, V3DF v2);

bool vdifferent(V3DF v1, V3DF v2);

void vnegate(V3DF v);

void vscalar2(V2DF v, float sca);
void vscalar(V3DF v, float sca);
void vscalar(V3DI v, int sca);

float vdot(V3DF v1, V3DF v2);

void vcross(V3DF vc, V3DF v1, V3DF v2);
void nvcross(V3DF vc, V3DF v1, V3DF v2);

float vlsquare(V3DF v);

float vlength(V3DF v);
float vlength(V3DF v, V3DF v2);

bool vnorm(V3DF v);

float vuangle(V3DF v1, V3DF v2);
float vsangle(V3DF v1, V3DF v2, V3DF n);

/////////////////////////////////////
//¹Î±³¼ö´Ô mtoolkits.h ÂüÁ¶	(ºÎÅÍ) //
/////////////////////////////////////
/*	v = |p1 - p2|		*/
void nvector(V3DF v, V3DF p1, V3DF p2);
float angle_r_2PIF(V3DF v1, V3DF v2, V3DF nm);
float min2f(float a, float b);
int min2i(int a, int b);
float max2f(float a, float b);
int max2i(int a, int b);
float angle_r(V3DF v1, V3DF v2);
void rotatemat(Matrix4DF mat, float ang, V3DF axis);
float dist(float pt1, float pt2);
float pdist(V3DF pt1, V3DF pt2);
float pdist2(V2DI pt1, V2DI pt2);
float pdist2f(V2DF pt1, V2DF pt2);
void get_point(V3DF pt, V3DF p0, float t, V3DF v);
int inside_triangle(V3DF bary, V3DF pt, V3DF p1, V3DF p2, V3DF p3);
void get_barycentric(V3DF bary, V3DF pt, V3DF p1, V3DF p2, V3DF p3);
float get_determinant2(float m11, float m12, float m21, float m22);
void internal_subdivision_3D(V3DF wpt, float v1, float v2, V3DF p1, V3DF p2);
/////////////////////////////////////
//¹Î±³¼ö´Ô mtoolkits.h ÂüÁ¶	(±îÁö) //
/////////////////////////////////////

// Matrix Operation

void matrix2(M2DI m, int a, int b, int c, int d);
void matrix2(M2DF m, float a, float b, float c, float d);
void matrix2(M2DD m, double a, double b, double c, double d);

void matrix3(M3DI m, int a, int b, int c, int d, int e, int f, int g, int h, int i);
void matrix3(M3DF m, float a, float b, float c, float d, float e, float f, float g, float h, float i);
void matrix3(M3DD m, double a, double b, double c, double d, double e, double f, double g, double h, double i);

void matrix4(M4DI m, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l, int n, int o, int p, int q);
void matrix4(M4DF m, float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float n, float o, float p, float q);
void matrix4(M4DD m, double a, double b, double c, double d, double e, double f, double g, double h, double i, double j, double k, double l, double n, double o, double p, double q);


// dest = src
void massign(M2DI dest, M2DI src);
void massign(M2DF dest, M2DF src);
void massign(M2DD dest, M2DD src);

void massign(M3DI dest, M3DI src);
void massign(M3DF dest, M3DF src);
void massign(M3DD dest, M3DD src);

void massign(M4DI dest, M4DI src);
void massign(M4DF dest, M4DF src);
void massign(M4DD dest, M4DD src);


// dest += src
void madd(M3DF m, float a, float b, float c, float d, float e, float f, float g, float h, float i);
void madd(M2DI dest, M2DI src);
void madd(M2DF dest, M2DF src);
void madd(M2DD dest, M2DD src);

void madd(M3DI dest, M3DI src);
void madd(M3DF dest, M3DF src);
void madd(M3DD dest, M3DD src);

void madd(M4DI dest, M4DI src);
void madd(M4DF dest, M4DF src);
void madd(M4DD dest, M4DD src);

// dest -= src
void msub(M2DI dest, M2DI src);
void msub(M2DF dest, M2DF src);
void msub(M2DD dest, M2DD src);

void msub(M3DI dest, M3DI src);
void msub(M3DF dest, M3DF src);
void msub(M3DD dest, M3DD src);

void msub(M4DI dest, M4DI src);
void msub(M4DF dest, M4DF src);
void msub(M4DD dest, M4DD src);



// dest = src1 + src2
void madd(M2DI dest, M2DI src1, M2DI src2);
void madd(M2DF dest, M2DF src1, M2DF src2);
void madd(M2DD dest, M2DD src1, M2DD src2);

void madd(M3DI dest, M3DI src1, M3DI src2);
void madd(M3DF dest, M3DF src1, M3DF src2);
void madd(M3DD dest, M3DD src1, M3DD src2);

void madd(M4DI dest, M4DI src1, M4DI src2);
void madd(M4DF dest, M4DF src1, M4DF src2);
void madd(M4DD dest, M4DD src1, M4DD src2);

// dest = src1 - src2
void msub(M2DI dest, M2DI src1, M2DI src2);
void msub(M2DF dest, M2DF src1, M2DF src2);
void msub(M2DD dest, M2DD src1, M2DD src2);

void msub(M3DI dest, M3DI src1, M2DI src2);
void msub(M3DF dest, M3DF src1, M2DF src2);
void msub(M3DD dest, M3DD src1, M2DD src2);

void msub(M4DI dest, M4DI src1, M2DI src2);
void msub(M4DF dest, M4DF src1, M2DF src2);
void msub(M4DD dest, M4DD src1, M2DD src2);




// Vector & Matrix Operation

void m_multi_v(V2DF dest, M2DF m, V2DF src);
void m_multi_v(V3DF dest, M3DF m, V3DF src);
void m_multi_v(V4DF dest, M4DF m, V4DF src);




// Transform

// Translate
void translateD(V2DF dest, V2DF src, float dx, float dy);
void translateD(V3DF dest, V3DF src, float dx, float dy, float dz);

// Rotate
void rotateD(V2DF dest, V2DF src, float theta);

// for Direction 
int is_zero_vector(V3DF v);
void rotate_vtx_z(V3DF vtx, float ang);
void vscale(V3DF v, float t);
int is_similar_vector(V3DF p1, V3DF p2, float thr);
void vectori(V3DI v, int p1, int p2, int p3);
int is_near_zero(float val, float thr);
void vsum(V3DF v, V3DF v1);
void vcopy3i(V3DI des, V3DI src);

#endif 