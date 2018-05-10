#include "stdafx.h"
#include "Timer.h"
#include "MarkerDetection.h"

CMarkerDetection::CMarkerDetection (float marker_width, float marker_height)
: _marker_width(marker_width), _marker_height(marker_height)
{
	_calib.LoadCalibParams (cvSize(640, 480));
}

CMarkerDetection::~CMarkerDetection(){}


void CMarkerDetection::MarkerRecog(IplImage *src, IplImage *dst)
{
	IplImage *img_gray = cvCreateImage (cvGetSize(src), IPL_DEPTH_8U, 1);
	IplImage *img_bin = cvCreateImage (cvGetSize(img_gray), IPL_DEPTH_8U, 1);

	// �Է��̹����� gray �̹����� �ٲ۴�.
	cvCvtColor(src, img_gray, CV_RGB2GRAY);

	// gray �̹����� �����Ͽ� threshold���� �������� binary �̹����� �����.
	cvCopyImage (img_gray, img_bin);
	cvAdaptiveThreshold(img_bin,  img_bin, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 31, 15);

	
	// ����� ã�� ������ �޸� ���� �Ҵ�
	CvMemStorage *storage = cvCreateMemStorage(0);
	CvSeq *contours = NULL;

	int noContour = cvFindContours (img_bin, storage, &contours, sizeof(CvContour), CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

	if (0 < noContour) {
		CvSeq *approxContours = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, 1., 1);
		_markers.clear ();
		FindMarkerInContour (approxContours, storage, 0);
		GetMarkerCode (img_gray, dst);

		vector<sMarkerInfo> markers_tmp;
		for (unsigned int i=0; i<_markers.size(); i++) {
			if (0 <= _markers[i].ID) {	
				markers_tmp.push_back (_markers[i]);
			}
		}
		_markers.swap (markers_tmp);

	}
	cvReleaseMemStorage (&storage);
	cvReleaseImage(&img_bin);
	cvReleaseImage(&img_gray);
}

inline double Distance (CvPoint &p1, CvPoint &p2){
	double dx = p1.x - p2.x;
	double dy = p1.y - p2.y;
	return sqrt (dx*dx + dy*dy);
}

bool CMarkerDetection::CheckRectCenter(CvSeq *seq) 
{
	CvPoint corner[4] = {
		*(CvPoint *)cvGetSeqElem(seq, 0),
		*(CvPoint *)cvGetSeqElem(seq, 1),
		*(CvPoint *)cvGetSeqElem(seq, 2),
		*(CvPoint *)cvGetSeqElem(seq, 3),
	};

	// �� �簢���� �� �밢�� ������ �簢�� �߾ӿ� ������ �˻��Ѵ�.
	// ���⼭�� �� ���� l1, l2�� �������� t�� u ���� ����ϴ� ���̴�.
	// l1 = (a1,b1) + t*(x1,y1)
	// l2 = (a2,b2) + u*(x2,y2)

	double a1 = corner[0].x;
	double b1 = corner[0].y;
	double x1 = corner[2].x - corner[0].x;
	double y1 = corner[2].y - corner[0].y;

	double a2 = corner[1].x;
	double b2 = corner[1].y;
	double x2 = corner[3].x - corner[1].x;
	double y2 = corner[3].y - corner[1].y;

	CvMat *A = cvCreateMat (2, 2, CV_64FC1);
	CvMat *B = cvCreateMat (2, 1, CV_64FC1);
	CvMat *Ainv = cvCreateMat(2, 2, CV_64FC1);
	CvMat *x = cvCreateMat(2, 1, CV_64FC1);

	cvmSet (A, 0, 0,  2*(x1*x1 + y1*y1));
	cvmSet (A, 0, 1, -2*(x1*x2 + y1*y2));
	cvmSet (A, 1, 0, -2*(x1*x2 + y1*y2));
	cvmSet (A, 1, 1,  2*(x2*x2 + y2*y2));

	cvmSet (B, 0, 0,  2*(x1*(a2 - a1) + y1*(b2 - b1)));
	cvmSet (B, 1, 0, -2*(x2*(a2 - a1) + y2*(b2 - b1)));

	cvInvert (A, Ainv);
	cvMatMul (Ainv, B, x);

	double x00 = cvmGet (x, 0, 0);
	double x10 = cvmGet (x, 1, 0);

	cvReleaseMat (&A);
	cvReleaseMat (&B);
	cvReleaseMat (&Ainv);
	cvReleaseMat (&x);

	const double l_th = 0.15;
	if (fabs(x00 - 0.5) < l_th && fabs(x10 - 0.5) < l_th) { // ����
		return true;
	}
	else return false;
}

