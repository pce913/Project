//----------------------
#ifndef _IMAGE_H_
#define _IMAGE_H_
//----------------------

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <math.h>

#include "vmg_math.h"
#include "BITMAP2.h"


#pragma warning (disable:4996)

#define RED_WEIGHT 0.299
#define GREEN_WEIGHT 0.587
#define BLUE_WEIGHT 0.114

class Image {
public:
	int MAX_X, MAX_Y, Zsp, Zep;
	V3DF **cim;	//color image(origianl image)
	V3DF **test;
	float **im;	//gray image

	int range;
	float MAX_Height;
	float ZstepSize;

	float ***VD;

	Image();
	~Image();

	bool loadBitmap2(char *fn);
	void draw();
	void graydraw();

};


#endif