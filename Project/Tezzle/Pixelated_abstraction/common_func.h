//----------------------
#ifndef _COMMON_FUNC_H_
#define _COMMON_FUNC_H_
//----------------------

#include "main.h"
#include "vmg_math.h"

void Ang2Vector(float iang, V3DF ovnt);
void GaussianFilter(float **InImg, float **OutImg, int width, int height);
void Vector2Ang(V3DF ivnt, float *oang);
/*	The angle ( degree ) between v1 and v2	*/
//	0 < angle < 180
float angle_d(V3DF v1, V3DF v2);
void init_buf(V3DF **OutImg, V3DF **InImg, int width, int height);
void GetValAtPoint(float **ival, int w, int h, float px, float py, float *oval);
void BuildGaussianMask(int n/*È¦¼ö*/, float s, float *m);
void ScalarBuf(float *OutBuf, float scalar, int length);
void DifferenceBuf(float *OutBuf, float *InBuf1, float *InBuf2, int length);

int GetSimpleBlkDeg(float deg);
//----------------------
#endif 
//----------------------