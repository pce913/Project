#include "StdAfx.h"
#include <gl/glu.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include "OpenGlDraw.h"

COpenGlDraw::COpenGlDraw(CDC *dc)
{
	_obj1.Load ("Model/cassini.obj");   //2
	_obj2.Load ("Model/DeadTree.obj");  //8
	_obj3.Load ("Model/balto.obj");   //10
	_obj4.Load("Model/UmbreonHighPoly.obj");  //12
	//balto
	//UmbreonHighPoly
	//DeadTree
	//cassini

	// DC에 대한 픽셀 포맷을 설정한 후 이와 연관된 RC를 생성합니다. 
	// RC는 모든 OpenGL 명령어들이 통과해야 하는 일종의 포트로 생각할 수 있습니다. 
	// RC는 DC에 지정된 것과 같은 픽셀 포맷을 지니는데 RC와 DC는 서로 같은 것이 아니며, 
	// DC는 GDI를 위한 정보를 포함하는 반면 RC는 OpenGL을 위한 정보를 담고 있습니다. 

	if (!SetupPixelFormat(dc->m_hDC)) {
		return;
	}
	// 렌더링 컨텍스트를 얻는다 
	_glrc = wglCreateContext(dc->m_hDC);
	if (!_glrc) {
		::AfxMessageBox("wglCreateContext failed"); 
		return; 
	} 
	// 현재의 렌더링 컨텍스트를 만든다. 
	if(!wglMakeCurrent(dc->m_hDC, _glrc)) { 
		::AfxMessageBox("wglMakeCurrent failed"); 
		return; 
	} 

	// 컬러버퍼와 깊이버퍼를 초기화
	// 배경을 따내기 좋도록 검은 색으로 설정한다.
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// 조명 설정
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	float AmbientColor[]    = { 0.0f, 0.1f, 0.2f, 0.0f };         
	float DiffuseColor[]    = { 0.5f, 0.5f, 0.5f, 0.0f };         
	float SpecularColor[]   = { 0.5f, 0.5f, 0.5f, 0.0f };        
	float Position[]        = { 100.0f, 100.0f, -400.0f, 1.0f };  

	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientColor);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseColor);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularColor);
	glLightfv(GL_LIGHT1, GL_POSITION, Position);

	// 재질의 속성 설정
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
}

COpenGlDraw::~COpenGlDraw ()
{
	if(!wglMakeCurrent(0, 0)) { // 현재 렌더링 컨텍스트 해제 
		::AfxMessageBox("wglMakeCurrent failed"); 
	} 
	if(!wglDeleteContext(_glrc)) { // 렌더링 컨텍스트 제거 
		::AfxMessageBox("wglDeleteContext failed"); 
	} 
}

BOOL COpenGlDraw::SetupPixelFormat(HDC hdc)
{
	// 픽셀 코드를 설정합니다. 
	// 픽셀 포맷은 직접 그릴 객체의 대상, 즉 윈도우나 비트맵에 대한 컬러 비트의 구조에 대한 속성을 지정하는 것을 의미합니다. 
	// PIXELFORMATDESCRIPTOR 구조체는 DC에 의해 사용되는 픽셀 포맷을 지정하며, 각 윈도우는 각자의 픽셀 포맷을 가지고 있습니다. 
	// 여기서 PIXELFORMATDESCRIPTOR 구조체에는 크기, 버전 넘버, 속성 플래그, 컬러 비트 수, 어큐뮬레이터(accumulate)나 
	// 깊이(depth) 버퍼, 스텐슬(stencil), 보조(auxiliary) 버퍼 등의 지정, 메인 레이어(layer)타입등의 정보를 지정할 수 있죠. 
	// 더블 버퍼링은 전면 버퍼(Screen Buffer)와 이면 버퍼(Off-Screen Buffer, 후면 버퍼라고도 한다.)를 이용하는데, 
	// 이면 버퍼에 먼저 렌더링한 후 전면 버퍼와 교체하는 방식을 통해 보다 빠른 애니메이션을 구현할 수 있습니다. 

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL |		    // support OpenGL
		PFD_DOUBLEBUFFER,				// double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		16,                             // 16-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};

	int pixelFormat = ChoosePixelFormat(hdc, &pfd);
	if(pixelFormat == 0) { 
		::AfxMessageBox("ChoosePixelFormat failed."); 
		return FALSE;
	} 

	BOOL ret = SetPixelFormat(hdc, pixelFormat, &pfd);
	if(ret == FALSE) { 
		::AfxMessageBox("SetPixelFormat failed."); 
		return FALSE; 
	} 
	return TRUE; 
}

