#include "stdafx.h"
#include "conv_clr.h"

//변환행렬
//M3DF m_RGBtoXYZ = {0.490f, 0.310f, 0.200f, 0.177f, 0.812f, 0.011f, 0.000f, 0.010f, 0.990f};		//RcGcBc
Matrix3DF m_RGBtoXYZ = { 0.607f, 0.174f, 0.200f, 0.299f, 0.587f, 0.114f, 0.000f, 0.066f, 1.116f };		//RnGnBn
//M3DF m_RGBtoXYZ = {0.393f, 0.365f, 0.192f, 0.212f, 0.701f, 0.087f, 0.019f, 0.112f, 0.958f};		//RsGsBs

//M3DF m_XYZtoRGB = {2.36486f, -0.897081f, -0.467783f, -0.515564f, 1.42727f, 0.0882959f, 0.00520772f, -0.0144169f, 1.00921f};		//RcGcBc
Matrix3DF m_XYZtoRGB = { 1.91046f, -0.53394f, -0.287834f, -0.984436f, 1.9985f, -0.027726f, 0.0582193f, -0.118191f, 0.897697f };		//RnGnBn
//M3DF m_XYZtoRGB = {3.50969f, -1.74031f, -0.545358f, -1.06828f, 1.97725f, 0.0345393f, 0.0552852f, -0.196645f, 1.05062f};		//RsGsBs

//reference white
//V3DF rWhite = {1.0f, 1.0f, 1.0f};
//V3DF rWhite = {0.46f, 0.46f, 0.46f};
Matrix3DF rWhite = { 0.964221f, 1.0f, 0.825211f };

void RGBtoXYZ(float iR, float iG, float iB, float *oX, float *oY, float *oZ)
{
	V3DF res, iRGB;		vector3(iRGB, iR, iG, iB); // 벡터만들기
	m_multi_v(res, m_RGBtoXYZ, iRGB);

	(*oX) = res[0];
	(*oY) = res[1];
	(*oZ) = res[2];
}

void XYZtoRGB(float iX, float iY, float iZ, float *oR, float *oG, float *oB)
{
	V3DF res, iXYZ;			vector3(iXYZ, iX, iY, iZ); // 벡터만들기
	m_multi_v(res, m_XYZtoRGB, iXYZ);

	(*oR) = res[0];
	(*oG) = res[1];
	(*oB) = res[2];
}

void XYZtoLUV(float iX, float iY, float iZ, float *oL, float *oU, float *oV)
{
	float x0, y0, z0;
	float u0, v0;

	x0 = 0.98072;
	y0 = 1.00000;
	z0 = 1.18225;
	/*x0 = 1.00000;
	y0 = 1.00000;
	z0 = 1.00000;*/

	u0 = 4.0f*x0 / (x0 + 15.0f*y0 + 3.0f*z0);
	v0 = 9.0f*y0 / (x0 + 15.0f*y0 + 3.0f*z0);

	float u_, v_;
	if ((iX + 15.0f*iY + 3.0f*iZ) == 0.0f)
		u_ = 0.0f;
	else
		u_ = 4.0f*iX / (iX + 15.0f*iY + 3.0f*iZ);

	if ((iX + 15.0f*iY + 3.0f*iZ) == 0.0f)
		v_ = 0.0f;
	else
		v_ = 9.0f*iY / (iX + 15.0f*iY + 3.0f*iZ);

	if (iY / y0 >= 0.008856)
		(*oL) = 25.0f * pow(100.0f * (iY / y0), 1.0f / 3.0f) - 16.0f;
	else if (iY / y0 < 0.008856)
		(*oL) = 903.3f * (iY / y0);

	(*oU) = 13.0f*(*oL)*(u_ - u0);
	(*oV) = 13.0f*(*oL)*(v_ - v0);
	//	(*oU) = (*oL);
	//	(*oV) = (*oL);
}

