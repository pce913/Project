/*
<<convert color space>>
conv_clr.h
작성자: 상명대학교 디지털미디어 전공 200611189 양희경
작성일: 2009. 5.

참고자료
- W. K. Pratt, Digital Image Processing. Wiley, second edition, 1991.
- (전달인자) 인천대 비전 랩
// Color Model Converting Functions
// (일부)made by tinywolf at gamil.com

*/

//----------------------
#ifndef _CONV_CLR_H_
#define _CONV_CLR_H_
//----------------------

#include "main.h"
//#include "mtoolkits.h"

//typedef float V3DF[3];
//typedef float V4DF[4];
/*	[range]
RGB: 0~1
XYZ: 0~1
LUV: L(0~100), U(-100~+100), V(-100~+100)
Lab: L(0~100), a(-100~+100)?, b(-100~+100)?	a,b는 independent 함.
HSV: 0~1(단,보통 H는 0~360이라 불리움)
*/

//사용법: RGBtoXYZ(ir, ig, ib, &buf[i][j][X], &buf[i][j][Y], &buf[i][j][X]);
void RGBtoXYZ(float iR, float iG, float iB, float *oX, float *oY, float *oZ);	//1.
void XYZtoRGB(float iX, float iY, float iZ, float *oR, float *oG, float *oB);	//2.
void XYZtoLUV(float iX, float iY, float iZ, float *oL, float *oU, float *oV);	//L 범위: 0 ~100
void LUVtoXYZ(float iL, float iU, float iV, float *oX, float *oY, float *oZ);
void RGBtoLUV(float iR, float iG, float iB, float *oL, float *oU, float *oV);
void LUVtoRGB(float iL, float iU, float iV, float *oR, float *oG, float *oB);

void RGBtoLAB(float iR, float iG, float iB, float *oL, float *oa, float *ob);
void LABtoRGB(float iL, float ia, float ib, float *oR, float *oG, float *oB);

void RGBtoHSV(float iR, float iG, float iB, float *oH, float *oS, float *oV);
void HSVtoRGB(float iH, float iS, float iV, float *oR, float *oG, float *oB);

void RGBtoHSV2(float r, float g, float b, float& h, float& s, float& v);
void HSVtoRGB2(float h, float s, float v, float& r, float& g, float& b);

void RGBtoCMY(float iR, float iG, float iB, float *oC, float *oM, float *oY);
void CMYtoRGB(float iC, float iM, float iY, float *oR, float *oG, float *oB);
void CMYtoCMYK(float iC, float iM, float iY, float *oC, float *oM, float *oY, float *oK);
void CMYKtoCMY(float iC, float iM, float iY, float iK, float *oC, float *oM, float *oY);

//convert color
void conv_RGBtoXYZ(V3DF** buf, int width, int height);		//RGB -> XYZ
void conv_XYZtoRGB(V3DF** buf, int width, int height);		//XYZ -> RGB
void conv_XYZtoLUV(V3DF** buf, int width, int height);		//XYZ -> LUV
void conv_LUVtoXYZ(V3DF** buf, int width, int height);		//LUV -> XYZ
void conv_RGBtoLUV(V3DF** buf, int width, int height);		//RGB -> LUV
void conv_LUVtoRGB(V3DF** buf, int width, int height);		//LUV -> RGB
void conv_RGBtoLAB(V3DF* buf, int width, int height);		//RGB -> LAB
void conv_RGBtoLAB(V3DF** buf, int width, int height);		//RGB -> LAB
void conv_LABtoRGB(V3DF** buf, int width, int height);		//LAB -> RGB
void conv_RGBtoHSV(V3DF** buf, int width, int height);		//RGB -> HSV
void conv_HSVtoRGB(V3DF** buf, int width, int height);		//HSV -> RGB
void conv_RGBtoCMY(V3DF** buf, int width, int height);	//RGB -> CMY
void conv_CMYtoRGB(V3DF** buf, int width, int height);	//CMY -> RGB

void conv_RGBtoHSV(V3DF* buf, int width, int height);		//RGB -> HSV
void conv_HSVtoRGB(V3DF* buf, int width, int height);		//HSV -> RGB

//void conv_RGBtoCMYK(V3DF** ibuf, V4DF** obuf, int width, int height);	//RGB -> CMYK
//CMYK -> RGB

void conv_CMYtoCMYK(V3DF** ibuf, V4DF** obuf, int width, int height);	//CMY -> CMYK
void conv_CMYKtoCMY(V4DF** ibuf, V3DF** obuf, int width, int height);	//CMYK -> CMY

//----------------------
#endif 
//----------------------