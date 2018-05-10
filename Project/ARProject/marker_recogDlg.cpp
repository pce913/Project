#include "stdafx.h"
#include "marker_recog.h"
#include "marker_recogDlg.h"
#include <string>

using namespace std;

// ��Ŀ�� ���� ���� ũ�⸦ ���� ������ �����Ѵ�.
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
	_camera = new CCamOpenCV();           //���⼭ ����Ʈ �����ڰ� �ҷ������� �����̴�. ���� CamOpenCV.cpp�� �ִ� �����ڸ� ȣ���ؾ� �Ѵ�.
	_camera = new CCamOpenCV(0,640,420);         
	_markRecog = new CMarkerDetection (MARKER_WIDTH, MARKER_HEIGHT);
	_oglDraw = new COpenGlDraw(GetDC());

	cvNamedWindow ("OpenGlDraw");  //������ �����

	SetTimer(1000, 30, 0);

	return TRUE;
}

void Cmarker_recogDlg::OnTimer(UINT_PTR nIDEvent){
	if (_camera) {				
		IplImage *img = _camera->CaptureImage();	            //img�� null�� �����Ƿ� ȭ�鿡 �ƹ��͵� ��Ÿ���� �ʴ´�.
		if (img) {
			IplImage *und = cvCreateImage (cvGetSize(img), IPL_DEPTH_8U, 3);
			IplImage *dst = cvCreateImage (cvGetSize(img), IPL_DEPTH_8U, 3);

			// ī�޶� �̹����� �ְ��� �����Ѵ�.	
			_markRecog->_calib.Undistort (img, und);

			// �̹������� ��Ŀ�� ã�´�.
			cvCopy(und, dst, 0);
			_markRecog->MarkerRecog(und, dst);

			// ��Ŀ�� �ν��� ���� OpenGL�� ��ü ������ �׸���.
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

