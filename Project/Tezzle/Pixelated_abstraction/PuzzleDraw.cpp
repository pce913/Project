#include "stdafx.h"
#include "Puzzle.h"
#include <ctime>
using namespace std;

//=======================================================
// 퍼즐 그리는 함수들
//=======================================================

void bigPicture::draw_orig_output(int w, int h)
{
	int i, j, idx_x, idx_y;
	V2DI sp;
	cout << w << endl;
	float SIZE;
	SIZE = (h*1.0f) / (pHeight * 1.0f);
	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {

			sp[0] = (pWidth * i) / w;
			sp[1] = (pHeight * j) / h;
			glColor3fv(origBPcolor[sp[0]][sp[1]]);

			glRecti(i, j, i + 1, j + 1);

		}
	}
}

void bigPicture::draw_orig_outputLine(int w, int h)
{
	int i, j, idx_x, idx_y;
	V2DI sp;
	float SIZE;
	SIZE = (h*1.0f) / (pHeight * 1.0f);
	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {

			sp[0] = (pWidth * i) / w;
			sp[1] = (pHeight * j) / h;

			glColor3fv(origBPcolor[sp[0]][sp[1]]);
			glRecti(i, j, i + 1, j + 1);



		}
	}
}



void bigPicture::draw_orig_outputTileLine(int w, int h)
{
	int blockLine[19][10][2] = {
		{ { 0, 0 }, { 0, 1 }, { 1, 1 }, { 1, 2 }, { 2, 2 }, { 2, 1 }, { 3, 1 }, { 3, 0 }, { 2, 0 }, { 1, 0 } },
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, { 0, 3 }, { 0, 2 }, { -1, 2 }, { -1, 1 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 }, { -1, 1 }, { -2, 1 }, { -2, 0 }, { -1, 0 }, { -1, -1 }, { 0, -1 } },
		{ { 0, 0 }, { 0, -1 }, { 0, -2 }, { 1, -2 }, { 1, -1 }, { 2, -1 }, { 2, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 } },

		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 2, 2 }, { 2, 3 }, { 1, 3 }, { 0, 3 }, { 0, 2 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 }, { -1, 1 }, { -1, 2 }, { -2, 2 }, { -2, 1 }, { -2, 0 }, { -1, 0 } },
		{ { 0, 0 }, { 0, -1 }, { -1, -1 }, { -1, -2 }, { 0, -2 }, { 1, -2 }, { 1, -1 }, { 1, 0 }, { 1, 1 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 2, -1 }, { 3, -1 }, { 3, 0 }, { 3, 1 }, { 2, 1 }, { 1, 1 }, { 0, 1 } },

		{ { 0, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 }, { 2, 0 }, { 2, -1 }, { 2, -2 }, { 1, -2 }, { 1, -1 }, { 1, 0 } },
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 }, { 3, 1 }, { 3, 2 }, { 2, 2 }, { 1, 2 }, { 0, 2 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 }, { 0, 2 }, { 0, 3 }, { -1, 3 }, { -1, 2 }, { -1, 1 }, { -1, 0 } },
		{ { 0, 0 }, { -1, 0 }, { -2, 0 }, { -2, -1 }, { -1, -1 }, { 0, -1 }, { 1, -1 }, { 1, 0 }, { 1, 1 }, { 0, 1 } },

		{ { 0, 0 }, { 1, 0 }, { 1, -1 }, { 2, -1 }, { 3, -1 }, { 3, 0 }, { 2, 0 }, { 2, 1 }, { 1, 1 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 }, { 2, 2 }, { 2, 3 }, { 1, 3 }, { 1, 2 }, { 0, 2 }, { 0, 1 } },

		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 2, 1 }, { 3, 1 }, { 3, 2 }, { 2, 2 }, { 1, 2 }, { 1, 1 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 0, 2 }, { 0, 3 }, { -1, 3 }, { -1, 2 }, { -1, 1 }, { 0, 1 } },

		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, { 1, 4 }, { 0, 4 }, { 0, 3 }, { 0, 2 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 }, { 4, 0 }, { 4, 1 }, { 3, 1 }, { 2, 1 }, { 1, 1 }, { 0, 1 } },

		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 2, 1 }, { 2, 2 }, { 1, 2 }, { 0, 2 }, { 0, 1 }, { 0, 0 }, { 0, 0 } },
	};


	int Type;
	float T;		//4*4 ? 8*8?
	float X, Y;
	float SIZE;

	SIZE = (h*1.0f) / (pHeight * 1.0f);
	cout << "선그리기" << h << " " << pHeight << endl;
	cout << SIZE << endl;

	for (int i = 0; i < bN; i++){
		Type = origbIdx[i];
		X = origbPos[i][0] * SIZE;
		Y = origbPos[i][1] * SIZE;

		//if (Type == 0 || Type == 7)
		//	continue;

		glColor3f(0.5, 0, 0);
		glLineWidth(1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(X + blockLine[Type][0][0] * SIZE, Y + blockLine[Type][0][1] * SIZE);
		glVertex2f(X + blockLine[Type][1][0] * SIZE, Y + blockLine[Type][1][1] * SIZE);
		glVertex2f(X + blockLine[Type][2][0] * SIZE, Y + blockLine[Type][2][1] * SIZE);
		glVertex2f(X + blockLine[Type][3][0] * SIZE, Y + blockLine[Type][3][1] * SIZE);
		glVertex2f(X + blockLine[Type][4][0] * SIZE, Y + blockLine[Type][4][1] * SIZE);
		glVertex2f(X + blockLine[Type][5][0] * SIZE, Y + blockLine[Type][5][1] * SIZE);
		glVertex2f(X + blockLine[Type][6][0] * SIZE, Y + blockLine[Type][6][1] * SIZE);
		glVertex2f(X + blockLine[Type][7][0] * SIZE, Y + blockLine[Type][7][1] * SIZE);
		glVertex2f(X + blockLine[Type][8][0] * SIZE, Y + blockLine[Type][8][1] * SIZE);
		glVertex2f(X + blockLine[Type][9][0] * SIZE, Y + blockLine[Type][9][1] * SIZE);


		//cout << "i : " << i << " X : " << X << " Y : " << Y << " type : " << Type << endl;
		//cout << X + blockLine[Type][0][0] * SIZE << " " << Y + blockLine[Type][0][1] * SIZE << endl;
		//cout << X + blockLine[Type][1][0] * SIZE << " " << Y + blockLine[Type][1][1] * SIZE << endl;
		//cout << X + blockLine[Type][2][0] * SIZE << " " << Y + blockLine[Type][2][1] * SIZE << endl;
		//cout << X + blockLine[Type][3][0] * SIZE << " " << Y + blockLine[Type][3][1] * SIZE << endl;
		//cout << X + blockLine[Type][4][0] * SIZE << " " << Y + blockLine[Type][4][1] * SIZE << endl;
		//cout << X + blockLine[Type][5][0] * SIZE << " " << Y + blockLine[Type][5][1] * SIZE << endl;
		//cout << X + blockLine[Type][6][0] * SIZE << " " << Y + blockLine[Type][6][1] * SIZE << endl;
		//cout << X + blockLine[Type][7][0] * SIZE << " " << Y + blockLine[Type][7][1] * SIZE << endl;
		//cout << X + blockLine[Type][8][0] * SIZE << " " << Y + blockLine[Type][8][1] * SIZE << endl;
		//cout << X + blockLine[Type][9][0] * SIZE << " " << Y + blockLine[Type][9][1] * SIZE << endl;

		glEnd();
	}

	for (int i = 0; i < tN; i++){
		Type = tIdx[i];
		if (Type < 16)
			T = SIZE * 4;
		else
			T = SIZE * 8;

		X = tPos[i][0] * SIZE;
		Y = tPos[i][1] * SIZE;

		glColor3f(0.2, 1, 1);
		glLineWidth(4.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(X, Y);
		glVertex2f(X + T, Y);
		glVertex2f(X + T, Y + T);
		glVertex2f(X, Y + T);
		glEnd();


	}


	int i, j;
	V2DI sp;

	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {

			sp[0] = (pWidth * i) / w;
			sp[1] = (pHeight * j) / h;

			glColor3fv(origBPcolor[sp[0]][sp[1]]);
			glRecti(i, j, i + 1, j + 1);
		}
	}
}

