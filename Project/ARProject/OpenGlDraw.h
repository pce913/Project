#pragma once

#pragma comment(lib, "Opengl32.lib")
#pragma comment(lib, "Glu32.lib")

#include "afxwin.h"
#include <opencv/cv.h>
#include "MarkerDetection.h"
#include "ObjLoader.h"

class COpenGlDraw
{
public:
	COpenGlDraw (CDC *dc);
	virtual ~COpenGlDraw ();

	void Draw(const IplImage *src, IplImage *dst, const CvMat *intrinsic, const vector<sMarkerInfo> &markers);

private:
	BOOL SetupPixelFormat(HDC hdc);
	void TransformCoordinate (const float rotation[3], const float translation[3]);
	void Draw3dObject (int id);
	void CopyOpenGlImage (const IplImage *src, IplImage *dst);

private:
	HGLRC _glrc;	//Rendering Context

	CObjLoader _obj1;
	CObjLoader _obj2;
	CObjLoader _obj3;
	CObjLoader _obj4;
};
