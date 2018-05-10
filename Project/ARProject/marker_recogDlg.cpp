#include "stdafx.h"
#include "marker_recog.h"
#include "marker_recogDlg.h"
#include <string>

using namespace std;

// 마커의 가로 세로 크기를 미터 단위로 설정한다.
#define MARKER_WIDTH	0.146f
#define MARKER_HEIGHT	0.146f


Cmarker_recogDlg::Cmarker_recogDlg(CWnd *pParent): CDialog(Cmarker_recogDlg::IDD, pParent){}

void Cmarker_recogDlg::DoDataExchange(CDataExchange *pDX){
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cmarker_recogDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


BOOL Cmarker_recogDlg::OnInitDialog(){
	_camera = new CCamOpenCV();           //여기서 디폴트 생성자가 불러와지기 때문이다. 따라서 CamOpenCV.cpp에 있는 생성자를 호출해야 한다.
	_camera = new CCamOpenCV(0,640,420);         
	_markRecog = new CMarkerDetection (MARKER_WIDTH, MARKER_HEIGHT);
	_oglDraw = new COpenGlDraw(GetDC());

	cvNamedWindow ("OpenGlDraw");  //윈도우 만들기

	SetTimer(1000, 30, 0);

	return TRUE;
}

void Cmarker_recogDlg::OnTimer(UINT_PTR nIDEvent){
	if (_camera) {				
		IplImage *img = _camera->CaptureImage();	            //img에 null이 들어오므로 화면에 아무것도 나타나지 않는다.
		if (img) {
			IplImage *und = cvCreateImage (cvGetSize(img), IPL_DEPTH_8U, 3);
			IplImage *dst = cvCreateImage (cvGetSize(img), IPL_DEPTH_8U, 3);

			// 카메라 이미지의 왜곡을 보정한다.	
			_markRecog->_calib.Undistort (img, und);

			// 이미지에서 마커를 찾는다.
			cvCopy(und, dst, 0);
			_markRecog->MarkerRecog(und, dst);

			// 마커를 인식한 영상에 OpenGL로 입체 도형을 그린다.
			cvCopy(und, dst, 0);
			_oglDraw->Draw(img, dst, _markRecog->_calib._intrinsic_matrix, _markRecog->_markers);

			cvShowImage ("OpenGlDraw", dst);

			cvReleaseImage(&dst);
			cvReleaseImage(&und);
		}
	}
}

void Cmarker_recogDlg::OnDestroy(){
	cvDestroyWindow ("OpenGlDraw");

	CDialog::OnDestroy();

	if(_camera)    delete _camera;
	if(_markRecog) delete _markRecog;
	if(_oglDraw)   delete _oglDraw;

	_camera    = NULL;
	_markRecog = NULL;
	_oglDraw   = NULL;
}