void bigPicture::draw_orig_outputBlockLine(int w, int h)
{
	int blockLine[19][10][2] = {
		{ { 0, 0 }, { 0, 1 }, { 1, 1 }, { 1, 2 }, { 2, 2 }, { 2, 1 }, { 3, 1 }, { 3, 0 }, { 2, 0 }, { 1, 0 } },
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, { 0, 3 }, { 0, 2 }, { -1, 2 }, { -1, 1 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 }, { -1, 1 }, { -2, 1 }, { -2, 0 }, { -1, 0 }, { -1, -1 }, { 0, -1 } },
		{ { 0, 0 }, { 0, -1 }, { 0, -2 }, { 1, -2 }, { 1, -1 }, { 2, -1 }, { 2, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 } },

		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 2, 2 }, { 2, 3 }, { 1, 3 }, { 0, 3 }, { 0, 2 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 }, { -1, 1 }, { -1, 2 }, { -2, 2 }, { -2, 1 }, { -2, 0 }, { -1, 0 } },
		{ { 0, 0 }, { 0, -1 }, { -1, -1 }, { -1, -2 }, { 0, -2 }, { 1, -2 }, { 1, -1 }, { 1, 0 }, { 1, 1 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 2, -1 }, { 3, -1 }, { 3, 0 }, { 3, 1 }, { 2, 1 }, { 1, 1 }, { 0, 1 } },

		{ { 0, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 }, { 2, 0 }, { 2, -1 }, { 2, -2 }, { 1, -2 }, { 1, -1 }, { 1, 0 } },
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 }, { 3, 1 }, { 3, 2 }, { 2, 2 }, { 1, 2 }, { 0, 2 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 }, { 0, 2 }, { 0, 3 }, { -1, 3 }, { -1, 2 }, { -1, 1 }, { -1, 0 } },
		{ { 0, 0 }, { -1, 0 }, { -2, 0 }, { -2, -1 }, { -1, -1 }, { 0, -1 }, { 1, -1 }, { 1, 0 }, { 1, 1 }, { 0, 1 } },

		{ { 0, 0 }, { 1, 0 }, { 1, -1 }, { 2, -1 }, { 3, -1 }, { 3, 0 }, { 2, 0 }, { 2, 1 }, { 1, 1 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 }, { 2, 2 }, { 2, 3 }, { 1, 3 }, { 1, 2 }, { 0, 2 }, { 0, 1 } },

		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 2, 1 }, { 3, 1 }, { 3, 2 }, { 2, 2 }, { 1, 2 }, { 1, 1 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 0, 2 }, { 0, 3 }, { -1, 3 }, { -1, 2 }, { -1, 1 }, { 0, 1 } },

		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, { 1, 4 }, { 0, 4 }, { 0, 3 }, { 0, 2 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 }, { 4, 0 }, { 4, 1 }, { 3, 1 }, { 2, 1 }, { 1, 1 }, { 0, 1 } },

		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 2, 1 }, { 2, 2 }, { 1, 2 }, { 0, 2 }, { 0, 1 }, { 0, 0 }, { 0, 0 } },
	};


	int Type;
	float T;		//4*4 ? 8*8?
	float X, Y;
	float SIZEY, SIZEX;

	SIZEX = (w*1.0f) / (pWidth * 1.0f);
	SIZEY = (h*1.0f) / (pHeight * 1.0f);

	cout << "선그리기" << h << " " << pHeight << endl;

	cout << SIZEX << " " << SIZEY << endl;

	for (int i = 0; i < bN; i++){
		Type = origbIdx[i];
		X = origbPos[i][0] * SIZEX;
		Y = origbPos[i][1] * SIZEY;

		//if (Type == 0 || Type == 7)
		//	continue;

		glColor3f(0.5, 0, 0);
		glLineWidth(1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(X + blockLine[Type][0][0] * SIZEX, Y + blockLine[Type][0][1] * SIZEY);
		glVertex2f(X + blockLine[Type][1][0] * SIZEX, Y + blockLine[Type][1][1] * SIZEY);
		glVertex2f(X + blockLine[Type][2][0] * SIZEX, Y + blockLine[Type][2][1] * SIZEY);
		glVertex2f(X + blockLine[Type][3][0] * SIZEX, Y + blockLine[Type][3][1] * SIZEY);
		glVertex2f(X + blockLine[Type][4][0] * SIZEX, Y + blockLine[Type][4][1] * SIZEY);
		glVertex2f(X + blockLine[Type][5][0] * SIZEX, Y + blockLine[Type][5][1] * SIZEY);
		glVertex2f(X + blockLine[Type][6][0] * SIZEX, Y + blockLine[Type][6][1] * SIZEY);
		glVertex2f(X + blockLine[Type][7][0] * SIZEX, Y + blockLine[Type][7][1] * SIZEY);
		glVertex2f(X + blockLine[Type][8][0] * SIZEX, Y + blockLine[Type][8][1] * SIZEY);
		glVertex2f(X + blockLine[Type][9][0] * SIZEX, Y + blockLine[Type][9][1] * SIZEY);

		glEnd();
	}


	int i, j;
	V2DI sp;

	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {

			sp[0] = (pWidth * i) / w;
			sp[1] = (pHeight * j) / h;

			glColor3fv(origBPcolor[sp[0]][sp[1]]);
			glRecti(i, j, i + 1, j + 1);
		}
	}
}



