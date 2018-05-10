/*
<3D Printing Prototype>
main.cpp
작성자: 민경하
작성일: 2014. 10. 10
*/

#include "stdafx.h"
#include "main.h"
#include "vmg_math.h" 
#include "Image.h"
#include "Pix.h"
#include "Puzzle.h"
#include "dir.h"

int Width;
int Height;

//char input[124] = "mario01.bmp";

int *ncpts;
int **cpts;
int **ipts;


V3DI picked = { 0, 0, 0 };

//	Global data structure for status
int Light;
int State;
int Shading;
int Wireframe;
int Flag;
int DRAW_WIRE;
float Bright;

//	Global data structure for camera control
float eyex, eyey, eyez;
int beginx, beginy;
int oldx, oldy;
float curquat[4], lastquat[4];
GLfloat m0[4][4], m1[4][4];
V4DF view, nview;
GLint viewport[4];
GLdouble mvmatrix[16], projmatrix[16];
GLfloat rotmat[4][4];

int tPICTURE = 2;	//0:circle, 1:mesh, 2:COLOR, 3:MONOCROME

//	Global data structure for rendering
V3DF White = { 1.0f, 1.0f, 1.0f };
V3DF LightGray = { 0.8f, 0.8f, 0.8f };
V3DF Gray = { 0.5f, 0.5f, 0.5f };
V3DF DarkGray = { 0.2f, 0.2f, 0.2f };
V3DF Black = { 0.0f, 0.0f, 0.0f };
V3DF Red = { 1.0f, 0.0f, 0.0f };
V3DF Green = { 0.0f, 1.0f, 0.0f };
V3DF Blue = { 0.0f, 0.0f, 1.0f };
V3DF Cyan = { 0.0f, 1.0f, 1.0f };
V3DF Violet = { 1.0f, 0.0f, 1.0f };
V3DF Yellow = { 1.0f, 1.0f, 0.0f };
V3DF Orange = { 1.0f, 0.5f, 0.0f };
V3DF LightRed = { 0.8f, 0.0f, 0.0f };
V3DF LightGreen = { 0.0f, 0.8f, 0.0f };
V3DF LightBlue = { 0.0f, 0.0f, 0.8f };
V3DF LightCyan = { 0.0f, 0.8f, 0.8f };
V3DF LightViolet = { 0.8f, 0.0f, 0.8f };
V3DF LightYellow = { 0.8f, 0.8f, 0.0f };
V3DF DarkRed = { 0.3f, 0.0f, 0.0f };
V3DF DarkGreen = { 0.0f, 0.3f, 0.0f };
V3DF DarkBlue = { 0.0f, 0.0f, 0.3f };
V3DF DarkCyan = { 0.0f, 0.3f, 0.3f };
V3DF DarkViolet = { 0.3f, 0.0f, 0.3f };
V3DF DarkYellow = { 0.3f, 0.3f, 0.0f };
V4DF TYellow = { 1.0f, 1.0f, 0.0f, 0.5f };
V3DF Whatisthis = { 1.0f, 0.0f, 0.5f };

GLfloat no_ambient[4];
GLfloat no_diffuse[4];
GLfloat no_specular[4];
GLfloat no_emission[4];
GLfloat no_shininess[1];

GLfloat ambient_diffuse1[4];
GLfloat ambient_diffuse2[4];
GLfloat ambient_diffuse3[4];

GLfloat shininess[1];
GLfloat light0_ambient[4];
GLfloat light0_diffuse[4];
GLfloat light0_position[4];

GLfloat light1_ambient[4];
GLfloat light1_diffuse[4];
GLfloat light1_position[4];

GLfloat light2_ambient[4];
GLfloat light2_diffuse[4];
GLfloat light2_position[4];

GLfloat light3_ambient[4];
GLfloat light3_diffuse[4];
GLfloat light3_position[4];

float factor = 1.0f;

//	trackball.cpp: extern functions for camera control
extern void trackball(float *, float, float, float, float);
extern void add_quats(float *, float *, float *);
extern void build_rotmatrix(GLfloat[4][4], float[4]);

extern void pick_pixel(int x, int y);
extern void pick_stream(int x, int y);
extern void save_bitmap_file(char *fn, int W, int H, GLubyte *rpxls);

extern void draw_axis();

int WIREFRAME = 0;
V3DF veye, vcent, vup;
V3DF cent;

int n_picked;

Pix* thisPix;                                    //포인터로 바꿔 줌으로써 매번 새로운 객체를 할당하게 한다. 물론 사용후 delete는 꼭 해준다.
bigPicture* bP;
Direction* thisImage;

int DRAWKEY = 0;

