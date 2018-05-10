#include "stdafx.h"
#include "vmg_math.h"

//******************* VECTOR *******************//

//Èñ°æÃß°¡
void vzero2(V2DF v)
{
	v[0] = 0.0f;
	v[1] = 0.0f;
}

void vzero(V3DI v)
{
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
}

void vzero(V3DD v)
{
	v[0] = 0.0;
	v[1] = 0.0;
	v[2] = 0.0;
}

void vzero(V3DF v)
{
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
}


void vector2(V2DF v, float v1, float v2)
{
	v[0] = v1;
	v[1] = v2;
}

void vector2(V2DD v, double v1, double v2)
{
	v[0] = v1;
	v[1] = v2;
}

void vector2(V2DI v, int v1, int v2)
{
	v[0] = v1;
	v[1] = v2;
}

void vector3(V3DF v, float v1, float v2, float v3)
{
	v[0] = v1;
	v[1] = v2;
	v[2] = v3;
}

void vector3(V3DD v, double v1, double v2, double v3)
{
	v[0] = v1;
	v[1] = v2;
	v[2] = v3;
}

void vector3(V3DI v, int v1, int v2, int v3)
{
	v[0] = v1;
	v[1] = v2;
	v[2] = v3;
}

void vector4(V4DF v, float v1, float v2, float v3, float v4)
{
	v[0] = v1;
	v[1] = v2;
	v[2] = v3;
	v[3] = v4;
}

void vector4(V4DD v, double v1, double v2, double v3, double v4)
{
	v[0] = v1;
	v[1] = v2;
	v[2] = v3;
	v[3] = v4;
}

void vector4(V4DI v, int v1, int v2, int v3, int v4)
{
	v[0] = v1;
	v[1] = v2;
	v[2] = v3;
	v[3] = v4;
}



void vassign(V3DF dest, V3DF src)
{
	dest[0] = src[0];	dest[1] = src[1];	dest[2] = src[2];
}

void vassign(V2DI dest, V2DI src)
{
	dest[0] = src[0];	dest[1] = src[1];
}

void vcopy(V3DI dest, V3DI src)
{
	dest[0] = src[0];	dest[1] = src[1];	dest[2] = src[2];
}

void vcopy(V3DF des, V3DF src)
{
	des[0] = src[0];
	des[1] = src[1];
	des[2] = src[2];
}

void vassign2(V2DF dest, V2DF src)
{
	dest[0] = src[0];	dest[1] = src[1];
}

void vassign2(V2DD dest, V2DD src)
{
	dest[0] = src[0];	dest[1] = src[1];
}

bool viszero(V3DF v)
{
	return ((v[0] == 0.0f) && (v[1] == 0.0f) && (v[2] == 0.0f));
}

bool vsame(V3DF v1, V3DF v2)
{
	return ((v1[0] == v2[0]) && (v1[1] == v2[1]) && (v1[2] == v2[2]));
}


//	vector not same
bool vdifferent(V3DF v1, V3DF v2)
{
	return !((v1[0] == v2[0]) && (v1[1] == v2[1]) && (v1[2] == v2[2]));
}

//	vector negate
void vnegate(V3DF v)
{
	v[0] *= -1.0f;
	v[1] *= -1.0f;
	v[2] *= -1.0f;
}

//	vector add
//	dest = src1 + src2
void vadd(V3DF dest, V3DF src1, V3DF src2)
{
	dest[0] = src1[0] + src2[0];
	dest[1] = src1[1] + src2[1];
	dest[2] = src1[2] + src2[2];
}

//	vector subtract
//	dest = src1 - src2;
void vsub(V3DF dest, V3DF src1, V3DF src2)
{
	dest[0] = src1[0] - src2[0];
	dest[1] = src1[1] - src2[1];
	dest[2] = src1[2] - src2[2];
}

//	vector add and assignment
//	dest = dest + src
void vadd(V3DF dest, V3DF src)
{
	dest[0] += src[0];
	dest[1] += src[1];
	dest[2] += src[2];
}

