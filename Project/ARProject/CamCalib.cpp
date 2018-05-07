#include "stdafx.h"
#include "CamCalib.h"

void CCamCalib::LoadCalibParams (CvSize &image_size)
{
	// 파일로 저장된 내부행렬과 왜곡 계수를 불러오기
	_intrinsic_matrix = (CvMat *)cvLoad("Intrinsics.xml");
	_distortion_coeffs = (CvMat *)cvLoad("Distortion.xml");

	if (_intrinsic_matrix && _distortion_coeffs) {
		// 왜곡 제거를 위한 지도를 생성
		_mapx = cvCreateImage( image_size, IPL_DEPTH_32F, 1 );
		_mapy = cvCreateImage( image_size, IPL_DEPTH_32F, 1 );

		// 왜곡 제거를 위한 지도를 구성
		cvInitUndistortMap (_intrinsic_matrix, _distortion_coeffs, _mapx, _mapy);
	}
}

void CCamCalib::Undistort(IplImage *src, IplImage *dst)
{
	// 카메라 입력영상(src)에서 왜곡을 제거한 영상(dst)을 만든다.
	cvRemap(src, dst, _mapx, _mapy );			// Undistort image
}