void LUVtoXYZ(float iL, float iU, float iV, float *oX, float *oY, float *oZ)
{
	float x0, y0, z0;
	float u0, v0;

	x0 = 0.98072;
	y0 = 1.00000;
	z0 = 1.18225;

	u0 = 4.0f*x0 / (x0 + 15.0f*y0 + 3.0f*z0);
	v0 = 9.0f*y0 / (x0 + 15.0f*y0 + 3.0f*z0);

	/*float u_ = (iL!=0.0f)? iU/(13.0f*iL) + u0: 0.0f;
	float v_ = (iL!=0.0f)? iV/(13.0f*iL) + v0: 0.0f;*/
	/*(*oY) = (y0/100.0f) * pow( (iL+16.0f) / 25.0f, 3.0f );
	(*oX) = (v_!=0.0f)? ( (9.0f*u_)/(4.0f*v_) ) * (*oY): 0.0f;
	(*oZ) = (v_!=0.0f)? (*oY) * ( (12.0f - 3.0f*u_ - 20.0f*v_) / (4.0f*v_) ): 0.0f;*/

	float u_ = iU / (13.0f*iL) + u0;
	float v_ = iV / (13.0f*iL) + v0;

	(*oY) = (y0 / 100.0f) * pow((iL + 16.0f) / 25.0f, 3.0f);
	(*oX) = ((9.0f*u_) / (4.0f*v_)) * (*oY);
	(*oZ) = (*oY) * ((12.0f - 3.0f*u_ - 20.0f*v_) / (4.0f*v_));


	/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

	/*(*oY) = ( iL + 16.0f ) / 116.0f;
	if ( (*oY) * (*oY) * (*oY) > 0.008856f )	(*oY) = (*oY) * (*oY) * (*oY);
	else							(*oY) = ( (*oY) - 16.0 / 116.0 ) / 7.787;

	iU /= ( 13.0 * iL );
	iV /= ( 13.0 * iL );

	iU *= ( 4.0 * x0 ) / ( x0 + ( 15.0 * y0 ) + ( 3.0 * z0 ) );
	iV *= ( 9.0 * y0 ) / ( x0 + ( 15.0 * y0 ) + ( 3.0 * z0 ) );

	(*oY) *= y0;
	(*oX) =  - ( 9.0 * (*oY) * iU ) / ( ( iU - 4.0 ) * iV - iU * iV );
	(*oZ) = ( 9.0 * (*oY) - ( 15.0 * iV * (*oY) ) - ( iV * (*oX) ) ) / ( 3.0 * iV );*/
}

void RGBtoLUV(float iR, float iG, float iB, float *oL, float *oU, float *oV)
{
	float x, y, z;
	RGBtoXYZ(iR, iG, iB, &x, &y, &z);
	XYZtoLUV(x, y, z, oL, oU, oV);
}

void LUVtoRGB(float iL, float iU, float iV, float *oR, float *oG, float *oB)
{
	float x, y, z;
	LUVtoXYZ(iL, iU, iV, &x, &y, &z);
	XYZtoRGB(x, y, z, oR, oG, oB);
}

void RGBtoLAB(float iR, float iG, float iB, float *oL, float *oa, float *ob){
	double r, g, b;
	double x, y, z;
	double l, a, b1;
	const double REF_X = 95.047; // Observer= 2°, Illuminant= D65
	const double REF_Y = 100.000;
	const double REF_Z = 108.883;

	b = iR;
	g = iG;
	r = iB;

	if (r > 0.04045)
	{
		r = (r + 0.055) / 1.055;
		r = pow(r, 2.4);
	}
	else { r = r / 12.92; }

	if (g > 0.04045)
	{
		g = (g + 0.055) / 1.055;
		g = pow(g, 2.4);
	}
	else { g = g / 12.92; }

	if (b > 0.04045)
	{
		b = (b + 0.055) / 1.055;
		b = pow(b, 2.4);
	}
	else { b = b / 12.92; }

	r = r * 100;
	g = g * 100;
	b = b * 100;

	//Observer. = 2°, Illuminant = D65
	x = r * 0.4124 + g * 0.3576 + b * 0.1805;
	y = r * 0.2126 + g * 0.7152 + b * 0.0722;
	z = r * 0.0193 + g * 0.1192 + b * 0.9505;

	x /= REF_X;
	y /= REF_Y;
	z /= REF_Z;

	if (x > 0.008856) { x = pow(x, 0.33333); } // 1/3
	else { x = (7.787 * x) + (0.137931); } //16/116

	if (y > 0.008856) { y = pow(y, 0.33333); }
	else { y = (7.787 * y) + (0.137931); }

	if (z > 0.008856) { z = pow(z, 0.33333); }
	else { z = (7.787 * z) + (0.137931); }

	l = (116.0 * y) - 16.0;
	a = 504.3 * (x - y);
	b1 = 201.7 * (y - z);

	if (l > 100)
		(*oL) = 100;
	else if (l < 0)
		(*oL) = 0;
	else
		(*oL) = (char)((116.0 * y) - 16.0); // l

	if (a > 127)
		(*oa) = 127;
	else if (a < -127)
		(*oa) = -127;
	else
		(*oa) = (char)(504.3 * (x - y)); // a

	if (b > 127)
		(*ob) = 127;
	else if (b < -127)
		(*ob) = -127;
	else
		(*ob) = (char)(201.7 * (y - z));  // b
}