void Main::lighting()
{
	vector4(no_ambient, 0.0f, 0.0f, 0.0f, 1.0f);
	vector4(no_diffuse, 0.0f, 0.0f, 0.0f, 1.0f);
	vector4(no_specular, 0.0f, 0.0f, 0.0f, 1.0f);
	vector4(no_emission, 0.0f, 0.0f, 0.0f, 1.0f);
	no_shininess[0] = 0.0f;

	vector4(ambient_diffuse1, 0.676f, 0.506f, 0.32f, 1.0f);
	vector4(ambient_diffuse2, 0.5f, 0.5f, 0.5f, 1.0f);
	vector4(ambient_diffuse3, 1.0f, 0.0f, 0.0f, 1.0f);

	shininess[0] = 10.0f;
	vector4(light0_ambient, 0.80f, 0.80f, 0.80f, 1.0f);
	vector4(light0_diffuse, 0.60f, 0.60f, 0.60f, 1.0f);
	vector4(light0_position, 0.0f, 0.0f, 1000.0f, 1.0f);

	vector4(light1_ambient, 0.10f, 0.10f, 0.10f, 1.0f);
	vector4(light1_diffuse, 0.25f, 0.25f, 0.25f, 1.0f);
	vector4(light1_position, 1000.0f, 0.0f, 0.0f, 1.0f);

	vector4(light2_ambient, 0.10f, 0.10f, 0.10f, 1.0f);
	vector4(light2_diffuse, 0.25f, 0.25f, 0.25f, 1.0f);
	vector4(light2_position, 0.0f, 1000.0f, 1000.0f, 1.0f);

	vector4(light3_ambient, 0.10f, 0.10f, 0.10f, 1.0f);
	vector4(light3_diffuse, 0.25f, 0.25f, 0.25f, 1.0f);
	vector4(light3_position, -1000.0f, 0.0f, 0.0f, 1.0f);
}

void Main::display(void)
{
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0f, Width * factor + 0.0f, 0.0f, Height * factor + 0.0f, -1000.0f, 1000.0f);
	gluLookAt(veye[0], veye[1], veye[2], vcent[0], vcent[1], vcent[2], vup[0], vup[1], vup[2]);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-eyex, -eyey, -eyez);
	build_rotmatrix(m1, curquat);
	glMultMatrixf(&m1[0][0]);
	vector4(view, 0.0f, 0.0f, -1.0f, 1.0f);
	m_multi_v(nview, m1, view);
	vector4(view, nview[0] / nview[3], nview[1] / nview[3], nview[2] / nview[3], 1.0f);

	//thisImage.draw();

	///////////////////////draw_output()을 출력해야 원래 보던 결과가 나옴!!!!!!!!!!!!!
	//thisPix.draw_output();

	/////팔레트적용
	/*switch (DRAWKEY)
	{
	case 0:
	cout << "원본" << endl;
	thisImage.draw();
	break;
	case 1:
	cout << "픽셀레이션" << endl;
	thisPix.draw_output_Palette();
	break;
	case 2:
	cout << "타일로 초기화" << endl;
	bP.draw_orig_output(Width, Height);
	break;
	case 3:
	cout << "타일로 초기화 테두리 버전" << endl;
	bP.draw_orig_outputBlockLine(Width, Height);
	break;
	case 4:
	cout << "특징유지 한번" << endl;
	bP.draw_pick_output(Width, Height);
	break;
	case 5:
	cout << "특징유지 한번 테두리 버전" << endl;
	bP.draw_pick_outputBlockLine(Width, Height);
	break;
	default:
	break;
	}*/

	//////////////////////////////////////////

	//thisPix.draw_test();


	////작게 출력하기 위함???///////
	//thisPix.draw_mini();
	////////////////////////////////////////////
	bP->draw_pick_outputBlockLine(Width, Height);

	glutSwapBuffers();

}

void Main::init(void)
{
	thisPix=new Pix;                              //메모리 할당
	bP=new bigPicture;
	thisImage=new Direction;

	/////////////
	lighting();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glViewport(0, 0, Width, Height);

	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);

	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);


	glShadeModel(GL_SMOOTH);

	glDisable(GL_BLEND);

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	factor = 1.0f;

	vector3(veye, 0.0f, 0.0f, 25.0f);
	vector3(vcent, 0.0f, 0.0f, 0.0f);
	vector3(vup, 0.0f, 1.0f, 0.0f);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

	glLightfv(GL_LIGHT3, GL_AMBIENT, light3_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
	glLightfv(GL_LIGHT3, GL_POSITION, light3_position);

	Flag = NONE;
	State = ROTATE;

	vzero(cent);

	//	Initial value settings for camera control
	/*trackball(curquat, 0.0, 0.0, 0.0, 0.0);
	build_rotmatrix(m1, curquat);
	eyex = eyey = 0.0;
	eyez = 0.0;
	vector4(view, 0.0f, 0.0f, -1.0f, 1.0f);
	m_multi_v(nview, m1, view);
	vassign(view, nview);*/

}