void vadd(V2DI dest, V2DI src)
{
	dest[0] += src[0];
	dest[1] += src[1];
}

void vadd2(V2DF dest, V2DF src)
{
	dest[0] += src[0];
	dest[1] += src[1];
}

//	vector sub and assignment
//	dest = dest - src;
void vsub(V3DF dest, V3DF src)
{
	dest[0] -= src[0];
	dest[1] -= src[1];
	dest[2] -= src[2];
}

//	vector scalar multiplication
void vscalar2(V2DF v, float sca)
{
	v[0] *= sca;
	v[1] *= sca;
}
void vscalar(V3DF v, float sca)
{
	v[0] *= sca;
	v[1] *= sca;
	v[2] *= sca;
}
void vscalar(V3DI v, int sca)
{
	v[0] *= sca;
	v[1] *= sca;
	v[2] *= sca;
}

//	vector inner product
float vdot(V3DF v1, V3DF v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

//	vector outer product
void vcross(V3DF vc, V3DF v1, V3DF v2)
{
	vc[0] = v1[1] * v2[2] - v1[2] * v2[1];
	vc[1] = v1[2] * v2[0] - v1[0] * v2[2];
	vc[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

void nvcross(V3DF vc, V3DF v1, V3DF v2)
{
	vc[0] = v1[1] * v2[2] - v1[2] * v2[1];
	vc[1] = v1[2] * v2[0] - v1[0] * v2[2];
	vc[2] = v1[0] * v2[1] - v1[1] * v2[0];

	vnorm(vc);
}

//	vector length square
float vlsquare(V3DF v)
{
	return vdot(v, v);
}

//	vector length
float vlength(V3DF v)
{
	return sqrt(vlsquare(v));
}

float vlength(V3DF v, V3DF v2)
{
	V3DF tmp;
	vsub(tmp, v, v2);
	return sqrt(vlsquare(tmp));
}

//	vector normalize
bool vnorm(V3DF v)
{
	float leng = vlength(v);

	if (leng == 0.0f)
		return 0.0f;

	v[0] /= leng;
	v[1] /= leng;
	v[2] /= leng;

	return 1.0f;

}

//	vector angle
// unsigned angle: 0 ~ PI
float vuangle(V3DF v1, V3DF v2)
{
	if (viszero(v1) || viszero(v2))
		return 0.0f;

	float tmp = vdot(v1, v2) / (vlength(v1) * vlength(v2));
	if (tmp < -1.0f)
		return 3.1415f;
	if (tmp > 1.0f)
		return 0.0f;

	return acos(tmp);
}

float vsangle(V3DF v1, V3DF v2, V3DF n)
{
	if (viszero(v1) || viszero(v2))
		return 0.0f;

	V3DF vn;
	vcross(vn, v1, v2);
	if (vdot(vn, n) > 0.0f)
		return acos(vdot(v1, v2) / (vlength(v1) * vlength(v2)));
	else
		return -1.0f * acos(vdot(v1, v2) / (vlength(v1) * vlength(v2)));
}

/////////////////////////////////////
//¹Î±³¼ö´Ô mtoolkits.h ÂüÁ¶	(ºÎÅÍ) //
/////////////////////////////////////
/*	v = |p1 - p2|		*/
void nvector(V3DF v, V3DF p1, V3DF p2)
{
	int i;

	for (i = 0; i < 3; i++)
		v[i] = p1[i] - p2[i];

	bool temp = vnorm(v);
}

/*	The angle ( radian ) between v1 and v2	*/
//	0 < angle < 2PIF
//	from v1 to v2
float angle_r_2PIF(V3DF v1, V3DF v2, V3DF nm)
{
	float temp, temp2;

	temp = vdot(v1, v2);
	temp2 = (float)sqrt(vdot(v1, v1))*(float)sqrt(vdot(v2, v2));
	if (temp2 == 0.0f)
		return 0.0f;
	temp = temp / temp2;

	if (temp > 0.0f)
		temp = min2f(temp, 1.0f);
	else
		temp = max2f(temp, -1.0f);

	V3DF vnm;
	vcross(vnm, v1, v2);
	float ac = (float)acos(temp);
	if (vdot(vnm, nm) > 0.0f) {
		return ac;
	}
	else {
		return 2.0f * PIF - ac;
	}
}

float min2f(float a, float b)
{
	if (a < b)
		return a;
	else
		return b;
}

int min2i(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

float max2f(float a, float b)
{
	if (a > b)
		return a;
	else
		return b;
}

int max2i(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

/*	The angle ( radian ) between v1 and v2	*/
//	0 < angle < PIF
float angle_r(V3DF v1, V3DF v2)
{
	float temp, temp2;

	temp = vdot(v1, v2);
	temp2 = (float)sqrt(vdot(v1, v1))*(float)sqrt(vdot(v2, v2));
	if (temp2 == 0.0f)
		return 0.0f;
	temp = temp / temp2;

	temp = (temp <= 1.0f) ? temp : 1.0f;
	return (float)acos(temp);
}

void rotatemat(Matrix4DF mat, float ang, V3DF axis)
{
	int i, j;
	float s = (float)-sin(ang);
	float c = (float)cos(ang);

	for (i = 0; i < 4; i++)
	for (j = 0; j < 4; j++)
		mat[i][j] = 0.0f;

	for (i = 0; i < 4; i++)
		mat[i][i] = 1.0f;

	mat[0][0] = (1 - c)*axis[0] * axis[0] + c;
	mat[0][1] = (1 - c)*axis[0] * axis[1] + s*axis[2];
	mat[0][2] = (1 - c)*axis[0] * axis[2] - s*axis[1];
	mat[1][0] = (1 - c)*axis[0] * axis[1] - s*axis[2];
	mat[1][1] = (1 - c)*axis[1] * axis[1] + c;
	mat[1][2] = (1 - c)*axis[1] * axis[2] + s*axis[0];
	mat[2][0] = (1 - c)*axis[0] * axis[2] + s*axis[1];
	mat[2][1] = (1 - c)*axis[1] * axis[2] - s*axis[0];
	mat[2][2] = (1 - c)*axis[2] * axis[2] + c;
}

float dist(float pt1, float pt2)
{
	float tmp;

	tmp = (pt1 - pt2)*(pt1 - pt2);

	return (float)sqrt(tmp);
}

float pdist(V3DF pt1, V3DF pt2)
{
	int i;
	float tmp;

	for (i = 0, tmp = 0.0; i < 3; i++)
		tmp += (pt1[i] - pt2[i])*(pt1[i] - pt2[i]);

	return (float)sqrt(tmp);
}

float pdist2(V2DI pt1, V2DI pt2)
{
	int i;
	float tmp;

	for (i = 0, tmp = 0.0; i < 2; i++)
		tmp += (pt1[i] - pt2[i])*(pt1[i] - pt2[i]);

	return (float)sqrt(tmp);
}

float pdist2f(V2DF pt1, V2DF pt2)
{
	int i;
	float tmp;

	for (i = 0, tmp = 0.0; i < 2; i++)
		tmp += (pt1[i] - pt2[i])*(pt1[i] - pt2[i]);

	return (float)sqrt(tmp);
}

void get_point(V3DF pt, V3DF p0, float t, V3DF v)
{
	pt[0] = p0[0] + t*v[0];
	pt[1] = p0[1] + t*v[1];
	pt[2] = p0[2] + t*v[2];
}

int inside_triangle(V3DF bary, V3DF pt, V3DF p1, V3DF p2, V3DF p3)
{
	get_barycentric(bary, pt, p1, p2, p3);

	return (bary[0] >= 0.0f && bary[1] >= 0.0f && bary[2] >= 0.0f);
}

void get_barycentric(V3DF bary, V3DF pt, V3DF p1, V3DF p2, V3DF p3)
{
	float l, s, t;
	V3DF v, ppt;
	V3DF v1, v2, npt;
	nvector(v, pt, p1);

	l = get_determinant2(p2[0] - p1[0], p2[0] - p3[0], p2[1] - p1[1], p2[1] - p3[1]) / get_determinant2(v[0], p2[0] - p3[0], v[1], p2[1] - p3[1]);
	get_point(ppt, p1, l, v);

	t = pdist(pt, p1) / l;
	internal_subdivision_3D(npt, t, 1.0f - t, p1, ppt);

	nvector(v1, ppt, p2);
	nvector(v2, p3, p2);
	if (vdot(v1, v2) > 0.0f)
		s = pdist(ppt, p2) / pdist(p2, p3);
	else
		s = -pdist(ppt, p2) / pdist(p2, p3);
	internal_subdivision_3D(npt, s, 1.0f - s, p2, p3);
	internal_subdivision_3D(ppt, t, 1.0f - t, p1, npt);
	vector3(bary, 1.0f - t, t*(1.0f - s), s*t);
}

float get_determinant2(float m11, float m12, float m21, float m22)
{
	return m11*m22 - m12*m21;
}

void internal_subdivision_3D(V3DF wpt, float v1, float v2, V3DF p1, V3DF p2)
{
	wpt[0] = (v2*p1[0] + v1*p2[0]) / (v1 + v2);
	wpt[1] = (v2*p1[1] + v1*p2[1]) / (v1 + v2);
	wpt[2] = (v2*p1[2] + v1*p2[2]) / (v1 + v2);
}

/////////////////////////////////////
//¹Î±³¼ö´Ô mtoolkits.h ÂüÁ¶	(±îÁö) //
/////////////////////////////////////

//******************************* MATRIX ****************************//
// Matris Operatrion
// Vector & Matrix operation 


void matrix2(M3DF m, float a, float b, float c, float d)
{
	m[0][0] = a; m[0][1] = b;
	m[1][0] = c; m[1][1] = d;
}

void matrix3(M3DF m, float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
	m[0][0] = a; m[0][1] = b; m[0][2] = c;
	m[1][0] = d; m[1][1] = e; m[1][2] = f;
	m[2][0] = g; m[2][1] = h; m[2][2] = i;
}

void matrix4(M4DF m, float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float n, float o, float p, float q)
{
	m[0][0] = a; m[0][1] = b; m[0][2] = c; m[0][3] = d;
	m[1][0] = e; m[1][1] = f; m[1][2] = g; m[1][3] = h;
	m[2][0] = i; m[2][1] = j; m[2][2] = k; m[2][3] = l;
	m[3][0] = n; m[3][1] = o; m[3][2] = p; m[3][3] = q;

}

void madd(M3DF m, float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
	m[0][0] += a; m[0][1] += b; m[0][2] += c;
	m[1][0] += d; m[1][1] += e; m[1][2] += f;
	m[2][0] += g; m[2][1] += h; m[2][2] += i;
}

void m_multi_v(V2DF dest, M2DF m, V2DF src)
{
	dest[0] = m[0][0] * src[0] + m[0][1] * src[1];
	dest[0] = m[1][0] * src[0] + m[1][1] * src[1];
}

void m_multi_v(V3DF dest, M3DF m, V3DF src)
{
	dest[0] = m[0][0] * src[0] + m[0][1] * src[1] + m[0][2] * src[2];
	dest[1] = m[1][0] * src[0] + m[1][1] * src[1] + m[1][2] * src[2];
	dest[2] = m[2][0] * src[0] + m[2][1] * src[1] + m[2][2] * src[2];
}

void m_multi_v(V4DF dest, M4DF m, V4DF src)
{
	dest[0] = m[0][0] * src[0] + m[0][1] * src[1] + m[0][2] * src[2] + m[0][3] * src[3];
	dest[1] = m[1][0] * src[0] + m[1][1] * src[1] + m[1][2] * src[2] + m[1][3] * src[3];
	dest[2] = m[2][0] * src[0] + m[2][1] * src[1] + m[2][2] * src[2] + m[2][3] * src[3];
	dest[3] = m[3][0] * src[0] + m[3][1] * src[1] + m[3][2] * src[2] + m[3][3] * src[3];
}




//******************************* TRANSFORM ***************************//


// Translate
void translateD(V2DF dest, V2DF src, float dx, float dy)
{
	V3DF hdest, hsrc;
	M3DF m;

	vector3(hsrc, src[0], src[1], 1.0f);
	matrix3(m, 1.0f, 0.0f, dx, 0.0, 1.0f, dy, 0.0, 0.0, 1.0f);
	m_multi_v(hdest, m, hsrc);
	vector2(dest, hdest[0], hdest[1]);
}

void translateD(V3DF dest, V3DF src, float dx, float dy, float dz)
{
	V4DF hdest, hsrc;
	M4DF m;

	vector4(hsrc, src[0], src[1], src[2], 1.0f);
	matrix4(m, 1.0f, 0.0, 0.0, dx, 0.0, 1.0f, 0.0, dy, 0.0, 0.0, 1.0f, dx, 0.0, 0.0, 0.0, 1.0f);
	m_multi_v(hdest, m, hsrc);
	vector3(dest, hdest[0], hdest[1], hdest[2]);
}


// Rotate
void rotateD(V2DF dest, V2DF src, float theta)
{
	V3DF hdest, hsrc;
	M3DF m;

	vector3(hsrc, src[0], src[1], 1.0f);
	matrix3(m, cos(theta), -sin(theta), 0.0, sin(theta), cos(theta), 0.0, 0.0, 0.0, 1.0f);
	m_multi_v(hdest, m, hsrc);
	vector2(dest, hdest[0], hdest[1]);

}

int is_zero_vector(V3DF v)
{
	return ((v[0] == 0.0f) && (v[1] == 0.0f) && (v[2] == 0.0f));
}

void rotate_vtx_z(V3DF vtx, float ang)
{
	int i, j;
	float rad = ang*(PIF / 180.0f);
	float rotmat[3][3];
	V3DF rvtx;

	for (i = 0; i < 3; i++)
	for (j = 0; j < 3; j++)
		rotmat[i][j] = 0.0;
	rotmat[0][0] = (float)cos(rad);
	rotmat[0][1] = (float)-sin(rad);
	rotmat[1][0] = (float)sin(rad);
	rotmat[1][1] = (float)cos(rad);
	rotmat[2][2] = 1.0f;

	for (i = 0; i < 3; i++)
	for (j = 0, rvtx[i] = 0; j < 3; j++)
		rvtx[i] += rotmat[i][j] * vtx[j];

	//	printf("%f, %f, %f: %f, %f, %f\n", vtx[0], vtx[1], vtx[2], rvtx[0], rvtx[1], rvtx[2] );

	vcopy(vtx, rvtx);
}

void vscale(V3DF v, float t)
{
	v[0] *= t;
	v[1] *= t;
	v[2] *= t;
}

int is_near_zero(float val, float thr)
{
	if (fabs(val) <= thr)
		return true;
	else
		return false;
}


int is_similar_vector(V3DF p1, V3DF p2, float thr)
{
	//	if ( is_near_zero ( p1[0]-p2[0], thr ) && is_near_zero ( p1[1]-p2[1], thr ) && is_near_zero ( p1[2]-p2[2], thr ) )
	if (is_near_zero(pdist(p1, p2), thr))
		return true;
	else
		return false;
}

void vectori(V3DI v, int p1, int p2, int p3)
{
	v[0] = p1;
	v[1] = p2;
	v[2] = p3;
}

void vsum(V3DF v, V3DF v1)
{
	v[0] += v1[0];
	v[1] += v1[1];
	v[2] += v1[2];
}

void vcopy3i(V3DI des, V3DI src)
{
	des[0] = src[0];
	des[1] = src[1];
	des[2] = src[2];
}
