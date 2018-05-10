#pragma once

#include <opencv/cv.h>
#include <opencv/highgui.h>

class CCamCalib
{
public:
	void LoadCalibParams (CvSize &image_size);
	void Undistort(IplImage *src, IplImage *dst);
	
	CvMat* _intrinsic_matrix;
	CvMat* _distortion_coeffs;

	IplImage* _mapx;
	IplImage* _mapy; 
};