void LABtoRGB(float iL, float ia, float ib, float *oR, float *oG, float *oB){
	const double REF_X = 95.047; // Observer= 2°, Illuminant= D65
	const double REF_Y = 100.000;
	const double REF_Z = 108.883;

	char l, a, b1;
	double x, y, z;
	double r, g, b;

	l = iL;
	a = ia;
	b1 = ib;

	y = (l + 16) / 116.0;
	x = a / 504.3 + y; // 500
	z = y - (b1 / 201.7); // 200

	if (pow(y, 3) > 0.008856) { y = pow(y, 3); }
	else { y = (y - 0.137931) / 7.787; }
	if (pow(x, 3) > 0.008856) { x = pow(x, 3); }
	else { x = (x - 0.137931) / 7.787; }
	if (pow(z, 3) > 0.008856) { z = pow(z, 3); }
	else { z = (z - 0.137931) / 7.787; }

	x = REF_X * x;
	y = REF_Y * y;
	z = REF_Z * z;

	x /= 100.0;
	y /= 100.0;
	z /= 100.0;

	r = x * 3.2406 + y * -1.5372 + z * -0.4986;
	g = x * -0.9689 + y * 1.8758 + z * 0.0415;
	b = x * 0.0557 + y * -0.2040 + z * 1.0570;

	if (r > 0.0031308) { r = 1.055 * pow(r, 0.416667) - 0.055; } //1/2.4
	else { r = 12.92 * r; }
	if (g > 0.0031308) { g = 1.055 * pow(g, 0.416667) - 0.055; }
	else { g = 12.92 * g; }
	if (b > 0.0031308) { b = 1.055 * pow(b, 0.416667) - 0.055; }
	else { b = 12.92 * b; }

	if (r > 1.0)
	{
		(*oB) = 1.0f;
	}
	else if (r < 0.0)
	{
		(*oB) = 0.0f;
	}
	else
		(*oB) = r;

	if (g > 1.0)
	{
		(*oG) = 1.0f;
	}
	else if (g < 0.0)
	{
		(*oG) = 0.0f;
	}
	else
		(*oG) = g;

	if (b > 1.0)
	{
		(*oR) = 1.0f;
	}
	else if (b < 0.0)
	{
		(*oR) = 0.0f;
	}
	else
		(*oR) = b;
}

void RGBtoHSV(float iR, float iG, float iB, float *oH, float *oS, float *oV)
{
	float var_Min = min2f(min2f(iR, iG), iB);	//Min. value of RGB
	float var_Max = max2f(max2f(iR, iG), iB);	//Max. value of RGB

	(*oV) = var_Max;

	if (var_Min == var_Max){
		// This is a gray, no chroma...
		(*oH) = 0.0f;	// HSV results = 0 ÷ 1
		(*oS) = 0.0f;
	}
	else{
		// Chromatic data...
		(*oS) = (var_Max - var_Min) / var_Max;

		// Optimized
		//	delta = var_Max - var_Min
		//	del_R = ( ( ( var_Max - var_R ) / 6.0 ) + ( delta / 2.0 ) ) / delta
		//	      = ( var_Max - var_R ) / ( 6.0 * delta ) + 1.0 / 2.0
		//	del_R - del_G = ( ( var_Max - var_R ) / ( 6.0 * delta ) + 1.0 / 2.0 ) - ( ( var_Max - var_G ) / ( 6.0 * delta ) + 1.0 / 2.0 )
		//	              = ( var_Max - var_R - var_Max + var_G ) / ( 6.0 * delta ) + ( 1.0 / 2.0 ) - ( 1.0 / 2.0 )
		//	              = ( var_G - var_R ) / ( 6.0 * delta)
		//	              = ( var_G - var_R ) / 6.0 / delta

		if (iR == var_Max) (*oH) = (iG - iB) / 6.0f / (var_Max - var_Min);					// = ( del_B - del_G )
		else if (iG == var_Max) (*oH) = (1.0f / 3.0f) + (iB - iR) / 6.0f / (var_Max - var_Min);	// ( 1.0 / 3.0 ) + ( del_R - del_B )
		else if (iB == var_Max) (*oH) = (2.0f / 3.0f) + (iR - iG) / 6.0f / (var_Max - var_Min);	// ( 2.0 / 3.0 ) + ( del_G - del_R )

		if ((*oH) < 0.0)	(*oH) += 1.0;
		if ((*oH) > 1.0)	(*oH) -= 1.0;
	}
}

