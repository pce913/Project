#include "stdafx.h"
#include "CamCalib.h"

void CCamCalib::LoadCalibParams (CvSize &image_size)
{
	// ���Ϸ� ����� ������İ� �ְ� ����� �ҷ�����
	_intrinsic_matrix = (CvMat *)cvLoad("Intrinsics.xml");
	_distortion_coeffs = (CvMat *)cvLoad("Distortion.xml");

	if (_intrinsic_matrix && _distortion_coeffs) {
		// �ְ� ���Ÿ� ���� ������ ����
		_mapx = cvCreateImage( image_size, IPL_DEPTH_32F, 1 );
		_mapy = cvCreateImage( image_size, IPL_DEPTH_32F, 1 );

		// �ְ� ���Ÿ� ���� ������ ����
		cvInitUndistortMap (_intrinsic_matrix, _distortion_coeffs, _mapx, _mapy);
	}
}

void CCamCalib::Undistort(IplImage *src, IplImage *dst)
{
	// ī�޶� �Է¿���(src)���� �ְ��� ������ ����(dst)�� �����.
	cvRemap(src, dst, _mapx, _mapy );			// Undistort image
}
