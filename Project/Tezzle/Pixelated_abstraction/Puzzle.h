#include <stdio.h>
#include <iostream>
#include <math.h>
#include "vmg_math.h"
#include <GL/glut.h>
#include "dir.h"
using namespace std;

class block{

public:
	int bType; // block의 유형(TLJSZIO)
	int bDirect; // block의 회전방향
	int bRange[4][2]; // block의 모양

public:
	void init();
	void setBlock(int type, int direct, int range[4][2]);
};

class tile{

public:
	int bN; // tile에 있는 block의 개수
	// n = wN*hN/4;
	int tWN; // 가로길이
	int tHN; // 세로길이

	int* bIdx;//block의 인덱스
	int** bPos;//tile에서의 block의 위치
	int* bColIdx;

public:
	void setTile(int wN, int hN);
};

class bigPicture
{

	int tN;				//tile의 개수
	int pWidth;			//픽셀의 가로
	int pHeight;		//픽셀의 세로
	int* tIdx;			//tile의 인덱스
	int** tPos;			//picture에서의 tile의 위치
	float length;

	int bN;				//저장된 블록의 개수
	int* bIdx;			//블록의 인덱스(타입)
	int ** bPos;		//picture에서의 블록의 위치
	int* bColor;		//블록의 색상
	int** BP;			//블록인덱스가 저장될 픽셀모양 저장공간
	V3DF** BPcolor;		//블록모양 색상이 저장될 픽셀모양 저장공간


	int* origbIdx;			//블록의 인덱스(타입) 스왑 되기 전 초기화
	int ** origbPos;		//picture에서의 블록의 위치 스왑 되기 전 초기화
	int* origbColor;		//블록의 색상 스왑 되기 전 초기화
	int** origBP;			//블록인덱스가 저장된 픽셀모양 저장공간 스왑 되기 전 초기화 모양
	V3DF** origBPcolor;		//블록모양 색상이 저장될 픽셀모양 저장공간 스왑 되기 전 초기화 모양




public:
	block bS[19];
	void setBlockSet(block bS[]); // 시작할 때 실행해서 blockSet을 초기화

	tile tS[36];
	void setTileSet(tile tS[]);


	//-------------------------------------------------------------------------------------
	//타일링 (초기화)

	void init(int w, int h);
	void getNumOfTile();
	void getNumOfBlock();
	void OrigBLtoBP();
	void BLtoBP();				//리스트로 저장된 블록을 픽셀공간에 저장 <int> BP, <V3DF> BPcolor
	void BPcolorMatching(int** PIXcolor);	//볼록과 픽셀레이션 결과를 비교하여 블록에 할당


	void getNumOfTile8();
	void getNumOfBlock8();
	//void BLtoBP8();				//리스트로 저장된 블록을 픽셀공간에 저장 <int> BP, <V3DF> BPcolor
	//void BPcolorMatching8(int** PIXcolor);	//볼록과 픽셀레이션 결과를 비교하여 블록에 할당
	void getNumBlk();				//블록종류 갯수 새서 출력


	void printBP();

	//-------------------------------------------------------------------------------------
	//스왑

	int MAXELN = 304;				//리스트 길이
	int** exchangeList;		//스왑 블록2쌍 블록인덱스 저장 리스트
	int** exchangeListPos;	//스왑 블록2쌍의 위치 저장
	float** exchangeListMatchPos; //스왑 블록2쌍의 매칭 위치 저장 (160908yj)
	float** exchangeListDir;	  //스왑 블록2쌍의 엣지방향 

	//152개
	void setExchangeList(int** list);	//스왑 블록 2쌍 블록 인덱스 생성, 할당
	void setList(int* arr, int* temp);	//setExchangeList에서 각 블록쌍 저장하는 함수
	void setExchangeListPos(int **list);//스왑 블록 2쌍 블록 위치 저장
	void setExchangeListMatchPos(float **list);//스왑 블록2쌍의 매칭 위치 저장 (160908yj)
	void setExchangeListDir(float **list);

	void findBlock();	//exchangelist의 블록을 BP에서 찾는다. 
	void findBlockVerNew(int _x, int _y); // 기존 findBlock함수에서 모든 픽셀에 대해서 하도록하려고 만듬 

	int pickIdx;		//랜덤하게 찍힌 좌표의 블록의 인덱스
	int closeIdx[4];	//0:right 1:left 2:up 3:down
	int closePickIdx;	//랜덤하게 찍힌 좌표랑 같이 바껴질 블록 인덱스
	int isFIND;			//스왑가능한 블록 쌍을 찾았는지?

	int swapIdx;			//스왑 가능한 블록 쌍 인덱스
	int swapRb;				//스왑 가능한 블록 쌍 라벨

	void swapBlock(int** BPPXcolor);	//블록 벼벼여여벼여벼영벼여벼영여연경
	void swapBlockVerNew(V3DF **dir, int** BPPXcolor, int w, int h);

	//-------------------------------------------------------------------------------------
	//출력

	//orig함수들 - 타일링으로 초기화된 스왑 되기 전 모양을 그림
	void draw_orig_output(int w, int h);
	void draw_orig_outputLine(int w, int h);
	void draw_orig_outputTileLine(int w, int h);		//타일의 범위를 그림	
	void draw_orig_outputBlockLine(int w, int h);
	void draw_pick_output(int w, int h);
	void draw_pick_outputBlockLine(int w, int h);		//랜덤하게 찍은 블록을 그리기 위한 함수
};

//4x4는 0~15
//8x8은 16~18