void bigPicture::draw_pick_output(int w, int h)
{
	int i, j;
	V2DI sp;

	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {
			sp[0] = (pWidth * i) / w;
			sp[1] = (pHeight * j) / h;

			glColor3fv(BPcolor[sp[0]][sp[1]]);
			glRecti(i, j, i + 1, j + 1);
		}
	}
}

void bigPicture::draw_pick_outputBlockLine(int w, int h)
{
	int blockLine[19][10][2] = {
		{ { 0, 0 }, { 0, 1 }, { 1, 1 }, { 1, 2 }, { 2, 2 }, { 2, 1 }, { 3, 1 }, { 3, 0 }, { 2, 0 }, { 1, 0 } },
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, { 0, 3 }, { 0, 2 }, { -1, 2 }, { -1, 1 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 }, { -1, 1 }, { -2, 1 }, { -2, 0 }, { -1, 0 }, { -1, -1 }, { 0, -1 } },
		{ { 0, 0 }, { 0, -1 }, { 0, -2 }, { 1, -2 }, { 1, -1 }, { 2, -1 }, { 2, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 } },

		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 2, 2 }, { 2, 3 }, { 1, 3 }, { 0, 3 }, { 0, 2 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 }, { -1, 1 }, { -1, 2 }, { -2, 2 }, { -2, 1 }, { -2, 0 }, { -1, 0 } },
		{ { 0, 0 }, { 0, -1 }, { -1, -1 }, { -1, -2 }, { 0, -2 }, { 1, -2 }, { 1, -1 }, { 1, 0 }, { 1, 1 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 2, -1 }, { 3, -1 }, { 3, 0 }, { 3, 1 }, { 2, 1 }, { 1, 1 }, { 0, 1 } },

		{ { 0, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 }, { 2, 0 }, { 2, -1 }, { 2, -2 }, { 1, -2 }, { 1, -1 }, { 1, 0 } },
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 }, { 3, 1 }, { 3, 2 }, { 2, 2 }, { 1, 2 }, { 0, 2 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 }, { 0, 2 }, { 0, 3 }, { -1, 3 }, { -1, 2 }, { -1, 1 }, { -1, 0 } },
		{ { 0, 0 }, { -1, 0 }, { -2, 0 }, { -2, -1 }, { -1, -1 }, { 0, -1 }, { 1, -1 }, { 1, 0 }, { 1, 1 }, { 0, 1 } },

		{ { 0, 0 }, { 1, 0 }, { 1, -1 }, { 2, -1 }, { 3, -1 }, { 3, 0 }, { 2, 0 }, { 2, 1 }, { 1, 1 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 }, { 2, 2 }, { 2, 3 }, { 1, 3 }, { 1, 2 }, { 0, 2 }, { 0, 1 } },

		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 2, 1 }, { 3, 1 }, { 3, 2 }, { 2, 2 }, { 1, 2 }, { 1, 1 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 0, 2 }, { 0, 3 }, { -1, 3 }, { -1, 2 }, { -1, 1 }, { 0, 1 } },

		{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, { 1, 4 }, { 0, 4 }, { 0, 3 }, { 0, 2 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 }, { 4, 0 }, { 4, 1 }, { 3, 1 }, { 2, 1 }, { 1, 1 }, { 0, 1 } },

		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 2, 1 }, { 2, 2 }, { 1, 2 }, { 0, 2 }, { 0, 1 }, { 0, 0 }, { 0, 0 } },
	};


	int Type;
	float T;		//4*4 ? 8*8?
	float X, Y;
	float SIZEY, SIZEX;

	SIZEX = (w*1.0f) / (pWidth * 1.0f);
	SIZEY = (h*1.0f) / (pHeight * 1.0f);


	for (int i = 0; i < bN; i++){
		Type = bIdx[i];
		X = bPos[i][0] * SIZEX;
		Y = bPos[i][1] * SIZEY;

		//if (Type == 0 || Type == 7)
		//	continue;

		glColor3f(0.5, 0, 0);
		glLineWidth(1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(X + blockLine[Type][0][0] * SIZEX, Y + blockLine[Type][0][1] * SIZEY);
		glVertex2f(X + blockLine[Type][1][0] * SIZEX, Y + blockLine[Type][1][1] * SIZEY);
		glVertex2f(X + blockLine[Type][2][0] * SIZEX, Y + blockLine[Type][2][1] * SIZEY);
		glVertex2f(X + blockLine[Type][3][0] * SIZEX, Y + blockLine[Type][3][1] * SIZEY);
		glVertex2f(X + blockLine[Type][4][0] * SIZEX, Y + blockLine[Type][4][1] * SIZEY);
		glVertex2f(X + blockLine[Type][5][0] * SIZEX, Y + blockLine[Type][5][1] * SIZEY);
		glVertex2f(X + blockLine[Type][6][0] * SIZEX, Y + blockLine[Type][6][1] * SIZEY);
		glVertex2f(X + blockLine[Type][7][0] * SIZEX, Y + blockLine[Type][7][1] * SIZEY);
		glVertex2f(X + blockLine[Type][8][0] * SIZEX, Y + blockLine[Type][8][1] * SIZEY);
		glVertex2f(X + blockLine[Type][9][0] * SIZEX, Y + blockLine[Type][9][1] * SIZEY);

		glEnd();
	}

	int i, j;
	V2DI sp;

	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {

			sp[0] = (pWidth * i) / w;
			sp[1] = (pHeight * j) / h;

			glColor3fv(BPcolor[sp[0]][sp[1]]);
			glRecti(i, j, i + 1, j + 1);
		}
	}
}

