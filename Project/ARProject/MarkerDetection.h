#pragma once

#include <vector>
#include <opencv/highgui.h>
#include "CamCalib.h"

using namespace std;

struct sMarkerInfo 
{
	int level;
	float width, height;	// 마커의 크기
	CvPoint2D32f center;	// 마커의 중심 점
	CvPoint2D32f corner[4];	// 사각형의 네 코너 점
	int ID;					// 마커에서 인식된 ID
	
	float rotation[3];		// 마커의 회전을 나타내는 벡터 (3 x 1)
	float translation[3];	// 마커의 이동을 나타내는 벡터 (3 x 1)
};

class CMarkerDetection
{
public:
	CMarkerDetection (float marker_width, float marker_height);
	~CMarkerDetection();

	void MarkerRecog(IplImage *src, IplImage *dst);

public:
	CCamCalib _calib;
	vector<sMarkerInfo> _markers;
	float _marker_width;
	float _marker_height;

private:
	void FindMarkerInContour (CvSeq *contours, CvMemStorage *storage, int level);
	bool CheckRectCenter(CvSeq *seq);

	void GetMarkerCode(IplImage *src, IplImage *dst);
	void ExtractMarkerImage (IplImage *src, IplImage *dst, sMarkerInfo &mi);
	void ExtractCodeFromImage (IplImage *src, double code_matrix[6][6]);

	bool CheckParity (double code_matrix[6][6]);
	int  GetRotation (double code_matrix[6][6]);
	void RotateMatrix (double code_matrix[6][6], int rotate_index);
	void RotateCorner (CvPoint2D32f corner[4], int angle_idx, int dir);
	int  CalcMarkerID (double code_matrix[6][6]);

	void FindMarkerPos3d (sMarkerInfo *marker);
};