void COpenGlDraw::TransformCoordinate (const float rotation[3], const float translation[3])
{	
	float _rot[3] = { -rotation[0], -rotation[1], rotation[2] };
	float _R[3][3] = {0., };

	CvMat R = cvMat (3, 3, CV_32FC1, &_R[0][0]);
	CvMat v = cvMat (3, 1, CV_32FC1, &_rot[0]);

	cvRodrigues2 (&v, &R, NULL);

	float m[16];
	m[0] = _R[0][0]; m[4] = _R[0][1];  m[8] = _R[0][2];  m[12] = translation[0]; 
	m[1] = _R[1][0]; m[5] = _R[1][1];  m[9] = _R[1][2];  m[13] = translation[1]; 
	m[2] = _R[2][0]; m[6] = _R[2][1];  m[10]= _R[2][2];  m[14] = -translation[2]; 
	m[3] = 0.;       m[7] = 0.;        m[11]= 0.;        m[15] = 1.; 

	glMultMatrixf(m);
}

void COpenGlDraw::Draw3dObject (int id)
{
	if (id == 2) {
		glTranslatef (0.1, 0.1, 0.1);
		_obj1.Draw (0.01);
	}
	else if (id == 8) {
		glTranslatef (0.1, 0.1, 0.1);
		_obj2.Draw (0.01);
	}
	else if (id == 4) {
		glTranslatef (0.1, 0.1, 0.1);
		_obj3.Draw (0.02);
	}
	else if (id == 12) {
		glTranslatef(0.1, 0.1, 0.1);
		_obj4.Draw(0.02);
	}
}

void COpenGlDraw::CopyOpenGlImage (const IplImage *src, IplImage *dst)
{
	IplImage *gli = cvCreateImage (cvGetSize(src), IPL_DEPTH_8U, 3);
	IplImage *mask = cvCreateImage (cvGetSize(src), IPL_DEPTH_8U, 1);

	// OpenGL로 그린 이미지를 읽어온다.
	glReadPixels (0, 0, src->width, src->height, GL_BGR_EXT, GL_UNSIGNED_BYTE, gli->imageData );
	
	// OpenGL로 그린 이미지에서 물체가 있는 부분만 흰색 마스크 이미지로 만든다.
	cvCvtColor (gli, mask, CV_RGB2GRAY);
	cvThreshold(mask, mask, 1, 255, CV_THRESH_BINARY); 

	// 이미지를 복사한다.
	cvCopy(src, dst, 0);
	// OpenCV로 읽은 이미지에다가 마스크를 지정하여 OpenGL 물체가 있는 부분만 복사한다.
	cvCopy (gli, dst, mask);

	cvReleaseImage (&mask);
	cvReleaseImage (&gli);
}

void COpenGlDraw::Draw(const IplImage *src, IplImage *dst, const CvMat *intrinsic, const vector<sMarkerInfo> &markers) 
{
	int width  = src->width;
	int height = src->height;

	float fx = CV_MAT_ELEM(*intrinsic, float, 0, 0);	// x축 초점 거리
	float fy = CV_MAT_ELEM(*intrinsic, float, 1, 1);	// y축 초점 거리
	float cx = CV_MAT_ELEM(*intrinsic, float, 0, 2);	// x축 주점(principal point), 광축과 영상 평면이 만나는 점
	float cy = CV_MAT_ELEM(*intrinsic, float, 1, 2);	// y축 주점

	// 뷰포드와 FOV를 변환하기 위해 Projection Matrix를 선택하고 초기화 한다.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 뷰포트의 크기는 src 이미지의 크기와 같게 설정
	glViewport(0, 0, width, height);

	// y축 화각을 결정한다.
	double fov_y = 2*atan(height/2/fy)*180/CV_PI;
	
	gluPerspective(fov_y, (double)width/height, 0.1, 10.);

	// 그리기 위한 Render 모드로 변경한다.
	glRenderMode(GL_RENDER);

	// Modelview Matrix를 선택하고 초기화한다. 
	glMatrixMode(GL_MODELVIEW);    
	glLoadIdentity();

	// Screen 과 Depth Buffer를 지운다.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 카메라 이미지 평면 상의 주점 위치(pixel 단위)를 카메라로부터 1미터 떨어진 평면 상으로 옮김 
	cx = (width/2  - cx)/fx;
	cy = (height/2 - cy)/fy;

	// 카메라를 중점(0, 0, 0)에 설치하고 카메라가 주점과 z축 상의 -1 위치(cx, cy, -1)를 바라보도록 설정
	gluLookAt( 0, 0, 0,  cx, cy, -1,  0, 1, 0 );

	for (unsigned int i=0; i<markers.size(); ++i) {
		glPushMatrix ();

		TransformCoordinate (markers[i].rotation, markers[i].translation);
		Draw3dObject (markers[i].ID);

		glPopMatrix ();
	}

	glFinish();

	CopyOpenGlImage (src, dst);
}