void HSVtoRGB(float iH, float iS, float iV, float *oR, float *oG, float *oB)
{
	if (iS == 0.0){	//HSV values = 0 ÷ 1
		(*oR) = iV;
		(*oG) = (*oR);
		(*oB) = (*oR);
	}
	else{
		iH *= 6.0f;
		if (iH >= 6.0f)	iH = 0.0f;	// H must be < 1
		int var_h = int(iH);			// Or ... var_i = floor( var_h )

		iH -= float(var_h);

		float var_1 = iV * (1.0f - iS);
		float var_2 = iV * (1.0f - iS * iH);
		float var_3 = iV * (1.0f - iS * (1.0f - iH));
		float var_4 = iV;

		if (var_h == 0)	{ (*oR) = var_4;	(*oG) = var_3;	(*oB) = var_1; }
		else if (var_h == 1) { (*oR) = var_2; (*oG) = var_4; (*oB) = var_1; }
		else if (var_h == 2) { (*oR) = var_1; (*oG) = var_4; (*oB) = var_3; }
		else if (var_h == 3) { (*oR) = var_1; (*oG) = var_2; (*oB) = var_4; }
		else if (var_h == 4) { (*oR) = var_3; (*oG) = var_1; (*oB) = var_4; }
		else                   { (*oR) = var_4; (*oG) = var_1; (*oB) = var_2; }
	}
}

void RGBtoHSV2(float r, float g, float b, float& h, float& s, float& v)
{
	float max, min;

	max = (r>g) ? r : g;
	max = (max>b) ? max : b;

	min = (r<g) ? r : g;
	min = (min<b) ? min : b;

	v = max;                                 // 명도(V) = max(r,g,b)
	s = (max != 0.0) ? (max - min) / max : 0.0;  // 채도(S)을 계산, S=0이면 R=G=B=0

	if (s == 0.0)
	{
		h = -1; // undefined
	}
	else {                                    // 채도(S)는 != 0
		float delta = max - min;              // 색상(H)를 구한다.

		if (r == max)
			h = (g - b) / delta;              // 색상이 Yello와 Magenta사이 
		else if (g == max)
			h = 2.0 + (b - r) / delta;        // 색상이 Cyan와 Yello사이 
		else if (b == max)
			h = 4.0 + (r - g) / delta;        // 색상이 Magenta와 Cyan사이
		h *= 60.0;

		if (h < 0.0)                           // 색상값을 각도로 바꾼다.
			h += 360.0;
	}
}

void HSVtoRGB2(float h, float s, float v, float& r, float& g, float& b)
{
	if (s == 0.0)                         // 컬러값은 흑백명암인 경우 색상 값은 없다.
	{
		if (h == -1) // undefined
			r = g = b = v;
		else
			r = g = b = -1; // undefined
	}
	else {                              // S != 0 이므로 색상(H)이 있다.
		float f, p, q, t;
		int i;

		if (h == 360.0)
			h = 0.0;

		h /= 60.0;                      // H 값은 [0,360)사이 값
		i = (int)h;                     // <=H 인 가장 큰 정수값
		f = h - i;                      // F 는 H 의 실수 부분
		p = v * (1.0 - s);
		q = v * (1.0 - (s * f));
		t = v * (1.0 - (s * (1.0 - f)));

		switch (i) {
		case 0:
			r = v;
			g = t;
			b = p;
			break;
		case 1:
			r = q;
			g = v;
			b = p;
			break;
		case 2:
			r = p;
			g = v;
			b = t;
			break;
		case 3:
			r = p;
			g = q;
			b = v;
			break;
		case 4:
			r = t;
			g = p;
			b = v;
			break;
		case 5:
			r = v;
			g = p;
			b = q;
			break;
		}
	}
}

void RGBtoCMY(float iR, float iG, float iB, float *oC, float *oM, float *oY)
{
	(*oC) = 1.0f - iR;
	(*oM) = 1.0f - iG;
	(*oY) = 1.0f - iB;
}

