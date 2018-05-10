#include "stdafx.h"
#include "common_func.h"

#define EXPF 2.718281828f

void Ang2Vector(float iang, V3DF ovnt){
	// ang --> vector
	vector3(ovnt, 1.0f, 0.0f, 0.0f);
	rotate_vtx_z(ovnt, iang);
	vnorm(ovnt);
}

void GaussianFilter(float **InImg, float **OutImg, int width, int height)
{
	int i, j;
	int row, col;
	int rowOffset;			// Row offset from the current pixel
	int colOffset;			// Col offset from the current pixel
	int rowTotal = 0;		// Row position of offset pixel
	int colTotal = 0;		// Col position of offset pixel
	float newPixel;
	float gaussianMask[5][5];		// Gaussian mask
	float **img_temp = new float*[height];
	for (i = 0; i<height; i++)
		img_temp[i] = new float[width];

	/* Declare Gaussian mask */
	gaussianMask[0][0] = 2.0f;		gaussianMask[0][1] = 4.0f;		gaussianMask[0][2] = 5.0f;		gaussianMask[0][3] = 4.0f;		gaussianMask[0][4] = 2.0f;
	gaussianMask[1][0] = 4.0f;		gaussianMask[1][1] = 9.0f;		gaussianMask[1][2] = 12.0f;		gaussianMask[1][3] = 9.0f;		gaussianMask[1][4] = 4.0f;
	gaussianMask[2][0] = 5.0f;		gaussianMask[2][1] = 12.0f;		gaussianMask[2][2] = 15.0f;		gaussianMask[2][3] = 12.0f;		gaussianMask[2][4] = 2.0f;
	gaussianMask[3][0] = 4.0f;		gaussianMask[3][1] = 9.0f;		gaussianMask[3][2] = 12.0f;		gaussianMask[3][3] = 9.0f;		gaussianMask[3][4] = 4.0f;
	gaussianMask[4][0] = 2.0f;		gaussianMask[4][1] = 4.0f;		gaussianMask[4][2] = 5.0f;		gaussianMask[4][3] = 4.0f;		gaussianMask[4][4] = 2.0f;

	/* Gaussian Blur */
	//for(row = 2; row < height-2; row++){
	//	for (col = 2; col < width-2; col++){
	//		newPixel = 0.0f;
	//		for (rowOffset = -2; rowOffset <= 2; rowOffset++){
	//			for (colOffset = -2; colOffset <= 2; colOffset++){
	//				rowTotal = row + rowOffset;
	//				colTotal = col + colOffset;
	//				//iOffset = (unsigned long)(rowTotal*3*W + colTotal*3);	//BMP를 1차원 배열로 저장했을 경우 쓴다.
	//				newPixel += (InImg[colTotal][rowTotal ])*gaussianMask[2 + rowOffset][2 + colOffset];
	//			}
	//		}
	//		img_temp[row][col] = (newPixel/159.0f);
	//	}
	//}
	for (row = 0; row < height; row++){
		for (col = 0; col < width; col++){
			newPixel = 0.0f;
			for (rowOffset = -2; rowOffset <= 2; rowOffset++){
				for (colOffset = -2; colOffset <= 2; colOffset++){
					rowTotal = row + rowOffset;
					colTotal = col + colOffset;
					//경계처리(대칭)
					if (rowTotal<0) rowTotal *= (-1.0f);
					else if (rowTotal >= height)	rowTotal = height - (rowTotal - (height - 1));
					if (colTotal<0) colTotal *= (-1.0f);
					else if (colTotal >= width)	colTotal = width - (colTotal - (width - 1));
					//iOffset = (unsigned long)(rowTotal*3*W + colTotal*3);	//BMP를 1차원 배열로 저장했을 경우 쓴다.
					newPixel += (InImg[colTotal][rowTotal])*gaussianMask[2 + rowOffset][2 + colOffset];
				}
			}
			img_temp[row][col] = (newPixel / 159.0f);
		}
	}

	for (i = 0; i<width; i++)
	for (j = 0; j<height; j++)
		OutImg[i][j] = img_temp[j][i];

	for (i = 0; i<height; i++)
		delete[]img_temp[i];
	delete[]img_temp;
}