void CMarkerDetection::FindMarkerInContour (CvSeq *contours, CvMemStorage *storage, int level)
{
	for (CvSeq *s = contours; s; s = s->h_next){
		// ����� �����ϴ� ���� ���� 4�� �̻� �Ǿ�� �簢�� �ĺ��� �ȴ�.
		if (s->total >= 4) {
			// �ٿ�� �ڽ��� ã�� ������ �������� �뷫���� ũ�⸦ �˱� ���ؼ���.
			// ũ�⿡ ���� ����� approximation �ϴ� ���е��� �����Ѵ�.
			// ���⼭�� �뷫 10%������ ���е��� �����Ѵ�. (d*approx_param �κ�)
			CvRect rect = cvBoundingRect (s);

			double d = sqrt ((double)rect.height*rect.width);

			const double d_th = 12.;
			const double approx_param = 0.1;

			// �������� �뷫���� ũ�Ⱑ d_th���� Ŀ�� �Ѵ�.
			if (d > d_th) {
				CvSeq *ss = cvApproxPoly (s, s->header_size, storage, CV_POLY_APPROX_DP, d*approx_param, 0);
				// ����� approximation �ϰ��� �ڳ��� ���� 4��(�簢��)���� �˻��Ѵ�.
				if (ss->total == 4) {
					// �߰�������, �� �簢���� �� �밢�� ������ �簢�� �߾ӿ� ������ �˻��Ѵ�.
					if (CheckRectCenter(ss)) {
						// ��Ŀ�� ã�Ҵ�. ��Ŀ ��Ͽ� �����Ѵ�.
						sMarkerInfo mi;

						mi.level = level;
						mi.width = _marker_width;		// ���� ��Ŀ�� ���� ���� (����: m)
						mi.height = _marker_height;		// ���� ��Ŀ�� ���� ���� (����: m)
						mi.ID = -1;						// -1�� �ʱ�ȭ
						mi.corner[0] = cvPointTo32f(*(CvPoint *)cvGetSeqElem(ss, 0));
						mi.corner[1] = cvPointTo32f(*(CvPoint *)cvGetSeqElem(ss, 1));
						mi.corner[2] = cvPointTo32f(*(CvPoint *)cvGetSeqElem(ss, 2));
						mi.corner[3] = cvPointTo32f(*(CvPoint *)cvGetSeqElem(ss, 3));
						
						_markers.push_back (mi);
					}
				}
			}
		}

		if (s->v_next) {
			FindMarkerInContour (s->v_next, storage, level+1);
		}
	}
}

void CMarkerDetection::GetMarkerCode(IplImage *src, IplImage *dst)
{
	for (unsigned int i=0; i<_markers.size(); ++i) {
		// ����� ��Ŀ�� �ڳʷκ��� �����ȼ� ��Ȯ���� �ڳ� ��ǥ�� �ٽ� ���Ѵ�.
		cvFindCornerSubPix (src, _markers[i].corner, 4, cvSize(2, 2), cvSize(-1, -1), 
			cvTermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 0.01));

		// src���� ã�� ��Ŀ�� �������κ��� ��Ŀ ������ �����Ѵ�.
		const int marker_size = 60;
		IplImage *img_marker = cvCreateImage (cvSize (marker_size, marker_size), IPL_DEPTH_8U, 1);
		ExtractMarkerImage (src, img_marker, _markers[i]);

		// ��Ŀ�� 6 x 6�� ��ķ� �����ȴ�.
		double code_matrix[6][6] = {0, };

		// ��Ŀ ������ �ȼ����� �����κ��� �ڵ� ���� �����Ѵ�.
		ExtractCodeFromImage (img_marker, code_matrix);

		if (CheckParity (code_matrix)) {
			int rotate_index = GetRotation (code_matrix);
			if (0 <= rotate_index) {
				// ��Ŀ �ν� ����!!!

				// ��Ŀ�� �ڵ带 ������ ����� ȸ���� ������ ������ �ش�.
				RotateMatrix (code_matrix, rotate_index);    //������Ʈ�� ������ ����������.
				RotateCorner (_markers[i].corner, rotate_index, _markers[i].level%2);

				_markers[i].ID = CalcMarkerID (code_matrix);
				
				FindMarkerPos3d (&_markers[i]);

			}
		}

		cvReleaseImage (&img_marker);
	}
}

