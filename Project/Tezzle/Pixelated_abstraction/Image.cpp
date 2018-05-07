#include "stdafx.h"
#include "Image.h"

extern int Width;
extern int Height;
extern void save_bitmap_file(char *fn, int W, int H, GLubyte *rpxls);

Image::Image()
{
	cim = NULL;
	im = NULL;
}

Image::~Image()
{
	if (cim){
		for (int i = 0; i < MAX_X; i++)
			delete[] cim[i];
		delete[] cim;
	}
	if (im){
		for (int i = 0; i < MAX_X; i++)
			delete[] im[i];
		delete[]im;
	}
}

bool Image::loadBitmap2(char *fn)
{
	V3DUC temp;
	Bitmap *image;
	int i, j;
	int idx;

	FILE *fp = fopen(fn, "r+b");
	if (fp == NULL)
		return false;

	image = new Bitmap();

	if (image == NULL) {
		return false;
	}

	if (image->loadBMP(fn)) {

		MAX_X = image->width;
		MAX_Y = image->height;


		/////////원래 크기로 출력할 때//////////////////////////////////


		//output에 palette추가x
		Width = MAX_X;
		Height = MAX_Y;

		//output에 palette추가o
		//Width = MAX_X+200;
		//Height = MAX_Y;
		///////////////////////////////////////////////////////////////



		/////////작은 크기로 출력할 때//////////////////////////////////


		//////output에 palette추가x

		//if (MAX_X < MAX_Y) {
		//	//output_h = wh;
		//	cin >> Height;
		//	Width = (MAX_X * Height) / MAX_Y;
		//}
		//else{
		//	//output_w = wh;
		//	cin >> Width;
		//	Height = (MAX_Y * Width) / MAX_X;
		//}
		//////output에 palette추가o
		//////Width = MAX_X+200;
		//////Height = MAX_Y;
		///////////////////////////////////////////////////////////////


		if (cim == NULL && im == NULL){
			cim = (V3DF **)calloc(MAX_X, sizeof(V3DF*));
			im = (float **)calloc(MAX_X, sizeof(float*));
			for (int i = 0; i < MAX_X; i++) {
				cim[i] = (V3DF*)calloc(MAX_Y, sizeof(V3DF));
				im[i] = (float*)calloc(MAX_Y, sizeof(float));
			}
		}


		for (i = 0; i < MAX_X; i++) {
			for (j = 0; j < MAX_Y; j++) {
				idx = 3 * (j * MAX_X + i);
				temp[0] = image->data[idx];
				temp[1] = image->data[idx + 1];
				temp[2] = image->data[idx + 2];
				vector3(cim[i][j], (float)temp[0] / 255.0f, (float)temp[1] / 255.0f, (float)temp[2] / 255.0f);
				im[i][j] = cim[i][j][0] * RED_WEIGHT + cim[i][j][1] * GREEN_WEIGHT + cim[i][j][2] * BLUE_WEIGHT;
			}
		}
	}
	else {
		return false;
	}

	return true;

}

void Image::draw()
{
	int i, j;

	for (i = 0; i < MAX_X; i++) {
		for (j = 0; j < MAX_Y; j++) {
			glColor3f(cim[i][j][0], cim[i][j][1], cim[i][j][2]);
			glRecti(i, j, i + 1, j + 1);
		}
	}
}

void Image::graydraw()
{
	int i, j;

	for (i = 0; i < MAX_X; i++) {
		for (j = 0; j < MAX_Y; j++) {
			glColor3f(im[i][j], im[i][j], im[i][j]);
			glRecti(i, j, i + 1, j + 1);
		}
	}
}

void FLOATtoBMP2(char *fn, int Width, int Height, float *InImg)
{
	int k;
	int m, n;
	GLubyte* Bits = new GLubyte[Width*Height * 3];
	memset(Bits, 0, Width*Height * 3);
	for (k = 0; k<Width*Height * 3; k = k + 3){
		m = (k / 3) % Width;
		n = k / (Width * 3);
		Bits[k] = (GLubyte)(InImg[k / 3] * 255);
		Bits[k + 1] = (GLubyte)(InImg[k / 3] * 255);
		Bits[k + 2] = (GLubyte)(InImg[k / 3] * 255);
	}

	save_bitmap_file(fn, Width, Height, Bits);
	delete[]Bits;
}


