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

	// DC�� ���� �ȼ� ������ ������ �� �̿� ������ RC�� �����մϴ�. 
	// RC�� ��� OpenGL ��ɾ���� ����ؾ� �ϴ� ������ ��Ʈ�� ������ �� �ֽ��ϴ�. 
	// RC�� DC�� ������ �Ͱ� ���� �ȼ� ������ ���ϴµ� RC�� DC�� ���� ���� ���� �ƴϸ�, 
	// DC�� GDI�� ���� ������ �����ϴ� �ݸ� RC�� OpenGL�� ���� ������ ��� �ֽ��ϴ�. 

	if (!SetupPixelFormat(dc->m_hDC)) {
		return;
	}
	// ������ ���ؽ�Ʈ�� ��´� 
	_glrc = wglCreateContext(dc->m_hDC);
	if (!_glrc) {
		::AfxMessageBox("wglCreateContext failed"); 
		return; 
	} 
	// ������ ������ ���ؽ�Ʈ�� �����. 
	if(!wglMakeCurrent(dc->m_hDC, _glrc)) { 
		::AfxMessageBox("wglMakeCurrent failed"); 
		return; 
	} 

	// �÷����ۿ� ���̹��۸� �ʱ�ȭ
	// ����� ������ ������ ���� ������ �����Ѵ�.
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// ���� ����
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

	// ������ �Ӽ� ����
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
}

COpenGlDraw::~COpenGlDraw ()
{
	if(!wglMakeCurrent(0, 0)) { // ���� ������ ���ؽ�Ʈ ���� 
		::AfxMessageBox("wglMakeCurrent failed"); 
	} 
	if(!wglDeleteContext(_glrc)) { // ������ ���ؽ�Ʈ ���� 
		::AfxMessageBox("wglDeleteContext failed"); 
	} 
}

BOOL COpenGlDraw::SetupPixelFormat(HDC hdc)
{
	// �ȼ� �ڵ带 �����մϴ�. 
	// �ȼ� ������ ���� �׸� ��ü�� ���, �� �����쳪 ��Ʈ�ʿ� ���� �÷� ��Ʈ�� ������ ���� �Ӽ��� �����ϴ� ���� �ǹ��մϴ�. 
	// PIXELFORMATDESCRIPTOR ����ü�� DC�� ���� ���Ǵ� �ȼ� ������ �����ϸ�, �� ������� ������ �ȼ� ������ ������ �ֽ��ϴ�. 
	// ���⼭ PIXELFORMATDESCRIPTOR ����ü���� ũ��, ���� �ѹ�, �Ӽ� �÷���, �÷� ��Ʈ ��, ��ť�ķ�����(accumulate)�� 
	// ����(depth) ����, ���ٽ�(stencil), ����(auxiliary) ���� ���� ����, ���� ���̾�(layer)Ÿ�Ե��� ������ ������ �� ����. 
	// ���� ���۸��� ���� ����(Screen Buffer)�� �̸� ����(Off-Screen Buffer, �ĸ� ���۶�� �Ѵ�.)�� �̿��ϴµ�, 
	// �̸� ���ۿ� ���� �������� �� ���� ���ۿ� ��ü�ϴ� ����� ���� ���� ���� �ִϸ��̼��� ������ �� �ֽ��ϴ�. 

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

	// OpenGL�� �׸� �̹����� �о�´�.
	glReadPixels (0, 0, src->width, src->height, GL_BGR_EXT, GL_UNSIGNED_BYTE, gli->imageData );
	
	// OpenGL�� �׸� �̹������� ��ü�� �ִ� �κи� ��� ����ũ �̹����� �����.
	cvCvtColor (gli, mask, CV_RGB2GRAY);
	cvThreshold(mask, mask, 1, 255, CV_THRESH_BINARY); 

	// �̹����� �����Ѵ�.
	cvCopy(src, dst, 0);
	// OpenCV�� ���� �̹������ٰ� ����ũ�� �����Ͽ� OpenGL ��ü�� �ִ� �κи� �����Ѵ�.
	cvCopy (gli, dst, mask);

	cvReleaseImage (&mask);
	cvReleaseImage (&gli);
}

void COpenGlDraw::Draw(const IplImage *src, IplImage *dst, const CvMat *intrinsic, const vector<sMarkerInfo> &markers) 
{
	int width  = src->width;
	int height = src->height;

	float fx = CV_MAT_ELEM(*intrinsic, float, 0, 0);	// x�� ���� �Ÿ�
	float fy = CV_MAT_ELEM(*intrinsic, float, 1, 1);	// y�� ���� �Ÿ�
	float cx = CV_MAT_ELEM(*intrinsic, float, 0, 2);	// x�� ����(principal point), ����� ���� ����� ������ ��
	float cy = CV_MAT_ELEM(*intrinsic, float, 1, 2);	// y�� ����

	// ������� FOV�� ��ȯ�ϱ� ���� Projection Matrix�� �����ϰ� �ʱ�ȭ �Ѵ�.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// ����Ʈ�� ũ��� src �̹����� ũ��� ���� ����
	glViewport(0, 0, width, height);

	// y�� ȭ���� �����Ѵ�.
	double fov_y = 2*atan(height/2/fy)*180/CV_PI;
	
	gluPerspective(fov_y, (double)width/height, 0.1, 10.);

	// �׸��� ���� Render ���� �����Ѵ�.
	glRenderMode(GL_RENDER);

	// Modelview Matrix�� �����ϰ� �ʱ�ȭ�Ѵ�. 
	glMatrixMode(GL_MODELVIEW);    
	glLoadIdentity();

	// Screen �� Depth Buffer�� �����.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ī�޶� �̹��� ��� ���� ���� ��ġ(pixel ����)�� ī�޶�κ��� 1���� ������ ��� ������ �ű� 
	cx = (width/2  - cx)/fx;
	cy = (height/2 - cy)/fy;

	// ī�޶� ����(0, 0, 0)�� ��ġ�ϰ� ī�޶� ������ z�� ���� -1 ��ġ(cx, cy, -1)�� �ٶ󺸵��� ����
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