void CMarkerDetection::ExtractMarkerImage (IplImage *src, IplImage *dst, sMarkerInfo &mi)
{
	const float ignoring_margin = 0.f;	// ���� �̹����κ��� ��Ŀ �̹����� �����ϸ鼭 ������ �׵θ��� ����

	CvMat *transform_matrix = cvCreateMat(3, 3, CV_32FC1);

	if (mi.level%2 == 0) {
		// ������ ��Ŀ�� ������ �̹��� ���� ��ǥ
		CvPoint2D32f dest_corner_cw[4] = { 
			{ -ignoring_margin,				-ignoring_margin}, 
			{ -ignoring_margin,				dst->height + ignoring_margin}, 
			{ dst->width + ignoring_margin,	dst->height + ignoring_margin}, 
			{ dst->width + ignoring_margin,	-ignoring_margin}, 
		};

		// �ҽ� �̹������� ��Ŀ�� �ڳʿ� ���� ������ ��Ŀ �̹��� ���� ����� �����ϱ� ���� ��ȯ ����� ���Ѵ�.
		cvGetPerspectiveTransform (mi.corner, dest_corner_cw, transform_matrix);
	}
	else {
		CvPoint2D32f dest_corner_ccw[4] = { 
			{ dst->width + ignoring_margin,	-ignoring_margin}, 
			{ dst->width + ignoring_margin,	dst->height + ignoring_margin}, 
			{ -ignoring_margin,				dst->height + ignoring_margin}, 
			{ -ignoring_margin,				-ignoring_margin}, 
		};

		// �ҽ� �̹������� ��Ŀ�� �ڳʿ� ���� ������ ��Ŀ �̹��� ���� ����� �����ϱ� ���� ��ȯ ����� ���Ѵ�.
		cvGetPerspectiveTransform (mi.corner, dest_corner_ccw, transform_matrix);
	}

	// �ҽ� �̹��� ���� ��Ŀ�� ��Ŀ �̹����� �����Ѵ�.
	cvWarpPerspective (src, dst, transform_matrix);

	if (mi.level%2 == 0) {
		cvNot (dst, dst);
	}

	cvReleaseMat (&transform_matrix);
}

void CMarkerDetection::ExtractCodeFromImage (IplImage *src, double code_matrix[6][6])
{
	#define PIXEL_YX(img,y,x)	(unsigned char &)img->imageData[(y)*img->widthStep + (x)]

	// ��Ŀ �̹����� 6x6 ���ڷ� �ɰ� �� ������ ���� ���� �ȼ����� ��� ���Ѵ�.
	for (int y = 0; y < src->height; y++) {
		for (int x = 0; x < src->width; x++) {
			int yi = y/10;
			int xi = x/10;
			code_matrix[yi][xi] += PIXEL_YX(src, y, x);
		}
	}

	double min_v = 255.; 
	double max_v = 0.;
	
	// ���� ���� 0 ~ 1 ������ ������ ����ȭ �ϸ鼭 �ִ밪�� �ּҰ��� ã�´�.
	// �ϳ��� ���ڿ��� 100���� �ȼ��� �������� �� �ȼ��� �ִ� ���� 255�̱� ������
	// ���� ���� 100*255�� �������ָ� �ȴ�.
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 6; x++) {
			code_matrix[y][x] /= 100.*255;

			if (min_v > code_matrix[y][x]) min_v = code_matrix[y][x];
			if (max_v < code_matrix[y][x]) max_v = code_matrix[y][x];
		}
	}

	// �ִ밪�� �ּҰ��� �߰����� ã�´�.
	double mid_v = (min_v + max_v)/2.;

	// �߰����� �������� �������� ������ 1.�� ����� ������ 0.�� �����Ѵ�.
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 6; x++) {
			code_matrix[y][x] = (code_matrix[y][x] < mid_v) ? 1. : 0.;
		}
	}
}

bool CMarkerDetection::CheckParity (double code_matrix[6][6])
{
	int sum = 0;

	// �׵θ��� ��� ����� �ִ��� �˻��Ѵ�.
	// ��, �� ������ �� ���� 6���̰� �𼭸��� 4���̴ϱ� 
	// ���� 24���� �Ǿ�� �Ѵ�.
	for (int i = 0; i < 6; i++) {
		sum += (int)code_matrix[0][i];
		sum += (int)code_matrix[5][i];
		sum += (int)code_matrix[i][0];
		sum += (int)code_matrix[i][5];
	}
	if (sum != 24) return false;

	sum = 0;

	// üũ���� �˻��Ѵ�.
	// �׵θ��� ������ ���� ���� ���� ¦���� �Ǿ�� �Ѵ�.
	for (int y = 1; y < 5; y++) {
		for (int x = 1; x < 5; x++) {
			sum += (int)code_matrix[y][x];
		}
	}
	return (sum%2 == 0);
}