void Main::abstraction(int resol)
{
	printf("create...");
	thisPix->create(thisImage->cim, thisImage->MAX_X, thisImage->MAX_Y, resol);

	thisPix->initialize();
	printf("initialize...done!\n\n");

	thisPix->Iterate();
	printf("iterate...done!\n\n");
	thisPix->text_output();
	thisPix->NearColor();
}

void Main::puzzlePreprocess()
{
	printf("puzzle preprocess\n");
	bP->init(thisPix->getOutputW(), thisPix->getOutputH());
	bP->getNumOfTile();
	bP->getNumOfBlock();
	bP->BPcolorMatching(thisPix->BPPXcolor);
	bP->OrigBLtoBP();
}

void Main::puzzlePreprocess8()
{
	printf("puzzle preprocess888888\n");
	bP->init(thisPix->getOutputW(), thisPix->getOutputH());
	bP->getNumOfTile8();
	bP->getNumOfBlock8();
	bP->BPcolorMatching(thisPix->BPPXcolor);
	bP->OrigBLtoBP();
	//bP.printBP();
}

void Main::puzzleSwap()
{
	bP->setExchangeList(bP->exchangeList);
	bP->setExchangeListPos(bP->exchangeListPos);
	bP->setExchangeListMatchPos(bP->exchangeListMatchPos);
	bP->setExchangeListDir(bP->exchangeListDir);

	thisImage->GetDir(12);

	for (int i = 0; i < 1000; i++) {
		bP->findBlock();
		bP->swapBlock(thisPix->BPPXcolor);
	}
	bP->swapBlockVerNew(thisImage->res_dir, thisPix->BPPXcolor, Width, Height);
}

void Main::setImg(char *fileName){
	init();
	thisImage->loadBitmap2(fileName);	//이미지 로드(크기 중 앞의 숫자가 4의 배수여야 한다.)	두번째 사진을 키면 여기서 에러남.

	/////////////////////////////////////////////////////////////////

}

void Main::puzzleProcessing(int n){
	if (n == 8)
		puzzlePreprocess8();
	else if (n == 4)
		puzzlePreprocess();
	puzzleSwap();

	///////////////////////////////////////////////////////////////////
	//saveImg("C:\\Users\\Chan\\Documents\\Visual Studio 2013\\Projects\\Pixelated_abstraction2_1\\mario02.bmp");

}

void Main::saveImg(char* filename){
	int size = Width * Height * 3;
	GLubyte *Bits = new GLubyte[size];
	GLubyte temp;

	memset(Bits, 0, size);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("");
	display();
	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, Width, Height, GL_RGB, GL_UNSIGNED_BYTE, Bits);
	//R,B자리 바꾸어야
	int i;
	temp;
	for (i = 0; i < Width * Height; i++){
		temp = Bits[i * 3];
		Bits[i * 3] = Bits[i * 3 + 2];
		Bits[i * 3 + 2] = temp;
	}
	//output 파일 이름 바꾸기

	save_bitmap_file(filename, Width, Height, Bits);	//bmp파일로 저장

	delete thisImage;            //메모리 해제
	delete bP;
	delete thisPix;
	//printf("%s save done!\n", filename);
}
void Main::start(int resol, int process, char* fileName, char *destName)
{
	//1. 
	//setImg("C:\\Users\\Chan\\Documents\\Visual Studio 2013\\Projects\\Pixelated_abstraction2_1\\mario01.bmp");
	setImg(fileName);                //이 안의 load 부분에서 에러남.    BITMAP2.cpp 의 error = "Bitmap loaded"; 이부분에서 문제있다고 나옴. 
									// 에러가 나오는 부분이 종종 달라지고 있다. 이번에는 Image.cpp 에서 에러남
									//아무래도 맨 위의 전역변수인 Direction thisImage;를 초기화 시켜줘야 될것 같다.


	//2.                             

	abstraction(resol);                       //throw 예외 발생
	//3.
	puzzleProcessing(process);
	//4. 저장
	saveImg(destName);         //절대경로로 바꿔줘야 함.
	
	//init();

	//thisImage.loadBitmap2(input);	//이미지 로드(크기 중 앞의 숫자가 4의 배수여야 한다.)	
	//abstraction();

	////=======================

	//cout << "******** 4 or 8 : ";
	//int n48;
	//cin >> n48;
	//
	//if (n48 == 8)
	//	puzzlePreprocess8();
	//else if (n48 == 4)
	//	puzzlePreprocess();


	//puzzleSwap();

	//========================

	//glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	//glutInitWindowPosition(0, 0);
	//glutInitWindowSize(Width, Height);
	//glutCreateWindow("SuperPixels");

	//glutKeyboardFunc(keyboard);
	//glutMouseFunc(mouse);
	//glutMotionFunc(motion);
	//glutDisplayFunc(display);

	//glutMainLoop();
}

