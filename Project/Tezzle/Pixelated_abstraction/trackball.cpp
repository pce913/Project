
/* Copyright (c) Mark J. Kilgard, 1996. */



/* This program is freely distributable without licensing fees
and is provided without guarantee or warrantee expressed or
implied. This program is -not- in the public domain. */
#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

/* This size should really be based on the distance from the
center of rotation to the point on the object underneath the
mouse.  That point would then track the mouse as closely as
possible.  This is a simple example, though, so that is left
as an Exercise for the Programmer. */

#define TRACKBALLSIZE (1.6)

static float tb_project_to_sphere();
static void normalize_quat();

void vzero(float *v)
{
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
}

void vset(float *v, float x, float y, float z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

void vsub(float *dst, float *src1, float *src2)
{
	dst[0] = src1[0] - src2[0];
	dst[1] = src1[1] - src2[1];
	dst[2] = src1[2] - src2[2];
}

void vcopy(float *v1, float *v2)
{
	int i;
	for (i = 0; i < 3; i++)
		v1[i] = v2[i];
}

void vcopy(int *v1, int *v2)
{
	int i;
	for (i = 0; i < 3; i++)
		v1[i] = v2[i];
}

void vcross(float *cross, float *v1, float *v2)
{
	float temp[3];

	temp[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
	temp[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
	temp[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);
	vcopy(cross, temp);
}

float vlength(const float *v)
{
	return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void vscale(float *v, float div)
{
	v[0] *= div;
	v[1] *= div;
	v[2] *= div;
}

void vnormal(float *v)
{
	vscale(v, 1.0 / vlength(v));
}

float vdot(const float *v1, const float *v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

void vadd(float *dst, float *src1, float *src2)
{
	dst[0] = src1[0] + src2[0];
	dst[1] = src1[1] + src2[1];
	dst[2] = src1[2] + src2[2];
}

/* Given an axis and angle, compute quaternion. */
void axis_to_quat(float a[3], float phi, float q[4])
{
	vnormal(a);
	vcopy(q, a);
	vscale(q, sin(phi / 2.0));
	q[3] = cos(phi / 2.0);
}

/* Project an x,y pair onto a sphere of radius r OR a
hyperbolic sheet if we are away from the center of the
sphere. */
static float tb_project_to_sphere(const float r, float x, float y)
{
	float d, t, z;

	d = sqrt(x * x + y * y);
	if (d < r * 0.70710678118654752440) {  /* Inside sphere. */
		z = sqrt(r * r - d * d);
	}
	else {              /* On hyperbola. */
		t = r / 1.41421356237309504880;
		z = t * t / d;
	}
	return z;
}

void trackball(float *q, float p1x, float p1y, float p2x, float p2y)
{
	float a[3];           /* Axis of rotation. */
	float phi;            /* How much to rotate about axis. */
	float p1[3], p2[3], d[3];
	float t;

	if (p1x == p2x && p1y == p2y) {
		/* Zero rotation */
		vzero(q);
		q[3] = 1.0;
		return;
	}
	/* First, figure out z-coordinates for projection of P1 and
	P2 to deformed sphere. */
	vset(p1, p1x, p1y, tb_project_to_sphere(TRACKBALLSIZE, p1x, p1y));
	vset(p2, p2x, p2y, tb_project_to_sphere(TRACKBALLSIZE, p2x, p2y));

	/* Now, we want the cross product of P1 and P2. */
	vcross(a, p2, p1);

	/* Figure out how much to rotate around that axis. */
	vsub(d, p1, p2);
	t = vlength(d) / (2.0 * TRACKBALLSIZE);

	/* Avoid problems with out-of-control values. */
	if (t > 1.0)
		t = 1.0;
	if (t < -1.0)
		t = -1.0;
	phi = 2.0 * asin(t);

	axis_to_quat(a, phi, q);

}

/* Quaternions always obey:  a^2 + b^2 + c^2 + d^2 = 1.0 If
they don't add up to 1.0, dividing by their magnitude will
renormalize them. */
static void normalize_quat(float q[4])
{
	int i;
	float mag;

	mag = (q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
	for (i = 0; i < 4; i++)
		q[i] /= mag;
}

/* Given two rotations, e1 and e2, expressed as quaternion
rotations, figure out the equivalent single rotation and
stuff it into dest.  This routine also normalizes the result
every RENORMCOUNT times it is called, to keep error from
creeping in.  NOTE: This routine is written so that q1 or q2
may be the same as dest (or each other). */

#define RENORMCOUNT 97

void add_quats(float *q1, float *q2, float *dest)
{
	static int count = 0;
	float t1[4], t2[4], t3[4];
	float tf[4];

	vcopy(t1, q1);
	vscale(t1, q2[3]);

	vcopy(t2, q2);
	vscale(t2, q1[3]);

	vcross(t3, q2, q1);
	vadd(tf, t1, t2);
	vadd(tf, t3, tf);
	tf[3] = q1[3] * q2[3] - vdot(q1, q2);

	dest[0] = tf[0];
	dest[1] = tf[1];
	dest[2] = tf[2];
	dest[3] = tf[3];

	if (++count > RENORMCOUNT) {
		count = 0;
		normalize_quat(dest);
	}
}

/* Build a rotation matrix, given a quaternion rotation. */
void build_rotmatrix(GLfloat m[4][4], float q[4])
{

	m[0][0] = 1.0 - 2.0 * (q[1] * q[1] + q[2] * q[2]);
	m[0][1] = 2.0 * (q[0] * q[1] - q[2] * q[3]);	//	for m[1][0], - -> + 
	m[0][2] = 2.0 * (q[2] * q[0] + q[1] * q[3]);	//	for m[2][0], + -> -
	m[0][3] = 0.0;

	m[1][0] = 2.0 * (q[0] * q[1] + q[2] * q[3]);	//	for m[0][1], + -> -
	m[1][1] = 1.0 - 2.0 * (q[2] * q[2] + q[0] * q[0]);
	m[1][2] = 2.0 * (q[1] * q[2] - q[0] * q[3]);	//	for m[2][1], - -> +
	m[1][3] = 0.0;

	m[2][0] = 2.0 * (q[2] * q[0] - q[1] * q[3]);	//	for m[0][2], - -> +
	m[2][1] = 2.0 * (q[1] * q[2] + q[0] * q[3]);	//	for m[1][2], + -> -
	m[2][2] = 1.0 - 2.0 * (q[1] * q[1] + q[0] * q[0]);
	m[2][3] = 0.0;

	m[3][0] = 0.0;
	m[3][1] = 0.0;
	m[3][2] = 0.0;
	m[3][3] = 1.0;

}