void Vector2Ang(V3DF ivnt, float *oang){
	V3DF zero_degree = { 1.0f, 0.0f, 0.0f };
	vnorm(ivnt);
	if ((ivnt[0] <= 0 && ivnt[1] <= 0) || (ivnt[0] >= 0 && ivnt[1] <= 0))
		vscale(ivnt, -1.0f);
	(*oang) = angle_d(zero_degree, ivnt);
}
/*	The angle ( degree ) between v1 and v2	*/
//	0 < angle < 180
float angle_d(V3DF v1, V3DF v2)
{
	int i;
	float temp, temp2;

	for (i = 0, temp = 0.0f; i < 3; i++) {
		temp += v1[i] * v2[i];
	}
	temp2 = (float)sqrt(v1[0] * v1[0] + v1[1] * v1[1] + v1[2] * v1[2])*(float)sqrt(v2[0] * v2[0] + v2[1] * v2[1] + v2[2] * v2[2]);
	if (temp2 == 0.0f)
		return 0.0f;
	temp = temp / temp2;

	temp = (temp <= 1.0f) ? temp : 1.0f;

	if (temp >= 0.999999999f)
		return 0.0f;
	if (temp <= -0.999999999f)
		return 180.0f;

	return (float)acos(temp)*(180.0f / PIF);
}

void init_buf(V3DF **OutImg, V3DF **InImg, int width, int height)
{
	int i, j;
	//OutImg 초기화
	for (i = 0; i < width; i++){
		for (j = 0; j < height; j++){
			vcopy(OutImg[i][j], InImg[i][j]);
		}
	}
}

void GetValAtPoint(float **ival, int w, int h, float px, float py, float *oval)
{
	int ulx, uly, lrx, lry;		//	upper-left (x, y), lower-right (x, y)
	float ivalA, ivalB, ivalC, ivalD;	//	etf at A,B,C,D
	float e1, e2, t1, t2;

	if (px + 1 >= w || py + 1 >= h){
		*oval = 0.0f;
		return;
	}

	ulx = (int)(px);
	uly = (int)(py + 1);
	lrx = (int)(px + 1);
	lry = (int)(py);
	ivalA = ival[ulx][lry];
	ivalB = ival[lrx][lry];
	ivalC = ival[ulx][uly];
	ivalD = ival[lrx][uly];

	//distA: A~(px,py) 거리
	//eA: etf at A
	//1. distB*etfA + distA*etfB
	t1 = ivalA;		t2 = ivalB;
	t1 *= (lrx - px);	t2 *= (px - ulx);
	e1 = t1 + t2;
	//2. distD*etfC + distC*etfD
	t1 = ivalC;		t2 = ivalD;
	t1 *= (lrx - px);	t2 *= (px - ulx);
	e2 = t1 + t2;
	//3. distC*1 + distA*2
	t1 = e1;		t2 = e2;
	t1 *= (uly - py);	t2 *= (py - lry);
	*oval = t1 + t2;
}

void BuildGaussianMask(int n/*홀수*/, float s, float *m)	//mask의 합은 1
{
	if (n % 2 == 0){
		cout << "Gaussian mask 생성 오류; 마스크 크기는 홀수여야 합니다.\n";
		exit(0);
	}
	int i;
	float div = pow(2.0f*PIF*s*s, 0.5f);
	int ct = n / 2;	//center
	float sum = 0.0f;
	float x2;

	for (i = 0; i<n; i++){
		x2 = (i - ct)*(i - ct);
		m[i] = pow(EXPF, -x2 / (2.0f*s*s)) / div;
		sum += m[i];
	}

	//float sum2 = 0.0f;
	for (i = 0; i<n; i++){
		m[i] /= sum;

		//sum2 += m[i];
	}
	//cout << endl << "Gaussian Size: " << sum2 << endl;
}

void ScalarBuf(float *OutBuf, float scalar, int length)
{
	for (int i = 0; i<length; i++)
		OutBuf[i] = OutBuf[i] * scalar;
}

void DifferenceBuf(float *OutBuf, float *InBuf1, float *InBuf2, int length)
{
	float sum = 0.0f;
	for (int i = 0; i<length; i++){
		OutBuf[i] = InBuf1[i] - InBuf2[i];
		sum += OutBuf[i];
	}
	//	cout << endl << "DoG Size: " << sum << endl;
}

int GetSimpleBlkDeg(float deg)	//GetDir(12)로 했을 시, 
{
	if (deg <= 15)
		return 0;
	if (deg > 15 && deg <= 37.5)
		return 30;
	if (deg > 37.5 && deg <= 52.5)
		return 45;
	if (deg > 52.2 && deg <= 75)
		return 60;
	if (deg > 75 && deg <= 105)
		return 90;
	if (deg > 105 && deg <= 122.5)
		return 120;
	if (deg > 122.5 && deg <= 142.5)
		return 135;
	if (deg > 142.5 && deg <= 165)
		return 150;
	if (deg > 165) // 180deg ==> 0deg
		return 0;
}