int CMarkerDetection::GetRotation (double code_matrix[6][6])
{
	if      (code_matrix[1][1] && !code_matrix[1][4] && !code_matrix[4][4] && !code_matrix[4][1]) return 0;	// ����
	else if (!code_matrix[1][1] && code_matrix[1][4] && !code_matrix[4][4] && !code_matrix[4][1]) return 1;	// �ð�������� 90�� ȸ����
	else if (!code_matrix[1][1] && !code_matrix[1][4] && code_matrix[4][4] && !code_matrix[4][1]) return 2; // �ð�������� 180�� ȸ����
	else if (!code_matrix[1][1] && !code_matrix[1][4] && !code_matrix[4][4] && code_matrix[4][1]) return 3; // �ð�������� 270�� ȸ����
	else return -1; // ������ ���� �����̴�. ����
}


void CMarkerDetection::RotateMatrix (double code_matrix[6][6], int angle_idx)
{
	if (angle_idx == 0) return;

	double cb[6][6];

	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 6; x++) {
			switch (angle_idx) {
			case 1: cb[y][x] = code_matrix[x][5-y];		break; // �ݽð� �������� 90�� ȸ��
			case 2: cb[y][x] = code_matrix[5-y][5-x];	break; // �ݽð� �������� 180�� ȸ��
			case 3: cb[y][x] = code_matrix[5-x][y];		break; // �ݽð� �������� 270�� ȸ��
			}
		}
	}
	memcpy (code_matrix, cb, sizeof(double)*6*6);
}

inline void swap (CvPoint2D32f &c1, CvPoint2D32f &c2)
{
	CvPoint2D32f temp = c1;
	c1 = c2;
	c2 = temp;
}

void CMarkerDetection::RotateCorner (CvPoint2D32f corner[4], int angle_idx, int dir)
{
	CvPoint2D32f c[4];

	if (dir) {
		for (int i=0; i<4; ++i) {
			c[i] = corner[(i + 3 + angle_idx)%4];
		}
		swap (c[1], c[3]);
	}
	else {
		for (int i=0; i<4; ++i) {
			c[i] = corner[(i + 4 - angle_idx)%4];
		}
	}
	memcpy (corner, c, sizeof(CvPoint2D32f)*4);
}

int CMarkerDetection::CalcMarkerID (double code_matrix[6][6])
{
	int id = 0;
	if (code_matrix[4][2]) id += 1;
	if (code_matrix[3][4]) id += 2;
	if (code_matrix[3][3]) id += 4;
	if (code_matrix[3][2]) id += 8;
	if (code_matrix[3][1]) id += 16;
	if (code_matrix[2][4]) id += 32;
	if (code_matrix[2][3]) id += 64;
	if (code_matrix[2][2]) id += 128;
	if (code_matrix[2][1]) id += 256;
	if (code_matrix[1][3]) id += 512;
	if (code_matrix[1][2]) id += 1024;

	return id;
}

void CMarkerDetection::FindMarkerPos3d (sMarkerInfo *marker)
{
	if (_calib._intrinsic_matrix && _calib._distortion_coeffs);
	else return;

	// ȸ��(rotation)�� �̵�(translation)�� ����Ͽ� ������ ��Ʈ���� ����
	CvMat rotation    = cvMat(3, 1, CV_32FC1, marker->rotation);
	CvMat translation = cvMat(3, 1, CV_32FC1, marker->translation);

	float image_xy[4][2] = {
		{ marker->corner[0].x, marker->corner[0].y },
		{ marker->corner[1].x, marker->corner[1].y },
		{ marker->corner[2].x, marker->corner[2].y },
		{ marker->corner[3].x, marker->corner[3].y },
	};

	float object_xyz[4][3] = {
		{ 0.0f,				0.0f,			0.0f },
		{ 0.0f,				marker->height,	0.0f },
		{ marker->width,	marker->height,	0.0f },
		{ marker->width,	0.0f,			0.0f },
	};

	CvMat object_points = cvMat(4, 3, CV_32FC1, &object_xyz[0][0]);
	CvMat image_points  = cvMat(4, 2, CV_32FC1, &image_xy[0][0]);
	
	// 3���� �������� ��Ŀ�� ��ġ�� ������ ã�´�.
	cvFindExtrinsicCameraParams2 (&object_points, &image_points, 
		_calib._intrinsic_matrix, _calib._distortion_coeffs, 
		&rotation, &translation);
}