void CMYtoRGB(float iC, float iM, float iY, float *oR, float *oG, float *oB)
{
	(*oR) = 1.0 - iC;
	(*oG) = 1.0 - iM;
	(*oB) = 1.0 - iY;
}

void CMYtoCMYK(float iC, float iM, float iY, float *oC, float *oM, float *oY, float *oK)
{
	(*oK) = min2f(min2f(iC, iM), iY);

	if ((*oK) >= 1.0f){		//Black
		(*oC) = 0.0f;
		(*oM) = 0.0f;
		(*oY) = 0.0f;
	}
	else{
		float var_k = 1.0f - (*oK);

		(*oC) -= (*oK);
		(*oM) -= (*oK);
		(*oY) -= (*oK);

		(*oC) /= var_k;
		(*oM) /= var_k;
		(*oY) /= var_k;
	}
}

void CMYKtoCMY(float iC, float iM, float iY, float iK, float *oC, float *oM, float *oY)
{
	float var_k = 1.0f - iK;
	(*oC) = (iC*var_k + iK);
	(*oM) = (iM * var_k + iK);
	(*oY) = (iY * var_k + iK);
}

//void conv_ssd()	//converting simple sample data
//{
//	cout << "RGB: " << d[X] << ' ' << d[Y] << ' ' << d[Z] << endl;
////	RGBtoXYZ(d[X],d[Y],d[Z],&d[X],&d[Y],&d[Z]);		//1-1. RGB -> XYZ
//	XYZtoLUV(d[X],d[Y],d[Z],&d[X],&d[Y],&d[Z]);		//1-2. XYZ -> LUV
//
//	LUVtoXYZ(d[X],d[Y],d[Z],&d[X],&d[Y],&d[Z]);		//2-1. LUV -> XYZ
////	XYZtoRGB(d[X],d[Y],d[Z],&d[X],&d[Y],&d[Z]);		//2-2. XYZ -> RGB
//	cout << "RGB: " << d[X] << ' ' << d[Y] << ' ' << d[Z] << endl;
//}

void conv_RGBtoXYZ(V3DF** buf, int width, int height)		//RGB -> XYZ
{
	int i, j;

	for (i = 0; i<width; i++){
		for (j = 0; j<height; j++){
			RGBtoXYZ(buf[i][j][0], buf[i][j][1], buf[i][j][2], &buf[i][j][0], &buf[i][j][1], &buf[i][j][2]);
		}
	}
}

void conv_XYZtoRGB(V3DF** buf, int width, int height)		//XYZ -> RGB
{
	int i, j;

	for (i = 0; i<width; i++){
		for (j = 0; j<height; j++){
			XYZtoRGB(buf[i][j][0], buf[i][j][1], buf[i][j][2], &buf[i][j][0], &buf[i][j][1], &buf[i][j][2]);
		}
	}
}

void conv_XYZtoLUV(V3DF** buf, int width, int height)		//XYZ -> LUV
{
	int i, j;

	for (i = 0; i<width; i++){
		for (j = 0; j<height; j++){
			XYZtoLUV(buf[i][j][0], buf[i][j][1], buf[i][j][2], &buf[i][j][0], &buf[i][j][1], &buf[i][j][2]);
		}
	}
}

void conv_LUVtoXYZ(V3DF** buf, int width, int height)		//LUV -> XYZ
{
	int i, j;

	for (i = 0; i<width; i++){
		for (j = 0; j<height; j++){
			LUVtoXYZ(buf[i][j][0], buf[i][j][1], buf[i][j][2], &buf[i][j][0], &buf[i][j][1], &buf[i][j][2]);
		}
	}
}

void conv_RGBtoLUV(V3DF** buf, int width, int height)		//RGB -> LUV
{
	conv_RGBtoXYZ(buf, width, height);	//RGB->XYZ
	conv_XYZtoLUV(buf, width, height);	//XYZ->LUV
}

void conv_LUVtoRGB(V3DF** buf, int width, int height)		//LUV -> RGB
{
	conv_LUVtoXYZ(buf, width, height);	//LUV->XYZ
	conv_XYZtoRGB(buf, width, height);	//XYZ->RGB
}

void conv_RGBtoLAB(V3DF* buf, int width, int height)		//RGB -> LAB
{
	int i, j;

	for (i = 0; i<width; i++){
		for (j = 0; j<height; j++){
			RGBtoLAB(buf[i + j*width][0], buf[i + j*width][1], buf[i + j*width][2], &buf[i + j*width][0], &buf[i + j*width][1], &buf[i + j*width][2]);
		}
	}
}

