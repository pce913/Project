#include <stdio.h>
#include <iostream>
#include <math.h>
#include "vmg_math.h"
#include <GL/glut.h>
#include "dir.h"
using namespace std;

class block{

public:
	int bType; // block�� ����(TLJSZIO)
	int bDirect; // block�� ȸ������
	int bRange[4][2]; // block�� ���

public:
	void init();
	void setBlock(int type, int direct, int range[4][2]);
};

class tile{

public:
	int bN; // tile�� �ִ� block�� ����
	// n = wN*hN/4;
	int tWN; // ���α���
	int tHN; // ���α���

	int* bIdx;//block�� �ε���
	int** bPos;//tile������ block�� ��ġ
	int* bColIdx;

public:
	void setTile(int wN, int hN);
};

class bigPicture
{

	int tN;				//tile�� ����
	int pWidth;			//�ȼ��� ����
	int pHeight;		//�ȼ��� ����
	int* tIdx;			//tile�� �ε���
	int** tPos;			//picture������ tile�� ��ġ
	float length;

	int bN;				//����� ����� ����
	int* bIdx;			//����� �ε���(Ÿ��)
	int ** bPos;		//picture������ ����� ��ġ
	int* bColor;		//����� ����
	int** BP;			//����ε����� ����� �ȼ���� �������
	V3DF** BPcolor;		//��ϸ�� ������ ����� �ȼ���� �������


	int* origbIdx;			//����� �ε���(Ÿ��) ���� �Ǳ� �� �ʱ�ȭ
	int ** origbPos;		//picture������ ����� ��ġ ���� �Ǳ� �� �ʱ�ȭ
	int* origbColor;		//����� ���� ���� �Ǳ� �� �ʱ�ȭ
	int** origBP;			//����ε����� ����� �ȼ���� ������� ���� �Ǳ� �� �ʱ�ȭ ���
	V3DF** origBPcolor;		//��ϸ�� ������ ����� �ȼ���� ������� ���� �Ǳ� �� �ʱ�ȭ ���




public:
	block bS[19];
	void setBlockSet(block bS[]); // ������ �� �����ؼ� blockSet�� �ʱ�ȭ

	tile tS[36];
	void setTileSet(tile tS[]);


	//-------------------------------------------------------------------------------------
	//Ÿ�ϸ� (�ʱ�ȭ)

	void init(int w, int h);
	void getNumOfTile();
	void getNumOfBlock();
	void OrigBLtoBP();
	void BLtoBP();				//����Ʈ�� ����� ����� �ȼ������� ���� <int> BP, <V3DF> BPcolor
	void BPcolorMatching(int** PIXcolor);	//���ϰ� �ȼ����̼� ����� ���Ͽ� ��Ͽ� �Ҵ�


	void getNumOfTile8();
	void getNumOfBlock8();
	//void BLtoBP8();				//����Ʈ�� ����� ����� �ȼ������� ���� <int> BP, <V3DF> BPcolor
	//void BPcolorMatching8(int** PIXcolor);	//���ϰ� �ȼ����̼� ����� ���Ͽ� ��Ͽ� �Ҵ�
	void getNumBlk();				//������� ���� ���� ���


	void printBP();

	//-------------------------------------------------------------------------------------
	//����

	int MAXELN = 304;				//����Ʈ ����
	int** exchangeList;		//���� ���2�� ����ε��� ���� ����Ʈ
	int** exchangeListPos;	//���� ���2���� ��ġ ����
	float** exchangeListMatchPos; //���� ���2���� ��Ī ��ġ ���� (160908yj)
	float** exchangeListDir;	  //���� ���2���� �������� 

	//152��
	void setExchangeList(int** list);	//���� ��� 2�� ��� �ε��� ����, �Ҵ�
	void setList(int* arr, int* temp);	//setExchangeList���� �� ��Ͻ� �����ϴ� �Լ�
	void setExchangeListPos(int **list);//���� ��� 2�� ��� ��ġ ����
	void setExchangeListMatchPos(float **list);//���� ���2���� ��Ī ��ġ ���� (160908yj)
	void setExchangeListDir(float **list);

	void findBlock();	//exchangelist�� ����� BP���� ã�´�. 
	void findBlockVerNew(int _x, int _y); // ���� findBlock�Լ����� ��� �ȼ��� ���ؼ� �ϵ����Ϸ��� ���� 

	int pickIdx;		//�����ϰ� ���� ��ǥ�� ����� �ε���
	int closeIdx[4];	//0:right 1:left 2:up 3:down
	int closePickIdx;	//�����ϰ� ���� ��ǥ�� ���� �ٲ��� ��� �ε���
	int isFIND;			//���Ұ����� ��� ���� ã�Ҵ���?

	int swapIdx;			//���� ������ ��� �� �ε���
	int swapRb;				//���� ������ ��� �� ��

	void swapBlock(int** BPPXcolor);	//��� ������������������������������
	void swapBlockVerNew(V3DF **dir, int** BPPXcolor, int w, int h);

	//-------------------------------------------------------------------------------------
	//���

	//orig�Լ��� - Ÿ�ϸ����� �ʱ�ȭ�� ���� �Ǳ� �� ����� �׸�
	void draw_orig_output(int w, int h);
	void draw_orig_outputLine(int w, int h);
	void draw_orig_outputTileLine(int w, int h);		//Ÿ���� ������ �׸�	
	void draw_orig_outputBlockLine(int w, int h);
	void draw_pick_output(int w, int h);
	void draw_pick_outputBlockLine(int w, int h);		//�����ϰ� ���� ����� �׸��� ���� �Լ�
};

//4x4�� 0~15
//8x8�� 16~18