void conv_RGBtoLAB(V3DF** buf, int width, int height)		//RGB -> LAB
{
	int i, j;

	for (i = 0; i<width; i++){
		for (j = 0; j<height; j++){
			RGBtoLAB(buf[i][j][0], buf[i][j][1], buf[i][j][2], &buf[i][j][0], &buf[i][j][1], &buf[i][j][2]);
		}
	}
}

void conv_LABtoRGB(V3DF** buf, int width, int height)		//LAB -> RGB
{
	int i, j;

	for (i = 0; i<width; i++){
		for (j = 0; j<height; j++){
			LABtoRGB(buf[i][j][0], buf[i][j][1], buf[i][j][2], &buf[i][j][0], &buf[i][j][1], &buf[i][j][2]);
		}
	}
}

void conv_RGBtoHSV(V3DF** buf, int width, int height)		//RGB -> HSV
{
	int i, j;
	for (i = 0; i<width; i++)
	for (j = 0; j<height; j++)
		RGBtoHSV(buf[i][j][0], buf[i][j][1], buf[i][j][2], &buf[i][j][0], &buf[i][j][1], &buf[i][j][2]);
}

void conv_HSVtoRGB(V3DF** buf, int width, int height)		//HSV -> RGB
{
	int i, j;
	for (i = 0; i<width; i++)
	for (j = 0; j<height; j++)
		HSVtoRGB(buf[i][j][0], buf[i][j][1], buf[i][j][2], &buf[i][j][0], &buf[i][j][1], &buf[i][j][2]);
}

void conv_RGBtoCMY(V3DF** buf, int width, int height)		//RGB -> CMY
{
	int i, j;
	for (i = 0; i<width; i++)
	for (j = 0; j<height; j++)
		RGBtoCMY(buf[i][j][0], buf[i][j][1], buf[i][j][2], &buf[i][j][0], &buf[i][j][1], &buf[i][j][2]);
}

void conv_CMYtoRGB(V3DF** buf, int width, int height)		//CMY -> RGB
{
	int i, j;
	for (i = 0; i<width; i++)
	for (j = 0; j<height; j++)
		CMYtoRGB(buf[i][j][0], buf[i][j][1], buf[i][j][2], &buf[i][j][0], &buf[i][j][1], &buf[i][j][2]);
}

void conv_RGBtoHSV(V3DF* buf, int w, int h)		//RGB -> HSV
{
	int i;
	for (i = 0; i<w*h; i++)
		RGBtoHSV(buf[i][0], buf[i][1], buf[i][2], &buf[i][0], &buf[i][1], &buf[i][2]);
}

void conv_HSVtoRGB(V3DF* buf, int w, int h)		//HSV -> RGB
{
	int i;
	for (i = 0; i<w*h; i++)
		HSVtoRGB(buf[i][0], buf[i][1], buf[i][2], &buf[i][0], &buf[i][1], &buf[i][2]);
}
//void conv_RGBtoCMYK(V3DF** ibuf, V4DF** obuf, int width, int height)	//RGB -> CMYK
//{
//	V3DF** temp = new V3DF*[width];
//	for (int i=0; i<width; i++)
//		temp[i] = new V3DF[height];
//
//	conv_RGBtoCMY(ibuf,width,height);
//
//	for (int i=0; i<width; i++)
//		delete []temp[i];
//	delete []temp;
//}

void conv_CMYtoCMYK(V3DF** ibuf, V4DF** obuf, int width, int height)	//CMY -> CMYK
{
	int i, j;
	for (i = 0; i<width; i++)
	for (j = 0; j<height; j++)
		CMYtoCMYK(ibuf[i][j][0], ibuf[i][j][1], ibuf[i][j][2], &obuf[i][j][0], &obuf[i][j][1], &obuf[i][j][2], &obuf[i][j][3]);
}

void conv_CMYKtoCMY(V4DF** ibuf, V3DF** obuf, int width, int height)	//CMYK -> CMY
{
	int i, j;
	for (i = 0; i<width; i++)
	for (j = 0; j<height; j++)
		CMYKtoCMY(ibuf[i][j][0], ibuf[i][j][1], ibuf[i][j][2], ibuf[i][j][3], &obuf[i][j][0], &obuf[i][j][1], &obuf[i][j][2]);
}