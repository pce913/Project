#include "stdafx.h"
#include "Puzzle.h"
#include <ctime>
using namespace std;

//=======================================================
// 각종 데이터 세트 할당함
//=======================================================


void block::init()
{
	bType = -1;

	bDirect = -1;


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			bRange[i][j] = -1;
		}
	}

}

void block::setBlock(int type, int direct, int range[4][2])
{
	bType = type;

	bDirect = direct;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			bRange[i][j] = range[i][j];
		}
	}

}

void bigPicture::setBlockSet(block bS[])
{
	//T
	bS[0].bType = 0;
	bS[0].bDirect = 0;
	bS[0].bRange[0][0] = 0;
	bS[0].bRange[0][1] = 0;
	bS[0].bRange[1][0] = 1;
	bS[0].bRange[1][1] = 0;
	bS[0].bRange[2][0] = 2;
	bS[0].bRange[2][1] = 0;
	bS[0].bRange[3][0] = 1;
	bS[0].bRange[3][1] = 1;

	bS[1].bType = 0;
	bS[1].bDirect = 1;
	bS[1].bRange[0][0] = 0;
	bS[1].bRange[0][1] = 0;
	bS[1].bRange[1][0] = 0;
	bS[1].bRange[1][1] = 1;
	bS[1].bRange[2][0] = 0;
	bS[1].bRange[2][1] = 2;
	bS[1].bRange[3][0] = -1;
	bS[1].bRange[3][1] = 1;

	bS[2].bType = 0;
	bS[2].bDirect = 2;
	bS[2].bRange[0][0] = 0;
	bS[2].bRange[0][1] = 0;
	bS[2].bRange[1][0] = -1;
	bS[2].bRange[1][1] = 0;
	bS[2].bRange[2][0] = -2;
	bS[2].bRange[2][1] = 0;
	bS[2].bRange[3][0] = -1;
	bS[2].bRange[3][1] = -1;

	bS[3].bType = 0;
	bS[3].bDirect = 3;
	bS[3].bRange[0][0] = 0;
	bS[3].bRange[0][1] = 0;
	bS[3].bRange[1][0] = 0;
	bS[3].bRange[1][1] = -1;
	bS[3].bRange[2][0] = 0;
	bS[3].bRange[2][1] = -2;
	bS[3].bRange[3][0] = 1;
	bS[3].bRange[3][1] = -1;

	//L
	bS[4].bType = 1;
	bS[4].bDirect = 0;
	bS[4].bRange[0][0] = 0;
	bS[4].bRange[0][1] = 0;
	bS[4].bRange[1][0] = 0;
	bS[4].bRange[1][1] = 1;
	bS[4].bRange[2][0] = 0;
	bS[4].bRange[2][1] = 2;
	bS[4].bRange[3][0] = 1;
	bS[4].bRange[3][1] = 2;

	bS[5].bType = 1;
	bS[5].bDirect = 1;
	bS[5].bRange[0][0] = 0;
	bS[5].bRange[0][1] = 0;
	bS[5].bRange[1][0] = -1;
	bS[5].bRange[1][1] = 0;
	bS[5].bRange[2][0] = -2;
	bS[5].bRange[2][1] = 0;
	bS[5].bRange[3][0] = -2;
	bS[5].bRange[3][1] = 1;

	bS[6].bType = 1;
	bS[6].bDirect = 2;
	bS[6].bRange[0][0] = 0;
	bS[6].bRange[0][1] = 0;
	bS[6].bRange[1][0] = 0;
	bS[6].bRange[1][1] = -1;
	bS[6].bRange[2][0] = 0;
	bS[6].bRange[2][1] = -2;
	bS[6].bRange[3][0] = -1;
	bS[6].bRange[3][1] = -2;

	bS[7].bType = 1;
	bS[7].bDirect = 3;
	bS[7].bRange[0][0] = 0;
	bS[7].bRange[0][1] = 0;
	bS[7].bRange[1][0] = 1;
	bS[7].bRange[1][1] = 0;
	bS[7].bRange[2][0] = 2;
	bS[7].bRange[2][1] = 0;
	bS[7].bRange[3][0] = 2;
	bS[7].bRange[3][1] = -1;

	//J
	bS[8].bType = 2;
	bS[8].bDirect = 0;
	bS[8].bRange[0][0] = 0;
	bS[8].bRange[0][1] = 0;
	bS[8].bRange[1][0] = 1;
	bS[8].bRange[1][1] = 0;
	bS[8].bRange[2][0] = 1;
	bS[8].bRange[2][1] = -1;
	bS[8].bRange[3][0] = 1;
	bS[8].bRange[3][1] = -2;

	bS[9].bType = 2;
	bS[9].bDirect = 1;
	bS[9].bRange[0][0] = 0;
	bS[9].bRange[0][1] = 0;
	bS[9].bRange[1][0] = 0;
	bS[9].bRange[1][1] = 1;
	bS[9].bRange[2][0] = 1;
	bS[9].bRange[2][1] = 1;
	bS[9].bRange[3][0] = 2;
	bS[9].bRange[3][1] = 1;

	bS[10].bType = 2;
	bS[10].bDirect = 2;
	bS[10].bRange[0][0] = 0;
	bS[10].bRange[0][1] = 0;
	bS[10].bRange[1][0] = -1;
	bS[10].bRange[1][1] = 0;
	bS[10].bRange[2][0] = -1;
	bS[10].bRange[2][1] = 1;
	bS[10].bRange[3][0] = -1;
	bS[10].bRange[3][1] = 2;

	bS[11].bType = 2;
	bS[11].bDirect = 3;
	bS[11].bRange[0][0] = 0;
	bS[11].bRange[0][1] = 0;
	bS[11].bRange[1][0] = 0;
	bS[11].bRange[1][1] = -1;
	bS[11].bRange[2][0] = -1;
	bS[11].bRange[2][1] = -1;
	bS[11].bRange[3][0] = -2;
	bS[11].bRange[3][1] = -1;

	//S
	bS[12].bType = 3;
	bS[12].bDirect = 0;
	bS[12].bRange[0][0] = 0;
	bS[12].bRange[0][1] = 0;
	bS[12].bRange[1][0] = 1;
	bS[12].bRange[1][1] = 0;
	bS[12].bRange[2][0] = 1;
	bS[12].bRange[2][1] = -1;
	bS[12].bRange[3][0] = 2;
	bS[12].bRange[3][1] = -1;

	bS[13].bType = 3;
	bS[13].bDirect = 1;
	bS[13].bRange[0][0] = 0;
	bS[13].bRange[0][1] = 0;
	bS[13].bRange[1][0] = 0;
	bS[13].bRange[1][1] = 1;
	bS[13].bRange[2][0] = 1;
	bS[13].bRange[2][1] = 1;
	bS[13].bRange[3][0] = 1;
	bS[13].bRange[3][1] = 2;

	//Z
	bS[14].bType = 4;
	bS[14].bDirect = 0;
	bS[14].bRange[0][0] = 0;
	bS[14].bRange[0][1] = 0;
	bS[14].bRange[1][0] = 1;
	bS[14].bRange[1][1] = 0;
	bS[14].bRange[2][0] = 1;
	bS[14].bRange[2][1] = 1;
	bS[14].bRange[3][0] = 2;
	bS[14].bRange[3][1] = 1;

	bS[15].bType = 4;
	bS[15].bDirect = 1;
	bS[15].bRange[0][0] = 0;
	bS[15].bRange[0][1] = 0;
	bS[15].bRange[1][0] = 0;
	bS[15].bRange[1][1] = 1;
	bS[15].bRange[2][0] = -1;
	bS[15].bRange[2][1] = 1;
	bS[15].bRange[3][0] = -1;
	bS[15].bRange[3][1] = 2;

	//I
	bS[16].bType = 5;
	bS[16].bDirect = 0;
	bS[16].bRange[0][0] = 0;
	bS[16].bRange[0][1] = 0;
	bS[16].bRange[1][0] = 0;
	bS[16].bRange[1][1] = 1;
	bS[16].bRange[2][0] = 0;
	bS[16].bRange[2][1] = 2;
	bS[16].bRange[3][0] = 0;
	bS[16].bRange[3][1] = 3;

	bS[17].bType = 5;
	bS[17].bDirect = 1;
	bS[17].bRange[0][0] = 0;
	bS[17].bRange[0][1] = 0;
	bS[17].bRange[1][0] = 1;
	bS[17].bRange[1][1] = 0;
	bS[17].bRange[2][0] = 2;
	bS[17].bRange[2][1] = 0;
	bS[17].bRange[3][0] = 3;
	bS[17].bRange[3][1] = 0;

	//O
	bS[18].bType = 5;
	bS[18].bDirect = 0;
	bS[18].bRange[0][0] = 0;
	bS[18].bRange[0][1] = 0;
	bS[18].bRange[1][0] = 1;
	bS[18].bRange[1][1] = 0;
	bS[18].bRange[2][0] = 0;
	bS[18].bRange[2][1] = 1;
	bS[18].bRange[3][0] = 1;
	bS[18].bRange[3][1] = 1;
}

void tile::setTile(int wN, int hN)
{
	tWN = wN;
	tHN = hN;
	bN = (tWN * tHN) / 4;

	bIdx = new int[bN];
	bPos = new int*[bN];
	bColIdx = new int[bN];
	for (int i = 0; i < bN; i++)
	{
		bPos[i] = new int[2];
	}
}

void bigPicture::setTileSet(tile tS[])
{
	// 4x4
	//1
	tS[0].tWN = 4;
	tS[0].tHN = 4;
	tS[0].setTile(tS[0].tWN, tS[0].tHN);
	tS[0].bIdx[0] = 16;
	tS[0].bIdx[1] = 16;
	tS[0].bIdx[2] = 16;
	tS[0].bIdx[3] = 16;

	tS[0].bPos[0][0] = 0;
	tS[0].bPos[0][1] = 0;

	tS[0].bPos[1][0] = 1;
	tS[0].bPos[1][1] = 0;

	tS[0].bPos[2][0] = 2;
	tS[0].bPos[2][1] = 0;

	tS[0].bPos[3][0] = 3;
	tS[0].bPos[3][1] = 0;

	//2
	tS[1].tWN = 4;
	tS[1].tHN = 4;
	tS[1].setTile(tS[1].tWN, tS[1].tHN);
	tS[1].bIdx[0] = 18;
	tS[1].bIdx[1] = 18;
	tS[1].bIdx[2] = 18;
	tS[1].bIdx[3] = 18;


	tS[1].bPos[0][0] = 0;
	tS[1].bPos[0][1] = 0;

	tS[1].bPos[1][0] = 2;
	tS[1].bPos[1][1] = 0;

	tS[1].bPos[2][0] = 0;
	tS[1].bPos[2][1] = 2;

	tS[1].bPos[3][0] = 2;
	tS[1].bPos[3][1] = 2;

	//3
	tS[2].tWN = 4;
	tS[2].tHN = 4;
	tS[2].setTile(tS[2].tWN, tS[2].tHN);
	tS[2].bIdx[0] = 0;
	tS[2].bIdx[1] = 1;
	tS[2].bIdx[2] = 2;
	tS[2].bIdx[3] = 3;


	tS[2].bPos[0][0] = 0;
	tS[2].bPos[0][1] = 0;

	tS[2].bPos[1][0] = 3;
	tS[2].bPos[1][1] = 0;

	tS[2].bPos[2][0] = 3;
	tS[2].bPos[2][1] = 3;

	tS[2].bPos[3][0] = 0;
	tS[2].bPos[3][1] = 3;

	//4
	tS[3].tWN = 4;
	tS[3].tHN = 4;
	tS[3].setTile(tS[3].tWN, tS[3].tHN);
	tS[3].bIdx[0] = 18;
	tS[3].bIdx[1] = 6;
	tS[3].bIdx[2] = 7;
	tS[3].bIdx[3] = 17;


	tS[3].bPos[0][0] = 0;
	tS[3].bPos[0][1] = 0;

	tS[3].bPos[1][0] = 3;
	tS[3].bPos[1][1] = 2;

	tS[3].bPos[2][0] = 0;
	tS[3].bPos[2][1] = 2;

	tS[3].bPos[3][0] = 0;
	tS[3].bPos[3][1] = 3;

	//5
	tS[4].tWN = 4;
	tS[4].tHN = 4;
	tS[4].setTile(tS[4].tWN, tS[4].tHN);
	tS[4].bIdx[0] = 5;
	tS[4].bIdx[1] = 7;
	tS[4].bIdx[2] = 5;
	tS[4].bIdx[3] = 7;


	tS[4].bPos[0][0] = 2;
	tS[4].bPos[0][1] = 0;

	tS[4].bPos[1][0] = 1;
	tS[4].bPos[1][1] = 1;

	tS[4].bPos[2][0] = 2;
	tS[4].bPos[2][1] = 2;

	tS[4].bPos[3][0] = 1;
	tS[4].bPos[3][1] = 3;

	//6
	tS[5].tWN = 4;
	tS[5].tHN = 4;
	tS[5].setTile(tS[5].tWN, tS[5].tHN);
	tS[5].bIdx[0] = 9;
	tS[5].bIdx[1] = 11;
	tS[5].bIdx[2] = 9;
	tS[5].bIdx[3] = 11;


	tS[5].bPos[0][0] = 0;
	tS[5].bPos[0][1] = 0;

	tS[5].bPos[1][0] = 3;
	tS[5].bPos[1][1] = 1;

	tS[5].bPos[2][0] = 0;
	tS[5].bPos[2][1] = 2;

	tS[5].bPos[3][0] = 3;
	tS[5].bPos[3][1] = 3;

	//7
	tS[6].tWN = 4;
	tS[6].tHN = 4;
	tS[6].setTile(tS[6].tWN, tS[6].tHN);
	tS[6].bIdx[0] = 3;
	tS[6].bIdx[1] = 0;
	tS[6].bIdx[2] = 1;
	tS[6].bIdx[3] = 2;


	tS[6].bPos[0][0] = 0;
	tS[6].bPos[0][1] = 2;

	tS[6].bPos[1][0] = 1;
	tS[6].bPos[1][1] = 0;

	tS[6].bPos[2][0] = 3;
	tS[6].bPos[2][1] = 1;

	tS[6].bPos[3][0] = 2;
	tS[6].bPos[3][1] = 3;

	//8
	tS[7].tWN = 4;
	tS[7].tHN = 4;
	tS[7].setTile(tS[7].tWN, tS[7].tHN);
	tS[7].bIdx[0] = 17;
	tS[7].bIdx[1] = 18;
	tS[7].bIdx[2] = 6;
	tS[7].bIdx[3] = 7;


	tS[7].bPos[0][0] = 0;
	tS[7].bPos[0][1] = 0;

	tS[7].bPos[1][0] = 0;
	tS[7].bPos[1][1] = 1;

	tS[7].bPos[2][0] = 3;
	tS[7].bPos[2][1] = 3;

	tS[7].bPos[3][0] = 0;
	tS[7].bPos[3][1] = 3;

	//9
	tS[8].tWN = 4;
	tS[8].tHN = 4;
	tS[8].setTile(tS[8].tWN, tS[8].tHN);
	tS[8].bIdx[0] = 17;
	tS[8].bIdx[1] = 5;
	tS[8].bIdx[2] = 7;
	tS[8].bIdx[3] = 17;



	tS[8].bPos[0][0] = 0;
	tS[8].bPos[0][1] = 0;

	tS[8].bPos[1][0] = 2;
	tS[8].bPos[1][1] = 1;

	tS[8].bPos[2][0] = 1;
	tS[8].bPos[2][1] = 2;

	tS[8].bPos[3][0] = 0;
	tS[8].bPos[3][1] = 3;



	//10
	tS[9].tWN = 4;
	tS[9].tHN = 4;
	tS[9].setTile(tS[9].tWN, tS[9].tHN);
	tS[9].bIdx[0] = 17;
	tS[9].bIdx[1] = 9;
	tS[9].bIdx[2] = 11;
	tS[9].bIdx[3] = 17;



	tS[9].bPos[0][0] = 0;
	tS[9].bPos[0][1] = 0;

	tS[9].bPos[1][0] = 0;
	tS[9].bPos[1][1] = 1;

	tS[9].bPos[2][0] = 3;
	tS[9].bPos[2][1] = 2;

	tS[9].bPos[3][0] = 0;
	tS[9].bPos[3][1] = 3;

	//11
	tS[10].tWN = 4;
	tS[10].tHN = 4;
	tS[10].setTile(tS[10].tWN, tS[10].tHN);
	tS[10].bIdx[0] = 10;
	tS[10].bIdx[1] = 18;
	tS[10].bIdx[2] = 9;
	tS[10].bIdx[3] = 17;



	tS[10].bPos[0][0] = 1;
	tS[10].bPos[0][1] = 0;

	tS[10].bPos[1][0] = 2;
	tS[10].bPos[1][1] = 0;

	tS[10].bPos[2][0] = 1;
	tS[10].bPos[2][1] = 1;

	tS[10].bPos[3][0] = 0;
	tS[10].bPos[3][1] = 3;

	//12
	tS[11].tWN = 4;
	tS[11].tHN = 4;
	tS[11].setTile(tS[11].tWN, tS[11].tHN);
	tS[11].bIdx[0] = 17;
	tS[11].bIdx[1] = 18;
	tS[11].bIdx[2] = 18;
	tS[11].bIdx[3] = 17;



	tS[11].bPos[0][0] = 0;
	tS[11].bPos[0][1] = 0;

	tS[11].bPos[1][0] = 0;
	tS[11].bPos[1][1] = 1;

	tS[11].bPos[2][0] = 2;
	tS[11].bPos[2][1] = 1;

	tS[11].bPos[3][0] = 0;
	tS[11].bPos[3][1] = 3;

	//13
	tS[12].tWN = 4;
	tS[12].tHN = 4;
	tS[12].setTile(tS[12].tWN, tS[12].tHN);
	tS[12].bIdx[0] = 5;
	tS[12].bIdx[1] = 7;
	tS[12].bIdx[2] = 17;
	tS[12].bIdx[3] = 17;



	tS[12].bPos[0][0] = 2;
	tS[12].bPos[0][1] = 0;

	tS[12].bPos[1][0] = 1;
	tS[12].bPos[1][1] = 1;

	tS[12].bPos[2][0] = 0;
	tS[12].bPos[2][1] = 2;

	tS[12].bPos[3][0] = 0;
	tS[12].bPos[3][1] = 3;

	//14
	tS[13].tWN = 4;
	tS[13].tHN = 4;
	tS[13].setTile(tS[13].tWN, tS[13].tHN);
	tS[13].bIdx[0] = 9;
	tS[13].bIdx[1] = 11;
	tS[13].bIdx[2] = 17;
	tS[13].bIdx[3] = 17;



	tS[13].bPos[0][0] = 0;
	tS[13].bPos[0][1] = 0;

	tS[13].bPos[1][0] = 3;
	tS[13].bPos[1][1] = 1;

	tS[13].bPos[2][0] = 0;
	tS[13].bPos[2][1] = 2;

	tS[13].bPos[3][0] = 0;
	tS[13].bPos[3][1] = 3;

	//15
	tS[14].tWN = 4;
	tS[14].tHN = 4;
	tS[14].setTile(tS[14].tWN, tS[14].tHN);
	tS[14].bIdx[0] = 5;
	tS[14].bIdx[1] = 1;
	tS[14].bIdx[2] = 15;
	tS[14].bIdx[3] = 2;



	tS[14].bPos[0][0] = 2;
	tS[14].bPos[0][1] = 0;

	tS[14].bPos[1][0] = 3;
	tS[14].bPos[1][1] = 0;

	tS[14].bPos[2][0] = 1;
	tS[14].bPos[2][1] = 1;

	tS[14].bPos[3][0] = 3;
	tS[14].bPos[3][1] = 3;

	//16
	tS[15].tWN = 4;
	tS[15].tHN = 4;
	tS[15].setTile(tS[15].tWN, tS[15].tHN);
	tS[15].bIdx[0] = 13;
	tS[15].bIdx[1] = 11;
	tS[15].bIdx[2] = 13;
	tS[15].bIdx[3] = 9;



	tS[15].bPos[0][0] = 0;
	tS[15].bPos[0][1] = 0;

	tS[15].bPos[1][0] = 3;
	tS[15].bPos[1][1] = 1;

	tS[15].bPos[2][0] = 2;
	tS[15].bPos[2][1] = 1;

	tS[15].bPos[3][0] = 0;
	tS[15].bPos[3][1] = 2;

	// 8x8 -------------------------------------------------------------------------------------------
	//17
	tS[16].tWN = 8;
	tS[16].tHN = 8;
	tS[16].setTile(tS[16].tWN, tS[16].tHN);
	tS[16].bIdx[0] = 13;
	tS[16].bIdx[1] = 6;
	tS[16].bIdx[2] = 9;
	tS[16].bIdx[3] = 17;
	tS[16].bIdx[4] = 17;
	tS[16].bIdx[5] = 6;
	tS[16].bIdx[6] = 9;
	tS[16].bIdx[7] = 12;
	tS[16].bIdx[8] = 1;
	tS[16].bIdx[9] = 13;
	tS[16].bIdx[10] = 14;
	tS[16].bIdx[11] = 3;
	tS[16].bIdx[12] = 12;
	tS[16].bIdx[13] = 14;
	tS[16].bIdx[14] = 13;
	tS[16].bIdx[15] = 17;

	tS[16].bPos[0][0] = 0;
	tS[16].bPos[0][1] = 0;

	tS[16].bPos[1][0] = 2;
	tS[16].bPos[1][1] = 2;

	tS[16].bPos[2][0] = 3;
	tS[16].bPos[2][1] = 0;

	tS[16].bPos[3][0] = 4;
	tS[16].bPos[3][1] = 0;

	tS[16].bPos[4][0] = 3;
	tS[16].bPos[4][1] = 2;

	tS[16].bPos[5][0] = 7;
	tS[16].bPos[5][1] = 3;

	tS[16].bPos[6][0] = 0;
	tS[16].bPos[6][1] = 2;

	tS[16].bPos[7][0] = 2;
	tS[16].bPos[7][1] = 4;

	tS[16].bPos[8][0] = 5;
	tS[16].bPos[8][1] = 3;

	tS[16].bPos[9][0] = 6;
	tS[16].bPos[9][1] = 3;

	tS[16].bPos[10][0] = 0;
	tS[16].bPos[10][1] = 4;

	tS[16].bPos[11][0] = 0;
	tS[16].bPos[11][1] = 7;

	tS[16].bPos[12][0] = 1;
	tS[16].bPos[12][1] = 7;

	tS[16].bPos[13][0] = 3;
	tS[16].bPos[13][1] = 5;

	tS[16].bPos[14][0] = 6;
	tS[16].bPos[14][1] = 5;

	tS[16].bPos[15][0] = 3;
	tS[16].bPos[15][1] = 7;

	//18
	tS[17].tWN = 8;
	tS[17].tHN = 8;
	tS[17].setTile(tS[17].tWN, tS[17].tHN);
	tS[17].bIdx[0] = 3;
	tS[17].bIdx[1] = 4;
	tS[17].bIdx[2] = 15;
	tS[17].bIdx[3] = 11;
	tS[17].bIdx[4] = 13;
	tS[17].bIdx[5] = 0;
	tS[17].bIdx[6] = 1;
	tS[17].bIdx[7] = 12;
	tS[17].bIdx[8] = 11;
	tS[17].bIdx[9] = 13;
	tS[17].bIdx[10] = 18;
	tS[17].bIdx[11] = 3;
	tS[17].bIdx[12] = 8;
	tS[17].bIdx[13] = 6;
	tS[17].bIdx[14] = 9;
	tS[17].bIdx[15] = 8;

	tS[17].bPos[0][0] = 0;
	tS[17].bPos[0][1] = 2;

	tS[17].bPos[1][0] = 0;
	tS[17].bPos[1][1] = 3;

	tS[17].bPos[2][0] = 2;
	tS[17].bPos[2][1] = 1;

	tS[17].bPos[3][0] = 3;
	tS[17].bPos[3][1] = 1;

	tS[17].bPos[4][0] = 4;
	tS[17].bPos[4][1] = 0;

	tS[17].bPos[5][0] = 5;
	tS[17].bPos[5][1] = 0;

	tS[17].bPos[6][0] = 7;
	tS[17].bPos[6][1] = 1;

	tS[17].bPos[7][0] = 2;
	tS[17].bPos[7][1] = 3;

	tS[17].bPos[8][0] = 3;
	tS[17].bPos[8][1] = 5;

	tS[17].bPos[9][0] = 4;
	tS[17].bPos[9][1] = 3;

	tS[17].bPos[10][0] = 0;
	tS[17].bPos[10][1] = 6;

	tS[17].bPos[11][0] = 2;
	tS[17].bPos[11][1] = 7;

	tS[17].bPos[12][0] = 3;
	tS[17].bPos[12][1] = 7;

	tS[17].bPos[13][0] = 6;
	tS[17].bPos[13][1] = 5;

	tS[17].bPos[14][0] = 5;
	tS[17].bPos[14][1] = 6;

	tS[17].bPos[15][0] = 6;
	tS[17].bPos[15][1] = 6;

	//19
	tS[18].tWN = 8;
	tS[18].tHN = 8;
	tS[18].setTile(tS[18].tWN, tS[18].tHN);
	tS[18].bIdx[0] = 3;
	tS[18].bIdx[1] = 4;
	tS[18].bIdx[2] = 15;
	tS[18].bIdx[3] = 11;
	tS[18].bIdx[4] = 13;
	tS[18].bIdx[5] = 0;
	tS[18].bIdx[6] = 1;
	tS[18].bIdx[7] = 12;
	tS[18].bIdx[8] = 11;
	tS[18].bIdx[9] = 13;
	tS[18].bIdx[10] = 18;
	tS[18].bIdx[11] = 3;
	tS[18].bIdx[12] = 8;
	tS[18].bIdx[13] = 6;
	tS[18].bIdx[14] = 18;
	tS[18].bIdx[15] = 16;

	tS[18].bPos[0][0] = 0;
	tS[18].bPos[0][1] = 2;

	tS[18].bPos[1][0] = 0;
	tS[18].bPos[1][1] = 3;

	tS[18].bPos[2][0] = 2;
	tS[18].bPos[2][1] = 1;

	tS[18].bPos[3][0] = 3;
	tS[18].bPos[3][1] = 1;

	tS[18].bPos[4][0] = 4;
	tS[18].bPos[4][1] = 0;

	tS[18].bPos[5][0] = 5;
	tS[18].bPos[5][1] = 0;

	tS[18].bPos[6][0] = 7;
	tS[18].bPos[6][1] = 1;

	tS[18].bPos[7][0] = 2;
	tS[18].bPos[7][1] = 3;

	tS[18].bPos[8][0] = 3;
	tS[18].bPos[8][1] = 5;

	tS[18].bPos[9][0] = 4;
	tS[18].bPos[9][1] = 3;

	tS[18].bPos[10][0] = 0;
	tS[18].bPos[10][1] = 6;

	tS[18].bPos[11][0] = 2;
	tS[18].bPos[11][1] = 7;

	tS[18].bPos[12][0] = 3;
	tS[18].bPos[12][1] = 7;

	tS[18].bPos[13][0] = 6;
	tS[18].bPos[13][1] = 5;

	tS[18].bPos[14][0] = 5;
	tS[18].bPos[14][1] = 6;

	tS[18].bPos[15][0] = 7;
	tS[18].bPos[15][1] = 4;

	// 20 -----------------------------------------------------------------------------------------------------------------------------
	tS[19].tWN = 8;
	tS[19].tHN = 8;
	tS[19].setTile(tS[19].tWN, tS[19].tHN);
	tS[19].bIdx[0] = 5;
	tS[19].bIdx[1] = 10;
	tS[19].bIdx[2] = 1;
	tS[19].bIdx[3] = 12;
	tS[19].bIdx[4] = 12;
	tS[19].bIdx[5] = 16;
	tS[19].bIdx[6] = 15;
	tS[19].bIdx[7] = 18;
	tS[19].bIdx[8] = 1;
	tS[19].bIdx[9] = 6;
	tS[19].bIdx[10] = 14;
	tS[19].bIdx[11] = 18;
	tS[19].bIdx[12] = 8;
	tS[19].bIdx[13] = 9;
	tS[19].bIdx[14] = 18;
	tS[19].bIdx[15] = 7;

	tS[19].bPos[0][0] = 2;
	tS[19].bPos[0][1] = 0;

	tS[19].bPos[1][0] = 4;
	tS[19].bPos[1][1] = 0;

	tS[19].bPos[2][0] = 7;
	tS[19].bPos[2][1] = 0;

	tS[19].bPos[3][0] = 4;
	tS[19].bPos[3][1] = 1;

	tS[19].bPos[4][0] = 0;
	tS[19].bPos[4][1] = 2;

	tS[19].bPos[5][0] = 2;
	tS[19].bPos[5][1] = 2;

	tS[19].bPos[6][0] = 4;
	tS[19].bPos[6][1] = 2;

	tS[19].bPos[7][0] = 0;
	tS[19].bPos[7][1] = 3;

	tS[19].bPos[8][0] = 5;
	tS[19].bPos[8][1] = 3;

	tS[19].bPos[9][0] = 6;
	tS[19].bPos[9][1] = 4;

	tS[19].bPos[10][0] = 0;
	tS[19].bPos[10][1] = 5;

	tS[19].bPos[11][0] = 3;
	tS[19].bPos[11][1] = 5;

	tS[19].bPos[12][0] = 6;
	tS[19].bPos[12][1] = 5;

	tS[19].bPos[13][0] = 0;
	tS[19].bPos[13][1] = 6;

	tS[19].bPos[14][0] = 6;
	tS[19].bPos[14][1] = 6;

	tS[19].bPos[15][0] = 7;
	tS[19].bPos[15][1] = 3;

	// 21
	tS[20].tWN = 8;
	tS[20].tHN = 8;
	tS[20].setTile(tS[20].tWN, tS[20].tHN);
	tS[20].bIdx[0] = 17;
	tS[20].bIdx[1] = 15;
	tS[20].bIdx[2] = 0;
	tS[20].bIdx[3] = 4;
	tS[20].bIdx[4] = 3;
	tS[20].bIdx[5] = 13;
	tS[20].bIdx[6] = 6;
	tS[20].bIdx[7] = 2;
	tS[20].bIdx[8] = 8;
	tS[20].bIdx[9] = 7;
	tS[20].bIdx[10] = 15;
	tS[20].bIdx[11] = 8;
	tS[20].bIdx[12] = 18;
	tS[20].bIdx[13] = 3;
	tS[20].bIdx[14] = 12;
	tS[20].bIdx[15] = 7;

	tS[20].bPos[0][0] = 0;
	tS[20].bPos[0][1] = 0;

	tS[20].bPos[1][0] = 4;
	tS[20].bPos[1][1] = 0;

	tS[20].bPos[2][0] = 0;
	tS[20].bPos[2][1] = 1;

	tS[20].bPos[3][0] = 0;
	tS[20].bPos[3][1] = 2;

	tS[20].bPos[4][0] = 5;
	tS[20].bPos[4][1] = 2;

	tS[20].bPos[5][0] = 6;
	tS[20].bPos[5][1] = 2;

	tS[20].bPos[6][0] = 7;
	tS[20].bPos[6][1] = 2;

	tS[20].bPos[7][0] = 3;
	tS[20].bPos[7][1] = 3;

	tS[20].bPos[8][0] = 3;
	tS[20].bPos[8][1] = 4;

	tS[20].bPos[9][0] = 0;
	tS[20].bPos[9][1] = 5;

	tS[20].bPos[10][0] = 3;
	tS[20].bPos[10][1] = 5;

	tS[20].bPos[11][0] = 4;
	tS[20].bPos[11][1] = 5;

	tS[20].bPos[12][0] = 0;
	tS[20].bPos[12][1] = 6;

	tS[20].bPos[13][0] = 6;
	tS[20].bPos[13][1] = 6;

	tS[20].bPos[14][0] = 3;
	tS[20].bPos[14][1] = 7;

	tS[20].bPos[15][0] = 5;
	tS[20].bPos[15][1] = 7;
	// 22
	tS[21].tWN = 8;
	tS[21].tHN = 8;
	tS[21].setTile(tS[21].tWN, tS[21].tHN);
	tS[21].bIdx[0] = 0;
	tS[21].bIdx[1] = 18;
	tS[21].bIdx[2] = 10;
	tS[21].bIdx[3] = 1;
	tS[21].bIdx[4] = 16;
	tS[21].bIdx[5] = 15;
	tS[21].bIdx[6] = 14;
	tS[21].bIdx[7] = 18;
	tS[21].bIdx[8] = 3;
	tS[21].bIdx[9] = 1;
	tS[21].bIdx[10] = 2;
	tS[21].bIdx[11] = 18;
	tS[21].bIdx[12] = 12;
	tS[21].bIdx[13] = 6;
	tS[21].bIdx[14] = 7;
	tS[21].bIdx[15] = 2;

	tS[21].bPos[0][0] = 0;
	tS[21].bPos[0][1] = 0;

	tS[21].bPos[1][0] = 3;
	tS[21].bPos[1][1] = 0;

	tS[21].bPos[2][0] = 6;
	tS[21].bPos[2][1] = 0;

	tS[21].bPos[3][0] = 7;
	tS[21].bPos[3][1] = 0;

	tS[21].bPos[4][0] = 0;
	tS[21].bPos[4][1] = 1;

	tS[21].bPos[5][0] = 2;
	tS[21].bPos[5][1] = 1;

	tS[21].bPos[6][0] = 3;
	tS[21].bPos[6][1] = 2;

	tS[21].bPos[7][0] = 2;
	tS[21].bPos[7][1] = 3;

	tS[21].bPos[8][0] = 6;
	tS[21].bPos[8][1] = 4;

	tS[21].bPos[9][0] = 7;
	tS[21].bPos[9][1] = 4;

	tS[21].bPos[10][0] = 2;
	tS[21].bPos[10][1] = 5;

	tS[21].bPos[11][0] = 0;
	tS[21].bPos[11][1] = 6;

	tS[21].bPos[12][0] = 2;
	tS[21].bPos[12][1] = 6;

	tS[21].bPos[13][0] = 5;
	tS[21].bPos[13][1] = 6;

	tS[21].bPos[14][0] = 2;
	tS[21].bPos[14][1] = 7;

	tS[21].bPos[15][0] = 7;
	tS[21].bPos[15][1] = 7;
	// 23
	tS[22].tWN = 8;
	tS[22].tHN = 8;
	tS[22].setTile(tS[22].tWN, tS[22].tHN);
	tS[22].bIdx[0] = 14;
	tS[22].bIdx[1] = 5;
	tS[22].bIdx[2] = 15;
	tS[22].bIdx[3] = 11;
	tS[22].bIdx[4] = 13;
	tS[22].bIdx[5] = 12;
	tS[22].bIdx[6] = 1;
	tS[22].bIdx[7] = 3;
	tS[22].bIdx[8] = 13;
	tS[22].bIdx[9] = 16;
	tS[22].bIdx[10] = 13;
	tS[22].bIdx[11] = 9;
	tS[22].bIdx[12] = 3;
	tS[22].bIdx[13] = 18;
	tS[22].bIdx[14] = 17;
	tS[22].bIdx[15] = 2;

	tS[22].bPos[0][0] = 0;
	tS[22].bPos[0][1] = 0;

	tS[22].bPos[1][0] = 7;
	tS[22].bPos[1][1] = 0;

	tS[22].bPos[2][0] = 3;
	tS[22].bPos[2][1] = 1;

	tS[22].bPos[3][0] = 4;
	tS[22].bPos[3][1] = 1;

	tS[22].bPos[4][0] = 4;
	tS[22].bPos[4][1] = 2;

	tS[22].bPos[5][0] = 5;
	tS[22].bPos[5][1] = 2;

	tS[22].bPos[6][0] = 7;
	tS[22].bPos[6][1] = 2;

	tS[22].bPos[7][0] = 0;
	tS[22].bPos[7][1] = 3;

	tS[22].bPos[8][0] = 1;
	tS[22].bPos[8][1] = 3;

	tS[22].bPos[9][0] = 0;
	tS[22].bPos[9][1] = 4;

	tS[22].bPos[10][0] = 6;
	tS[22].bPos[10][1] = 4;

	tS[22].bPos[11][0] = 1;
	tS[22].bPos[11][1] = 5;

	tS[22].bPos[12][0] = 3;
	tS[22].bPos[12][1] = 5;

	tS[22].bPos[13][0] = 4;
	tS[22].bPos[13][1] = 5;

	tS[22].bPos[14][0] = 1;
	tS[22].bPos[14][1] = 7;

	tS[22].bPos[15][0] = 7;
	tS[22].bPos[15][1] = 7;
	// 24
	tS[23].tWN = 8;
	tS[23].tHN = 8;
	tS[23].setTile(tS[23].tWN, tS[23].tHN);
	tS[23].bIdx[0] = 17;
	tS[23].bIdx[1] = 14;
	tS[23].bIdx[2] = 18;
	tS[23].bIdx[3] = 0;
	tS[23].bIdx[4] = 6;
	tS[23].bIdx[5] = 7;
	tS[23].bIdx[6] = 5;
	tS[23].bIdx[7] = 11;
	tS[23].bIdx[8] = 16;
	tS[23].bIdx[9] = 10;
	tS[23].bIdx[10] = 15;
	tS[23].bIdx[11] = 0;
	tS[23].bIdx[12] = 10;
	tS[23].bIdx[13] = 4;
	tS[23].bIdx[14] = 18;
	tS[23].bIdx[15] = 7;

	tS[23].bPos[0][0] = 0;
	tS[23].bPos[0][1] = 0;

	tS[23].bPos[1][0] = 4;
	tS[23].bPos[1][1] = 0;

	tS[23].bPos[2][0] = 0;
	tS[23].bPos[2][1] = 1;

	tS[23].bPos[3][0] = 2;
	tS[23].bPos[3][1] = 1;

	tS[23].bPos[4][0] = 7;
	tS[23].bPos[4][1] = 2;

	tS[23].bPos[5][0] = 0;
	tS[23].bPos[5][1] = 3;

	tS[23].bPos[6][0] = 5;
	tS[23].bPos[6][1] = 3;

	tS[23].bPos[7][0] = 6;
	tS[23].bPos[7][1] = 3;

	tS[23].bPos[8][0] = 7;
	tS[23].bPos[8][1] = 3;

	tS[23].bPos[9][0] = 1;
	tS[23].bPos[9][1] = 4;

	tS[23].bPos[10][0] = 2;
	tS[23].bPos[10][1] = 4;

	tS[23].bPos[11][0] = 4;
	tS[23].bPos[11][1] = 4;

	tS[23].bPos[12][0] = 4;
	tS[23].bPos[12][1] = 5;

	tS[23].bPos[13][0] = 6;
	tS[23].bPos[13][1] = 5;

	tS[23].bPos[14][0] = 4;
	tS[23].bPos[14][1] = 6;

	tS[23].bPos[15][0] = 0;
	tS[23].bPos[15][1] = 7;
	// 25
	tS[24].tWN = 8;
	tS[24].tHN = 8;
	tS[24].setTile(tS[24].tWN, tS[24].tHN);
	tS[24].bIdx[0] = 10;
	tS[24].bIdx[1] = 15;
	tS[24].bIdx[2] = 17;
	tS[24].bIdx[3] = 0;
	tS[24].bIdx[4] = 3;
	tS[24].bIdx[5] = 14;
	tS[24].bIdx[6] = 7;
	tS[24].bIdx[7] = 18;
	tS[24].bIdx[8] = 16;
	tS[24].bIdx[9] = 14;
	tS[24].bIdx[10] = 15;
	tS[24].bIdx[11] = 8;
	tS[24].bIdx[12] = 9;
	tS[24].bIdx[13] = 18;
	tS[24].bIdx[14] = 17;
	tS[24].bIdx[15] = 6;

	tS[24].bPos[0][0] = 1;
	tS[24].bPos[0][1] = 0;

	tS[24].bPos[1][0] = 2;
	tS[24].bPos[1][1] = 0;

	tS[24].bPos[2][0] = 4;
	tS[24].bPos[2][1] = 0;

	tS[24].bPos[3][0] = 5;
	tS[24].bPos[3][1] = 1;

	tS[24].bPos[4][0] = 3;
	tS[24].bPos[4][1] = 2;

	tS[24].bPos[5][0] = 4;
	tS[24].bPos[5][1] = 2;

	tS[24].bPos[6][0] = 0;
	tS[24].bPos[6][1] = 3;

	tS[24].bPos[7][0] = 3;
	tS[24].bPos[7][1] = 3;

	tS[24].bPos[8][0] = 0;
	tS[24].bPos[8][1] = 4;

	tS[24].bPos[9][0] = 1;
	tS[24].bPos[9][1] = 4;

	tS[24].bPos[10][0] = 5;
	tS[24].bPos[10][1] = 4;

	tS[24].bPos[11][0] = 6;
	tS[24].bPos[11][1] = 4;

	tS[24].bPos[12][0] = 1;
	tS[24].bPos[12][1] = 5;

	tS[24].bPos[13][0] = 5;
	tS[24].bPos[13][1] = 6;

	tS[24].bPos[14][0] = 1;
	tS[24].bPos[14][1] = 7;

	tS[24].bPos[15][0] = 7;
	tS[24].bPos[15][1] = 7;
	// 26
	tS[25].tWN = 8;
	tS[25].tHN = 8;
	tS[25].setTile(tS[25].tWN, tS[25].tHN);
	tS[25].bIdx[0] = 18;
	tS[25].bIdx[1] = 10;
	tS[25].bIdx[2] = 2;
	tS[25].bIdx[3] = 11;
	tS[25].bIdx[4] = 10;
	tS[25].bIdx[5] = 13;
	tS[25].bIdx[6] = 2;
	tS[25].bIdx[7] = 7;
	tS[25].bIdx[8] = 16;
	tS[25].bIdx[9] = 15;
	tS[25].bIdx[10] = 4;
	tS[25].bIdx[11] = 18;
	tS[25].bIdx[12] = 8;
	tS[25].bIdx[13] = 2;
	tS[25].bIdx[14] = 12;
	tS[25].bIdx[15] = 2;

	tS[25].bPos[0][0] = 0;
	tS[25].bPos[0][1] = 0;

	tS[25].bPos[1][0] = 3;
	tS[25].bPos[1][1] = 0;

	tS[25].bPos[2][0] = 5;
	tS[25].bPos[2][1] = 1;

	tS[25].bPos[3][0] = 7;
	tS[25].bPos[3][1] = 1;

	tS[25].bPos[4][0] = 1;
	tS[25].bPos[4][1] = 2;

	tS[25].bPos[5][0] = 4;
	tS[25].bPos[5][1] = 2;

	tS[25].bPos[6][0] = 7;
	tS[25].bPos[6][1] = 2;

	tS[25].bPos[7][0] = 1;
	tS[25].bPos[7][1] = 3;

	tS[25].bPos[8][0] = 7;
	tS[25].bPos[8][1] = 3;

	tS[25].bPos[9][0] = 1;
	tS[25].bPos[9][1] = 4;

	tS[25].bPos[10][0] = 2;
	tS[25].bPos[10][1] = 4;

	tS[25].bPos[11][0] = 3;
	tS[25].bPos[11][1] = 4;

	tS[25].bPos[12][0] = 5;
	tS[25].bPos[12][1] = 5;

	tS[25].bPos[13][0] = 2;
	tS[25].bPos[13][1] = 7;

	tS[25].bPos[14][0] = 3;
	tS[25].bPos[14][1] = 7;

	tS[25].bPos[15][0] = 7;
	tS[25].bPos[15][1] = 7;
	// 27
	tS[26].tWN = 8;
	tS[26].tHN = 8;
	tS[26].setTile(tS[26].tWN, tS[26].tHN);
	tS[26].bIdx[0] = 16;
	tS[26].bIdx[1] = 5;
	tS[26].bIdx[2] = 17;
	tS[26].bIdx[3] = 11;
	tS[26].bIdx[4] = 14;
	tS[26].bIdx[5] = 0;
	tS[26].bIdx[6] = 8;
	tS[26].bIdx[7] = 15;
	tS[26].bIdx[8] = 1;
	tS[26].bIdx[9] = 4;
	tS[26].bIdx[10] = 13;
	tS[26].bIdx[11] = 11;
	tS[26].bIdx[12] = 18;
	tS[26].bIdx[13] = 6;
	tS[26].bIdx[14] = 8;
	tS[26].bIdx[15] = 17;

	tS[26].bPos[0][0] = 0;
	tS[26].bPos[0][1] = 0;

	tS[26].bPos[1][0] = 3;
	tS[26].bPos[1][1] = 0;

	tS[26].bPos[2][0] = 2;
	tS[26].bPos[2][1] = 1;

	tS[26].bPos[3][0] = 6;
	tS[26].bPos[3][1] = 1;

	tS[26].bPos[4][0] = 1;
	tS[26].bPos[4][1] = 2;

	tS[26].bPos[5][0] = 3;
	tS[26].bPos[5][1] = 2;

	tS[26].bPos[6][0] = 6;
	tS[26].bPos[6][1] = 2;

	tS[26].bPos[7][0] = 1;
	tS[26].bPos[7][1] = 3;

	tS[26].bPos[8][0] = 2;
	tS[26].bPos[8][1] = 4;

	tS[26].bPos[9][0] = 5;
	tS[26].bPos[9][1] = 4;

	tS[26].bPos[10][0] = 6;
	tS[26].bPos[10][1] = 4;

	tS[26].bPos[11][0] = 7;
	tS[26].bPos[11][1] = 4;

	tS[26].bPos[12][0] = 0;
	tS[26].bPos[12][1] = 6;

	tS[26].bPos[13][0] = 4;
	tS[26].bPos[13][1] = 6;

	tS[26].bPos[14][0] = 2;
	tS[26].bPos[14][1] = 7;

	tS[26].bPos[15][0] = 4;
	tS[26].bPos[15][1] = 7;
	// 28
	tS[27].tWN = 8;
	tS[27].tHN = 8;
	tS[27].setTile(tS[27].tWN, tS[27].tHN);
	tS[27].bIdx[0] = 0;
	tS[27].bIdx[1] = 0;
	tS[27].bIdx[2] = 13;
	tS[27].bIdx[3] = 18;
	tS[27].bIdx[4] = 18;
	tS[27].bIdx[5] = 6;
	tS[27].bIdx[6] = 4;
	tS[27].bIdx[7] = 2;
	tS[27].bIdx[8] = 10;
	tS[27].bIdx[9] = 2;
	tS[27].bIdx[10] = 4;
	tS[27].bIdx[11] = 16;
	tS[27].bIdx[12] = 7;
	tS[27].bIdx[13] = 9;
	tS[27].bIdx[14] = 9;
	tS[27].bIdx[15] = 11;

	tS[27].bPos[0][0] = 0;
	tS[27].bPos[0][1] = 0;

	tS[27].bPos[1][0] = 3;
	tS[27].bPos[1][1] = 0;

	tS[27].bPos[2][0] = 0;
	tS[27].bPos[2][1] = 1;

	tS[27].bPos[3][0] = 2;
	tS[27].bPos[3][1] = 1;

	tS[27].bPos[4][0] = 5;
	tS[27].bPos[4][1] = 1;

	tS[27].bPos[5][0] = 7;
	tS[27].bPos[5][1] = 2;

	tS[27].bPos[6][0] = 0;
	tS[27].bPos[6][1] = 3;

	tS[27].bPos[7][0] = 5;
	tS[27].bPos[7][1] = 3;

	tS[27].bPos[8][0] = 7;
	tS[27].bPos[8][1] = 3;

	tS[27].bPos[9][0] = 3;
	tS[27].bPos[9][1] = 4;

	tS[27].bPos[10][0] = 5;
	tS[27].bPos[10][1] = 4;

	tS[27].bPos[11][0] = 7;
	tS[27].bPos[11][1] = 4;

	tS[27].bPos[12][0] = 2;
	tS[27].bPos[12][1] = 5;

	tS[27].bPos[13][0] = 0;
	tS[27].bPos[13][1] = 6;

	tS[27].bPos[14][0] = 4;
	tS[27].bPos[14][1] = 6;

	tS[27].bPos[15][0] = 3;
	tS[27].bPos[15][1] = 7;

	//28
	tS[28].tWN = 8;
	tS[28].tHN = 8;
	tS[28].setTile(tS[28].tWN, tS[28].tHN);
	tS[28].bIdx[0] = 9;
	tS[28].bIdx[1] = 17;
	tS[28].bIdx[2] = 1;
	tS[28].bIdx[3] = 18;
	tS[28].bIdx[4] = 10;
	tS[28].bIdx[5] = 2;
	tS[28].bIdx[6] = 13;
	tS[28].bIdx[7] = 6;
	tS[28].bIdx[8] = 14;
	tS[28].bIdx[9] = 0;
	tS[28].bIdx[10] = 6;
	tS[28].bIdx[11] = 4;
	tS[28].bIdx[12] = 13;
	tS[28].bIdx[13] = 18;
	tS[28].bIdx[14] = 4;
	tS[28].bIdx[15] = 1;

	tS[28].bPos[0][0] = 0;
	tS[28].bPos[0][1] = 0;

	tS[28].bPos[1][0] = 1;
	tS[28].bPos[1][1] = 0;

	tS[28].bPos[2][0] = 5;
	tS[28].bPos[2][1] = 0;

	tS[28].bPos[3][0] = 6;
	tS[28].bPos[3][1] = 0;

	tS[28].bPos[4][0] = 1;
	tS[28].bPos[4][1] = 2;

	tS[28].bPos[5][0] = 3;
	tS[28].bPos[5][1] = 3;

	tS[28].bPos[6][0] = 3;
	tS[28].bPos[6][1] = 1;

	tS[28].bPos[7][0] = 7;
	tS[28].bPos[7][1] = 4;

	tS[28].bPos[8][0] = 1;
	tS[28].bPos[8][1] = 4;

	tS[28].bPos[9][0] = 3;
	tS[28].bPos[9][1] = 4;

	tS[28].bPos[10][0] = 6;
	tS[28].bPos[10][1] = 5;

	tS[28].bPos[11][0] = 0;
	tS[28].bPos[11][1] = 5;

	tS[28].bPos[12][0] = 1;
	tS[28].bPos[12][1] = 5;

	tS[28].bPos[13][0] = 3;
	tS[28].bPos[13][1] = 6;

	tS[28].bPos[14][0] = 5;
	tS[28].bPos[14][1] = 5;

	tS[28].bPos[15][0] = 7;
	tS[28].bPos[15][1] = 5;

	//29
	tS[29].tWN = 8;
	tS[29].tHN = 8;
	tS[29].setTile(tS[29].tWN, tS[29].tHN);
	tS[29].bIdx[0] = 13;
	tS[29].bIdx[1] = 14;
	tS[29].bIdx[2] = 0;
	tS[29].bIdx[3] = 12;
	tS[29].bIdx[4] = 17;
	tS[29].bIdx[5] = 1;
	tS[29].bIdx[6] = 4;
	tS[29].bIdx[7] = 14;
	tS[29].bIdx[8] = 6;
	tS[29].bIdx[9] = 18;
	tS[29].bIdx[10] = 7;
	tS[29].bIdx[11] = 11;
	tS[29].bIdx[12] = 9;
	tS[29].bIdx[13] = 18;
	tS[29].bIdx[14] = 17;
	tS[29].bIdx[15] = 18;

	tS[29].bPos[0][0] = 0;
	tS[29].bPos[0][1] = 0;

	tS[29].bPos[1][0] = 1;
	tS[29].bPos[1][1] = 0;

	tS[29].bPos[2][0] = 3;
	tS[29].bPos[2][1] = 0;

	tS[29].bPos[3][0] = 5;
	tS[29].bPos[3][1] = 1;

	tS[29].bPos[4][0] = 2;
	tS[29].bPos[4][1] = 2;

	tS[29].bPos[5][0] = 7;
	tS[29].bPos[5][1] = 1;

	tS[29].bPos[6][0] = 0;
	tS[29].bPos[6][1] = 2;

	tS[29].bPos[7][0] = 1;
	tS[29].bPos[7][1] = 3;

	tS[29].bPos[8][0] = 4;
	tS[29].bPos[8][1] = 5;

	tS[29].bPos[9][0] = 5;
	tS[29].bPos[9][1] = 3;

	tS[29].bPos[10][0] = 5;
	tS[29].bPos[10][1] = 5;

	tS[29].bPos[11][0] = 2;
	tS[29].bPos[11][1] = 6;

	tS[29].bPos[12][0] = 3;
	tS[29].bPos[12][1] = 5;

	tS[29].bPos[13][0] = 0;
	tS[29].bPos[13][1] = 6;

	tS[29].bPos[14][0] = 2;
	tS[29].bPos[14][1] = 7;

	tS[29].bPos[15][0] = 6;
	tS[29].bPos[15][1] = 6;

	//30
	tS[30].tWN = 8;
	tS[30].tHN = 8;
	tS[30].setTile(tS[30].tWN, tS[30].tHN);
	tS[30].bIdx[0] = 3;
	tS[30].bIdx[1] = 14;
	tS[30].bIdx[2] = 6;
	tS[30].bIdx[3] = 11;
	tS[30].bIdx[4] = 0;
	tS[30].bIdx[5] = 18;
	tS[30].bIdx[6] = 14;
	tS[30].bIdx[7] = 5;
	tS[30].bIdx[8] = 15;
	tS[30].bIdx[9] = 16;
	tS[30].bIdx[10] = 13;
	tS[30].bIdx[11] = 18;
	tS[30].bIdx[12] = 4;
	tS[30].bIdx[13] = 13;
	tS[30].bIdx[14] = 9;
	tS[30].bIdx[15] = 17;

	tS[30].bPos[0][0] = 0;
	tS[30].bPos[0][1] = 2;

	tS[30].bPos[1][0] = 1;
	tS[30].bPos[1][1] = 0;

	tS[30].bPos[2][0] = 4;
	tS[30].bPos[2][1] = 2;

	tS[30].bPos[3][0] = 7;
	tS[30].bPos[3][1] = 1;

	tS[30].bPos[4][0] = 1;
	tS[30].bPos[4][1] = 2;

	tS[30].bPos[5][0] = 5;
	tS[30].bPos[5][1] = 1;

	tS[30].bPos[6][0] = 0;
	tS[30].bPos[6][1] = 3;

	tS[30].bPos[7][0] = 5;
	tS[30].bPos[7][1] = 3;

	tS[30].bPos[8][0] = 6;
	tS[30].bPos[8][1] = 3;

	tS[30].bPos[9][0] = 7;
	tS[30].bPos[9][1] = 2;

	tS[30].bPos[10][0] = 0;
	tS[30].bPos[10][1] = 4;

	tS[30].bPos[11][0] = 2;
	tS[30].bPos[11][1] = 5;

	tS[30].bPos[12][0] = 4;
	tS[30].bPos[12][1] = 4;

	tS[30].bPos[13][0] = 6;
	tS[30].bPos[13][1] = 5;

	tS[30].bPos[14][0] = 0;
	tS[30].bPos[14][1] = 6;

	tS[30].bPos[15][0] = 3;
	tS[30].bPos[15][1] = 7;

	//31
	tS[31].tWN = 8;
	tS[31].tHN = 8;
	tS[31].setTile(tS[31].tWN, tS[31].tHN);
	tS[31].bIdx[0] = 14;
	tS[31].bIdx[1] = 6;
	tS[31].bIdx[2] = 10;
	tS[31].bIdx[3] = 12;
	tS[31].bIdx[4] = 4;
	tS[31].bIdx[5] = 14;
	tS[31].bIdx[6] = 18;
	tS[31].bIdx[7] = 16;
	tS[31].bIdx[8] = 18;
	tS[31].bIdx[9] = 7;
	tS[31].bIdx[10] = 7;
	tS[31].bIdx[11] = 13;
	tS[31].bIdx[12] = 2;
	tS[31].bIdx[13] = 9;
	tS[31].bIdx[14] = 12;
	tS[31].bIdx[15] = 2;

	tS[31].bPos[0][0] = 0;
	tS[31].bPos[0][1] = 0;

	tS[31].bPos[1][0] = 3;
	tS[31].bPos[1][1] = 2;

	tS[31].bPos[2][0] = 5;
	tS[31].bPos[2][1] = 0;

	tS[31].bPos[3][0] = 5;
	tS[31].bPos[3][1] = 1;

	tS[31].bPos[4][0] = 0;
	tS[31].bPos[4][1] = 1;

	tS[31].bPos[5][0] = 1;
	tS[31].bPos[5][1] = 2;

	tS[31].bPos[6][0] = 5;
	tS[31].bPos[6][1] = 2;

	tS[31].bPos[7][0] = 7;
	tS[31].bPos[7][1] = 1;

	tS[31].bPos[8][0] = 0;
	tS[31].bPos[8][1] = 4;

	tS[31].bPos[9][0] = 2;
	tS[31].bPos[9][1] = 4;

	tS[31].bPos[10][0] = 3;
	tS[31].bPos[10][1] = 5;

	tS[31].bPos[11][0] = 6;
	tS[31].bPos[11][1] = 4;

	tS[31].bPos[12][0] = 3;
	tS[31].bPos[12][1] = 6;

	tS[31].bPos[13][0] = 0;
	tS[31].bPos[13][1] = 6;

	tS[31].bPos[14][0] = 3;
	tS[31].bPos[14][1] = 7;

	tS[31].bPos[15][0] = 7;
	tS[31].bPos[15][1] = 7;

	//32
	tS[32].tWN = 8;
	tS[32].tHN = 8;
	tS[32].setTile(tS[32].tWN, tS[32].tHN);
	tS[32].bIdx[0] = 16;
	tS[32].bIdx[1] = 4;
	tS[32].bIdx[2] = 18;
	tS[32].bIdx[3] = 14;
	tS[32].bIdx[4] = 6;
	tS[32].bIdx[5] = 15;
	tS[32].bIdx[6] = 3;
	tS[32].bIdx[7] = 2;
	tS[32].bIdx[8] = 15;
	tS[32].bIdx[9] = 17;
	tS[32].bIdx[10] = 1;
	tS[32].bIdx[11] = 18;
	tS[32].bIdx[12] = 6;
	tS[32].bIdx[13] = 5;
	tS[32].bIdx[14] = 12;
	tS[32].bIdx[15] = 2;

	tS[32].bPos[0][0] = 0;
	tS[32].bPos[0][1] = 0;

	tS[32].bPos[1][0] = 1;
	tS[32].bPos[1][1] = 0;

	tS[32].bPos[2][0] = 2;
	tS[32].bPos[2][1] = 0;

	tS[32].bPos[3][0] = 4;
	tS[32].bPos[3][1] = 0;

	tS[32].bPos[4][0] = 7;
	tS[32].bPos[4][1] = 2;

	tS[32].bPos[5][0] = 3;
	tS[32].bPos[5][1] = 2;

	tS[32].bPos[6][0] = 4;
	tS[32].bPos[6][1] = 3;

	tS[32].bPos[7][0] = 7;
	tS[32].bPos[7][1] = 3;

	tS[32].bPos[8][0] = 1;
	tS[32].bPos[8][1] = 3;

	tS[32].bPos[9][0] = 3;
	tS[32].bPos[9][1] = 4;

	tS[32].bPos[10][0] = 7;
	tS[32].bPos[10][1] = 4;

	tS[32].bPos[11][0] = 0;
	tS[32].bPos[11][1] = 6;

	tS[32].bPos[12][0] = 2;
	tS[32].bPos[12][1] = 7;

	tS[32].bPos[13][0] = 5;
	tS[32].bPos[13][1] = 5;

	tS[32].bPos[14][0] = 3;
	tS[32].bPos[14][1] = 7;

	tS[32].bPos[15][0] = 7;
	tS[32].bPos[15][1] = 7;

	//33
	tS[33].tWN = 8;
	tS[33].tHN = 8;
	tS[33].setTile(tS[33].tWN, tS[33].tHN);
	tS[33].bIdx[0] = 18;
	tS[33].bIdx[1] = 3;
	tS[33].bIdx[2] = 6;
	tS[33].bIdx[3] = 11;
	tS[33].bIdx[4] = 14;
	tS[33].bIdx[5] = 14;
	tS[33].bIdx[6] = 13;
	tS[33].bIdx[7] = 3;
	tS[33].bIdx[8] = 15;
	tS[33].bIdx[9] = 4;
	tS[33].bIdx[10] = 11;
	tS[33].bIdx[11] = 18;
	tS[33].bIdx[12] = 9;
	tS[33].bIdx[13] = 2;
	tS[33].bIdx[14] = 17;
	tS[33].bIdx[15] = 1;

	tS[33].bPos[0][0] = 0;
	tS[33].bPos[0][1] = 0;

	tS[33].bPos[1][0] = 2;
	tS[33].bPos[1][1] = 2;

	tS[33].bPos[2][0] = 4;
	tS[33].bPos[2][1] = 2;

	tS[33].bPos[3][0] = 7;
	tS[33].bPos[3][1] = 1;

	tS[33].bPos[4][0] = 5;
	tS[33].bPos[4][1] = 1;

	tS[33].bPos[5][0] = 0;
	tS[33].bPos[5][1] = 2;

	tS[33].bPos[6][0] = 3;
	tS[33].bPos[6][1] = 2;

	tS[33].bPos[7][0] = 5;
	tS[33].bPos[7][1] = 4;

	tS[33].bPos[8][0] = 7;
	tS[33].bPos[8][1] = 3;

	tS[33].bPos[9][0] = 0;
	tS[33].bPos[9][1] = 3;

	tS[33].bPos[10][0] = 3;
	tS[33].bPos[10][1] = 5;

	tS[33].bPos[11][0] = 4;
	tS[33].bPos[11][1] = 5;

	tS[33].bPos[12][0] = 0;
	tS[33].bPos[12][1] = 6;

	tS[33].bPos[13][0] = 3;
	tS[33].bPos[13][1] = 6;

	tS[33].bPos[14][0] = 3;
	tS[33].bPos[14][1] = 7;

	tS[33].bPos[15][0] = 7;
	tS[33].bPos[15][1] = 5;

	//34
	tS[34].tWN = 8;
	tS[34].tHN = 8;
	tS[34].setTile(tS[34].tWN, tS[34].tHN);
	tS[34].bIdx[0] = 9;
	tS[34].bIdx[1] = 17;
	tS[34].bIdx[2] = 2;
	tS[34].bIdx[3] = 6;
	tS[34].bIdx[4] = 7;
	tS[34].bIdx[5] = 11;
	tS[34].bIdx[6] = 3;
	tS[34].bIdx[7] = 12;
	tS[34].bIdx[8] = 18;
	tS[34].bIdx[9] = 1;
	tS[34].bIdx[10] = 5;
	tS[34].bIdx[11] = 13;
	tS[34].bIdx[12] = 10;
	tS[34].bIdx[13] = 2;
	tS[34].bIdx[14] = 14;
	tS[34].bIdx[15] = 18;

	tS[34].bPos[0][0] = 0;
	tS[34].bPos[0][1] = 0;

	tS[34].bPos[1][0] = 1;
	tS[34].bPos[1][1] = 0;

	tS[34].bPos[2][0] = 6;
	tS[34].bPos[2][1] = 1;

	tS[34].bPos[3][0] = 7;
	tS[34].bPos[3][1] = 2;

	tS[34].bPos[4][0] = 1;
	tS[34].bPos[4][1] = 2;

	tS[34].bPos[5][0] = 6;
	tS[34].bPos[5][1] = 3;

	tS[34].bPos[6][0] = 0;
	tS[34].bPos[6][1] = 4;

	tS[34].bPos[7][0] = 1;
	tS[34].bPos[7][1] = 4;

	tS[34].bPos[8][0] = 4;
	tS[34].bPos[8][1] = 3;

	tS[34].bPos[9][0] = 7;
	tS[34].bPos[9][1] = 3;

	tS[34].bPos[10][0] = 2;
	tS[34].bPos[10][1] = 5;

	tS[34].bPos[11][0] = 3;
	tS[34].bPos[11][1] = 4;

	tS[34].bPos[12][0] = 6;
	tS[34].bPos[12][1] = 5;

	tS[34].bPos[13][0] = 3;
	tS[34].bPos[13][1] = 4;

	tS[34].bPos[14][0] = 2;
	tS[34].bPos[14][1] = 6;

	tS[34].bPos[15][0] = 6;
	tS[34].bPos[15][1] = 6;

	//35
	tS[35].tWN = 8;
	tS[35].tHN = 8;
	tS[35].setTile(tS[35].tWN, tS[35].tHN);
	tS[35].bIdx[0] = 16;
	tS[35].bIdx[1] = 0;
	tS[35].bIdx[2] = 12;
	tS[35].bIdx[3] = 18;
	tS[35].bIdx[4] = 9;
	tS[35].bIdx[5] = 2;
	tS[35].bIdx[6] = 18;
	tS[35].bIdx[7] = 7;
	tS[35].bIdx[8] = 10;
	tS[35].bIdx[9] = 6;
	tS[35].bIdx[10] = 11;
	tS[35].bIdx[11] = 8;
	tS[35].bIdx[12] = 15;
	tS[35].bIdx[13] = 18;
	tS[35].bIdx[14] = 17;
	tS[35].bIdx[15] = 13;

	tS[35].bPos[0][0] = 0;
	tS[35].bPos[0][1] = 0;

	tS[35].bPos[1][0] = 1;
	tS[35].bPos[1][1] = 0;

	tS[35].bPos[2][0] = 3;
	tS[35].bPos[2][1] = 1;

	tS[35].bPos[3][0] = 6;
	tS[35].bPos[3][1] = 0;

	tS[35].bPos[4][0] = 1;
	tS[35].bPos[4][1] = 1;

	tS[35].bPos[5][0] = 6;
	tS[35].bPos[5][1] = 2;

	tS[35].bPos[6][0] = 3;
	tS[35].bPos[6][1] = 3;

	tS[35].bPos[7][0] = 5;
	tS[35].bPos[7][1] = 3;

	tS[35].bPos[8][0] = 1;
	tS[35].bPos[8][1] = 4;

	tS[35].bPos[9][0] = 2;
	tS[35].bPos[9][1] = 5;

	tS[35].bPos[10][0] = 7;
	tS[35].bPos[10][1] = 5;

	tS[35].bPos[11][0] = 0;
	tS[35].bPos[11][1] = 7;

	tS[35].bPos[12][0] = 3;
	tS[35].bPos[12][1] = 5;

	tS[35].bPos[13][0] = 4;
	tS[35].bPos[13][1] = 5;

	tS[35].bPos[14][0] = 3;
	tS[35].bPos[14][1] = 7;

	tS[35].bPos[15][0] = 6;
	tS[35].bPos[15][1] = 5;
}

void bigPicture::setExchangeList(int** list)
{
	exchangeList = new int*[MAXELN];
	for (int i = 0; i < MAXELN; i++){
		exchangeList[i] = new int[3];
		exchangeList[i][0] = -1; //블록쌍 라벨
		exchangeList[i][1] = -1; //노랑블록(첫번째 블록)
		exchangeList[i][2] = -1; //초록블록(두번째 블록)
	}

	//1장
	exchangeList[0][0] = 0;
	exchangeList[0][1] = 4;
	exchangeList[0][2] = 17;

	exchangeList[1][0] = 0;
	exchangeList[1][1] = 16;
	exchangeList[1][2] = 9;

	exchangeList[2][0] = 1;
	exchangeList[2][1] = 13;
	exchangeList[2][2] = 9;

	exchangeList[3][0] = 1;
	exchangeList[3][1] = 3;
	exchangeList[3][2] = 2;

	exchangeList[4][0] = 1;
	exchangeList[4][1] = 16;
	exchangeList[4][2] = 4;

	exchangeList[5][0] = 2;
	exchangeList[5][1] = 10;
	exchangeList[5][2] = 18;

	exchangeList[6][0] = 2;
	exchangeList[6][1] = 18;
	exchangeList[6][2] = 7;

	exchangeList[7][0] = 2;
	exchangeList[7][1] = 14;
	exchangeList[7][2] = 9;

	exchangeList[8][0] = 2;
	exchangeList[8][1] = 4;
	exchangeList[8][2] = 13;

	exchangeList[9][0] = 3;
	exchangeList[9][1] = 18;
	exchangeList[9][2] = 15;

	exchangeList[10][0] = 3;
	exchangeList[10][1] = 9;
	exchangeList[10][2] = 7;

	exchangeList[11][0] = 4;
	exchangeList[11][1] = 3;
	exchangeList[11][2] = 1;

	exchangeList[12][0] = 4;
	exchangeList[12][1] = 13;
	exchangeList[12][2] = 13;

	exchangeList[13][0] = 4;
	exchangeList[13][1] = 16;
	exchangeList[13][2] = 16;

	exchangeList[14][0] = 5;
	exchangeList[14][1] = 18;
	exchangeList[14][2] = 18;

	exchangeList[15][0] = 5;
	exchangeList[15][1] = 5;
	exchangeList[15][2] = 7;

	exchangeList[16][0] = 5;
	exchangeList[16][1] = 17;
	exchangeList[16][2] = 17;

	exchangeList[17][0] = 6;
	exchangeList[17][1] = 7;
	exchangeList[17][2] = 17;

	exchangeList[18][0] = 6;
	exchangeList[18][1] = 18;
	exchangeList[18][2] = 4;

	exchangeList[19][0] = 7;
	exchangeList[19][1] = 18;
	exchangeList[19][2] = 17;

	exchangeList[20][0] = 7;
	exchangeList[20][1] = 10;
	exchangeList[20][2] = 9;

	exchangeList[21][0] = 8;
	exchangeList[21][1] = 13;
	exchangeList[21][2] = 8;

	exchangeList[22][0] = 8;
	exchangeList[22][1] = 9;
	exchangeList[22][2] = 18;

	exchangeList[23][0] = 9;
	exchangeList[23][1] = 13;
	exchangeList[23][2] = 13;

	exchangeList[24][0] = 9;
	exchangeList[24][1] = 9;
	exchangeList[24][2] = 11;

	exchangeList[25][0] = 10;
	exchangeList[25][1] = 2;
	exchangeList[25][2] = 17;

	exchangeList[26][0] = 10;
	exchangeList[26][1] = 15;
	exchangeList[26][2] = 2;

	exchangeList[27][0] = 11;
	exchangeList[27][1] = 13;
	exchangeList[27][2] = 1;

	exchangeList[28][0] = 11;
	exchangeList[28][1] = 7;
	exchangeList[28][2] = 0;

	exchangeList[29][0] = 12;
	exchangeList[29][1] = 8;
	exchangeList[29][2] = 10;

	exchangeList[30][0] = 12;
	exchangeList[30][1] = 7;
	exchangeList[30][2] = 5;

	exchangeList[31][0] = 12;
	exchangeList[31][1] = 2;
	exchangeList[31][2] = 0;

	exchangeList[32][0] = 13;
	exchangeList[32][1] = 18;
	exchangeList[32][2] = 3;

	exchangeList[33][0] = 13;
	exchangeList[33][1] = 9;
	exchangeList[33][2] = 2;

	exchangeList[34][0] = 14;
	exchangeList[34][1] = 18;
	exchangeList[34][2] = 10;

	exchangeList[35][0] = 14;
	exchangeList[35][1] = 6;
	exchangeList[35][2] = 16;

	exchangeList[36][0] = 15;
	exchangeList[36][1] = 15;
	exchangeList[36][2] = 2;

	exchangeList[37][0] = 15;
	exchangeList[37][1] = 1;
	exchangeList[37][2] = 9;

	exchangeList[38][0] = 16;
	exchangeList[38][1] = 3;
	exchangeList[38][2] = 11;

	exchangeList[39][0] = 16;
	exchangeList[39][1] = 15;
	exchangeList[39][2] = 0;

	exchangeList[40][0] = 17;
	exchangeList[40][1] = 4;
	exchangeList[40][2] = 16;

	exchangeList[41][0] = 17;
	exchangeList[41][1] = 18;
	exchangeList[41][2] = 8;

	exchangeList[42][0] = 18;
	exchangeList[42][1] = 11;
	exchangeList[42][2] = 0;

	exchangeList[43][0] = 18;
	exchangeList[43][1] = 18;
	exchangeList[43][2] = 1;

	exchangeList[44][0] = 19;
	exchangeList[44][1] = 0;
	exchangeList[44][2] = 2;

	exchangeList[45][0] = 19;
	exchangeList[45][1] = 5;
	exchangeList[45][2] = 7;

	exchangeList[46][0] = 19;
	exchangeList[46][1] = 10;
	exchangeList[46][2] = 8;

	exchangeList[47][0] = 20;
	exchangeList[47][1] = 5;
	exchangeList[47][2] = 2;

	exchangeList[48][0] = 20;
	exchangeList[48][1] = 13;
	exchangeList[48][2] = 3;

	exchangeList[49][0] = 21;
	exchangeList[49][1] = 15;
	exchangeList[49][2] = 0;

	exchangeList[50][0] = 21;
	exchangeList[50][1] = 0;
	exchangeList[50][2] = 17;

	exchangeList[51][0] = 22;
	exchangeList[51][1] = 11;
	exchangeList[51][2] = 9;

	exchangeList[52][0] = 22;
	exchangeList[52][1] = 13;
	exchangeList[52][2] = 13;

	exchangeList[53][0] = 23;
	exchangeList[53][1] = 11;
	exchangeList[53][2] = 18;

	exchangeList[54][0] = 23;
	exchangeList[54][1] = 13;
	exchangeList[54][2] = 10;

	exchangeList[55][0] = 24;
	exchangeList[55][1] = 8;
	exchangeList[55][2] = 11;

	exchangeList[56][0] = 24;
	exchangeList[56][1] = 18;
	exchangeList[56][2] = 17;

	exchangeList[57][0] = 25;
	exchangeList[57][1] = 18;
	exchangeList[57][2] = 6;

	exchangeList[58][0] = 25;
	exchangeList[58][1] = 5;
	exchangeList[58][2] = 17;

	exchangeList[59][0] = 26;
	exchangeList[59][1] = 17;
	exchangeList[59][2] = 17;

	exchangeList[60][0] = 26;
	exchangeList[60][1] = 7;
	exchangeList[60][2] = 5;

	exchangeList[61][0] = 26;
	exchangeList[61][1] = 18;
	exchangeList[61][2] = 18;

	exchangeList[62][0] = 27;
	exchangeList[62][1] = 16;
	exchangeList[62][2] = 16;

	exchangeList[63][0] = 27;
	exchangeList[63][1] = 13;
	exchangeList[63][2] = 13;

	exchangeList[64][0] = 27;
	exchangeList[64][1] = 1;
	exchangeList[64][2] = 3;

	exchangeList[65][0] = 28;
	exchangeList[65][1] = 11;
	exchangeList[65][2] = 5;

	exchangeList[66][0] = 28;
	exchangeList[66][1] = 18;
	exchangeList[66][2] = 15;

	exchangeList[67][0] = 29;
	exchangeList[67][1] = 6;
	exchangeList[67][2] = 13;

	exchangeList[68][0] = 29;
	exchangeList[68][1] = 14;
	exchangeList[68][2] = 11;

	exchangeList[69][0] = 29;
	exchangeList[69][1] = 18;
	exchangeList[69][2] = 5;

	exchangeList[70][0] = 29;
	exchangeList[70][1] = 8;
	exchangeList[70][2] = 18;

	exchangeList[71][0] = 30;
	exchangeList[71][1] = 16;
	exchangeList[37][2] = 6;

	exchangeList[72][0] = 30;
	exchangeList[72][1] = 1;
	exchangeList[72][2] = 0;

	exchangeList[73][0] = 30;
	exchangeList[73][1] = 13;
	exchangeList[73][2] = 11;

	exchangeList[74][0] = 31;
	exchangeList[74][1] = 16;
	exchangeList[74][2] = 11;

	exchangeList[75][0] = 31;
	exchangeList[75][1] = 6;
	exchangeList[75][2] = 17;

	exchangeList[76][0] = 32;
	exchangeList[76][1] = 17;
	exchangeList[76][2] = 17;

	exchangeList[77][0] = 32;
	exchangeList[77][1] = 12;
	exchangeList[77][2] = 12;

	exchangeList[78][0] = 32;
	exchangeList[78][1] = 2;
	exchangeList[78][2] = 0;

	exchangeList[79][0] = 33;
	exchangeList[79][1] = 8;
	exchangeList[79][2] = 10;

	exchangeList[80][0] = 33;
	exchangeList[80][1] = 12;
	exchangeList[80][2] = 12;

	exchangeList[81][0] = 34;
	exchangeList[81][1] = 5;
	exchangeList[81][2] = 17;

	exchangeList[82][0] = 34;
	exchangeList[82][1] = 18;
	exchangeList[82][2] = 9;

	exchangeList[83][0] = 35;
	exchangeList[83][1] = 8;
	exchangeList[83][2] = 6;

	exchangeList[84][0] = 35;
	exchangeList[84][1] = 18;
	exchangeList[84][2] = 14;

	exchangeList[85][0] = 36;
	exchangeList[85][1] = 8;
	exchangeList[85][2] = 18;

	exchangeList[86][0] = 36;
	exchangeList[86][1] = 12;
	exchangeList[86][2] = 11;

	exchangeList[87][0] = 37;
	exchangeList[87][1] = 8;
	exchangeList[87][2] = 1;

	exchangeList[88][0] = 37;
	exchangeList[88][1] = 18;
	exchangeList[88][2] = 2;

	exchangeList[89][0] = 38;
	exchangeList[89][1] = 18;
	exchangeList[89][2] = 6;

	exchangeList[90][0] = 38;
	exchangeList[90][1] = 7;
	exchangeList[90][2] = 12;

	exchangeList[91][0] = 38;
	exchangeList[91][1] = 9;
	exchangeList[91][2] = 18;

	exchangeList[92][0] = 38;
	exchangeList[92][1] = 15;
	exchangeList[92][2] = 8;

	exchangeList[93][0] = 39;
	exchangeList[93][1] = 9;
	exchangeList[93][2] = 8;

	exchangeList[94][0] = 39;
	exchangeList[94][1] = 18;
	exchangeList[94][2] = 16;

	exchangeList[95][0] = 40;
	exchangeList[95][1] = 1;
	exchangeList[95][2] = 3;

	exchangeList[96][0] = 40;
	exchangeList[96][1] = 11;
	exchangeList[96][2] = 9;

	exchangeList[97][0] = 40;
	exchangeList[97][1] = 6;
	exchangeList[97][2] = 4;

	exchangeList[98][0] = 41;
	exchangeList[98][1] = 17;
	exchangeList[98][2] = 7;

	exchangeList[99][0] = 41;
	exchangeList[99][1] = 12;
	exchangeList[99][2] = 8;

	exchangeList[100][0] = 41;
	exchangeList[100][1] = 2;
	exchangeList[100][2] = 1;

	exchangeList[101][0] = 42;
	exchangeList[101][1] = 18;
	exchangeList[101][2] = 7;

	exchangeList[102][0] = 42;
	exchangeList[102][1] = 6;
	exchangeList[102][2] = 16;

	exchangeList[103][0] = 43;
	exchangeList[103][1] = 6;
	exchangeList[103][2] = 3;

	exchangeList[104][0] = 43;
	exchangeList[104][1] = 12;
	exchangeList[104][2] = 0;

	exchangeList[105][0] = 44;
	exchangeList[105][1] = 17;
	exchangeList[105][2] = 8;

	exchangeList[106][0] = 44;
	exchangeList[106][1] = 7;
	exchangeList[106][2] = 16;

	exchangeList[107][0] = 45;
	exchangeList[107][1] = 16;
	exchangeList[107][2] = 16;

	exchangeList[108][0] = 45;
	exchangeList[108][1] = 4;
	exchangeList[108][2] = 6;

	exchangeList[109][0] = 45;
	exchangeList[109][1] = 18;
	exchangeList[109][2] = 18;

	exchangeList[110][0] = 46;
	exchangeList[110][1] = 14;
	exchangeList[110][2] = 1;

	exchangeList[111][0] = 46;
	exchangeList[111][1] = 1;
	exchangeList[111][2] = 16;

	exchangeList[112][0] = 47;
	exchangeList[112][1] = 0;
	exchangeList[112][2] = 8;

	exchangeList[113][0] = 47;
	exchangeList[113][1] = 14;
	exchangeList[113][2] = 1;

	exchangeList[114][0] = 48;
	exchangeList[114][1] = 14;
	exchangeList[114][2] = 3;

	exchangeList[115][0] = 48;
	exchangeList[115][1] = 2;
	exchangeList[115][2] = 10;

	exchangeList[116][0] = 49;
	exchangeList[116][1] = 3;
	exchangeList[116][2] = 16;

	exchangeList[117][0] = 49;
	exchangeList[117][1] = 14;
	exchangeList[117][2] = 3;

	exchangeList[118][0] = 50;
	exchangeList[118][1] = 18;
	exchangeList[118][2] = 18;

	exchangeList[119][0] = 50;
	exchangeList[119][1] = 6;
	exchangeList[119][2] = 4;

	exchangeList[120][0] = 50;
	exchangeList[120][1] = 16;
	exchangeList[120][2] = 16;

	exchangeList[121][0] = 51;
	exchangeList[121][1] = 5;
	exchangeList[121][2] = 16;

	exchangeList[122][0] = 51;
	exchangeList[122][1] = 17;
	exchangeList[122][2] = 10;

	exchangeList[123][0] = 52;
	exchangeList[123][1] = 12;
	exchangeList[123][2] = 2;

	exchangeList[124][0] = 52;
	exchangeList[124][1] = 4;
	exchangeList[124][2] = 1;

	exchangeList[125][0] = 53;
	exchangeList[125][1] = 4;
	exchangeList[125][2] = 16;

	exchangeList[126][0] = 53;
	exchangeList[126][1] = 18;
	exchangeList[126][2] = 5;

	exchangeList[127][0] = 54;
	exchangeList[127][1] = 0;
	exchangeList[127][2] = 3;

	exchangeList[128][0] = 54;
	exchangeList[128][1] = 12;
	exchangeList[128][2] = 10;

	exchangeList[129][0] = 54;
	exchangeList[129][1] = 17;
	exchangeList[129][2] = 5;

	exchangeList[130][0] = 55;
	exchangeList[130][1] = 4;
	exchangeList[130][2] = 6;

	exchangeList[131][0] = 55;
	exchangeList[131][1] = 9;
	exchangeList[131][2] = 11;

	exchangeList[132][0] = 55;
	exchangeList[132][1] = 3;
	exchangeList[132][2] = 1;

	exchangeList[133][0] = 56;
	exchangeList[133][1] = 18;
	exchangeList[133][2] = 16;

	exchangeList[134][0] = 56;
	exchangeList[134][1] = 11;
	exchangeList[134][2] = 10;

	exchangeList[135][0] = 57;
	exchangeList[135][1] = 15;
	exchangeList[135][2] = 10;

	exchangeList[136][0] = 57;
	exchangeList[136][1] = 11;
	exchangeList[136][2] = 18;

	exchangeList[137][0] = 57;
	exchangeList[137][1] = 5;
	exchangeList[137][2] = 12;

	exchangeList[138][0] = 57;
	exchangeList[138][1] = 18;
	exchangeList[138][2] = 4;

	exchangeList[139][0] = 58;
	exchangeList[139][1] = 18;
	exchangeList[139][2] = 0;

	exchangeList[140][0] = 58;
	exchangeList[140][1] = 10;
	exchangeList[140][2] = 3;

	exchangeList[141][0] = 59;
	exchangeList[141][1] = 12;
	exchangeList[141][2] = 9;

	exchangeList[142][0] = 59;
	exchangeList[142][1] = 10;
	exchangeList[142][2] = 18;

	exchangeList[143][0] = 60;
	exchangeList[143][1] = 18;
	exchangeList[143][2] = 14;

	exchangeList[144][0] = 60;
	exchangeList[144][1] = 10;
	exchangeList[144][2] = 4;

	exchangeList[145][0] = 61;
	exchangeList[145][1] = 18;
	exchangeList[145][2] = 11;

	exchangeList[146][0] = 61;
	exchangeList[146][1] = 7;
	exchangeList[146][2] = 17;

	exchangeList[147][0] = 62;
	exchangeList[147][1] = 12;
	exchangeList[147][2] = 12;

	exchangeList[148][0] = 62;
	exchangeList[148][1] = 10;
	exchangeList[148][2] = 8;

	exchangeList[149][0] = 63;
	exchangeList[149][1] = 0;
	exchangeList[149][2] = 2;

	exchangeList[150][0] = 63;
	exchangeList[150][1] = 12;
	exchangeList[150][2] = 12;

	exchangeList[151][0] = 63;
	exchangeList[151][1] = 17;
	exchangeList[151][2] = 17;

	////추가
	exchangeList[152][0] = 64;
	exchangeList[152][1] = 1;
	exchangeList[152][2] = 3;

	exchangeList[153][0] = 64;
	exchangeList[153][1] = 15;
	exchangeList[153][2] = 15;

	exchangeList[154][0] = 64;
	exchangeList[154][1] = 16;
	exchangeList[154][2] = 16;

	exchangeList[155][0] = 65;
	exchangeList[155][1] = 18;
	exchangeList[155][2] = 13;

	exchangeList[156][0] = 65;
	exchangeList[156][1] = 7;
	exchangeList[156][2] = 9;

	exchangeList[157][0] = 66;
	exchangeList[157][1] = 18;
	exchangeList[157][2] = 9;

	exchangeList[158][0] = 66;
	exchangeList[158][1] = 6;
	exchangeList[158][2] = 18;

	exchangeList[159][0] = 66;
	exchangeList[159][1] = 8;
	exchangeList[159][2] = 15;

	exchangeList[160][0] = 66;
	exchangeList[160][1] = 12;
	exchangeList[160][2] = 7;

	exchangeList[161][0] = 67;
	exchangeList[161][1] = 15;
	exchangeList[161][2] = 7;

	exchangeList[162][0] = 67;
	exchangeList[162][1] = 16;
	exchangeList[162][2] = 8;

	exchangeList[163][0] = 67;
	exchangeList[163][1] = 1;
	exchangeList[163][2] = 2;

	exchangeList[164][0] = 68;
	exchangeList[164][1] = 8;
	exchangeList[164][2] = 17;

	exchangeList[165][0] = 68;
	exchangeList[165][1] = 16;
	exchangeList[165][2] = 7;

	exchangeList[166][0] = 69;
	exchangeList[166][1] = 15;
	exchangeList[166][2] = 15;

	exchangeList[167][0] = 69;
	exchangeList[167][1] = 7;
	exchangeList[167][2] = 5;

	exchangeList[168][0] = 70;
	exchangeList[168][1] = 15;
	exchangeList[168][2] = 4;

	exchangeList[169][0] = 70;
	exchangeList[169][1] = 7;
	exchangeList[169][2] = 18;

	exchangeList[170][0] = 71;
	exchangeList[170][1] = 18;
	exchangeList[170][2] = 17;

	exchangeList[171][0] = 71;
	exchangeList[171][1] = 6;
	exchangeList[171][2] = 7;

	exchangeList[172][0] = 72;
	exchangeList[172][1] = 9;
	exchangeList[172][2] = 17;

	exchangeList[173][0] = 72;
	exchangeList[173][1] = 18;
	exchangeList[173][2] = 8;

	exchangeList[174][0] = 73;
	exchangeList[174][1] = 18;
	exchangeList[174][2] = 18;

	exchangeList[175][0] = 73;
	exchangeList[175][1] = 11;
	exchangeList[175][2] = 9;

	exchangeList[176][0] = 73;
	exchangeList[176][1] = 17;
	exchangeList[176][2] = 17;

	exchangeList[177][0] = 74;
	exchangeList[177][1] = 18;
	exchangeList[177][2] = 6;

	exchangeList[178][0] = 74;
	exchangeList[178][1] = 10;
	exchangeList[178][2] = 16;

	exchangeList[179][0] = 75;
	exchangeList[179][1] = 18;
	exchangeList[179][2] = 1;

	exchangeList[180][0] = 75;
	exchangeList[180][1] = 7;
	exchangeList[180][2] = 2;

	exchangeList[181][0] = 76;
	exchangeList[181][1] = 4;
	exchangeList[181][2] = 6;

	exchangeList[182][0] = 76;
	exchangeList[182][1] = 2;
	exchangeList[182][2] = 0;

	exchangeList[183][0] = 76;
	exchangeList[183][1] = 9;
	exchangeList[183][2] = 11;

	exchangeList[184][0] = 77;
	exchangeList[184][1] = 15;
	exchangeList[184][2] = 3;

	exchangeList[185][0] = 77;
	exchangeList[185][1] = 9;
	exchangeList[185][2] = 0;

	exchangeList[186][0] = 78;
	exchangeList[186][1] = 2;
	exchangeList[186][2] = 17;

	exchangeList[187][0] = 78;
	exchangeList[187][1] = 13;
	exchangeList[187][2] = 2;

	exchangeList[188][0] = 79;
	exchangeList[188][1] = 13;
	exchangeList[188][2] = 2;

	exchangeList[189][0] = 79;
	exchangeList[189][1] = 3;
	exchangeList[189][2] = 7;

	exchangeList[190][0] = 80;
	exchangeList[190][1] = 1;
	exchangeList[190][2] = 5;

	exchangeList[191][0] = 80;
	exchangeList[191][1] = 13;
	exchangeList[191][2] = 0;

	exchangeList[192][0] = 81;
	exchangeList[192][1] = 13;
	exchangeList[192][2] = 0;

	exchangeList[193][0] = 81;
	exchangeList[193][1] = 0;
	exchangeList[193][2] = 17;

	exchangeList[194][0] = 82;
	exchangeList[194][1] = 11;
	exchangeList[194][2] = 2;

	exchangeList[195][0] = 82;
	exchangeList[195][1] = 15;
	exchangeList[195][2] = 1;

	exchangeList[196][0] = 83;
	exchangeList[196][1] = 11;
	exchangeList[196][2] = 9;

	exchangeList[197][0] = 83;
	exchangeList[197][1] = 0;
	exchangeList[197][2] = 2;

	exchangeList[198][0] = 83;
	exchangeList[198][1] = 6;
	exchangeList[198][2] = 4;

	exchangeList[199][0] = 84;
	exchangeList[199][1] = 5;
	exchangeList[199][2] = 0;

	exchangeList[200][0] = 84;
	exchangeList[200][1] = 18;
	exchangeList[200][2] = 3;

	exchangeList[201][0] = 85;
	exchangeList[201][1] = 8;
	exchangeList[201][2] = 16;

	exchangeList[202][0] = 85;
	exchangeList[202][1] = 18;
	exchangeList[202][2] = 4;

	exchangeList[203][0] = 86;
	exchangeList[203][1] = 17;
	exchangeList[203][2] = 17;

	exchangeList[204][0] = 86;
	exchangeList[204][1] = 9;
	exchangeList[204][2] = 11;

	exchangeList[205][0] = 86;
	exchangeList[205][1] = 18;
	exchangeList[205][2] = 18;

	exchangeList[206][0] = 87;
	exchangeList[206][1] = 18;
	exchangeList[206][2] = 10;

	exchangeList[207][0] = 87;
	exchangeList[207][1] = 11;
	exchangeList[207][2] = 17;

	exchangeList[208][0] = 88;
	exchangeList[208][1] = 4;
	exchangeList[208][2] = 5;

	exchangeList[209][0] = 88;
	exchangeList[209][1] = 18;
	exchangeList[209][2] = 17;

	exchangeList[210][0] = 89;
	exchangeList[210][1] = 5;
	exchangeList[210][2] = 18;

	exchangeList[211][0] = 89;
	exchangeList[211][1] = 15;
	exchangeList[211][2] = 6;

	exchangeList[212][0] = 90;
	exchangeList[212][1] = 5;
	exchangeList[212][2] = 7;

	exchangeList[213][0] = 90;
	exchangeList[213][1] = 15;
	exchangeList[213][2] = 15;

	exchangeList[214][0] = 91;
	exchangeList[214][1] = 16;
	exchangeList[214][2] = 5;

	exchangeList[215][0] = 91;
	exchangeList[215][1] = 10;
	exchangeList[215][2] = 17;

	exchangeList[216][0] = 92;
	exchangeList[216][1] = 3;
	exchangeList[216][2] = 0;

	exchangeList[217][0] = 92;
	exchangeList[217][1] = 16;
	exchangeList[217][2] = 10;

	exchangeList[218][0] = 92;
	exchangeList[218][1] = 15;
	exchangeList[218][2] = 5;

	exchangeList[219][0] = 93;
	exchangeList[219][1] = 12;
	exchangeList[219][2] = 5;

	exchangeList[220][0] = 93;
	exchangeList[220][1] = 10;
	exchangeList[220][2] = 15;

	exchangeList[221][0] = 93;
	exchangeList[221][1] = 4;
	exchangeList[221][2] = 18;

	exchangeList[222][0] = 93;
	exchangeList[222][1] = 18;
	exchangeList[222][2] = 11;

	exchangeList[223][0] = 94;
	exchangeList[223][1] = 5;
	exchangeList[223][2] = 11;

	exchangeList[224][0] = 94;
	exchangeList[224][1] = 18;
	exchangeList[224][2] = 13;

	exchangeList[225][0] = 95;
	exchangeList[225][1] = 16;
	exchangeList[225][2] = 16;

	exchangeList[226][0] = 95;
	exchangeList[226][1] = 15;
	exchangeList[226][2] = 15;

	exchangeList[227][0] = 95;
	exchangeList[227][1] = 3;
	exchangeList[227][2] = 1;

	exchangeList[228][0] = 96;
	exchangeList[228][1] = 11;
	exchangeList[228][2] = 17;

	exchangeList[229][0] = 96;
	exchangeList[229][1] = 18;
	exchangeList[229][2] = 7;

	exchangeList[230][0] = 97;
	exchangeList[230][1] = 4;
	exchangeList[230][2] = 6;

	exchangeList[231][0] = 97;
	exchangeList[231][1] = 14;
	exchangeList[231][2] = 14;

	exchangeList[232][0] = 98;
	exchangeList[232][1] = 17;
	exchangeList[232][2] = 17;

	exchangeList[233][0] = 98;
	exchangeList[233][1] = 14;
	exchangeList[233][2] = 14;

	exchangeList[234][0] = 98;
	exchangeList[234][1] = 2;
	exchangeList[234][2] = 0;

	exchangeList[235][0] = 99;
	exchangeList[235][1] = 4;
	exchangeList[235][2] = 3;

	exchangeList[236][0] = 99;
	exchangeList[236][1] = 18;
	exchangeList[236][2] = 2;

	exchangeList[237][0] = 100;
	exchangeList[237][1] = 4;
	exchangeList[237][2] = 18;

	exchangeList[238][0] = 100;
	exchangeList[238][1] = 14;
	exchangeList[238][2] = 5;

	exchangeList[239][0] = 101;
	exchangeList[239][1] = 4;
	exchangeList[239][2] = 10;

	exchangeList[240][0] = 101;
	exchangeList[240][1] = 18;
	exchangeList[240][2] = 12;

	exchangeList[241][0] = 102;
	exchangeList[241][1] = 3;
	exchangeList[241][2] = 1;

	exchangeList[242][0] = 102;
	exchangeList[242][1] = 10;
	exchangeList[242][2] = 8;

	exchangeList[243][0] = 102;
	exchangeList[243][1] = 5;
	exchangeList[243][2] = 7;

	exchangeList[244][0] = 103;
	exchangeList[244][1] = 7;
	exchangeList[244][2] = 4;

	exchangeList[245][0] = 103;
	exchangeList[245][1] = 18;
	exchangeList[245][2] = 16;

	exchangeList[246][0] = 104;
	exchangeList[246][1] = 9;
	exchangeList[246][2] = 14;

	exchangeList[247][0] = 104;
	exchangeList[247][1] = 18;
	exchangeList[247][2] = 10;

	exchangeList[248][0] = 104;
	exchangeList[248][1] = 13;
	exchangeList[248][2] = 4;

	exchangeList[249][0] = 104;
	exchangeList[249][1] = 7;
	exchangeList[249][2] = 18;

	exchangeList[250][0] = 105;
	exchangeList[250][1] = 10;
	exchangeList[250][2] = 1;

	exchangeList[251][0] = 105;
	exchangeList[251][1] = 14;
	exchangeList[251][2] = 0;

	exchangeList[252][0] = 106;
	exchangeList[252][1] = 18;
	exchangeList[252][2] = 9;

	exchangeList[253][0] = 106;
	exchangeList[253][1] = 10;
	exchangeList[253][2] = 16;

	exchangeList[254][0] = 107;
	exchangeList[254][1] = 17;
	exchangeList[254][2] = 9;

	exchangeList[255][0] = 107;
	exchangeList[255][1] = 2;
	exchangeList[255][2] = 3;

	exchangeList[256][0] = 107;
	exchangeList[256][1] = 14;
	exchangeList[256][2] = 4;

	exchangeList[257][0] = 108;
	exchangeList[257][1] = 0;
	exchangeList[257][2] = 4;

	exchangeList[258][0] = 108;
	exchangeList[258][1] = 12;
	exchangeList[258][2] = 3;

	exchangeList[259][0] = 109;
	exchangeList[259][1] = 12;
	exchangeList[259][2] = 3;

	exchangeList[260][0] = 109;
	exchangeList[260][1] = 3;
	exchangeList[260][2] = 16;

	exchangeList[261][0] = 110;
	exchangeList[261][1] = 16;
	exchangeList[261][2] = 16;

	exchangeList[262][0] = 110;
	exchangeList[262][1] = 8;
	exchangeList[262][2] = 10;

	exchangeList[263][0] = 110;
	exchangeList[263][1] = 18;
	exchangeList[263][2] = 18;

	exchangeList[264][0] = 111;
	exchangeList[264][1] = 17;
	exchangeList[264][2] = 4;

	exchangeList[265][0] = 111;
	exchangeList[265][1] = 9;
	exchangeList[265][2] = 16;

	exchangeList[266][0] = 112;
	exchangeList[266][1] = 11;
	exchangeList[266][2] = 16;

	exchangeList[267][0] = 112;
	exchangeList[267][1] = 17;
	exchangeList[267][2] = 6;

	exchangeList[268][0] = 113;
	exchangeList[268][1] = 18;
	exchangeList[268][2] = 18;

	exchangeList[269][0] = 113;
	exchangeList[269][1] = 10;
	exchangeList[269][2] = 8;

	exchangeList[270][0] = 113;
	exchangeList[270][1] = 16;
	exchangeList[270][2] = 16;

	exchangeList[271][0] = 114;
	exchangeList[271][1] = 1;
	exchangeList[271][2] = 16;

	exchangeList[272][0] = 114;
	exchangeList[272][1] = 12;
	exchangeList[272][2] = 1;

	exchangeList[273][0] = 115;
	exchangeList[273][1] = 12;
	exchangeList[273][2] = 1;

	exchangeList[274][0] = 115;
	exchangeList[274][1] = 2;
	exchangeList[274][2] = 6;

	exchangeList[275][0] = 116;
	exchangeList[275][1] = 14;
	exchangeList[275][2] = 6;

	exchangeList[276][0] = 116;
	exchangeList[276][1] = 0;
	exchangeList[276][2] = 1;

	exchangeList[277][0] = 116;
	exchangeList[277][1] = 17;
	exchangeList[277][2] = 11;

	exchangeList[278][0] = 117;
	exchangeList[278][1] = 8;
	exchangeList[278][2] = 16;

	exchangeList[279][0] = 117;
	exchangeList[279][1] = 18;
	exchangeList[279][2] = 11;

	exchangeList[280][0] = 118;
	exchangeList[280][1] = 14;
	exchangeList[280][2] = 2;

	exchangeList[281][0] = 118;
	exchangeList[281][1] = 8;
	exchangeList[281][2] = 3;

	exchangeList[282][0] = 119;
	exchangeList[282][1] = 5;
	exchangeList[282][2] = 18;

	exchangeList[283][0] = 119;
	exchangeList[283][1] = 13;
	exchangeList[283][2] = 6;

	exchangeList[284][0] = 119;
	exchangeList[284][1] = 18;
	exchangeList[284][2] = 8;

	exchangeList[285][0] = 119;
	exchangeList[285][1] = 11;
	exchangeList[285][2] = 14;

	exchangeList[286][0] = 120;
	exchangeList[286][1] = 18;
	exchangeList[286][2] = 16;

	exchangeList[287][0] = 120;
	exchangeList[287][1] = 5;
	exchangeList[287][2] = 6;

	exchangeList[288][0] = 121;
	exchangeList[288][1] = 7;
	exchangeList[288][2] = 5;
	//						   
	exchangeList[289][0] = 121;
	exchangeList[289][1] = 8;
	exchangeList[289][2] = 10;

	exchangeList[290][0] = 121;
	exchangeList[290][1] = 1;
	exchangeList[290][2] = 3;

	exchangeList[291][0] = 122;
	exchangeList[291][1] = 18;
	exchangeList[291][2] = 12;

	exchangeList[292][0] = 122;
	exchangeList[292][1] = 6;
	exchangeList[292][2] = 8;

	exchangeList[293][0] = 123;
	exchangeList[293][1] = 14;
	exchangeList[293][2] = 7;

	exchangeList[294][0] = 123;
	exchangeList[294][1] = 6;
	exchangeList[294][2] = 18;

	exchangeList[295][0] = 124;
	exchangeList[295][1] = 18;
	exchangeList[295][2] = 0;

	exchangeList[296][0] = 124;
	exchangeList[296][1] = 6;
	exchangeList[296][2] = 1;

	exchangeList[297][0] = 125;
	exchangeList[297][1] = 0;
	exchangeList[297][2] = 2;

	exchangeList[298][0] = 125;
	exchangeList[298][1] = 14;
	exchangeList[298][2] = 14;

	exchangeList[299][0] = 125;
	exchangeList[299][1] = 17;
	exchangeList[299][2] = 17;

	exchangeList[300][0] = 126;
	exchangeList[300][1] = 14;
	exchangeList[300][2] = 14;

	exchangeList[301][0] = 126;
	exchangeList[301][1] = 6;
	exchangeList[301][2] = 4;

	exchangeList[302][0] = 127;
	exchangeList[302][1] = 18;
	exchangeList[302][2] = 5;

	exchangeList[303][0] = 127;
	exchangeList[303][1] = 9;
	exchangeList[303][2] = 17;
}


void bigPicture::setExchangeListPos(int** list)
{
	exchangeListPos = new int*[MAXELN];
	for (int i = 0; i < MAXELN; i++)
	{
		exchangeListPos[i] = new int[5];
		exchangeListPos[i][0] = -1;	//블록쌍 라벨
		exchangeListPos[i][1] = -1;	//첫번째 블록 x위치
		exchangeListPos[i][2] = -1;	//첫번째 블록 y위치
		exchangeListPos[i][3] = -1;	//두번째 블록 x위치
		exchangeListPos[i][4] = -1;	//두번째 블록 y위치
	}
	//

	//1장
	exchangeListPos[0][0] = 0;
	exchangeListPos[0][1] = 0;
	exchangeListPos[0][2] = 0;
	exchangeListPos[0][3] = 0;
	exchangeListPos[0][4] = 3;

	exchangeListPos[1][0] = 0;
	exchangeListPos[1][1] = 0;
	exchangeListPos[1][2] = 0;
	exchangeListPos[1][3] = 1;
	exchangeListPos[1][4] = 2;

	exchangeListPos[2][0] = 1;
	exchangeListPos[2][1] = 0;
	exchangeListPos[2][2] = 0;
	exchangeListPos[2][3] = 0;
	exchangeListPos[2][4] = 2;

	exchangeListPos[3][0] = 1;
	exchangeListPos[3][1] = 0;
	exchangeListPos[3][2] = 2;
	exchangeListPos[3][3] = 2;
	exchangeListPos[3][4] = 3;

	exchangeListPos[4][0] = 1;
	exchangeListPos[4][1] = 0;
	exchangeListPos[4][2] = 0;
	exchangeListPos[4][3] = 1;
	exchangeListPos[4][4] = 1;

	exchangeListPos[5][0] = 2;
	exchangeListPos[5][1] = 1;
	exchangeListPos[5][2] = 0;
	exchangeListPos[5][3] = 1;
	exchangeListPos[5][4] = 1;

	exchangeListPos[6][0] = 2;
	exchangeListPos[6][1] = 0;
	exchangeListPos[6][2] = 0;
	exchangeListPos[6][3] = 0;
	exchangeListPos[6][4] = 2;

	exchangeListPos[7][0] = 2;
	exchangeListPos[7][1] = 0;
	exchangeListPos[7][2] = 0;
	exchangeListPos[7][3] = 0;
	exchangeListPos[7][4] = 1;

	exchangeListPos[8][0] = 2;
	exchangeListPos[8][1] = 0;
	exchangeListPos[8][2] = 0;
	exchangeListPos[8][3] = 1;
	exchangeListPos[8][4] = 0;

	exchangeListPos[9][0] = 3;
	exchangeListPos[9][1] = 0;
	exchangeListPos[9][2] = 1;
	exchangeListPos[9][3] = 3;
	exchangeListPos[9][4] = 0;

	exchangeListPos[10][0] = 3;
	exchangeListPos[10][1] = 0;
	exchangeListPos[10][2] = 1;
	exchangeListPos[10][3] = 1;
	exchangeListPos[10][4] = 1;

	exchangeListPos[11][0] = 4;
	exchangeListPos[11][1] = 0;
	exchangeListPos[11][2] = 2;
	exchangeListPos[11][3] = 1;
	exchangeListPos[11][4] = 2;

	exchangeListPos[12][0] = 4;
	exchangeListPos[12][1] = 0;
	exchangeListPos[12][2] = 0;
	exchangeListPos[12][3] = 0;
	exchangeListPos[12][4] = 2;

	exchangeListPos[13][0] = 4;
	exchangeListPos[13][1] = 0;
	exchangeListPos[13][2] = 0;
	exchangeListPos[13][3] = 1;
	exchangeListPos[13][4] = 1;

	exchangeListPos[14][0] = 5;
	exchangeListPos[14][1] = 0;
	exchangeListPos[14][2] = 0;
	exchangeListPos[14][3] = 2;
	exchangeListPos[14][4] = 0;

	exchangeListPos[15][0] = 5;
	exchangeListPos[15][1] = 2;
	exchangeListPos[15][2] = 0;
	exchangeListPos[15][3] = 1;
	exchangeListPos[15][4] = 1;

	exchangeListPos[16][0] = 5;
	exchangeListPos[16][1] = 0;
	exchangeListPos[16][2] = 0;
	exchangeListPos[16][3] = 0;
	exchangeListPos[16][4] = 1;

	exchangeListPos[17][0] = 6;
	exchangeListPos[17][1] = 0;
	exchangeListPos[17][2] = 1;
	exchangeListPos[17][3] = 0;
	exchangeListPos[17][4] = 2;

	exchangeListPos[18][0] = 6;
	exchangeListPos[18][1] = 0;
	exchangeListPos[18][2] = 1;
	exchangeListPos[18][3] = 2;
	exchangeListPos[18][4] = 0;

	exchangeListPos[19][0] = 7;
	exchangeListPos[19][1] = 0;
	exchangeListPos[19][2] = 0;
	exchangeListPos[19][3] = 0;
	exchangeListPos[19][4] = 2;

	exchangeListPos[20][0] = 7;
	exchangeListPos[20][1] = 1;
	exchangeListPos[20][2] = 0;
	exchangeListPos[20][3] = 1;
	exchangeListPos[20][4] = 1;

	exchangeListPos[21][0] = 8;
	exchangeListPos[21][1] = 0;
	exchangeListPos[21][2] = 0;
	exchangeListPos[21][3] = 1;
	exchangeListPos[21][4] = 3;

	exchangeListPos[22][0] = 8;
	exchangeListPos[22][1] = 0;
	exchangeListPos[22][2] = 0;
	exchangeListPos[22][3] = 1;
	exchangeListPos[22][4] = 2;

	exchangeListPos[23][0] = 9;
	exchangeListPos[23][1] = 0;
	exchangeListPos[23][2] = 0;
	exchangeListPos[23][3] = 2;
	exchangeListPos[23][4] = 1;

	exchangeListPos[24][0] = 9;
	exchangeListPos[24][1] = 0;
	exchangeListPos[24][2] = 0;
	exchangeListPos[24][3] = 3;
	exchangeListPos[24][4] = 3;

	exchangeListPos[25][0] = 10;
	exchangeListPos[25][1] = 2;
	exchangeListPos[25][2] = 1;
	exchangeListPos[25][3] = 0;
	exchangeListPos[25][4] = 2;

	exchangeListPos[26][0] = 10;
	exchangeListPos[26][1] = 1;
	exchangeListPos[26][2] = 0;
	exchangeListPos[26][3] = 3;
	exchangeListPos[26][4] = 2;

	exchangeListPos[27][0] = 11;
	exchangeListPos[27][1] = 0;
	exchangeListPos[27][2] = 1;
	exchangeListPos[27][3] = 2;
	exchangeListPos[27][4] = 0;

	exchangeListPos[28][0] = 11;
	exchangeListPos[28][1] = 0;
	exchangeListPos[28][2] = 1;
	exchangeListPos[28][3] = 0;
	exchangeListPos[28][4] = 2;

	exchangeListPos[29][0] = 12;
	exchangeListPos[29][1] = 0;
	exchangeListPos[29][2] = 2;
	exchangeListPos[29][3] = 3;
	exchangeListPos[29][4] = 0;

	exchangeListPos[30][0] = 12;
	exchangeListPos[30][1] = 0;
	exchangeListPos[30][2] = 2;
	exchangeListPos[30][3] = 3;
	exchangeListPos[30][4] = 0;

	exchangeListPos[31][0] = 12;
	exchangeListPos[31][1] = 2;
	exchangeListPos[31][2] = 2;
	exchangeListPos[31][3] = 1;
	exchangeListPos[31][4] = 0;

	exchangeListPos[32][0] = 13;
	exchangeListPos[32][1] = 0;
	exchangeListPos[32][2] = 1;
	exchangeListPos[32][3] = 2;
	exchangeListPos[32][4] = 2;

	exchangeListPos[33][0] = 13;
	exchangeListPos[33][1] = 0;
	exchangeListPos[33][2] = 1;
	exchangeListPos[33][3] = 3;
	exchangeListPos[33][4] = 1;

	exchangeListPos[34][0] = 14;
	exchangeListPos[34][1] = 0;
	exchangeListPos[34][2] = 0;
	exchangeListPos[34][3] = 1;
	exchangeListPos[34][4] = 2;

	exchangeListPos[35][0] = 14;
	exchangeListPos[35][1] = 1;
	exchangeListPos[35][2] = 2;
	exchangeListPos[35][3] = 0;
	exchangeListPos[35][4] = 1;

	exchangeListPos[36][0] = 15;
	exchangeListPos[36][1] = 1;
	exchangeListPos[36][2] = 0;
	exchangeListPos[36][3] = 2;
	exchangeListPos[36][4] = 3;

	exchangeListPos[37][0] = 15;
	exchangeListPos[37][1] = 1;
	exchangeListPos[37][2] = 0;
	exchangeListPos[37][3] = 0;
	exchangeListPos[37][4] = 2;

	exchangeListPos[38][0] = 16;
	exchangeListPos[38][1] = 1;
	exchangeListPos[38][2] = 3;
	exchangeListPos[38][3] = 2;
	exchangeListPos[38][4] = 1;

	exchangeListPos[39][0] = 16;
	exchangeListPos[39][1] = 2;
	exchangeListPos[39][2] = 1;
	exchangeListPos[39][3] = 0;
	exchangeListPos[39][4] = 0;

	exchangeListPos[40][0] = 17;
	exchangeListPos[40][1] = 0;
	exchangeListPos[40][2] = 2;
	exchangeListPos[40][3] = 1;
	exchangeListPos[40][4] = 0;

	exchangeListPos[41][0] = 17;
	exchangeListPos[41][1] = 0;
	exchangeListPos[41][2] = 3;
	exchangeListPos[41][3] = 0;
	exchangeListPos[41][4] = 2;

	exchangeListPos[42][0] = 18;
	exchangeListPos[42][1] = 3;
	exchangeListPos[42][2] = 1;
	exchangeListPos[42][3] = 0;
	exchangeListPos[42][4] = 1;

	exchangeListPos[43][0] = 18;
	exchangeListPos[43][1] = 2;
	exchangeListPos[43][2] = 0;
	exchangeListPos[43][3] = 1;
	exchangeListPos[43][4] = 0;

	exchangeListPos[44][0] = 19;
	exchangeListPos[44][1] = 1;
	exchangeListPos[44][2] = 0;
	exchangeListPos[44][3] = 2;
	exchangeListPos[44][4] = 2;

	exchangeListPos[45][0] = 19;
	exchangeListPos[45][1] = 3;
	exchangeListPos[45][2] = 0;
	exchangeListPos[45][3] = 0;
	exchangeListPos[45][4] = 2;

	exchangeListPos[46][0] = 19;
	exchangeListPos[46][1] = 3;
	exchangeListPos[46][2] = 0;
	exchangeListPos[46][3] = 0;
	exchangeListPos[46][4] = 2;

	exchangeListPos[47][0] = 20;
	exchangeListPos[47][1] = 2;
	exchangeListPos[47][2] = 2;
	exchangeListPos[47][3] = 2;
	exchangeListPos[47][4] = 1;

	exchangeListPos[48][0] = 20;
	exchangeListPos[48][1] = 1;
	exchangeListPos[48][2] = 0;
	exchangeListPos[48][3] = 0;
	exchangeListPos[48][4] = 3;

	exchangeListPos[49][0] = 21;
	exchangeListPos[49][1] = 3;
	exchangeListPos[49][2] = 0;
	exchangeListPos[49][3] = 0;
	exchangeListPos[49][4] = 0;

	exchangeListPos[50][0] = 21;
	exchangeListPos[50][1] = 1;
	exchangeListPos[50][2] = 1;
	exchangeListPos[50][3] = 0;
	exchangeListPos[50][4] = 0;

	exchangeListPos[51][0] = 22;
	exchangeListPos[51][1] = 3;
	exchangeListPos[51][2] = 3;
	exchangeListPos[51][3] = 0;
	exchangeListPos[51][4] = 0;

	exchangeListPos[52][0] = 22;
	exchangeListPos[52][1] = 2;
	exchangeListPos[52][2] = 1;
	exchangeListPos[52][3] = 0;
	exchangeListPos[52][4] = 0;

	exchangeListPos[53][0] = 23;
	exchangeListPos[53][1] = 2;
	exchangeListPos[53][2] = 3;
	exchangeListPos[53][3] = 0;
	exchangeListPos[53][4] = 0;

	exchangeListPos[54][0] = 23;
	exchangeListPos[54][1] = 1;
	exchangeListPos[54][2] = 1;
	exchangeListPos[54][3] = 1;
	exchangeListPos[54][4] = 0;

	exchangeListPos[55][0] = 24;
	exchangeListPos[55][1] = 2;
	exchangeListPos[55][2] = 2;
	exchangeListPos[55][3] = 2;
	exchangeListPos[55][4] = 1;

	exchangeListPos[56][0] = 24;
	exchangeListPos[56][1] = 2;
	exchangeListPos[56][2] = 1;
	exchangeListPos[56][3] = 0;
	exchangeListPos[56][4] = 0;

	exchangeListPos[57][0] = 25;
	exchangeListPos[57][1] = 2;
	exchangeListPos[57][2] = 0;
	exchangeListPos[57][3] = 1;
	exchangeListPos[57][4] = 2;

	exchangeListPos[58][0] = 25;
	exchangeListPos[58][1] = 3;
	exchangeListPos[58][2] = 1;
	exchangeListPos[58][3] = 0;
	exchangeListPos[58][4] = 0;

	exchangeListPos[59][0] = 26;
	exchangeListPos[59][1] = 0;
	exchangeListPos[59][2] = 1;
	exchangeListPos[59][3] = 0;
	exchangeListPos[59][4] = 0;

	exchangeListPos[60][0] = 26;
	exchangeListPos[60][1] = 1;
	exchangeListPos[60][2] = 1;
	exchangeListPos[60][3] = 2;
	exchangeListPos[60][4] = 0;

	exchangeListPos[61][0] = 26;
	exchangeListPos[61][1] = 2;
	exchangeListPos[61][2] = 0;
	exchangeListPos[61][3] = 0;
	exchangeListPos[61][4] = 0;

	exchangeListPos[62][0] = 27;
	exchangeListPos[62][1] = 1;
	exchangeListPos[62][2] = 1;
	exchangeListPos[62][3] = 0;
	exchangeListPos[62][4] = 0;

	exchangeListPos[63][0] = 27;
	exchangeListPos[63][1] = 0;
	exchangeListPos[63][2] = 2;
	exchangeListPos[63][3] = 0;
	exchangeListPos[63][4] = 0;

	exchangeListPos[64][0] = 27;
	exchangeListPos[64][1] = 1;
	exchangeListPos[64][2] = 2;
	exchangeListPos[64][3] = 0;
	exchangeListPos[64][4] = 2;

	exchangeListPos[65][0] = 28;
	exchangeListPos[65][1] = 3;
	exchangeListPos[65][2] = 1;
	exchangeListPos[65][3] = 2;
	exchangeListPos[65][4] = 1;

	exchangeListPos[66][0] = 28;
	exchangeListPos[66][1] = 2;
	exchangeListPos[66][2] = 0;
	exchangeListPos[66][3] = 1;
	exchangeListPos[66][4] = 0;

	exchangeListPos[67][0] = 29;
	exchangeListPos[67][1] = 2;
	exchangeListPos[67][2] = 2;
	exchangeListPos[67][3] = 0;
	exchangeListPos[67][4] = 0;

	exchangeListPos[68][0] = 29;
	exchangeListPos[68][1] = 0;
	exchangeListPos[68][2] = 1;
	exchangeListPos[68][3] = 2;
	exchangeListPos[68][4] = 1;

	exchangeListPos[69][0] = 29;
	exchangeListPos[69][1] = 1;
	exchangeListPos[69][2] = 1;
	exchangeListPos[69][3] = 2;
	exchangeListPos[69][4] = 0;

	exchangeListPos[70][0] = 29;
	exchangeListPos[70][1] = 1;
	exchangeListPos[70][2] = 2;
	exchangeListPos[70][3] = 0;
	exchangeListPos[70][4] = 0;

	exchangeListPos[71][0] = 30;
	exchangeListPos[71][1] = 2;
	exchangeListPos[71][2] = 0;
	exchangeListPos[71][3] = 1;
	exchangeListPos[71][4] = 2;

	exchangeListPos[72][0] = 30;
	exchangeListPos[72][1] = 2;
	exchangeListPos[72][2] = 1;
	exchangeListPos[72][3] = 0;
	exchangeListPos[72][4] = 0;

	exchangeListPos[73][0] = 30;
	exchangeListPos[73][1] = 1;
	exchangeListPos[73][2] = 1;
	exchangeListPos[73][3] = 2;
	exchangeListPos[73][4] = 1;

	exchangeListPos[74][0] = 31;
	exchangeListPos[74][1] = 3;
	exchangeListPos[74][2] = 0;
	exchangeListPos[74][3] = 2;
	exchangeListPos[74][4] = 1;

	exchangeListPos[75][0] = 31;
	exchangeListPos[75][1] = 3;
	exchangeListPos[75][2] = 3;
	exchangeListPos[75][3] = 0;
	exchangeListPos[75][4] = 0;

	//3장
	exchangeListPos[76][0] = 32;
	exchangeListPos[76][1] = 0;
	exchangeListPos[76][2] = 1;
	exchangeListPos[76][3] = 1;
	exchangeListPos[76][4] = 0;

	exchangeListPos[77][0] = 32;
	exchangeListPos[77][1] = 0;
	exchangeListPos[77][2] = 1;
	exchangeListPos[77][3] = 2;
	exchangeListPos[77][4] = 1;

	exchangeListPos[78][0] = 32;
	exchangeListPos[78][1] = 2;
	exchangeListPos[78][2] = 1;
	exchangeListPos[78][3] = 2;
	exchangeListPos[78][4] = 0;

	exchangeListPos[79][0] = 33;
	exchangeListPos[79][1] = 0;
	exchangeListPos[79][2] = 3;
	exchangeListPos[79][3] = 3;
	exchangeListPos[79][4] = 0;

	exchangeListPos[80][0] = 33;
	exchangeListPos[80][1] = 0;
	exchangeListPos[80][2] = 3;
	exchangeListPos[80][3] = 1;
	exchangeListPos[80][4] = 1;

	exchangeListPos[81][0] = 34;
	exchangeListPos[81][1] = 2;
	exchangeListPos[81][2] = 0;
	exchangeListPos[81][3] = 1;
	exchangeListPos[81][4] = 1;

	exchangeListPos[82][0] = 34;
	exchangeListPos[82][1] = 0;
	exchangeListPos[82][2] = 0;
	exchangeListPos[82][3] = 2;
	exchangeListPos[82][4] = 0;

	exchangeListPos[83][0] = 35;
	exchangeListPos[83][1] = 1;
	exchangeListPos[83][2] = 3;
	exchangeListPos[83][3] = 1;
	exchangeListPos[83][4] = 2;

	exchangeListPos[84][0] = 35;
	exchangeListPos[84][1] = 1;
	exchangeListPos[84][2] = 2;
	exchangeListPos[84][3] = 0;
	exchangeListPos[84][4] = 0;

	exchangeListPos[85][0] = 36;
	exchangeListPos[85][1] = 0;
	exchangeListPos[85][2] = 2;
	exchangeListPos[85][3] = 2;
	exchangeListPos[85][4] = 0;

	exchangeListPos[86][0] = 36;
	exchangeListPos[86][1] = 0;
	exchangeListPos[86][2] = 2;
	exchangeListPos[86][3] = 3;
	exchangeListPos[86][4] = 1;

	exchangeListPos[87][0] = 37;
	exchangeListPos[87][1] = 1;
	exchangeListPos[87][2] = 3;
	exchangeListPos[87][3] = 1;
	exchangeListPos[87][4] = 0;

	exchangeListPos[88][0] = 37;
	exchangeListPos[88][1] = 1;
	exchangeListPos[88][2] = 2;
	exchangeListPos[88][3] = 2;
	exchangeListPos[88][4] = 1;

	exchangeListPos[89][0] = 38;
	exchangeListPos[89][1] = 0;
	exchangeListPos[89][2] = 1;
	exchangeListPos[89][3] = 2;
	exchangeListPos[89][4] = 2;

	exchangeListPos[90][0] = 38;
	exchangeListPos[90][1] = 0;
	exchangeListPos[90][2] = 2;
	exchangeListPos[90][3] = 0;
	exchangeListPos[90][4] = 1;

	exchangeListPos[91][0] = 38;
	exchangeListPos[91][1] = 0;
	exchangeListPos[91][2] = 1;
	exchangeListPos[91][3] = 1;
	exchangeListPos[91][4] = 0;

	exchangeListPos[92][0] = 38;
	exchangeListPos[92][1] = 1;
	exchangeListPos[92][2] = 0;
	exchangeListPos[92][3] = 1;
	exchangeListPos[92][4] = 2;

	exchangeListPos[93][0] = 39;
	exchangeListPos[93][1] = 0;
	exchangeListPos[93][2] = 2;
	exchangeListPos[93][3] = 1;
	exchangeListPos[93][4] = 2;

	exchangeListPos[94][0] = 39;
	exchangeListPos[94][1] = 0;
	exchangeListPos[94][2] = 2;
	exchangeListPos[94][3] = 2;
	exchangeListPos[94][4] = 0;

	exchangeListPos[95][0] = 40;
	exchangeListPos[95][1] = 2;
	exchangeListPos[95][2] = 1;
	exchangeListPos[95][3] = 0;
	exchangeListPos[95][4] = 2;

	exchangeListPos[96][0] = 40;
	exchangeListPos[96][1] = 2;
	exchangeListPos[96][2] = 3;
	exchangeListPos[96][3] = 0;
	exchangeListPos[96][4] = 0;

	exchangeListPos[97][0] = 40;
	exchangeListPos[97][1] = 2;
	exchangeListPos[97][2] = 3;
	exchangeListPos[97][3] = 0;
	exchangeListPos[97][4] = 0;

	exchangeListPos[98][0] = 41;
	exchangeListPos[98][1] = 0;
	exchangeListPos[98][2] = 2;
	exchangeListPos[98][3] = 1;
	exchangeListPos[98][4] = 1;

	exchangeListPos[99][0] = 41;
	exchangeListPos[99][1] = 0;
	exchangeListPos[99][2] = 2;
	exchangeListPos[99][3] = 2;
	exchangeListPos[99][4] = 2;

	exchangeListPos[100][0] = 41;
	exchangeListPos[100][1] = 2;
	exchangeListPos[100][2] = 2;
	exchangeListPos[100][3] = 3;
	exchangeListPos[100][4] = 0;

	exchangeListPos[101][0] = 42;
	exchangeListPos[101][1] = 1;
	exchangeListPos[101][2] = 2;
	exchangeListPos[101][3] = 0;
	exchangeListPos[101][4] = 1;

	exchangeListPos[102][0] = 42;
	exchangeListPos[102][1] = 1;
	exchangeListPos[102][2] = 3;
	exchangeListPos[102][3] = 2;
	exchangeListPos[102][4] = 0;

	exchangeListPos[103][0] = 43;
	exchangeListPos[103][1] = 1;
	exchangeListPos[103][2] = 2;
	exchangeListPos[103][3] = 2;
	exchangeListPos[103][4] = 2;

	exchangeListPos[104][0] = 43;
	exchangeListPos[104][1] = 1;
	exchangeListPos[104][2] = 2;
	exchangeListPos[104][3] = 0;
	exchangeListPos[104][4] = 0;

	exchangeListPos[105][0] = 44;
	exchangeListPos[105][1] = 0;
	exchangeListPos[105][2] = 3;
	exchangeListPos[105][3] = 2;
	exchangeListPos[105][4] = 2;

	exchangeListPos[106][0] = 44;
	exchangeListPos[106][1] = 0;
	exchangeListPos[106][2] = 3;
	exchangeListPos[106][3] = 3;
	exchangeListPos[106][4] = 0;

	exchangeListPos[107][0] = 45;
	exchangeListPos[107][1] = 0;
	exchangeListPos[107][2] = 0;
	exchangeListPos[107][3] = 1;
	exchangeListPos[107][4] = 0;

	exchangeListPos[108][0] = 45;
	exchangeListPos[108][1] = 0;
	exchangeListPos[108][2] = 1;
	exchangeListPos[108][3] = 1;
	exchangeListPos[108][4] = 2;

	exchangeListPos[109][0] = 45;
	exchangeListPos[109][1] = 0;
	exchangeListPos[109][2] = 2;
	exchangeListPos[109][3] = 0;
	exchangeListPos[109][4] = 0;

	exchangeListPos[110][0] = 46;
	exchangeListPos[110][1] = 0;
	exchangeListPos[110][2] = 2;
	exchangeListPos[110][3] = 2;
	exchangeListPos[110][4] = 0;

	exchangeListPos[111][0] = 46;
	exchangeListPos[111][1] = 1;
	exchangeListPos[111][2] = 1;
	exchangeListPos[111][3] = 2;
	exchangeListPos[111][4] = 0;

	exchangeListPos[112][0] = 47;
	exchangeListPos[112][1] = 0;
	exchangeListPos[112][2] = 1;
	exchangeListPos[112][3] = 2;
	exchangeListPos[112][4] = 2;

	exchangeListPos[113][0] = 47;
	exchangeListPos[113][1] = 0;
	exchangeListPos[113][2] = 1;
	exchangeListPos[113][3] = 3;
	exchangeListPos[113][4] = 0;

	//4장
	exchangeListPos[114][0] = 48;
	exchangeListPos[114][1] = 1;
	exchangeListPos[114][2] = 0;
	exchangeListPos[114][3] = 0;
	exchangeListPos[114][4] = 2;

	exchangeListPos[115][0] = 48;
	exchangeListPos[115][1] = 3;
	exchangeListPos[115][2] = 1;
	exchangeListPos[115][3] = 1;
	exchangeListPos[115][4] = 0;

	exchangeListPos[116][0] = 49;
	exchangeListPos[116][1] = 1;
	exchangeListPos[116][2] = 2;
	exchangeListPos[116][3] = 0;
	exchangeListPos[116][4] = 0;

	exchangeListPos[117][0] = 49;
	exchangeListPos[117][1] = 0;
	exchangeListPos[117][2] = 0;
	exchangeListPos[117][3] = 0;
	exchangeListPos[117][4] = 3;

	exchangeListPos[118][0] = 50;
	exchangeListPos[118][1] = 0;
	exchangeListPos[118][2] = 0;
	exchangeListPos[118][3] = 0;
	exchangeListPos[118][4] = 2;

	exchangeListPos[119][0] = 50;
	exchangeListPos[119][1] = 1;
	exchangeListPos[119][2] = 2;
	exchangeListPos[119][3] = 0;
	exchangeListPos[119][4] = 1;

	exchangeListPos[120][0] = 50;
	exchangeListPos[120][1] = 1;
	exchangeListPos[120][2] = 0;
	exchangeListPos[120][3] = 0;
	exchangeListPos[120][4] = 0;

	exchangeListPos[121][0] = 51;
	exchangeListPos[121][1] = 3;
	exchangeListPos[121][2] = 0;
	exchangeListPos[121][3] = 0;
	exchangeListPos[121][4] = 0;

	exchangeListPos[122][0] = 51;
	exchangeListPos[122][1] = 0;
	exchangeListPos[122][2] = 0;
	exchangeListPos[122][3] = 1;
	exchangeListPos[122][4] = 1;

	exchangeListPos[123][0] = 52;
	exchangeListPos[123][1] = 0;
	exchangeListPos[123][2] = 1;
	exchangeListPos[123][3] = 3;
	exchangeListPos[123][4] = 2;

	exchangeListPos[124][0] = 52;
	exchangeListPos[124][1] = 2;
	exchangeListPos[124][2] = 0;
	exchangeListPos[124][3] = 1;
	exchangeListPos[124][4] = 0;

	exchangeListPos[125][0] = 53;
	exchangeListPos[125][1] = 1;
	exchangeListPos[125][2] = 0;
	exchangeListPos[125][3] = 0;
	exchangeListPos[125][4] = 0;

	exchangeListPos[126][0] = 53;
	exchangeListPos[126][1] = 0;
	exchangeListPos[126][2] = 0;
	exchangeListPos[126][3] = 2;
	exchangeListPos[126][4] = 2;

	exchangeListPos[127][0] = 54;
	exchangeListPos[127][1] = 1;
	exchangeListPos[127][2] = 0;
	exchangeListPos[127][3] = 0;
	exchangeListPos[127][4] = 2;

	exchangeListPos[128][0] = 54;
	exchangeListPos[128][1] = 1;
	exchangeListPos[128][2] = 1;
	exchangeListPos[128][3] = 1;
	exchangeListPos[128][4] = 0;

	exchangeListPos[129][0] = 54;
	exchangeListPos[129][1] = 0;
	exchangeListPos[129][2] = 0;
	exchangeListPos[129][3] = 2;
	exchangeListPos[129][4] = 1;

	exchangeListPos[130][0] = 55;
	exchangeListPos[130][1] = 0;
	exchangeListPos[130][2] = 0;
	exchangeListPos[130][3] = 2;
	exchangeListPos[130][4] = 3;

	exchangeListPos[131][0] = 55;
	exchangeListPos[131][1] = 0;
	exchangeListPos[131][2] = 0;
	exchangeListPos[131][3] = 2;
	exchangeListPos[131][4] = 3;

	exchangeListPos[132][0] = 55;
	exchangeListPos[132][1] = 0;
	exchangeListPos[132][2] = 2;
	exchangeListPos[132][3] = 2;
	exchangeListPos[132][4] = 1;

	exchangeListPos[133][0] = 56;
	exchangeListPos[133][1] = 1;
	exchangeListPos[133][2] = 0;
	exchangeListPos[133][3] = 0;
	exchangeListPos[133][4] = 0;

	exchangeListPos[134][0] = 56;
	exchangeListPos[134][1] = 2;
	exchangeListPos[134][2] = 1;
	exchangeListPos[134][3] = 1;
	exchangeListPos[134][4] = 1;

	exchangeListPos[135][0] = 57;
	exchangeListPos[135][1] = 2;
	exchangeListPos[135][2] = 0;
	exchangeListPos[135][3] = 1;
	exchangeListPos[135][4] = 0;

	exchangeListPos[136][0] = 57;
	exchangeListPos[136][1] = 2;
	exchangeListPos[136][2] = 1;
	exchangeListPos[136][3] = 0;
	exchangeListPos[136][4] = 1;

	exchangeListPos[137][0] = 57;
	exchangeListPos[137][1] = 2;
	exchangeListPos[137][2] = 0;
	exchangeListPos[137][3] = 0;
	exchangeListPos[137][4] = 2;

	exchangeListPos[138][0] = 57;
	exchangeListPos[138][1] = 1;
	exchangeListPos[138][2] = 0;
	exchangeListPos[138][3] = 0;
	exchangeListPos[138][4] = 0;

	exchangeListPos[139][0] = 58;
	exchangeListPos[139][1] = 0;
	exchangeListPos[139][2] = 0;
	exchangeListPos[139][3] = 0;
	exchangeListPos[139][4] = 2;

	exchangeListPos[140][0] = 58;
	exchangeListPos[140][1] = 1;
	exchangeListPos[140][2] = 0;
	exchangeListPos[140][3] = 1;
	exchangeListPos[140][4] = 3;

	exchangeListPos[141][0] = 59;
	exchangeListPos[141][1] = 1;
	exchangeListPos[141][2] = 1;
	exchangeListPos[141][3] = 0;
	exchangeListPos[141][4] = 1;

	exchangeListPos[142][0] = 59;
	exchangeListPos[142][1] = 3;
	exchangeListPos[142][2] = 0;
	exchangeListPos[142][3] = 0;
	exchangeListPos[142][4] = 1;

	exchangeListPos[143][0] = 60;
	exchangeListPos[143][1] = 0;
	exchangeListPos[143][2] = 0;
	exchangeListPos[143][3] = 0;
	exchangeListPos[143][4] = 2;

	exchangeListPos[144][0] = 60;
	exchangeListPos[144][1] = 1;
	exchangeListPos[144][2] = 0;
	exchangeListPos[144][3] = 1;
	exchangeListPos[144][4] = 1;

	exchangeListPos[145][0] = 61;
	exchangeListPos[145][1] = 3;
	exchangeListPos[145][2] = 0;
	exchangeListPos[145][3] = 2;
	exchangeListPos[145][4] = 1;

	exchangeListPos[146][0] = 61;
	exchangeListPos[146][1] = 2;
	exchangeListPos[146][2] = 1;
	exchangeListPos[146][3] = 0;
	exchangeListPos[146][4] = 0;

	exchangeListPos[147][0] = 62;
	exchangeListPos[147][1] = 1;
	exchangeListPos[147][2] = 1;
	exchangeListPos[147][3] = 0;
	exchangeListPos[147][4] = 3;

	exchangeListPos[148][0] = 62;
	exchangeListPos[148][1] = 3;
	exchangeListPos[148][2] = 0;
	exchangeListPos[148][3] = 0;
	exchangeListPos[148][4] = 3;

	exchangeListPos[149][0] = 63;
	exchangeListPos[149][1] = 2;
	exchangeListPos[149][2] = 0;
	exchangeListPos[149][3] = 2;
	exchangeListPos[149][4] = 1;

	exchangeListPos[150][0] = 63;
	exchangeListPos[150][1] = 2;
	exchangeListPos[150][2] = 1;
	exchangeListPos[150][3] = 0;
	exchangeListPos[150][4] = 1;

	exchangeListPos[151][0] = 63;
	exchangeListPos[151][1] = 1;
	exchangeListPos[151][2] = 0;
	exchangeListPos[151][3] = 0;
	exchangeListPos[151][4] = 1;
	//
	exchangeListPos[152][0] = 64;
	exchangeListPos[152][1] = 1;
	exchangeListPos[152][2] = 0;
	exchangeListPos[152][3] = 0;
	exchangeListPos[152][4] = 4;

	exchangeListPos[153][0] = 64;
	exchangeListPos[153][1] = 1;
	exchangeListPos[153][2] = 0;
	exchangeListPos[153][3] = 1;
	exchangeListPos[153][4] = 2;

	exchangeListPos[154][0] = 64;
	exchangeListPos[154][1] = 1;
	exchangeListPos[154][2] = 0;
	exchangeListPos[154][3] = 0;
	exchangeListPos[154][4] = 1;

	exchangeListPos[155][0] = 65;
	exchangeListPos[155][1] = 2;
	exchangeListPos[155][2] = 1;
	exchangeListPos[155][3] = 0;
	exchangeListPos[155][4] = 0;

	exchangeListPos[156][0] = 65;
	exchangeListPos[156][1] = 1;
	exchangeListPos[156][2] = 2;
	exchangeListPos[156][3] = 0;
	exchangeListPos[156][4] = 0;

	exchangeListPos[157][0] = 66;
	exchangeListPos[157][1] = 1;
	exchangeListPos[157][2] = 0;
	exchangeListPos[157][3] = 0;
	exchangeListPos[157][4] = 1;

	exchangeListPos[158][0] = 66;
	exchangeListPos[158][1] = 2;
	exchangeListPos[158][2] = 2;
	exchangeListPos[158][3] = 0;
	exchangeListPos[158][4] = 1;

	exchangeListPos[159][0] = 66;
	exchangeListPos[159][1] = 1;
	exchangeListPos[159][2] = 2;
	exchangeListPos[159][3] = 1;
	exchangeListPos[159][4] = 0;

	exchangeListPos[160][0] = 66;
	exchangeListPos[160][1] = 0;
	exchangeListPos[160][2] = 1;
	exchangeListPos[160][3] = 0;
	exchangeListPos[160][4] = 2;

	exchangeListPos[161][0] = 67;
	exchangeListPos[161][1] = 2;
	exchangeListPos[161][2] = 0;
	exchangeListPos[161][3] = 0;
	exchangeListPos[161][4] = 3;

	exchangeListPos[162][0] = 67;
	exchangeListPos[162][1] = 2;
	exchangeListPos[162][2] = 0;
	exchangeListPos[162][3] = 0;
	exchangeListPos[162][4] = 3;

	exchangeListPos[163][0] = 67;
	exchangeListPos[163][1] = 2;
	exchangeListPos[163][2] = 0;
	exchangeListPos[163][3] = 2;
	exchangeListPos[163][4] = 3;

	exchangeListPos[164][0] = 68;
	exchangeListPos[164][1] = 2;
	exchangeListPos[164][2] = 2;
	exchangeListPos[164][3] = 0;
	exchangeListPos[164][4] = 3;

	exchangeListPos[165][0] = 68;
	exchangeListPos[165][1] = 3;
	exchangeListPos[165][2] = 0;
	exchangeListPos[165][3] = 0;
	exchangeListPos[165][4] = 3;

	exchangeListPos[166][0] = 69;
	exchangeListPos[166][1] = 3;
	exchangeListPos[166][2] = 0;
	exchangeListPos[166][3] = 1;
	exchangeListPos[166][4] = 1;

	exchangeListPos[167][0] = 69;
	exchangeListPos[167][1] = 1;
	exchangeListPos[167][2] = 1;
	exchangeListPos[167][3] = 2;
	exchangeListPos[167][4] = 2;

	exchangeListPos[168][0] = 70;
	exchangeListPos[168][1] = 2;
	exchangeListPos[168][2] = 0;
	exchangeListPos[168][3] = 0;
	exchangeListPos[168][4] = 1;

	exchangeListPos[169][0] = 70;
	exchangeListPos[169][1] = 0;
	exchangeListPos[169][2] = 1;
	exchangeListPos[169][3] = 0;
	exchangeListPos[169][4] = 2;

	exchangeListPos[170][0] = 71;
	exchangeListPos[170][1] = 2;
	exchangeListPos[170][2] = 0;
	exchangeListPos[170][3] = 0;
	exchangeListPos[170][4] = 2;

	exchangeListPos[171][0] = 71;
	exchangeListPos[171][1] = 3;
	exchangeListPos[171][2] = 2;
	exchangeListPos[171][3] = 0;
	exchangeListPos[171][4] = 2;

	exchangeListPos[172][0] = 72;
	exchangeListPos[172][1] = 1;
	exchangeListPos[172][2] = 0;
	exchangeListPos[172][3] = 0;
	exchangeListPos[172][4] = 2;

	exchangeListPos[173][0] = 72;
	exchangeListPos[173][1] = 2;
	exchangeListPos[173][2] = 1;
	exchangeListPos[173][3] = 0;
	exchangeListPos[173][4] = 2;

	exchangeListPos[174][0] = 73;
	exchangeListPos[174][1] = 2;
	exchangeListPos[174][2] = 0;
	exchangeListPos[174][3] = 0;
	exchangeListPos[174][4] = 0;

	exchangeListPos[175][0] = 73;
	exchangeListPos[175][1] = 3;
	exchangeListPos[175][2] = 1;
	exchangeListPos[175][3] = 0;
	exchangeListPos[175][4] = 0;

	exchangeListPos[176][0] = 73;
	exchangeListPos[176][1] = 0;
	exchangeListPos[176][2] = 0;
	exchangeListPos[176][3] = 0;
	exchangeListPos[176][4] = 1;

	exchangeListPos[177][0] = 74;
	exchangeListPos[177][1] = 0;
	exchangeListPos[177][2] = 0;
	exchangeListPos[177][3] = 1;
	exchangeListPos[177][4] = 4;

	exchangeListPos[178][0] = 74;
	exchangeListPos[178][1] = 1;
	exchangeListPos[178][2] = 0;
	exchangeListPos[178][3] = 1;
	exchangeListPos[178][4] = 1;

	exchangeListPos[179][0] = 75;
	exchangeListPos[179][1] = 2;
	exchangeListPos[179][2] = 1;
	exchangeListPos[179][3] = 1;
	exchangeListPos[179][4] = 0;

	exchangeListPos[180][0] = 75;
	exchangeListPos[180][1] = 1;
	exchangeListPos[180][2] = 2;
	exchangeListPos[180][3] = 2;
	exchangeListPos[180][4] = 1;

	exchangeListPos[181][0] = 76;
	exchangeListPos[181][1] = 2;
	exchangeListPos[181][2] = 0;
	exchangeListPos[181][3] = 1;
	exchangeListPos[181][4] = 2;

	exchangeListPos[182][0] = 76;
	exchangeListPos[182][1] = 3;
	exchangeListPos[182][2] = 2;
	exchangeListPos[182][3] = 0;
	exchangeListPos[182][4] = 0;

	exchangeListPos[183][0] = 76;
	exchangeListPos[183][1] = 1;
	exchangeListPos[183][2] = 1;
	exchangeListPos[183][3] = 2;
	exchangeListPos[183][4] = 1;

	exchangeListPos[184][0] = 77;
	exchangeListPos[184][1] = 2;
	exchangeListPos[184][2] = 1;
	exchangeListPos[184][3] = 0;
	exchangeListPos[184][4] = 2;

	exchangeListPos[185][0] = 77;
	exchangeListPos[185][1] = 0;
	exchangeListPos[185][2] = 0;
	exchangeListPos[185][3] = 0;
	exchangeListPos[185][4] = 2;

	exchangeListPos[186][0] = 78;
	exchangeListPos[186][1] = 3;
	exchangeListPos[186][2] = 1;
	exchangeListPos[186][3] = 0;
	exchangeListPos[186][4] = 2;

	exchangeListPos[187][0] = 78;
	exchangeListPos[187][1] = 2;
	exchangeListPos[187][2] = 0;
	exchangeListPos[187][3] = 2;
	exchangeListPos[187][4] = 2;

	exchangeListPos[188][0] = 79;
	exchangeListPos[188][1] = 1;
	exchangeListPos[188][2] = 0;
	exchangeListPos[188][3] = 2;
	exchangeListPos[188][4] = 3;

	exchangeListPos[189][0] = 79;
	exchangeListPos[189][1] = 1;
	exchangeListPos[189][2] = 2;
	exchangeListPos[189][3] = 0;
	exchangeListPos[189][4] = 3;

	exchangeListPos[190][0] = 80;
	exchangeListPos[190][1] = 1;
	exchangeListPos[190][2] = 1;
	exchangeListPos[190][3] = 2;
	exchangeListPos[190][4] = 0;

	exchangeListPos[191][0] = 80;
	exchangeListPos[191][1] = 0;
	exchangeListPos[191][2] = 1;
	exchangeListPos[191][3] = 0;
	exchangeListPos[191][4] = 0;

	exchangeListPos[192][0] = 81;
	exchangeListPos[192][1] = 0;
	exchangeListPos[192][2] = 0;
	exchangeListPos[192][3] = 1;
	exchangeListPos[192][4] = 0;

	exchangeListPos[193][0] = 81;
	exchangeListPos[193][1] = 0;
	exchangeListPos[193][2] = 1;
	exchangeListPos[193][3] = 0;
	exchangeListPos[193][4] = 0;

	exchangeListPos[194][0] = 82;
	exchangeListPos[194][1] = 2;
	exchangeListPos[194][2] = 3;
	exchangeListPos[194][3] = 2;
	exchangeListPos[194][4] = 1;

	exchangeListPos[195][0] = 82;
	exchangeListPos[195][1] = 1;
	exchangeListPos[195][2] = 0;
	exchangeListPos[195][3] = 2;
	exchangeListPos[195][4] = 1;

	exchangeListPos[196][0] = 83;
	exchangeListPos[196][1] = 2;
	exchangeListPos[196][2] = 1;
	exchangeListPos[196][3] = 1;
	exchangeListPos[196][4] = 1;

	exchangeListPos[197][0] = 83;
	exchangeListPos[197][1] = 0;
	exchangeListPos[197][2] = 0;
	exchangeListPos[197][3] = 3;
	exchangeListPos[197][4] = 2;

	exchangeListPos[198][0] = 83;
	exchangeListPos[198][1] = 1;
	exchangeListPos[198][2] = 2;
	exchangeListPos[198][3] = 2;
	exchangeListPos[198][4] = 0;

	exchangeListPos[199][0] = 84;
	exchangeListPos[199][1] = 2;
	exchangeListPos[199][2] = 0;
	exchangeListPos[199][3] = 1;
	exchangeListPos[199][4] = 1;

	exchangeListPos[200][0] = 84;
	exchangeListPos[200][1] = 0;
	exchangeListPos[200][2] = 0;
	exchangeListPos[200][3] = 2;
	exchangeListPos[200][4] = 2;

	exchangeListPos[201][0] = 85;
	exchangeListPos[201][1] = 0;
	exchangeListPos[201][2] = 4;
	exchangeListPos[201][3] = 0;
	exchangeListPos[201][4] = 0;

	exchangeListPos[202][0] = 85;
	exchangeListPos[202][1] = 0;
	exchangeListPos[202][2] = 3;
	exchangeListPos[202][3] = 0;
	exchangeListPos[202][4] = 0;

	exchangeListPos[203][0] = 86;
	exchangeListPos[203][1] = 0;
	exchangeListPos[203][2] = 1;
	exchangeListPos[203][3] = 0;
	exchangeListPos[203][4] = 0;

	exchangeListPos[204][0] = 86;
	exchangeListPos[204][1] = 0;
	exchangeListPos[204][2] = 0;
	exchangeListPos[204][3] = 3;
	exchangeListPos[204][4] = 1;

	exchangeListPos[205][0] = 86;
	exchangeListPos[205][1] = 0;
	exchangeListPos[205][2] = 0;
	exchangeListPos[205][3] = 2;
	exchangeListPos[205][4] = 0;

	exchangeListPos[206][0] = 87;
	exchangeListPos[206][1] = 0;
	exchangeListPos[206][2] = 0;
	exchangeListPos[206][3] = 3;
	exchangeListPos[206][4] = 0;

	exchangeListPos[207][0] = 87;
	exchangeListPos[207][1] = 2;
	exchangeListPos[207][2] = 2;
	exchangeListPos[207][3] = 0;
	exchangeListPos[207][4] = 0;

	exchangeListPos[208][0] = 88;
	exchangeListPos[208][1] = 0;
	exchangeListPos[208][2] = 0;
	exchangeListPos[208][3] = 3;
	exchangeListPos[208][4] = 0;

	exchangeListPos[209][0] = 88;
	exchangeListPos[209][1] = 0;
	exchangeListPos[209][2] = 1;
	exchangeListPos[209][3] = 0;
	exchangeListPos[209][4] = 0;

	exchangeListPos[210][0] = 89;
	exchangeListPos[210][1] = 2;
	exchangeListPos[210][2] = 2;
	exchangeListPos[210][3] = 1;
	exchangeListPos[210][4] = 0;

	exchangeListPos[211][0] = 89;
	exchangeListPos[211][1] = 1;
	exchangeListPos[211][2] = 1;
	exchangeListPos[211][3] = 2;
	exchangeListPos[211][4] = 2;

	exchangeListPos[212][0] = 90;
	exchangeListPos[212][1] = 2;
	exchangeListPos[212][2] = 2;
	exchangeListPos[212][3] = 1;
	exchangeListPos[212][4] = 1;

	exchangeListPos[213][0] = 90;
	exchangeListPos[213][1] = 1;
	exchangeListPos[213][2] = 1;
	exchangeListPos[213][3] = 3;
	exchangeListPos[213][4] = 0;

	exchangeListPos[214][0] = 91;
	exchangeListPos[214][1] = 0;
	exchangeListPos[214][2] = 0;
	exchangeListPos[214][3] = 3;
	exchangeListPos[214][4] = 0;

	exchangeListPos[215][0] = 91;
	exchangeListPos[215][1] = 1;
	exchangeListPos[215][2] = 1;
	exchangeListPos[215][3] = 0;
	exchangeListPos[215][4] = 0;

	exchangeListPos[216][0] = 92;
	exchangeListPos[216][1] = 0;
	exchangeListPos[216][2] = 3;
	exchangeListPos[216][3] = 0;
	exchangeListPos[216][4] = 0;

	exchangeListPos[217][0] = 92;
	exchangeListPos[217][1] = 0;
	exchangeListPos[217][2] = 0;
	exchangeListPos[217][3] = 2;
	exchangeListPos[217][4] = 0;

	exchangeListPos[218][0] = 92;
	exchangeListPos[218][1] = 1;
	exchangeListPos[218][2] = 1;
	exchangeListPos[218][3] = 2;
	exchangeListPos[218][4] = 0;

	exchangeListPos[219][0] = 93;
	exchangeListPos[219][1] = 0;
	exchangeListPos[219][2] = 2;
	exchangeListPos[219][3] = 2;
	exchangeListPos[219][4] = 0;

	exchangeListPos[220][0] = 93;
	exchangeListPos[220][1] = 1;
	exchangeListPos[220][2] = 0;
	exchangeListPos[220][3] = 2;
	exchangeListPos[220][4] = 0;

	exchangeListPos[221][0] = 93;
	exchangeListPos[221][1] = 0;
	exchangeListPos[221][2] = 0;
	exchangeListPos[221][3] = 1;
	exchangeListPos[221][4] = 0;

	exchangeListPos[222][0] = 93;
	exchangeListPos[222][1] = 0;
	exchangeListPos[222][2] = 1;
	exchangeListPos[222][3] = 2;
	exchangeListPos[222][4] = 1;

	exchangeListPos[223][0] = 94;
	exchangeListPos[223][1] = 2;
	exchangeListPos[223][2] = 0;
	exchangeListPos[223][3] = 3;
	exchangeListPos[223][4] = 2;

	exchangeListPos[224][0] = 94;
	exchangeListPos[224][1] = 0;
	exchangeListPos[224][2] = 0;
	exchangeListPos[224][3] = 2;
	exchangeListPos[224][4] = 0;

	exchangeListPos[225][0] = 95;
	exchangeListPos[225][1] = 0;
	exchangeListPos[225][2] = 1;
	exchangeListPos[225][3] = 1;
	exchangeListPos[225][4] = 0;

	exchangeListPos[226][0] = 95;
	exchangeListPos[226][1] = 1;
	exchangeListPos[226][2] = 2;
	exchangeListPos[226][3] = 1;
	exchangeListPos[226][4] = 0;

	exchangeListPos[227][0] = 95;
	exchangeListPos[227][1] = 0;
	exchangeListPos[227][2] = 4;
	exchangeListPos[227][3] = 1;
	exchangeListPos[227][4] = 0;
	//7장		    
	exchangeListPos[228][0] = 96;
	exchangeListPos[228][1] = 4;
	exchangeListPos[228][2] = 1;
	exchangeListPos[228][3] = 0;
	exchangeListPos[228][4] = 1;

	exchangeListPos[229][0] = 96;
	exchangeListPos[229][1] = 3;
	exchangeListPos[229][2] = 0;
	exchangeListPos[229][3] = 0;
	exchangeListPos[229][4] = 1;

	exchangeListPos[230][0] = 97;
	exchangeListPos[230][1] = 2;
	exchangeListPos[230][2] = 1;
	exchangeListPos[230][3] = 1;
	exchangeListPos[230][4] = 2;

	exchangeListPos[231][0] = 97;
	exchangeListPos[231][1] = 1;
	exchangeListPos[231][2] = 2;
	exchangeListPos[231][3] = 0;
	exchangeListPos[231][4] = 0;

	exchangeListPos[232][0] = 98;
	exchangeListPos[232][1] = 1;
	exchangeListPos[232][2] = 1;
	exchangeListPos[232][3] = 0;
	exchangeListPos[232][4] = 0;

	exchangeListPos[233][0] = 98;
	exchangeListPos[233][1] = 2;
	exchangeListPos[233][2] = 0;
	exchangeListPos[233][3] = 0;
	exchangeListPos[233][4] = 0;

	exchangeListPos[234][0] = 98;
	exchangeListPos[234][1] = 4;
	exchangeListPos[234][2] = 1;
	exchangeListPos[234][3] = 0;
	exchangeListPos[234][4] = 0;

	exchangeListPos[235][0] = 99;
	exchangeListPos[235][1] = 0;
	exchangeListPos[235][2] = 1;
	exchangeListPos[235][3] = 1;
	exchangeListPos[235][4] = 2;

	exchangeListPos[236][0] = 99;
	exchangeListPos[236][1] = 0;
	exchangeListPos[236][2] = 2;
	exchangeListPos[236][3] = 2;
	exchangeListPos[236][4] = 1;

	exchangeListPos[237][0] = 100;
	exchangeListPos[237][1] = 2;
	exchangeListPos[237][2] = 0;
	exchangeListPos[237][3] = 0;
	exchangeListPos[237][4] = 0;

	exchangeListPos[238][0] = 100;
	exchangeListPos[238][1] = 1;
	exchangeListPos[238][2] = 1;
	exchangeListPos[238][3] = 2;
	exchangeListPos[238][4] = 0;

	exchangeListPos[239][0] = 101;
	exchangeListPos[239][1] = 0;
	exchangeListPos[239][2] = 1;
	exchangeListPos[239][3] = 2;
	exchangeListPos[239][4] = 0;

	exchangeListPos[240][0] = 101;
	exchangeListPos[240][1] = 0;
	exchangeListPos[240][2] = 2;
	exchangeListPos[240][3] = 0;
	exchangeListPos[240][4] = 1;

	exchangeListPos[241][0] = 102;
	exchangeListPos[241][1] = 0;
	exchangeListPos[241][2] = 3;
	exchangeListPos[241][3] = 2;
	exchangeListPos[241][4] = 0;

	exchangeListPos[242][0] = 102;
	exchangeListPos[242][1] = 1;
	exchangeListPos[242][2] = 1;
	exchangeListPos[242][3] = 1;
	exchangeListPos[242][4] = 2;

	exchangeListPos[243][0] = 102;
	exchangeListPos[243][1] = 2;
	exchangeListPos[243][2] = 2;
	exchangeListPos[243][3] = 0;
	exchangeListPos[243][4] = 1;

	exchangeListPos[244][0] = 103;
	exchangeListPos[244][1] = 0;
	exchangeListPos[244][2] = 3;
	exchangeListPos[244][3] = 0;
	exchangeListPos[244][4] = 0;

	exchangeListPos[245][0] = 103;
	exchangeListPos[245][1] = 1;
	exchangeListPos[245][2] = 2;
	exchangeListPos[245][3] = 0;
	exchangeListPos[245][4] = 0;

	exchangeListPos[246][0] = 104;
	exchangeListPos[246][1] = 0;
	exchangeListPos[246][2] = 1;
	exchangeListPos[246][3] = 0;
	exchangeListPos[246][4] = 0;

	exchangeListPos[247][0] = 104;
	exchangeListPos[247][1] = 1;
	exchangeListPos[247][2] = 1;
	exchangeListPos[247][3] = 1;
	exchangeListPos[247][4] = 0;

	exchangeListPos[248][0] = 104;
	exchangeListPos[248][1] = 1;
	exchangeListPos[248][2] = 0;
	exchangeListPos[248][3] = 0;
	exchangeListPos[248][4] = 0;

	exchangeListPos[249][0] = 104;
	exchangeListPos[249][1] = 0;
	exchangeListPos[249][2] = 2;
	exchangeListPos[249][3] = 0;
	exchangeListPos[249][4] = 0;

	exchangeListPos[250][0] = 105;
	exchangeListPos[250][1] = 3;
	exchangeListPos[250][2] = 0;
	exchangeListPos[250][3] = 1;
	exchangeListPos[250][4] = 0;

	exchangeListPos[251][0] = 105;
	exchangeListPos[251][1] = 0;
	exchangeListPos[251][2] = 1;
	exchangeListPos[251][3] = 1;
	exchangeListPos[251][4] = 0;

	exchangeListPos[252][0] = 106;
	exchangeListPos[252][1] = 0;
	exchangeListPos[252][2] = 2;
	exchangeListPos[252][3] = 0;
	exchangeListPos[252][4] = 0;

	exchangeListPos[253][0] = 106;
	exchangeListPos[253][1] = 2;
	exchangeListPos[253][2] = 1;
	exchangeListPos[253][3] = 0;
	exchangeListPos[253][4] = 0;

	exchangeListPos[254][0] = 107;
	exchangeListPos[254][1] = 0;
	exchangeListPos[254][2] = 2;
	exchangeListPos[254][3] = 0;
	exchangeListPos[254][4] = 0;

	exchangeListPos[255][0] = 107;
	exchangeListPos[255][1] = 3;
	exchangeListPos[255][2] = 2;
	exchangeListPos[255][3] = 0;
	exchangeListPos[255][4] = 2;

	exchangeListPos[256][0] = 107;
	exchangeListPos[256][1] = 1;
	exchangeListPos[256][2] = 1;
	exchangeListPos[256][3] = 0;
	exchangeListPos[256][4] = 0;

	exchangeListPos[257][0] = 108;
	exchangeListPos[257][1] = 1;
	exchangeListPos[257][2] = 1;
	exchangeListPos[257][3] = 0;
	exchangeListPos[257][4] = 0;

	exchangeListPos[258][0] = 108;
	exchangeListPos[258][1] = 1;
	exchangeListPos[258][2] = 2;
	exchangeListPos[258][3] = 0;
	exchangeListPos[258][4] = 2;

	exchangeListPos[259][0] = 109;
	exchangeListPos[259][1] = 0;
	exchangeListPos[259][2] = 3;
	exchangeListPos[259][3] = 0;
	exchangeListPos[259][4] = 2;

	exchangeListPos[260][0] = 109;
	exchangeListPos[260][1] = 1;
	exchangeListPos[260][2] = 3;
	exchangeListPos[260][3] = 0;
	exchangeListPos[260][4] = 0;

	exchangeListPos[261][0] = 110;
	exchangeListPos[261][1] = 1;
	exchangeListPos[261][2] = 0;
	exchangeListPos[261][3] = 0;
	exchangeListPos[261][4] = 0;

	exchangeListPos[262][0] = 110;
	exchangeListPos[262][1] = 0;
	exchangeListPos[262][2] = 3;
	exchangeListPos[262][3] = 1;
	exchangeListPos[262][4] = 0;

	exchangeListPos[263][0] = 110;
	exchangeListPos[263][1] = 0;
	exchangeListPos[263][2] = 2;
	exchangeListPos[263][3] = 0;
	exchangeListPos[263][4] = 0;

	exchangeListPos[264][0] = 111;
	exchangeListPos[264][1] = 0;
	exchangeListPos[264][2] = 3;
	exchangeListPos[264][3] = 0;
	exchangeListPos[264][4] = 0;

	exchangeListPos[265][0] = 111;
	exchangeListPos[265][1] = 1;
	exchangeListPos[265][2] = 2;
	exchangeListPos[265][3] = 0;
	exchangeListPos[265][4] = 0;
	//8장
	exchangeListPos[266][0] = 112;
	exchangeListPos[266][1] = 2;
	exchangeListPos[266][2] = 1;
	exchangeListPos[266][3] = 3;
	exchangeListPos[266][4] = 0;

	exchangeListPos[267][0] = 112;
	exchangeListPos[267][1] = 0;
	exchangeListPos[267][2] = 0;
	exchangeListPos[267][3] = 3;
	exchangeListPos[267][4] = 3;

	exchangeListPos[268][0] = 113;
	exchangeListPos[268][1] = 0;
	exchangeListPos[268][2] = 0;
	exchangeListPos[268][3] = 0;
	exchangeListPos[268][4] = 2;

	exchangeListPos[269][0] = 113;
	exchangeListPos[269][1] = 1;
	exchangeListPos[269][2] = 0;
	exchangeListPos[269][3] = 0;
	exchangeListPos[269][4] = 3;

	exchangeListPos[270][0] = 113;
	exchangeListPos[270][1] = 0;
	exchangeListPos[270][2] = 0;
	exchangeListPos[270][3] = 1;
	exchangeListPos[270][4] = 0;

	exchangeListPos[271][0] = 114;
	exchangeListPos[271][1] = 1;
	exchangeListPos[271][2] = 0;
	exchangeListPos[271][3] = 2;
	exchangeListPos[271][4] = 0;

	exchangeListPos[272][0] = 114;
	exchangeListPos[272][1] = 0;
	exchangeListPos[272][2] = 1;
	exchangeListPos[272][3] = 2;
	exchangeListPos[272][4] = 1;

	exchangeListPos[273][0] = 115;
	exchangeListPos[273][1] = 0;
	exchangeListPos[273][2] = 1;
	exchangeListPos[273][3] = 3;
	exchangeListPos[273][4] = 0;

	exchangeListPos[274][0] = 115;
	exchangeListPos[274][1] = 2;
	exchangeListPos[274][2] = 1;
	exchangeListPos[274][3] = 3;
	exchangeListPos[274][4] = 2;

	exchangeListPos[275][0] = 116;
	exchangeListPos[275][1] = 0;
	exchangeListPos[275][2] = 0;
	exchangeListPos[275][3] = 3;
	exchangeListPos[275][4] = 2;

	exchangeListPos[276][0] = 116;
	exchangeListPos[276][1] = 0;
	exchangeListPos[276][2] = 0;
	exchangeListPos[276][3] = 3;
	exchangeListPos[276][4] = 0;

	exchangeListPos[277][0] = 116;
	exchangeListPos[277][1] = 0;
	exchangeListPos[277][2] = 0;
	exchangeListPos[277][3] = 3;
	exchangeListPos[277][4] = 2;

	exchangeListPos[278][0] = 117;
	exchangeListPos[278][1] = 0;
	exchangeListPos[278][2] = 2;
	exchangeListPos[278][3] = 2;
	exchangeListPos[278][4] = 0;

	exchangeListPos[279][0] = 117;
	exchangeListPos[279][1] = 1;
	exchangeListPos[279][2] = 0;
	exchangeListPos[279][3] = 2;
	exchangeListPos[279][4] = 3;

	exchangeListPos[280][0] = 118;
	exchangeListPos[280][1] = 1;
	exchangeListPos[280][2] = 0;
	exchangeListPos[280][3] = 2;
	exchangeListPos[280][4] = 2;

	exchangeListPos[281][0] = 118;
	exchangeListPos[281][1] = 0;
	exchangeListPos[281][2] = 2;
	exchangeListPos[281][3] = 2;
	exchangeListPos[281][4] = 2;

	exchangeListPos[282][0] = 119;
	exchangeListPos[282][1] = 2;
	exchangeListPos[282][2] = 0;
	exchangeListPos[282][3] = 1;
	exchangeListPos[282][4] = 1;

	exchangeListPos[283][0] = 119;
	exchangeListPos[283][1] = 0;
	exchangeListPos[283][2] = 0;
	exchangeListPos[283][3] = 2;
	exchangeListPos[283][4] = 2;

	exchangeListPos[284][0] = 119;
	exchangeListPos[284][1] = 0;
	exchangeListPos[284][2] = 0;
	exchangeListPos[284][3] = 1;
	exchangeListPos[284][4] = 2;

	exchangeListPos[285][0] = 119;
	exchangeListPos[285][1] = 2;
	exchangeListPos[285][2] = 1;
	exchangeListPos[285][3] = 0;
	exchangeListPos[285][4] = 1;

	exchangeListPos[286][0] = 120;
	exchangeListPos[286][1] = 0;
	exchangeListPos[286][2] = 0;
	exchangeListPos[286][3] = 2;
	exchangeListPos[286][4] = 0;

	exchangeListPos[287][0] = 120;
	exchangeListPos[287][1] = 2;
	exchangeListPos[287][2] = 0;
	exchangeListPos[287][3] = 2;
	exchangeListPos[287][4] = 3;

	exchangeListPos[288][0] = 121;
	exchangeListPos[288][1] = 0;
	exchangeListPos[288][2] = 1;
	exchangeListPos[288][3] = 2;
	exchangeListPos[288][4] = 2;

	exchangeListPos[289][0] = 121;
	exchangeListPos[289][1] = 1;
	exchangeListPos[289][2] = 2;
	exchangeListPos[289][3] = 1;
	exchangeListPos[289][4] = 1;

	exchangeListPos[290][0] = 121;
	exchangeListPos[290][1] = 2;
	exchangeListPos[290][2] = 0;
	exchangeListPos[290][3] = 0;
	exchangeListPos[290][4] = 3;

	exchangeListPos[291][0] = 122;
	exchangeListPos[291][1] = 1;
	exchangeListPos[291][2] = 0;
	exchangeListPos[291][3] = 0;
	exchangeListPos[291][4] = 3;

	exchangeListPos[292][0] = 122;
	exchangeListPos[292][1] = 2;
	exchangeListPos[292][2] = 2;
	exchangeListPos[292][3] = 0;
	exchangeListPos[292][4] = 3;

	exchangeListPos[293][0] = 123;
	exchangeListPos[293][1] = 0;
	exchangeListPos[293][2] = 0;
	exchangeListPos[293][3] = 1;
	exchangeListPos[293][4] = 2;

	exchangeListPos[294][0] = 123;
	exchangeListPos[294][1] = 1;
	exchangeListPos[294][2] = 2;
	exchangeListPos[294][3] = 2;
	exchangeListPos[294][4] = 1;

	exchangeListPos[295][0] = 124;
	exchangeListPos[295][1] = 1;
	exchangeListPos[295][2] = 0;
	exchangeListPos[295][3] = 0;
	exchangeListPos[295][4] = 2;

	exchangeListPos[296][0] = 124;
	exchangeListPos[296][1] = 2;
	exchangeListPos[296][2] = 2;
	exchangeListPos[296][3] = 1;
	exchangeListPos[296][4] = 1;

	exchangeListPos[297][0] = 125;
	exchangeListPos[297][1] = 0;
	exchangeListPos[297][2] = 0;
	exchangeListPos[297][3] = 4;
	exchangeListPos[297][4] = 1;

	exchangeListPos[298][0] = 125;
	exchangeListPos[298][1] = 0;
	exchangeListPos[298][2] = 0;
	exchangeListPos[298][3] = 2;
	exchangeListPos[298][4] = 0;

	exchangeListPos[299][0] = 125;
	exchangeListPos[299][1] = 0;
	exchangeListPos[299][2] = 0;
	exchangeListPos[299][3] = 1;
	exchangeListPos[299][4] = 1;

	exchangeListPos[300][0] = 126;
	exchangeListPos[300][1] = 0;
	exchangeListPos[300][2] = 0;
	exchangeListPos[300][3] = 1;
	exchangeListPos[300][4] = 2;

	exchangeListPos[301][0] = 126;
	exchangeListPos[301][1] = 1;
	exchangeListPos[301][2] = 2;
	exchangeListPos[301][3] = 2;
	exchangeListPos[301][4] = 1;

	exchangeListPos[302][0] = 127;
	exchangeListPos[302][1] = 0;
	exchangeListPos[302][2] = 0;
	exchangeListPos[302][3] = 4;
	exchangeListPos[302][4] = 0;

	exchangeListPos[303][0] = 127;
	exchangeListPos[303][1] = 0;
	exchangeListPos[303][2] = 0;
	exchangeListPos[303][3] = 1;
	exchangeListPos[303][4] = 0;
}

void bigPicture::setExchangeListMatchPos(float **list)
{
	exchangeListMatchPos = new float*[MAXELN];
	for (int i = 0; i < MAXELN; i++){
		exchangeListMatchPos[i] = new float[3];
		exchangeListMatchPos[i][0] = -1.0f; //블록쌍 라벨
		exchangeListMatchPos[i][1] = -1.0f; //블록쌍의 매칭점 x위치
		exchangeListMatchPos[i][2] = -1.0f; //블록쌍의 매칭점 y위치
	}

	//1장-------------------------------------------------------------------
	exchangeListMatchPos[0][0] = 0;
	exchangeListMatchPos[0][1] = 1.0;
	exchangeListMatchPos[0][2] = 3.0;

	exchangeListMatchPos[1][0] = 0;
	exchangeListMatchPos[1][1] = 1.0;
	exchangeListMatchPos[1][2] = 1.0;
	//			
	exchangeListMatchPos[2][0] = 1;
	exchangeListMatchPos[2][1] = 1.0;
	exchangeListMatchPos[2][2] = 2.5;

	exchangeListMatchPos[3][0] = 1;
	exchangeListMatchPos[3][1] = 1.0;
	exchangeListMatchPos[3][2] = 2.5;
	//			
	exchangeListMatchPos[4][0] = 2;
	exchangeListMatchPos[4][1] = 1.0;
	exchangeListMatchPos[4][2] = 2.5;

	exchangeListMatchPos[5][0] = 2;
	exchangeListMatchPos[5][1] = 1.5;
	exchangeListMatchPos[5][2] = 2.0;
	//			
	exchangeListMatchPos[6][0] = 2;
	exchangeListMatchPos[6][1] = 1.0;
	exchangeListMatchPos[6][2] = 1.5;

	exchangeListMatchPos[7][0] = 2;
	exchangeListMatchPos[7][1] = 1.5;
	exchangeListMatchPos[7][2] = 1.5;
	//			
	exchangeListMatchPos[8][0] = 3;
	exchangeListMatchPos[8][1] = 1.5;
	exchangeListMatchPos[8][2] = 1.5;

	exchangeListMatchPos[9][0] = 3;
	exchangeListMatchPos[9][1] = 2.0;
	exchangeListMatchPos[9][2] = 2.0;

	exchangeListMatchPos[10][0] = 4;
	exchangeListMatchPos[10][1] = 2.0;
	exchangeListMatchPos[10][2] = 1.5;
	//			
	exchangeListMatchPos[11][0] = 4;
	exchangeListMatchPos[11][1] = 1.0;
	exchangeListMatchPos[11][2] = 2.5;

	exchangeListMatchPos[12][0] = 4;
	exchangeListMatchPos[12][1] = 1.0;
	exchangeListMatchPos[12][2] = 2.5;

	exchangeListMatchPos[13][0] = 5;
	exchangeListMatchPos[13][1] = 1.0;
	exchangeListMatchPos[13][2] = 2.5;
	//			
	exchangeListMatchPos[14][0] = 5;
	exchangeListMatchPos[14][1] = 2.0;
	exchangeListMatchPos[14][2] = 1.0;

	exchangeListMatchPos[15][0] = 5;
	exchangeListMatchPos[15][1] = 2.0;
	exchangeListMatchPos[15][2] = 1.5;
	//			
	exchangeListMatchPos[16][0] = 6;
	exchangeListMatchPos[16][1] = 2.0;
	exchangeListMatchPos[16][2] = 1.0;

	exchangeListMatchPos[17][0] = 6;
	exchangeListMatchPos[17][1] = 1.5;
	exchangeListMatchPos[17][2] = 2.0;

	exchangeListMatchPos[18][0] = 7;
	exchangeListMatchPos[18][1] = 2.0;
	exchangeListMatchPos[18][2] = 2.0;

	exchangeListMatchPos[19][0] = 7;
	exchangeListMatchPos[19][1] = 1.0;
	exchangeListMatchPos[19][2] = 2.0;
	//			
	exchangeListMatchPos[20][0] = 8;
	exchangeListMatchPos[20][1] = 1.5;
	exchangeListMatchPos[20][2] = 2.0;

	exchangeListMatchPos[21][0] = 8;
	exchangeListMatchPos[21][1] = 1.5;
	exchangeListMatchPos[21][2] = 2.0;

	exchangeListMatchPos[22][0] = 9;
	exchangeListMatchPos[22][1] = 2.0;
	exchangeListMatchPos[22][2] = 2.0;
	//			
	exchangeListMatchPos[23][0] = 9;
	exchangeListMatchPos[23][1] = 2.0;
	exchangeListMatchPos[23][2] = 2.0;

	exchangeListMatchPos[24][0] = 9;
	exchangeListMatchPos[24][1] = 3.0f;
	exchangeListMatchPos[24][2] = 1.0f;
	//2장------------------------------------------------------------------
	exchangeListMatchPos[25][0] = 10;
	exchangeListMatchPos[25][1] = 2.0;
	exchangeListMatchPos[25][2] = 2.0;

	exchangeListMatchPos[26][0] = 10;
	exchangeListMatchPos[26][1] = 1.5;
	exchangeListMatchPos[26][2] = 2.0;
	//			
	exchangeListMatchPos[27][0] = 11;
	exchangeListMatchPos[27][1] = 1.5;
	exchangeListMatchPos[27][2] = 2.0;

	exchangeListMatchPos[28][0] = 11;
	exchangeListMatchPos[28][1] = 1.5;
	exchangeListMatchPos[28][2] = 2.0;
	//			
	exchangeListMatchPos[29][0] = 12;
	exchangeListMatchPos[29][1] = 1.5;
	exchangeListMatchPos[29][2] = 2.0;

	exchangeListMatchPos[30][0] = 12;
	exchangeListMatchPos[30][1] = 2.0;
	exchangeListMatchPos[30][2] = 1.5;

	exchangeListMatchPos[31][0] = 12;
	exchangeListMatchPos[31][1] = 2.0;
	exchangeListMatchPos[31][2] = 1.5;
	//			
	exchangeListMatchPos[32][0] = 13;
	exchangeListMatchPos[32][1] = 2.0;
	exchangeListMatchPos[32][2] = 1.5;

	exchangeListMatchPos[33][0] = 13;
	exchangeListMatchPos[33][1] = 2.0;
	exchangeListMatchPos[33][2] = 1.5;
	//			
	exchangeListMatchPos[34][0] = 14;
	exchangeListMatchPos[34][1] = 2.0;
	exchangeListMatchPos[34][2] = 1.5;

	exchangeListMatchPos[35][0] = 14;
	exchangeListMatchPos[35][1] = 1.0;
	exchangeListMatchPos[35][2] = 2.0;
	//			
	exchangeListMatchPos[36][0] = 15;
	exchangeListMatchPos[36][1] = 1.0;
	exchangeListMatchPos[36][2] = 1.5;

	exchangeListMatchPos[37][0] = 15;
	exchangeListMatchPos[37][1] = 1.0;
	exchangeListMatchPos[37][2] = 2.5;
	//3장	   
	exchangeListMatchPos[38][0] = 16;
	exchangeListMatchPos[38][1] = 1.0;
	exchangeListMatchPos[38][2] = 2.5;

	exchangeListMatchPos[39][0] = 16;
	exchangeListMatchPos[39][1] = 2.0;
	exchangeListMatchPos[39][2] = 1.5;
	//			
	exchangeListMatchPos[40][0] = 17;
	exchangeListMatchPos[40][1] = 2.0;
	exchangeListMatchPos[40][2] = 1.5;

	exchangeListMatchPos[41][0] = 17;
	exchangeListMatchPos[41][1] = 1.0;
	exchangeListMatchPos[41][2] = 3.0;
	//			
	exchangeListMatchPos[42][0] = 18;
	exchangeListMatchPos[42][1] = 1.0;
	exchangeListMatchPos[42][2] = 3.0;

	exchangeListMatchPos[43][0] = 18;
	exchangeListMatchPos[43][1] = 2.0;
	exchangeListMatchPos[43][2] = 1.5;
	//			
	exchangeListMatchPos[44][0] = 19;
	exchangeListMatchPos[44][1] = 2.0;
	exchangeListMatchPos[44][2] = 1.0;

	exchangeListMatchPos[45][0] = 19;
	exchangeListMatchPos[45][1] = 2.0;
	exchangeListMatchPos[45][2] = 1.5;

	exchangeListMatchPos[46][0] = 19;
	exchangeListMatchPos[46][1] = 2.0;
	exchangeListMatchPos[46][2] = 1.5;
	//			
	exchangeListMatchPos[47][0] = 20;
	exchangeListMatchPos[47][1] = 2.0;
	exchangeListMatchPos[47][2] = 1.5;

	exchangeListMatchPos[48][0] = 20;
	exchangeListMatchPos[48][1] = 1.5;
	exchangeListMatchPos[48][2] = 2.0;
	//			
	exchangeListMatchPos[49][0] = 21;
	exchangeListMatchPos[49][1] = 1.5;
	exchangeListMatchPos[49][2] = 2.0;

	exchangeListMatchPos[50][0] = 21;
	exchangeListMatchPos[50][1] = 2.5;
	exchangeListMatchPos[50][2] = 1.0;
	//4장--------------------------------------------------------------
	exchangeListMatchPos[51][0] = 22;
	exchangeListMatchPos[51][1] = 2.5;
	exchangeListMatchPos[51][2] = 1.0;

	exchangeListMatchPos[52][0] = 22;
	exchangeListMatchPos[52][1] = 2.0;
	exchangeListMatchPos[52][2] = 2.0;

	exchangeListMatchPos[53][0] = 23;
	exchangeListMatchPos[53][1] = 2.0;
	exchangeListMatchPos[53][2] = 2.0;
	//			
	exchangeListMatchPos[54][0] = 23;
	exchangeListMatchPos[54][1] = 1.0;
	exchangeListMatchPos[54][2] = 2.0;

	exchangeListMatchPos[55][0] = 24;
	exchangeListMatchPos[55][1] = 1.5;
	exchangeListMatchPos[55][2] = 2.0;
	//			
	exchangeListMatchPos[56][0] = 24;
	exchangeListMatchPos[56][1] = 2.5;
	exchangeListMatchPos[56][2] = 1.0;

	exchangeListMatchPos[57][0] = 25;
	exchangeListMatchPos[57][1] = 3.0;
	exchangeListMatchPos[57][2] = 1.0;
	//			
	exchangeListMatchPos[58][0] = 25;
	exchangeListMatchPos[58][1] = 2.0;
	exchangeListMatchPos[58][2] = 1.0;

	exchangeListMatchPos[59][0] = 26;
	exchangeListMatchPos[59][1] = 2.5;
	exchangeListMatchPos[59][2] = 1.0;
	//			
	exchangeListMatchPos[60][0] = 26;
	exchangeListMatchPos[60][1] = 2.0;
	exchangeListMatchPos[60][2] = 1.0;

	exchangeListMatchPos[61][0] = 26;
	exchangeListMatchPos[61][1] = 2.0;
	exchangeListMatchPos[61][2] = 1.0;

	exchangeListMatchPos[62][0] = 27;
	exchangeListMatchPos[62][1] = 2.0;
	exchangeListMatchPos[62][2] = 1.0;

	exchangeListMatchPos[63][0] = 27;
	exchangeListMatchPos[63][1] = 1.0;
	exchangeListMatchPos[63][2] = 2.5;
	//			
	exchangeListMatchPos[64][0] = 27;
	exchangeListMatchPos[64][1] = 1.0;
	exchangeListMatchPos[64][2] = 2.5;

	exchangeListMatchPos[65][0] = 28;
	exchangeListMatchPos[65][1] = 1.0;
	exchangeListMatchPos[65][2] = 2.5;
	//			
	exchangeListMatchPos[66][0] = 28;
	exchangeListMatchPos[66][1] = 2.0;
	exchangeListMatchPos[66][2] = 1.5;

	exchangeListMatchPos[67][0] = 29;
	exchangeListMatchPos[67][1] = 2.0;
	exchangeListMatchPos[67][2] = 1.0;

	exchangeListMatchPos[68][0] = 29;
	exchangeListMatchPos[68][1] = 1.5;
	exchangeListMatchPos[68][2] = 1.5;
	//			
	exchangeListMatchPos[69][0] = 29;
	exchangeListMatchPos[69][1] = 1.5;
	exchangeListMatchPos[69][2] = 1.5;

	exchangeListMatchPos[70][0] = 29;
	exchangeListMatchPos[70][1] = 2.0;
	exchangeListMatchPos[70][2] = 1.5;
	//			
	exchangeListMatchPos[71][0] = 30;
	exchangeListMatchPos[71][1] = 1.5;
	exchangeListMatchPos[71][2] = 1.0;

	exchangeListMatchPos[72][0] = 30;
	exchangeListMatchPos[72][1] = 2.0;
	exchangeListMatchPos[72][2] = 1.5;
	//			
	exchangeListMatchPos[73][0] = 30;
	exchangeListMatchPos[73][1] = 2.0;
	exchangeListMatchPos[73][2] = 1.5;

	exchangeListMatchPos[74][0] = 31;
	exchangeListMatchPos[74][1] = 2.0;
	exchangeListMatchPos[74][2] = 1.5;

	exchangeListMatchPos[75][0] = 31;
	exchangeListMatchPos[75][1] = 3.0;
	exchangeListMatchPos[75][2] = 1.0;
	//5장--------------------------------------------------------------
	exchangeListMatchPos[76][0] = 32;
	exchangeListMatchPos[76][1] = 3.0;
	exchangeListMatchPos[76][2] = 1.0;

	exchangeListMatchPos[77][0] = 32;
	exchangeListMatchPos[77][1] = 2.5;
	exchangeListMatchPos[77][2] = 1.0;
	//			
	exchangeListMatchPos[78][0] = 32;
	exchangeListMatchPos[78][1] = 2.5;
	exchangeListMatchPos[78][2] = 1.0;

	exchangeListMatchPos[79][0] = 33;
	exchangeListMatchPos[79][1] = 2.5;
	exchangeListMatchPos[79][2] = 1.0;
	//			
	exchangeListMatchPos[80][0] = 33;
	exchangeListMatchPos[80][1] = 2.0;
	exchangeListMatchPos[80][2] = 2.0;

	exchangeListMatchPos[81][0] = 34;
	exchangeListMatchPos[81][1] = 2.0;
	exchangeListMatchPos[81][2] = 2.0;

	exchangeListMatchPos[82][0] = 34;
	exchangeListMatchPos[82][1] = 2.0;
	exchangeListMatchPos[82][2] = 1.5;
	//			
	exchangeListMatchPos[83][0] = 35;
	exchangeListMatchPos[83][1] = 2.0;
	exchangeListMatchPos[83][2] = 1.0;

	exchangeListMatchPos[84][0] = 35;
	exchangeListMatchPos[84][1] = 1.5;
	exchangeListMatchPos[84][2] = 2.0;
	//			
	exchangeListMatchPos[85][0] = 36;
	exchangeListMatchPos[85][1] = 2.0;
	exchangeListMatchPos[85][2] = 2.0;

	exchangeListMatchPos[86][0] = 36;
	exchangeListMatchPos[86][1] = 2.0;
	exchangeListMatchPos[86][2] = 1.0;

	exchangeListMatchPos[87][0] = 37;
	exchangeListMatchPos[87][1] = 2.0;
	exchangeListMatchPos[87][2] = 1.5;

	exchangeListMatchPos[88][0] = 37;
	exchangeListMatchPos[88][1] = 1.5;
	exchangeListMatchPos[88][2] = 2.0;
	//6장------------------------------------------------------------------
	exchangeListMatchPos[89][0] = 38;
	exchangeListMatchPos[89][1] = 2.0;
	exchangeListMatchPos[89][2] = 2.0;

	exchangeListMatchPos[90][0] = 38;
	exchangeListMatchPos[90][1] = 1.5;
	exchangeListMatchPos[90][2] = 2.0;

	exchangeListMatchPos[91][0] = 38;
	exchangeListMatchPos[91][1] = 1.5;
	exchangeListMatchPos[91][2] = 1.5;
	//			
	exchangeListMatchPos[92][0] = 38;
	exchangeListMatchPos[92][1] = 2.0;
	exchangeListMatchPos[92][2] = 1.5;

	exchangeListMatchPos[93][0] = 39;
	exchangeListMatchPos[93][1] = 1.5;
	exchangeListMatchPos[93][2] = 1.5;
	//			
	exchangeListMatchPos[94][0] = 39;
	exchangeListMatchPos[94][1] = 2.0;
	exchangeListMatchPos[94][2] = 2.5;

	exchangeListMatchPos[95][0] = 40;
	exchangeListMatchPos[95][1] = 2.0;
	exchangeListMatchPos[95][2] = 3.0;
	//			
	exchangeListMatchPos[96][0] = 40;
	exchangeListMatchPos[96][1] = 1.5;
	exchangeListMatchPos[96][2] = 2.0;

	exchangeListMatchPos[97][0] = 40;
	exchangeListMatchPos[97][1] = 1.5;
	exchangeListMatchPos[97][2] = 2.0;

	exchangeListMatchPos[98][0] = 41;
	exchangeListMatchPos[98][1] = 1.5;
	exchangeListMatchPos[98][2] = 2.0;
	//			
	exchangeListMatchPos[99][0] = 41;
	exchangeListMatchPos[99][1] = 2.5;
	exchangeListMatchPos[99][2] = 2.0;

	exchangeListMatchPos[100][0] = 41;
	exchangeListMatchPos[100][1] = 2.5;
	exchangeListMatchPos[100][2] = 2.0;
	//			
	exchangeListMatchPos[101][0] = 42;
	exchangeListMatchPos[101][1] = 2.5;
	exchangeListMatchPos[101][2] = 2.0;

	exchangeListMatchPos[102][0] = 42;
	exchangeListMatchPos[102][1] = 2.0;
	exchangeListMatchPos[102][2] = 2.0;

	exchangeListMatchPos[103][0] = 43;
	exchangeListMatchPos[103][1] = 2.0;
	exchangeListMatchPos[103][2] = 2.5;

	exchangeListMatchPos[104][0] = 43;
	exchangeListMatchPos[104][1] = 2.0;
	exchangeListMatchPos[104][2] = 1.5;
	//			
	exchangeListMatchPos[105][0] = 44;
	exchangeListMatchPos[105][1] = 2.0;
	exchangeListMatchPos[105][2] = 1.5;

	exchangeListMatchPos[106][0] = 44;
	exchangeListMatchPos[106][1] = 3.0;
	exchangeListMatchPos[106][2] = 3.0;
	//			
	exchangeListMatchPos[107][0] = 45;
	exchangeListMatchPos[107][1] = 3.0;
	exchangeListMatchPos[107][2] = 3.0;

	exchangeListMatchPos[108][0] = 45;
	exchangeListMatchPos[108][1] = 1.0;
	exchangeListMatchPos[108][2] = 2.0;
	//			
	exchangeListMatchPos[109][0] = 45;
	exchangeListMatchPos[109][1] = 1.0;
	exchangeListMatchPos[109][2] = 2.0;

	exchangeListMatchPos[110][0] = 46;
	exchangeListMatchPos[110][1] = 1.0;
	exchangeListMatchPos[110][2] = 2.0;
	//			
	exchangeListMatchPos[111][0] = 46;
	exchangeListMatchPos[111][1] = 2.0;
	exchangeListMatchPos[111][2] = 2.5;

	exchangeListMatchPos[112][0] = 47;
	exchangeListMatchPos[112][1] = 2.0;
	exchangeListMatchPos[112][2] = 2.5;

	exchangeListMatchPos[113][0] = 47;
	exchangeListMatchPos[113][1] = 2.5;
	exchangeListMatchPos[113][2] = 2.0;
	//7장--------------------------------------------------------------
	exchangeListMatchPos[114][0] = 48;
	exchangeListMatchPos[114][1] = 2.5;
	exchangeListMatchPos[114][2] = 2.0;

	exchangeListMatchPos[115][0] = 48;
	exchangeListMatchPos[115][1] = 1.5;
	exchangeListMatchPos[115][2] = 1.0;
	//			
	exchangeListMatchPos[116][0] = 49;
	exchangeListMatchPos[116][1] = 1.5;
	exchangeListMatchPos[116][2] = 1.0;

	exchangeListMatchPos[117][0] = 49;
	exchangeListMatchPos[117][1] = 1.0;
	exchangeListMatchPos[117][2] = 1.5;
	//			
	exchangeListMatchPos[118][0] = 50;
	exchangeListMatchPos[118][1] = 1.0;
	exchangeListMatchPos[118][2] = 1.5;

	exchangeListMatchPos[119][0] = 50;
	exchangeListMatchPos[119][1] = 1.0;
	exchangeListMatchPos[119][2] = 2.0;

	exchangeListMatchPos[120][0] = 50;
	exchangeListMatchPos[120][1] = 1.0;
	exchangeListMatchPos[120][2] = 2.0;
	//			
	exchangeListMatchPos[121][0] = 51;
	exchangeListMatchPos[121][1] = 1.0;
	exchangeListMatchPos[121][2] = 2.0;

	exchangeListMatchPos[122][0] = 51;
	exchangeListMatchPos[122][1] = 1.0;
	exchangeListMatchPos[122][2] = 1.0;
	//			
	exchangeListMatchPos[123][0] = 52;
	exchangeListMatchPos[123][1] = 1.0;
	exchangeListMatchPos[123][2] = 1.0;

	exchangeListMatchPos[124][0] = 52;
	exchangeListMatchPos[124][1] = 2.0;
	exchangeListMatchPos[124][2] = 1.5;
	//			
	exchangeListMatchPos[125][0] = 53;
	exchangeListMatchPos[125][1] = 2.0;
	exchangeListMatchPos[125][2] = 1.5;

	exchangeListMatchPos[126][0] = 53;
	exchangeListMatchPos[126][1] = 1.0;
	exchangeListMatchPos[126][2] = 1.5;
	//8장--------------------------------------------------------------
	exchangeListMatchPos[127][0] = 54;
	exchangeListMatchPos[127][1] = 1.0;
	exchangeListMatchPos[127][2] = 2.0;

	exchangeListMatchPos[128][0] = 54;
	exchangeListMatchPos[128][1] = 1.5;
	exchangeListMatchPos[128][2] = 1.0;
	//			
	exchangeListMatchPos[129][0] = 54;
	exchangeListMatchPos[129][1] = 1.5;
	exchangeListMatchPos[129][2] = 1.0;

	exchangeListMatchPos[130][0] = 55;
	exchangeListMatchPos[130][1] = 1.5;
	exchangeListMatchPos[130][2] = 1.0;

	exchangeListMatchPos[131][0] = 55;
	exchangeListMatchPos[131][1] = 1.5;
	exchangeListMatchPos[131][2] = 2.0;
	//			
	exchangeListMatchPos[132][0] = 55;
	exchangeListMatchPos[132][1] = 1.5;
	exchangeListMatchPos[132][2] = 2.0;

	exchangeListMatchPos[133][0] = 56;
	exchangeListMatchPos[133][1] = 1.5;
	exchangeListMatchPos[133][2] = 2.0;

	exchangeListMatchPos[134][0] = 56;
	exchangeListMatchPos[134][1] = 1.0;
	exchangeListMatchPos[134][2] = 1.0;

	exchangeListMatchPos[135][0] = 57;
	exchangeListMatchPos[135][1] = 1.5;
	exchangeListMatchPos[135][2] = 1.5;
	//			
	exchangeListMatchPos[136][0] = 57;
	exchangeListMatchPos[136][1] = 1.0;
	exchangeListMatchPos[136][2] = 1.5;

	exchangeListMatchPos[137][0] = 57;
	exchangeListMatchPos[137][1] = 1.5;
	exchangeListMatchPos[137][2] = 1.5;
	//			
	exchangeListMatchPos[138][0] = 57;
	exchangeListMatchPos[138][1] = 1.5;
	exchangeListMatchPos[138][2] = 1.0;

	exchangeListMatchPos[139][0] = 58;
	exchangeListMatchPos[139][1] = 1.0;
	exchangeListMatchPos[139][2] = 2.0;

	exchangeListMatchPos[140][0] = 58;
	exchangeListMatchPos[140][1] = 1.5;
	exchangeListMatchPos[140][2] = 2.0;
	//			
	exchangeListMatchPos[141][0] = 59;
	exchangeListMatchPos[141][1] = 2.0;
	exchangeListMatchPos[141][2] = 1.5;

	exchangeListMatchPos[142][0] = 59;
	exchangeListMatchPos[142][1] = 2.0;
	exchangeListMatchPos[142][2] = 2.0;

	exchangeListMatchPos[143][0] = 60;
	exchangeListMatchPos[143][1] = 1.0;
	exchangeListMatchPos[143][2] = 2.0;
	//			
	exchangeListMatchPos[144][0] = 60;
	exchangeListMatchPos[144][1] = 1.5;
	exchangeListMatchPos[144][2] = 2.0;

	exchangeListMatchPos[145][0] = 61;
	exchangeListMatchPos[145][1] = 3.0;
	exchangeListMatchPos[145][2] = 1.0;
	//			
	exchangeListMatchPos[146][0] = 61;
	exchangeListMatchPos[146][1] = 3.0;
	exchangeListMatchPos[146][2] = 0.5;

	exchangeListMatchPos[147][0] = 62;
	exchangeListMatchPos[147][1] = 2.0;
	exchangeListMatchPos[147][2] = 2.0;
	//			
	exchangeListMatchPos[148][0] = 62;
	exchangeListMatchPos[148][1] = 2.0;
	exchangeListMatchPos[148][2] = 2.0;

	exchangeListMatchPos[149][0] = 63;
	exchangeListMatchPos[149][1] = 2.5;
	exchangeListMatchPos[149][2] = 1.0;
	//		
	exchangeListMatchPos[150][0] = 63;
	exchangeListMatchPos[150][1] = 2.5;
	exchangeListMatchPos[150][2] = 1.0;

	exchangeListMatchPos[151][0] = 63;
	exchangeListMatchPos[151][1] = 2.5;
	exchangeListMatchPos[151][2] = 1.0;
	////추가
	exchangeListMatchPos[152][0] = 64;
	exchangeListMatchPos[152][1] = 1.0;
	exchangeListMatchPos[152][2] = 2.5;

	exchangeListMatchPos[153][0] = 64;
	exchangeListMatchPos[153][1] = 1.0;
	exchangeListMatchPos[153][2] = 2.5;
	//					 
	exchangeListMatchPos[154][0] = 64;
	exchangeListMatchPos[154][1] = 1.0;
	exchangeListMatchPos[154][2] = 2.5;

	exchangeListMatchPos[155][0] = 65;
	exchangeListMatchPos[155][1] = 2.0;
	exchangeListMatchPos[155][2] = 2.0;
	//					 
	exchangeListMatchPos[156][0] = 65;
	exchangeListMatchPos[156][1] = 2.0;
	exchangeListMatchPos[156][2] = 1.5;

	exchangeListMatchPos[157][0] = 66;
	exchangeListMatchPos[157][1] = 2.0;
	exchangeListMatchPos[157][2] = 1.5;
	//					 
	exchangeListMatchPos[158][0] = 66;
	exchangeListMatchPos[158][1] = 1.5;
	exchangeListMatchPos[158][2] = 2.0;

	exchangeListMatchPos[159][0] = 66;
	exchangeListMatchPos[159][1] = 1.5;
	exchangeListMatchPos[159][2] = 1.5;
	//					 
	exchangeListMatchPos[160][0] = 66;
	exchangeListMatchPos[160][1] = 1.5;
	exchangeListMatchPos[160][2] = 1.5;

	exchangeListMatchPos[161][0] = 67;
	exchangeListMatchPos[161][1] = 2.0;
	exchangeListMatchPos[161][2] = 2.5;

	exchangeListMatchPos[162][0] = 67;
	exchangeListMatchPos[162][1] = 2.0;
	exchangeListMatchPos[162][2] = 2.5;
	//					 
	exchangeListMatchPos[163][0] = 67;
	exchangeListMatchPos[163][1] = 2.0;
	exchangeListMatchPos[163][2] = 2.5;

	exchangeListMatchPos[164][0] = 68;
	exchangeListMatchPos[164][1] = 3.0;
	exchangeListMatchPos[164][2] = 3.0;

	exchangeListMatchPos[165][0] = 68;
	exchangeListMatchPos[165][1] = 3.0;
	exchangeListMatchPos[165][2] = 3.0;
	//					 
	exchangeListMatchPos[166][0] = 69;
	exchangeListMatchPos[166][1] = 2.0;
	exchangeListMatchPos[166][2] = 2.0;

	exchangeListMatchPos[167][0] = 69;
	exchangeListMatchPos[167][1] = 2.0;
	exchangeListMatchPos[167][2] = 2.0;
	//					 
	exchangeListMatchPos[168][0] = 70;
	exchangeListMatchPos[168][1] = 1.5;
	exchangeListMatchPos[168][2] = 2.0;

	exchangeListMatchPos[169][0] = 70;
	exchangeListMatchPos[169][1] = 1.0;
	exchangeListMatchPos[169][2] = 2.0;

	exchangeListMatchPos[170][0] = 71;
	exchangeListMatchPos[170][1] = 3.0;
	exchangeListMatchPos[170][2] = 2.0;

	exchangeListMatchPos[171][0] = 71;
	exchangeListMatchPos[171][1] = 2.5;
	exchangeListMatchPos[171][2] = 2.0;
	//					 
	exchangeListMatchPos[172][0] = 72;
	exchangeListMatchPos[172][1] = 2.5;
	exchangeListMatchPos[172][2] = 2.0;

	exchangeListMatchPos[173][0] = 72;
	exchangeListMatchPos[173][1] = 2.0;
	exchangeListMatchPos[173][2] = 2.0;

	exchangeListMatchPos[174][0] = 73;
	exchangeListMatchPos[174][1] = 2.0;
	exchangeListMatchPos[174][2] = 1.0;
	//					 
	exchangeListMatchPos[175][0] = 73;
	exchangeListMatchPos[175][1] = 2.0;
	exchangeListMatchPos[175][2] = 1.0;

	exchangeListMatchPos[176][0] = 73;
	exchangeListMatchPos[176][1] = 2.0;
	exchangeListMatchPos[176][2] = 1.0;
	//2장-----------------------------------------------------------
	exchangeListMatchPos[177][0] = 74;
	exchangeListMatchPos[177][1] = 1.0;
	exchangeListMatchPos[177][2] = 2.0;

	exchangeListMatchPos[178][0] = 74;
	exchangeListMatchPos[178][1] = 1.5;
	exchangeListMatchPos[178][2] = 2.0;
	//					 
	exchangeListMatchPos[179][0] = 75;
	exchangeListMatchPos[179][1] = 2.0;
	exchangeListMatchPos[179][2] = 2.0;

	exchangeListMatchPos[180][0] = 75;
	exchangeListMatchPos[180][1] = 2.0;
	exchangeListMatchPos[180][2] = 1.5;
	//					 
	exchangeListMatchPos[181][0] = 76;
	exchangeListMatchPos[181][1] = 2.0;
	exchangeListMatchPos[181][2] = 1.5;

	exchangeListMatchPos[182][0] = 76;
	exchangeListMatchPos[182][1] = 2.0;
	exchangeListMatchPos[182][2] = 1.5;

	exchangeListMatchPos[183][0] = 76;
	exchangeListMatchPos[183][1] = 2.0;
	exchangeListMatchPos[183][2] = 1.5;
	//					 
	exchangeListMatchPos[184][0] = 77;
	exchangeListMatchPos[184][1] = 1.5;
	exchangeListMatchPos[184][2] = 2.0;

	exchangeListMatchPos[185][0] = 77;
	exchangeListMatchPos[185][1] = 1.5;
	exchangeListMatchPos[185][2] = 2.0;
	//					 
	exchangeListMatchPos[186][0] = 78;
	exchangeListMatchPos[186][1] = 2.5;
	exchangeListMatchPos[186][2] = 2.0;

	exchangeListMatchPos[187][0] = 78;
	exchangeListMatchPos[187][1] = 2.5;
	exchangeListMatchPos[187][2] = 2.0;
	//					 
	exchangeListMatchPos[188][0] = 79;
	exchangeListMatchPos[188][1] = 2.0;
	exchangeListMatchPos[188][2] = 2.5;

	exchangeListMatchPos[189][0] = 79;
	exchangeListMatchPos[189][1] = 2.0;
	exchangeListMatchPos[189][2] = 2.5;
	//3장	   			 
	exchangeListMatchPos[190][0] = 80;
	exchangeListMatchPos[190][1] = 1.0;
	exchangeListMatchPos[190][2] = 1.5;

	exchangeListMatchPos[191][0] = 80;
	exchangeListMatchPos[191][1] = 1.0;
	exchangeListMatchPos[191][2] = 1.5;
	//					 
	exchangeListMatchPos[192][0] = 81;
	exchangeListMatchPos[192][1] = 1.5;
	exchangeListMatchPos[192][2] = 1.0;

	exchangeListMatchPos[193][0] = 81;
	exchangeListMatchPos[193][1] = 1.5;
	exchangeListMatchPos[193][2] = 1.0;
	//					 
	exchangeListMatchPos[194][0] = 82;
	exchangeListMatchPos[194][1] = 1.5;
	exchangeListMatchPos[194][2] = 2.0;

	exchangeListMatchPos[195][0] = 82;
	exchangeListMatchPos[195][1] = 1.5;
	exchangeListMatchPos[195][2] = 2.0;
	//					 
	exchangeListMatchPos[196][0] = 83;
	exchangeListMatchPos[196][1] = 2.0;
	exchangeListMatchPos[196][2] = 1.5;

	exchangeListMatchPos[197][0] = 83;
	exchangeListMatchPos[197][1] = 2.0;
	exchangeListMatchPos[197][2] = 1.5;

	exchangeListMatchPos[198][0] = 83;
	exchangeListMatchPos[198][1] = 2.0;
	exchangeListMatchPos[198][2] = 1.5;
	//					 
	exchangeListMatchPos[199][0] = 84;
	exchangeListMatchPos[199][1] = 2.0;
	exchangeListMatchPos[199][2] = 1.5;

	exchangeListMatchPos[200][0] = 84;
	exchangeListMatchPos[200][1] = 2.0;
	exchangeListMatchPos[200][2] = 1.5;
	//					 
	exchangeListMatchPos[201][0] = 85;
	exchangeListMatchPos[201][1] = 0.5;
	exchangeListMatchPos[201][2] = 3.0;

	exchangeListMatchPos[202][0] = 85;
	exchangeListMatchPos[202][1] = 1.0;
	exchangeListMatchPos[202][2] = 3.0;
	//4장-------------------------------------------------------
	exchangeListMatchPos[203][0] = 86;
	exchangeListMatchPos[203][1] = 2.0;
	exchangeListMatchPos[203][2] = 1.0;

	exchangeListMatchPos[204][0] = 86;
	exchangeListMatchPos[204][1] = 2.0;
	exchangeListMatchPos[204][2] = 1.0;

	exchangeListMatchPos[205][0] = 86;
	exchangeListMatchPos[205][1] = 2.0;
	exchangeListMatchPos[205][2] = 1.0;
	//					 
	exchangeListMatchPos[206][0] = 87;
	exchangeListMatchPos[206][1] = 2.0;
	exchangeListMatchPos[206][2] = 1.0;

	exchangeListMatchPos[207][0] = 87;
	exchangeListMatchPos[207][1] = 1.5;
	exchangeListMatchPos[207][2] = 1.0;
	//					 
	exchangeListMatchPos[208][0] = 88;
	exchangeListMatchPos[208][1] = 1.5;
	exchangeListMatchPos[208][2] = 1.0;

	exchangeListMatchPos[209][0] = 88;
	exchangeListMatchPos[209][1] = 1.0;
	exchangeListMatchPos[209][2] = 1.0;
	//					 
	exchangeListMatchPos[210][0] = 89;
	exchangeListMatchPos[210][1] = 2.0;
	exchangeListMatchPos[210][2] = 2.0;

	exchangeListMatchPos[211][0] = 89;
	exchangeListMatchPos[211][1] = 1.5;
	exchangeListMatchPos[211][2] = 2.0;
	//					 
	exchangeListMatchPos[212][0] = 90;
	exchangeListMatchPos[212][1] = 2.0;
	exchangeListMatchPos[212][2] = 2.0;

	exchangeListMatchPos[213][0] = 90;
	exchangeListMatchPos[213][1] = 2.0;
	exchangeListMatchPos[213][2] = 2.0;

	exchangeListMatchPos[214][0] = 91;
	exchangeListMatchPos[214][1] = 1.0;
	exchangeListMatchPos[214][2] = 1.0;

	exchangeListMatchPos[215][0] = 91;
	exchangeListMatchPos[215][1] = 1.0;
	exchangeListMatchPos[215][2] = 1.0;
	//					 
	exchangeListMatchPos[216][0] = 92;
	exchangeListMatchPos[216][1] = 1.0;
	exchangeListMatchPos[216][2] = 1.5;

	exchangeListMatchPos[217][0] = 92;
	exchangeListMatchPos[217][1] = 1.0;
	exchangeListMatchPos[217][2] = 1.5;
	//					 
	exchangeListMatchPos[218][0] = 92;
	exchangeListMatchPos[218][1] = 1.0;
	exchangeListMatchPos[218][2] = 1.5;

	exchangeListMatchPos[219][0] = 93;
	exchangeListMatchPos[219][1] = 1.5;
	exchangeListMatchPos[219][2] = 1.5;

	exchangeListMatchPos[220][0] = 93;
	exchangeListMatchPos[220][1] = 1.5;
	exchangeListMatchPos[220][2] = 1.5;
	//					 
	exchangeListMatchPos[221][0] = 93;
	exchangeListMatchPos[221][1] = 1.5;
	exchangeListMatchPos[221][2] = 1.0;

	exchangeListMatchPos[222][0] = 93;
	exchangeListMatchPos[222][1] = 1.0;
	exchangeListMatchPos[222][2] = 1.5;
	//					 
	exchangeListMatchPos[223][0] = 94;
	exchangeListMatchPos[223][1] = 2.0;
	exchangeListMatchPos[223][2] = 1.5;

	exchangeListMatchPos[224][0] = 94;
	exchangeListMatchPos[224][1] = 2.0;
	exchangeListMatchPos[224][2] = 1.0;
	//					 
	exchangeListMatchPos[225][0] = 95;
	exchangeListMatchPos[225][1] = 1.0;
	exchangeListMatchPos[225][2] = 2.5;

	exchangeListMatchPos[226][0] = 95;
	exchangeListMatchPos[226][1] = 1.0;
	exchangeListMatchPos[226][2] = 2.5;

	exchangeListMatchPos[227][0] = 95;
	exchangeListMatchPos[227][1] = 1.0;
	exchangeListMatchPos[227][2] = 2.5;
	//5장-------------------------------------------------------
	exchangeListMatchPos[228][0] = 96;
	exchangeListMatchPos[228][1] = 3.0;
	exchangeListMatchPos[228][2] = 1.5;

	exchangeListMatchPos[229][0] = 96;
	exchangeListMatchPos[229][1] = 3.0;
	exchangeListMatchPos[229][2] = 1.0;
	//					 
	exchangeListMatchPos[230][0] = 97;
	exchangeListMatchPos[230][1] = 2.0;
	exchangeListMatchPos[230][2] = 2.0;

	exchangeListMatchPos[231][0] = 97;
	exchangeListMatchPos[231][1] = 2.0;
	exchangeListMatchPos[231][2] = 2.0;
	//					 
	exchangeListMatchPos[232][0] = 98;
	exchangeListMatchPos[232][1] = 2.5;
	exchangeListMatchPos[232][2] = 1.0;

	exchangeListMatchPos[233][0] = 98;
	exchangeListMatchPos[233][1] = 2.5;
	exchangeListMatchPos[233][2] = 1.0;

	exchangeListMatchPos[234][0] = 98;
	exchangeListMatchPos[234][1] = 2.5;
	exchangeListMatchPos[234][2] = 1.0;
	//					 
	exchangeListMatchPos[235][0] = 99;
	exchangeListMatchPos[235][1] = 1.5;
	exchangeListMatchPos[235][2] = 2.0;

	exchangeListMatchPos[236][0] = 99;
	exchangeListMatchPos[236][1] = 1.0;
	exchangeListMatchPos[236][2] = 2.0;
	//					 
	exchangeListMatchPos[237][0] = 100;
	exchangeListMatchPos[237][1] = 2.0;
	exchangeListMatchPos[237][2] = 1.0;

	exchangeListMatchPos[238][0] = 100;
	exchangeListMatchPos[238][1] = 2.0;
	exchangeListMatchPos[238][2] = 1.5;

	exchangeListMatchPos[239][0] = 101;
	exchangeListMatchPos[239][1] = 1.5;
	exchangeListMatchPos[239][2] = 2.0;

	exchangeListMatchPos[240][0] = 101;
	exchangeListMatchPos[240][1] = 1.0;
	exchangeListMatchPos[240][2] = 2.0;
	//6장-----------------------------------------------------------
	exchangeListMatchPos[241][0] = 102;
	exchangeListMatchPos[241][1] = 1.5;
	exchangeListMatchPos[241][2] = 2.0;

	exchangeListMatchPos[242][0] = 102;
	exchangeListMatchPos[242][1] = 1.5;
	exchangeListMatchPos[242][2] = 2.0;

	exchangeListMatchPos[243][0] = 102;
	exchangeListMatchPos[243][1] = 1.5;
	exchangeListMatchPos[243][2] = 2.0;
	//					 
	exchangeListMatchPos[244][0] = 103;
	exchangeListMatchPos[244][1] = 1.0;
	exchangeListMatchPos[244][2] = 2.5;

	exchangeListMatchPos[245][0] = 103;
	exchangeListMatchPos[245][1] = 1.0;
	exchangeListMatchPos[245][2] = 3.0;
	//					 
	exchangeListMatchPos[246][0] = 104;
	exchangeListMatchPos[246][1] = 1.5;
	exchangeListMatchPos[246][2] = 1.5;

	exchangeListMatchPos[247][0] = 104;
	exchangeListMatchPos[247][1] = 1.5;
	exchangeListMatchPos[247][2] = 2.0;
	//					 
	exchangeListMatchPos[248][0] = 104;
	exchangeListMatchPos[248][1] = 1.5;
	exchangeListMatchPos[248][2] = 1.5;

	exchangeListMatchPos[249][0] = 104;
	exchangeListMatchPos[249][1] = 1.0;
	exchangeListMatchPos[249][2] = 1.5;

	exchangeListMatchPos[250][0] = 105;
	exchangeListMatchPos[250][1] = 2.0;
	exchangeListMatchPos[250][2] = 1.5;
	//					 
	exchangeListMatchPos[251][0] = 105;
	exchangeListMatchPos[251][1] = 2.0;
	exchangeListMatchPos[251][2] = 1.5;

	exchangeListMatchPos[252][0] = 106;
	exchangeListMatchPos[252][1] = 1.0;
	exchangeListMatchPos[252][2] = 2.0;
	//			
	exchangeListMatchPos[253][0] = 106;
	exchangeListMatchPos[253][1] = 1.0;
	exchangeListMatchPos[253][2] = 2.5;

	exchangeListMatchPos[254][0] = 107;
	exchangeListMatchPos[254][1] = 1.5;
	exchangeListMatchPos[254][2] = 2.0;

	exchangeListMatchPos[255][0] = 107;
	exchangeListMatchPos[255][1] = 1.5;
	exchangeListMatchPos[255][2] = 2.0;

	exchangeListMatchPos[256][0] = 107;
	exchangeListMatchPos[256][1] = 1.5;
	exchangeListMatchPos[256][2] = 2.0;
	//			
	exchangeListMatchPos[257][0] = 108;
	exchangeListMatchPos[257][1] = 1.5;
	exchangeListMatchPos[257][2] = 2.0;

	exchangeListMatchPos[258][0] = 108;
	exchangeListMatchPos[258][1] = 1.5;
	exchangeListMatchPos[258][2] = 2.0;
	//			
	exchangeListMatchPos[259][0] = 109;
	exchangeListMatchPos[259][1] = 1.0;
	exchangeListMatchPos[259][2] = 2.5;

	exchangeListMatchPos[260][0] = 109;
	exchangeListMatchPos[260][1] = 1.0;
	exchangeListMatchPos[260][2] = 2.5;
	//			
	exchangeListMatchPos[261][0] = 110;
	exchangeListMatchPos[261][1] = 1.0;
	exchangeListMatchPos[261][2] = 2.0;

	exchangeListMatchPos[262][0] = 110;
	exchangeListMatchPos[262][1] = 1.0;
	exchangeListMatchPos[262][2] = 2.0;
	//			
	exchangeListMatchPos[263][0] = 110;
	exchangeListMatchPos[263][1] = 1.0;
	exchangeListMatchPos[263][2] = 2.0;

	exchangeListMatchPos[264][0] = 111;
	exchangeListMatchPos[264][1] = 1.0;
	exchangeListMatchPos[264][2] = 3.0;

	exchangeListMatchPos[265][0] = 111;
	exchangeListMatchPos[265][1] = 1.0;
	exchangeListMatchPos[265][2] = 3.0;
	//7장------------------------------------------------------
	exchangeListMatchPos[266][0] = 112;
	exchangeListMatchPos[266][1] = 3.0;
	exchangeListMatchPos[266][2] = 1.0;

	exchangeListMatchPos[267][0] = 112;
	exchangeListMatchPos[267][1] = 3.0;
	exchangeListMatchPos[267][2] = 1.0;
	//			
	exchangeListMatchPos[268][0] = 113;
	exchangeListMatchPos[268][1] = 1.0;
	exchangeListMatchPos[268][2] = 2.0;

	exchangeListMatchPos[269][0] = 113;
	exchangeListMatchPos[269][1] = 1.0;
	exchangeListMatchPos[269][2] = 2.0;
	//			
	exchangeListMatchPos[270][0] = 113;
	exchangeListMatchPos[270][1] = 1.0;
	exchangeListMatchPos[270][2] = 2.0;

	exchangeListMatchPos[271][0] = 114;
	exchangeListMatchPos[271][1] = 2.0;
	exchangeListMatchPos[271][2] = 1.5;

	exchangeListMatchPos[272][0] = 114;
	exchangeListMatchPos[272][1] = 2.0;
	exchangeListMatchPos[272][2] = 1.5;
	//			
	exchangeListMatchPos[273][0] = 115;
	exchangeListMatchPos[273][1] = 2.5;
	exchangeListMatchPos[273][2] = 1.0;

	exchangeListMatchPos[274][0] = 115;
	exchangeListMatchPos[274][1] = 2.5;
	exchangeListMatchPos[274][2] = 1.0;
	//			
	exchangeListMatchPos[275][0] = 116;
	exchangeListMatchPos[275][1] = 2.5;
	exchangeListMatchPos[275][2] = 1.0;

	exchangeListMatchPos[276][0] = 116;
	exchangeListMatchPos[276][1] = 2.5;
	exchangeListMatchPos[276][2] = 1.0;
	//			
	exchangeListMatchPos[277][0] = 116;
	exchangeListMatchPos[277][1] = 2.5;
	exchangeListMatchPos[277][2] = 1.0;

	exchangeListMatchPos[278][0] = 117;
	exchangeListMatchPos[278][1] = 2.0;
	exchangeListMatchPos[278][2] = 1.5;
	//8장------------------------------------------------------
	exchangeListMatchPos[279][0] = 117;
	exchangeListMatchPos[279][1] = 2.0;
	exchangeListMatchPos[279][2] = 2.0;

	exchangeListMatchPos[280][0] = 118;
	exchangeListMatchPos[280][1] = 2.0;
	exchangeListMatchPos[280][2] = 1.5;
	//			
	exchangeListMatchPos[281][0] = 118;
	exchangeListMatchPos[281][1] = 2.0;
	exchangeListMatchPos[281][2] = 1.5;

	exchangeListMatchPos[282][0] = 119;
	exchangeListMatchPos[282][1] = 2.0;
	exchangeListMatchPos[282][2] = 1.5;

	exchangeListMatchPos[283][0] = 119;
	exchangeListMatchPos[283][1] = 1.5;
	exchangeListMatchPos[283][2] = 1.5;
	//			
	exchangeListMatchPos[284][0] = 119;
	exchangeListMatchPos[284][1] = 1.5;
	exchangeListMatchPos[284][2] = 1.0;

	exchangeListMatchPos[285][0] = 119;
	exchangeListMatchPos[285][1] = 1.5;
	exchangeListMatchPos[285][2] = 1.5;

	exchangeListMatchPos[286][0] = 120;
	exchangeListMatchPos[286][1] = 2.0;
	exchangeListMatchPos[286][2] = 1.0;

	exchangeListMatchPos[287][0] = 120;
	exchangeListMatchPos[287][1] = 2.0;
	exchangeListMatchPos[287][2] = 1.5;
	//			
	exchangeListMatchPos[288][0] = 121;
	exchangeListMatchPos[288][1] = 1.5;
	exchangeListMatchPos[288][2] = 2.0;

	exchangeListMatchPos[289][0] = 121;
	exchangeListMatchPos[289][1] = 1.5;
	exchangeListMatchPos[289][2] = 2.0;
	//			
	exchangeListMatchPos[290][0] = 121;
	exchangeListMatchPos[290][1] = 1.5;
	exchangeListMatchPos[290][2] = 2.0;

	exchangeListMatchPos[291][0] = 122;
	exchangeListMatchPos[291][1] = 2.0;
	exchangeListMatchPos[291][2] = 2.0;

	exchangeListMatchPos[292][0] = 122;
	exchangeListMatchPos[292][1] = 1.5;
	exchangeListMatchPos[292][2] = 2.0;
	//			
	exchangeListMatchPos[293][0] = 123;
	exchangeListMatchPos[293][1] = 2.0;
	exchangeListMatchPos[293][2] = 1.5;

	exchangeListMatchPos[294][0] = 123;
	exchangeListMatchPos[294][1] = 2.0;
	exchangeListMatchPos[294][2] = 2.0;

	exchangeListMatchPos[295][0] = 124;
	exchangeListMatchPos[295][1] = 2.0;
	exchangeListMatchPos[295][2] = 2.0;
	//			
	exchangeListMatchPos[296][0] = 124;
	exchangeListMatchPos[296][1] = 1.5;
	exchangeListMatchPos[296][2] = 2.0;

	exchangeListMatchPos[297][0] = 125;
	exchangeListMatchPos[297][1] = 2.5;
	exchangeListMatchPos[297][2] = 1.0;
	//			
	exchangeListMatchPos[298][0] = 125;
	exchangeListMatchPos[298][1] = 2.5;
	exchangeListMatchPos[298][2] = 1.0;

	exchangeListMatchPos[299][0] = 125;
	exchangeListMatchPos[299][1] = 2.5;
	exchangeListMatchPos[299][2] = 1.0;
	//			
	exchangeListMatchPos[300][0] = 126;
	exchangeListMatchPos[300][1] = 2.0;
	exchangeListMatchPos[300][2] = 2.0;

	exchangeListMatchPos[301][0] = 126;
	exchangeListMatchPos[301][1] = 2.0;
	exchangeListMatchPos[301][2] = 2.0;
	//		
	exchangeListMatchPos[302][0] = 127;
	exchangeListMatchPos[302][1] = 2.0;
	exchangeListMatchPos[302][2] = 1.0;

	exchangeListMatchPos[303][0] = 127;
	exchangeListMatchPos[303][1] = 2.0;
	exchangeListMatchPos[303][2] = 0.5;
}

void bigPicture::setExchangeListDir(float **list)
{
	exchangeListDir = new float*[MAXELN];
	for (int i = 0; i < MAXELN; i++){
		exchangeListDir[i] = new float[4];
		exchangeListDir[i][0] = -1.0f; //블록쌍 라벨
		exchangeListDir[i][1] = -1.0f; //블록쌍 엣지방향 x
		exchangeListDir[i][2] = -1.0f; //블록쌍 엣지방향 y
		exchangeListDir[i][3] = -1.0f; //블록쌍 엣지방향 z
	}

	//1장-------------------------------------------------------------------
	exchangeListDir[0][0] = 0;     exchangeListDir[0][1] = 1.0;        exchangeListDir[0][2] = 0.0f;    exchangeListDir[0][3] = 0.0f;

	exchangeListDir[1][0] = 0;	   exchangeListDir[1][1] = 0.0;        exchangeListDir[1][2] = 1.0f;    exchangeListDir[1][3] = 0.0f;
	//						    					      	   					  							    
	exchangeListDir[2][0] = 1;	   exchangeListDir[2][1] = -2.0;       exchangeListDir[2][2] = 1.0f;    exchangeListDir[2][3] = 0.0f;

	exchangeListDir[3][0] = 1;	   exchangeListDir[3][1] = 2.0;        exchangeListDir[3][2] = 1.0f;    exchangeListDir[3][3] = 0.0f;
	//						   						      	   					  							    
	exchangeListDir[4][0] = 1;	   exchangeListDir[4][1] = 0.0;        exchangeListDir[4][2] = 1.0f;    exchangeListDir[4][3] = 0.0f;

	exchangeListDir[5][0] = 2;	   exchangeListDir[5][1] = 1.0;        exchangeListDir[5][2] = 2.0f;    exchangeListDir[5][3] = 0.0f;
	//						   						      	    					  							    
	exchangeListDir[6][0] = 2;	   exchangeListDir[6][1] = 1.0;        exchangeListDir[6][2] = 2.0f;    exchangeListDir[6][3] = 0.0f;

	exchangeListDir[7][0] = 2;	   exchangeListDir[7][1] = -2.0;       exchangeListDir[7][2] = 1.0f;    exchangeListDir[7][3] = 0.0f;
	//						   						      	   					  							    
	exchangeListDir[8][0] = 2;	   exchangeListDir[8][1] = -1.0;       exchangeListDir[8][2] = 2.0f;    exchangeListDir[8][3] = 0.0f;

	exchangeListDir[9][0] = 3;	   exchangeListDir[9][1] = 0.0;        exchangeListDir[9][2] = 1.0f;    exchangeListDir[9][3] = 0.0f;

	exchangeListDir[10][0] = 3;    exchangeListDir[10][1] = -2.0;     exchangeListDir[10][2] = 1.0f;    exchangeListDir[10][3] = 0.0f;
	//						      						  	 						 
	exchangeListDir[11][0] = 4;	   exchangeListDir[11][1] = 2.0;      exchangeListDir[11][2] = 1.0f;    exchangeListDir[11][3] = 0.0f;

	exchangeListDir[12][0] = 4;	   exchangeListDir[12][1] = -2.0;     exchangeListDir[12][2] = 1.0f;    exchangeListDir[12][3] = 0.0f;

	exchangeListDir[13][0] = 4;	   exchangeListDir[13][1] = 0.0;      exchangeListDir[13][2] = 1.0f;    exchangeListDir[13][3] = 0.0f;
	//						    						 	 
	exchangeListDir[14][0] = 5;	   exchangeListDir[14][1] = 0.0;      exchangeListDir[14][2] = 1.0f;    exchangeListDir[14][3] = 0.0f;

	exchangeListDir[15][0] = 5;	   exchangeListDir[15][1] = 1.0;      exchangeListDir[15][2] = 1.0f;    exchangeListDir[15][3] = 0.0f;
	//						    						 	 
	exchangeListDir[16][0] = 5;	   exchangeListDir[16][1] = 1.0;      exchangeListDir[16][2] = 0.0f;    exchangeListDir[16][3] = 0.0f;

	exchangeListDir[17][0] = 6;	   exchangeListDir[17][1] = 1.0;      exchangeListDir[17][2] = 0.0f;    exchangeListDir[17][3] = 0.0f;

	exchangeListDir[18][0] = 6;	   exchangeListDir[18][1] = 0.0;      exchangeListDir[18][2] = 1.0f;    exchangeListDir[18][3] = 0.0f;

	exchangeListDir[19][0] = 7;	   exchangeListDir[19][1] = 1.0;      exchangeListDir[19][2] = 0.0f;    exchangeListDir[19][3] = 0.0f;
	//						    						 	 
	exchangeListDir[20][0] = 7;	   exchangeListDir[20][1] = 1.0;      exchangeListDir[20][2] = 2.0f;    exchangeListDir[20][3] = 0.0f;

	exchangeListDir[21][0] = 8;	   exchangeListDir[21][1] = 1.0;      exchangeListDir[21][2] = 2.0f;    exchangeListDir[21][3] = 0.0f;

	exchangeListDir[22][0] = 8;	   exchangeListDir[22][1] = 1.0;      exchangeListDir[22][2] = 0.0f;    exchangeListDir[22][3] = 0.0f;
	//						    						 	 
	exchangeListDir[23][0] = 9;	   exchangeListDir[23][1] = 0.0;      exchangeListDir[23][2] = 1.0f;    exchangeListDir[23][3] = 0.0f;

	exchangeListDir[24][0] = 9;	   exchangeListDir[24][1] = 1.0;      exchangeListDir[24][2] = 0.0f;    exchangeListDir[24][3] = 0.0f;
	//2장------------------------- 						          	  						    
	exchangeListDir[25][0] = 10;   exchangeListDir[25][1] = 1.0;      exchangeListDir[25][2] = 0.0f;    exchangeListDir[25][3] = 0.0f;

	exchangeListDir[26][0] = 10;       exchangeListDir[26][1] = 1.0;      exchangeListDir[26][2] = 2.0f;    exchangeListDir[26][3] = 0.0f;
	//						      	   				  	  
	exchangeListDir[27][0] = 11;       exchangeListDir[27][1] = -1.0f;    exchangeListDir[27][2] = 2.0f;    exchangeListDir[27][3] = 0.0f;

	exchangeListDir[28][0] = 11;       exchangeListDir[28][1] = 1.0;      exchangeListDir[28][2] = 0.0f;    exchangeListDir[28][3] = 0.0f;
	//						      	   				 	  
	exchangeListDir[29][0] = 12;       exchangeListDir[29][1] = 0.0;      exchangeListDir[29][2] = 1.0f;    exchangeListDir[29][3] = 0.0f;

	exchangeListDir[30][0] = 12;       exchangeListDir[30][1] = 2.0f;     exchangeListDir[30][2] = 1.0f;    exchangeListDir[30][3] = 0.0f;

	exchangeListDir[31][0] = 12;       exchangeListDir[31][1] = -2.0;     exchangeListDir[31][2] = 1.0f;    exchangeListDir[31][3] = 0.0f;
	//						      	   				 	  
	exchangeListDir[32][0] = 13;       exchangeListDir[32][1] = 0.0f;     exchangeListDir[32][2] = 1.0f;    exchangeListDir[32][3] = 0.0f;

	exchangeListDir[33][0] = 13;       exchangeListDir[33][1] = -2.0;     exchangeListDir[33][2] = 1.0f;    exchangeListDir[33][3] = 0.0f;
	//						   	  	   				 	  
	exchangeListDir[34][0] = 14;       exchangeListDir[34][1] = 1.0;      exchangeListDir[34][2] = 0.0f;    exchangeListDir[34][3] = 0.0f;

	exchangeListDir[35][0] = 14;       exchangeListDir[35][1] = -1.0f;    exchangeListDir[35][2] = 2.0f;    exchangeListDir[35][3] = 0.0f;
	//						   	  	   				 	  
	exchangeListDir[36][0] = 15;       exchangeListDir[36][1] = 2.0;      exchangeListDir[36][2] = 1.0f;    exchangeListDir[36][3] = 0.0f;

	exchangeListDir[37][0] = 15;      exchangeListDir[37][1] = -2.0;      exchangeListDir[37][2] = 1.0f;    exchangeListDir[37][3] = 0.0f;
	//3장	   				   	  	   				     						       
	exchangeListDir[38][0] = 16;      exchangeListDir[38][1] = -2.0;     exchangeListDir[38][2] = 1.0;    exchangeListDir[38][3] = 0.0f;

	exchangeListDir[39][0] = 16;      exchangeListDir[39][1] = 2.0;      exchangeListDir[39][2] = 1.0;    exchangeListDir[39][3] = 0.0f;
	//						   	  	   				  	  								  
	exchangeListDir[40][0] = 17;      exchangeListDir[40][1] = -1.0;     exchangeListDir[40][2] = 2.0;    exchangeListDir[40][3] = 0.0f;

	exchangeListDir[41][0] = 17;      exchangeListDir[41][1] = 1.0;      exchangeListDir[41][2] = 0.0;    exchangeListDir[41][3] = 0.0f;
	//						      	   				 		  							  
	exchangeListDir[42][0] = 18;      exchangeListDir[42][1] = -2.0;     exchangeListDir[42][2] = 1.0;    exchangeListDir[42][3] = 0.0f;

	exchangeListDir[43][0] = 18;      exchangeListDir[43][1] = 0.0;      exchangeListDir[43][2] = 1.0;    exchangeListDir[43][3] = 0.0f;
	//						   	  	   				  	  								  
	exchangeListDir[44][0] = 19;      exchangeListDir[44][1] = -2.0f;    exchangeListDir[44][2] = 1.0;    exchangeListDir[44][3] = 0.0f;

	exchangeListDir[45][0] = 19;      exchangeListDir[45][1] = 2.0;      exchangeListDir[45][2] = 1.0;    exchangeListDir[45][3] = 0.0f;

	exchangeListDir[46][0] = 19;      exchangeListDir[46][1] = 0.0;      exchangeListDir[46][2] = 1.0;    exchangeListDir[46][3] = 0.0f;
	//						      	   				  	  								  
	exchangeListDir[47][0] = 20;      exchangeListDir[47][1] = 1.0;      exchangeListDir[47][2] = 0.0;    exchangeListDir[47][3] = 0.0f;

	exchangeListDir[48][0] = 20;      exchangeListDir[48][1] = -1.0;     exchangeListDir[48][2] = 2.0;    exchangeListDir[48][3] = 0.0f;
	//						      	   				  	  								  
	exchangeListDir[49][0] = 21;      exchangeListDir[49][1] = 1.0;      exchangeListDir[49][2] = 2.0;    exchangeListDir[49][3] = 0.0f;

	exchangeListDir[50][0] = 21;      exchangeListDir[50][1] = 1.0;      exchangeListDir[50][2] = 0.0;    exchangeListDir[50][3] = 0.0f;
	//4장---------------------- 	  	   			         						       	  
	exchangeListDir[51][0] = 22;      exchangeListDir[51][1] = 1.0;      exchangeListDir[51][2] = 0.0;    exchangeListDir[51][3] = 0.0f;

	exchangeListDir[52][0] = 22;      exchangeListDir[52][1] = 0.0;      exchangeListDir[52][2] = 1.0;    exchangeListDir[52][3] = 0.0f;

	exchangeListDir[53][0] = 23;      exchangeListDir[53][1] = 1.0f;     exchangeListDir[53][2] = 0.0;    exchangeListDir[53][3] = 0.0f;
	//						   	     						 	  								  
	exchangeListDir[54][0] = 23;      exchangeListDir[54][1] = 1.0;      exchangeListDir[54][2] = 2.0;    exchangeListDir[54][3] = 0.0f;

	exchangeListDir[55][0] = 24;      exchangeListDir[55][1] = 1.0;      exchangeListDir[55][2] = 2.0;    exchangeListDir[55][3] = 0.0f;
	//						   	     						  	  								  
	exchangeListDir[56][0] = 24;      exchangeListDir[56][1] = 1.0;      exchangeListDir[56][2] = 0.0;    exchangeListDir[56][3] = 0.0f;

	exchangeListDir[57][0] = 25;      exchangeListDir[57][1] = 0.0;      exchangeListDir[57][2] = 1.0;    exchangeListDir[57][3] = 0.0f;
	//						   	     						  		  
	exchangeListDir[58][0] = 25;      exchangeListDir[58][1] = 1.0;      exchangeListDir[58][2] = 0.0;    exchangeListDir[58][3] = 0.0f;

	exchangeListDir[59][0] = 26;      exchangeListDir[59][1] = 1.0f;     exchangeListDir[59][2] = 0.0;    exchangeListDir[59][3] = 0.0f;
	//						         						 	  
	exchangeListDir[60][0] = 26;      exchangeListDir[60][1] = 1.0f;     exchangeListDir[60][2] = 1.0;    exchangeListDir[60][3] = 0.0f;

	exchangeListDir[61][0] = 26;      exchangeListDir[61][1] = 0.0;      exchangeListDir[61][2] = 1.0;    exchangeListDir[61][3] = 0.0f;

	exchangeListDir[62][0] = 27;      exchangeListDir[62][1] = 0.0f;     exchangeListDir[62][2] = 1.0;    exchangeListDir[62][3] = 0.0f;

	exchangeListDir[63][0] = 27;      exchangeListDir[63][1] = -2.0;      exchangeListDir[63][2] = .0f;    exchangeListDir[63][3] = 0.0f;
	//						   	     						 	  
	exchangeListDir[64][0] = 27;      exchangeListDir[64][1] = 2.0f;     exchangeListDir[64][2] = 1.0;    exchangeListDir[64][3] = 0.0f;

	exchangeListDir[65][0] = 28;      exchangeListDir[65][1] = -2.0;     exchangeListDir[65][2] = 1.0;    exchangeListDir[65][3] = 0.0f;
	//						   	     						 	  
	exchangeListDir[66][0] = 28;      exchangeListDir[66][1] = 0.0;      exchangeListDir[66][2] = 1.0;    exchangeListDir[66][3] = 0.0f;

	exchangeListDir[67][0] = 29;      exchangeListDir[67][1] = -1.0;     exchangeListDir[67][2] = 2.0;    exchangeListDir[67][3] = 0.0f;

	exchangeListDir[68][0] = 29;      exchangeListDir[68][1] = -2.0f;    exchangeListDir[68][2] = 1.0;    exchangeListDir[68][3] = 0.0f;
	//						         						 
	exchangeListDir[69][0] = 29;      exchangeListDir[69][1] = 2.0;      exchangeListDir[69][2] = 1.0;    exchangeListDir[69][3] = 0.0f;

	exchangeListDir[70][0] = 29;      exchangeListDir[70][1] = 1.0;      exchangeListDir[70][2] = 2.0;    exchangeListDir[70][3] = 0.0f;
	//						         						  
	exchangeListDir[71][0] = 30;      exchangeListDir[71][1] = 0.0;      exchangeListDir[71][2] = 1.0;    exchangeListDir[71][3] = 0.0f;

	exchangeListDir[72][0] = 30;      exchangeListDir[72][1] = 2.0;      exchangeListDir[72][2] = 1.0;    exchangeListDir[72][3] = 0.0f;
	//						    						  
	exchangeListDir[73][0] = 30;      exchangeListDir[73][1] = -2.0;     exchangeListDir[73][2] = 1.0;    exchangeListDir[73][3] = 0.0f;

	exchangeListDir[74][0] = 31;      exchangeListDir[74][1] = 0.0f;     exchangeListDir[74][2] = 1.0;    exchangeListDir[74][3] = 0.0f;

	exchangeListDir[75][0] = 31;      exchangeListDir[75][1] = 1.0f;      exchangeListDir[75][2] = 0.0f;    exchangeListDir[75][3] = 0.0f;
	//5장---------------------- 	  	  				      	   						       
	exchangeListDir[76][0] = 32;      exchangeListDir[76][1] = 1.0f;      exchangeListDir[76][2] = 0.0f;    exchangeListDir[76][3] = 0.0f;

	exchangeListDir[77][0] = 32;      exchangeListDir[77][1] = 1.0f;      exchangeListDir[77][2] = 2.0f;    exchangeListDir[77][3] = 0.0f;
	//						   	  	  					     
	exchangeListDir[78][0] = 32;      exchangeListDir[78][1] = -1.0f;     exchangeListDir[78][2] = 2.0f;    exchangeListDir[78][3] = 0.0f;

	exchangeListDir[79][0] = 33;      exchangeListDir[79][1] = 0.0f;      exchangeListDir[79][2] = 1.0f;    exchangeListDir[79][3] = 0.0f;
	//						   	  	  					     
	exchangeListDir[80][0] = 33;      exchangeListDir[80][1] = 1.0f;      exchangeListDir[80][2] = 0.0f;    exchangeListDir[80][3] = 0.0f;

	exchangeListDir[81][0] = 34;      exchangeListDir[81][1] = 2.0f;      exchangeListDir[81][2] = 1.0f;    exchangeListDir[81][3] = 0.0f;

	exchangeListDir[82][0] = 34;     exchangeListDir[82][1] = 0.0f;       exchangeListDir[82][2] = 1.0f;    exchangeListDir[82][3] = 0.0f;
	//						 	  	  					 
	exchangeListDir[83][0] = 35;     exchangeListDir[83][1] = 1.0;        exchangeListDir[83][2] = 2.0f;    exchangeListDir[83][3] = 0.0f;

	exchangeListDir[84][0] = 35;     exchangeListDir[84][1] = 1.0;        exchangeListDir[84][2] = 0.0f;    exchangeListDir[84][3] = 0.0f;
	//							  	  					 
	exchangeListDir[85][0] = 36;     exchangeListDir[85][1] = 0.0f;       exchangeListDir[85][2] = 1.0f;    exchangeListDir[85][3] = 0.0f;

	exchangeListDir[86][0] = 36;     exchangeListDir[86][1] = -2.0;       exchangeListDir[86][2] = 1.0f;    exchangeListDir[86][3] = 0.0f;
	//						   	  	  				  
	exchangeListDir[87][0] = 37;     exchangeListDir[87][1] = 1.0;        exchangeListDir[87][2] = 2.0f;    exchangeListDir[87][3] = 0.0f;

	exchangeListDir[88][0] = 37;     exchangeListDir[88][1] = 1.0f;       exchangeListDir[88][2] = 0.0f;    exchangeListDir[88][3] = 0.0f;
	//6장-------				  	  	  					  							       
	exchangeListDir[89][0] = 38;     exchangeListDir[89][1] = -1.0;       exchangeListDir[89][2] = 2.0f;    exchangeListDir[89][3] = 0.0f;

	exchangeListDir[90][0] = 38;     exchangeListDir[90][1] = 2.0f;       exchangeListDir[90][2] = 1.0f;    exchangeListDir[90][3] = 0.0f;

	exchangeListDir[91][0] = 38;     exchangeListDir[91][1] = -2.0;       exchangeListDir[91][2] = 1.0f;    exchangeListDir[91][3] = 0.0f;
	//												  		   
	exchangeListDir[92][0] = 38;     exchangeListDir[92][1] = 1.0;      exchangeListDir[92][2] = 2.0f;    exchangeListDir[92][3] = 0.0f;

	exchangeListDir[93][0] = 39;     exchangeListDir[93][1] = -2.0;     exchangeListDir[93][2] = 1.0f;    exchangeListDir[93][3] = 0.0f;
	//								  			  		   
	exchangeListDir[94][0] = 39;     exchangeListDir[94][1] = 0.0;      exchangeListDir[94][2] = 1.0f;    exchangeListDir[94][3] = 0.0f;

	exchangeListDir[95][0] = 40;     exchangeListDir[95][1] = 1.0;      exchangeListDir[95][2] = 2.0f;    exchangeListDir[95][3] = 0.0f;
	//								  					  
	exchangeListDir[96][0] = 40;     exchangeListDir[96][1] = 1.0;      exchangeListDir[96][2] = 0.0f;    exchangeListDir[96][3] = 0.0f;

	exchangeListDir[97][0] = 40;     exchangeListDir[97][1] = -1.0;     exchangeListDir[97][2] = 2.0f;    exchangeListDir[97][3] = 0.0f;

	exchangeListDir[98][0] = 41;     exchangeListDir[98][1] = 1.0;      exchangeListDir[98][2] = 0.0f;    exchangeListDir[98][3] = 0.0f;
	//						 		  					 	  
	exchangeListDir[99][0] = 41;     exchangeListDir[99][1] = 1.0;      exchangeListDir[99][2] = 2.0f;    exchangeListDir[99][3] = 0.0f;

	exchangeListDir[100][0] = 41;   exchangeListDir[100][1] = -1.0f;  exchangeListDir[100][2] = 2.0f;   exchangeListDir[100][3] = 0.0f;
	//						       							 							
	exchangeListDir[101][0] = 42;   exchangeListDir[101][1] = 1.0;    exchangeListDir[101][2] = 0.0f;   exchangeListDir[101][3] = 0.0f;

	exchangeListDir[102][0] = 42;   exchangeListDir[102][1] = 0.0f;   exchangeListDir[102][2] = 1.0f;   exchangeListDir[102][3] = 0.0f;

	exchangeListDir[103][0] = 43;   exchangeListDir[103][1] = 0.0;    exchangeListDir[103][2] = 1.0f;   exchangeListDir[103][3] = 0.0f;

	exchangeListDir[104][0] = 43;   exchangeListDir[104][1] = 2.0f;   exchangeListDir[104][2] = 1.0f;   exchangeListDir[104][3] = 0.0f;
	//						 		 						
	exchangeListDir[105][0] = 44;   exchangeListDir[105][1] = 1.0f;   exchangeListDir[105][2] = 0.0f;   exchangeListDir[104][3] = 0.0f;

	exchangeListDir[106][0] = 44;   exchangeListDir[106][1] = 0.0;    exchangeListDir[106][2] = 1.0f;   exchangeListDir[106][3] = 0.0f;
	//						 							 	 
	exchangeListDir[107][0] = 45;   exchangeListDir[107][1] = 0.0;    exchangeListDir[107][2] = 1.0f;   exchangeListDir[107][3] = 0.0f;

	exchangeListDir[108][0] = 45;   exchangeListDir[108][1] = -1.0;   exchangeListDir[108][2] = 2.0f;   exchangeListDir[108][3] = 0.0f;
	//						   		 					 	  	  
	exchangeListDir[109][0] = 45;   exchangeListDir[109][1] = 1.0;    exchangeListDir[109][2] = 0.0f;   exchangeListDir[109][3] = 0.0f;

	exchangeListDir[110][0] = 46;   exchangeListDir[110][1] = -2.0;   exchangeListDir[110][2] = 1.0f;   exchangeListDir[110][3] = 0.0f;
	//						   		 						 
	exchangeListDir[111][0] = 46;   exchangeListDir[111][1] = 0.0;    exchangeListDir[111][2] = 1.0f;   exchangeListDir[111][3] = 0.0f;

	exchangeListDir[112][0] = 47;   exchangeListDir[112][1] = 1.0;    exchangeListDir[112][2] = 2.0f;   exchangeListDir[112][3] = 0.0f;

	exchangeListDir[113][0] = 47;   exchangeListDir[113][1] = -1.0;   exchangeListDir[113][2] = 2.0f;   exchangeListDir[113][3] = 0.0f;
	//7장----------------------   							     						       
	exchangeListDir[114][0] = 48;   exchangeListDir[114][1] = -1.0;   exchangeListDir[114][2] = 2.0f;   exchangeListDir[114][3] = 0.0f;

	exchangeListDir[115][0] = 48;   exchangeListDir[115][1] = 1.0;    exchangeListDir[115][2] = 2.0f;   exchangeListDir[115][3] = 0.0f;
	//						  		 					 	 
	exchangeListDir[116][0] = 49;   exchangeListDir[116][1] = 0.0;    exchangeListDir[116][2] = 1.0f;   exchangeListDir[116][3] = 0.0f;

	exchangeListDir[117][0] = 49;   exchangeListDir[117][1] = -2.0;   exchangeListDir[117][2] = 1.0f;   exchangeListDir[117][3] = 0.0f;
	//								 					 	 
	exchangeListDir[118][0] = 50;   exchangeListDir[118][1] = 1.0;    exchangeListDir[118][2] = 0.0f;   exchangeListDir[118][3] = 0.0f;

	exchangeListDir[119][0] = 50;   exchangeListDir[119][1] = -1.0;   exchangeListDir[119][2] = 1.0f;   exchangeListDir[119][3] = 0.0f;

	exchangeListDir[120][0] = 50;   exchangeListDir[120][1] = 0.0;    exchangeListDir[120][2] = 1.0f;   exchangeListDir[120][3] = 0.0f;
	//						 		 						 
	exchangeListDir[121][0] = 51;   exchangeListDir[121][1] = 0.0;    exchangeListDir[121][2] = 1.0f;   exchangeListDir[121][3] = 0.0f;

	exchangeListDir[122][0] = 51;   exchangeListDir[122][1] = 1.0;    exchangeListDir[122][2] = 0.0f;   exchangeListDir[122][3] = 0.0f;
	//						  		 						 
	exchangeListDir[123][0] = 52;   exchangeListDir[123][1] = 2.0;    exchangeListDir[123][2] = 1.0f;   exchangeListDir[123][3] = 0.0f;

	exchangeListDir[124][0] = 52;   exchangeListDir[124][1] = 0.0;    exchangeListDir[124][2] = 1.0f;   exchangeListDir[124][3] = 0.0f;
	//						  		 						  
	exchangeListDir[125][0] = 53;   exchangeListDir[125][1] = 0.0;    exchangeListDir[125][2] = 1.0f;   exchangeListDir[125][3] = 0.0f;

	exchangeListDir[126][0] = 53;   exchangeListDir[126][1] = 1.0f;   exchangeListDir[126][2] = 0.0f;   exchangeListDir[126][3] = 0.0f;
	//8장----------------------   							     						       
	exchangeListDir[127][0] = 54;   exchangeListDir[127][1] = -1.0;   exchangeListDir[127][2] = 2.0f;   exchangeListDir[127][3] = 0.0f;

	exchangeListDir[128][0] = 54;   exchangeListDir[128][1] = 1.0;    exchangeListDir[128][2] = 2.0f;   exchangeListDir[128][3] = 0.0f;
	//					 			 					  
	exchangeListDir[129][0] = 54;   exchangeListDir[129][1] = 1.0f;   exchangeListDir[129][2] = 0.0f;   exchangeListDir[129][3] = 0.0f;

	exchangeListDir[130][0] = 55;   exchangeListDir[130][1] = -1.0;   exchangeListDir[130][2] = 2.0f;   exchangeListDir[130][3] = 0.0f;

	exchangeListDir[131][0] = 55;   exchangeListDir[131][1] = 1.0;    exchangeListDir[131][2] = 0.0f;   exchangeListDir[131][3] = 0.0f;
	//						  		 						  
	exchangeListDir[132][0] = 55;   exchangeListDir[132][1] = 1.0;    exchangeListDir[132][2] = 2.0f;   exchangeListDir[132][3] = 0.0f;

	exchangeListDir[133][0] = 56;   exchangeListDir[133][1] = 0.0;    exchangeListDir[133][2] = 1.0f;   exchangeListDir[133][3] = 0.0f;

	exchangeListDir[134][0] = 56;   exchangeListDir[134][1] = -2.0f;  exchangeListDir[134][2] = 1.0f;   exchangeListDir[134][3] = 0.0f;

	exchangeListDir[135][0] = 57;   exchangeListDir[135][1] = 1.0f;   exchangeListDir[135][2] = 2.0f;   exchangeListDir[135][3] = 0.0f;
	//								 	   
	exchangeListDir[136][0] = 57;   exchangeListDir[136][1] = -2.0;   exchangeListDir[136][2] = 1.0f;   exchangeListDir[136][3] = 0.0f;

	exchangeListDir[137][0] = 57;   exchangeListDir[137][1] = 1.0f;   exchangeListDir[137][2] = 2.0f;   exchangeListDir[137][3] = 0.0f;
	//					  			 					  
	exchangeListDir[138][0] = 57;   exchangeListDir[138][1] = -1.0;   exchangeListDir[138][2] = 2.0f;   exchangeListDir[138][3] = 0.0f;

	exchangeListDir[139][0] = 58;   exchangeListDir[139][1] = 1.0f;   exchangeListDir[139][2] = 0.0f;   exchangeListDir[139][3] = 0.0f;

	exchangeListDir[140][0] = 58;   exchangeListDir[140][1] = 1.0;    exchangeListDir[140][2] = 2.0f;   exchangeListDir[140][3] = 0.0f;
	//								 		  	  
	exchangeListDir[141][0] = 59;   exchangeListDir[141][1] = -2.0;   exchangeListDir[141][2] = 1.0f;   exchangeListDir[141][3] = 0.0f;

	exchangeListDir[142][0] = 59;   exchangeListDir[142][1] = 0.0f;   exchangeListDir[142][2] = 1.0f;   exchangeListDir[142][3] = 0.0f;

	exchangeListDir[143][0] = 60;   exchangeListDir[143][1] = 1.0f;   exchangeListDir[143][2] = 0.0f;   exchangeListDir[143][3] = 0.0f;
	//						   		 						   
	exchangeListDir[144][0] = 60;   exchangeListDir[144][1] = 1.0f;   exchangeListDir[144][2] = 2.0f;   exchangeListDir[144][3] = 0.0f;

	exchangeListDir[145][0] = 61;   exchangeListDir[145][1] = 0.0f;   exchangeListDir[145][2] = 1.0f;   exchangeListDir[145][3] = 0.0f;
	//								 		  	  
	exchangeListDir[146][0] = 61;   exchangeListDir[146][1] = 2.0f;   exchangeListDir[146][2] = 1.0f;   exchangeListDir[146][3] = 0.0f;

	exchangeListDir[147][0] = 62;   exchangeListDir[147][1] = 1.0f;   exchangeListDir[147][2] = 0.0f;   exchangeListDir[147][3] = 0.0f;
	//						  		 						   
	exchangeListDir[148][0] = 62;   exchangeListDir[148][1] = 0.0f;   exchangeListDir[148][2] = 1.0f;   exchangeListDir[148][3] = 0.0f;

	exchangeListDir[149][0] = 63;   exchangeListDir[149][1] = -1.0f;  exchangeListDir[149][2] = 2.0f;   exchangeListDir[149][3] = 0.0f;
	//						   		 						   
	exchangeListDir[150][0] = 63;   exchangeListDir[150][1] = 1.0f;   exchangeListDir[150][2] = 2.0f;   exchangeListDir[150][3] = 0.0f;

	exchangeListDir[151][0] = 63;   exchangeListDir[151][1] = 1.0f;   exchangeListDir[151][2] = 0.0f;   exchangeListDir[151][3] = 0.0f;
	//추가----------------------------------------------------------------------------------------------------------------------------------------------
	exchangeListDir[152][0] = 64;     exchangeListDir[0][1] = -2.0;	      exchangeListDir[0][2] = 1.0;   exchangeListDir[0][3] = 0.0f;

	exchangeListDir[153][0] = 64;	  exchangeListDir[1][1] = 2.0;	      exchangeListDir[1][2] = 1.0;   exchangeListDir[1][3] = 0.0f;
	//						  				      	   			   	  						    
	exchangeListDir[154][0] = 64;	  exchangeListDir[2][1] = 0.0;	      exchangeListDir[2][2] = 1.0;   exchangeListDir[2][3] = 0.0f;

	exchangeListDir[155][0] = 65;	  exchangeListDir[3][1] = 0.0;	      exchangeListDir[3][2] = 1.0;   exchangeListDir[3][3] = 0.0f;
	//						  				      	   			   	  						    
	exchangeListDir[156][0] = 65;	  exchangeListDir[4][1] = 2.0;	      exchangeListDir[4][2] = 1.0;   exchangeListDir[4][3] = 0.0f;

	exchangeListDir[157][0] = 66;	  exchangeListDir[5][1] = -2.0;	      exchangeListDir[5][2] = 1.0;   exchangeListDir[5][3] = 0.0f;
	//						  				      	    		   		 						
	exchangeListDir[158][0] = 66;	  exchangeListDir[6][1] = -1.0;	      exchangeListDir[6][2] = 2.0;   exchangeListDir[6][3] = 0.0f;

	exchangeListDir[159][0] = 66;	  exchangeListDir[7][1] = 1.0;	      exchangeListDir[7][2] = 2.0;   exchangeListDir[7][3] = 0.0f;
	//						  				      	   			   	  						    
	exchangeListDir[160][0] = 66;	  exchangeListDir[8][1] = 2.0;	      exchangeListDir[8][2] = 1.0;   exchangeListDir[8][3] = 0.0f;

	exchangeListDir[161][0] = 67;	  exchangeListDir[9][1] = 2.0;	      exchangeListDir[9][2] = 1.0;   exchangeListDir[9][3] = 0.0f;

	exchangeListDir[162][0] = 67;    exchangeListDir[10][1] = 0.0;	      exchangeListDir[10][2] = 1.0;    exchangeListDir[10][3] = 0.0f;
	//					      					  	 			   		 
	exchangeListDir[163][0] = 67;	 exchangeListDir[11][1] = -2.0;	      exchangeListDir[11][2] = 1.0;    exchangeListDir[11][3] = 0.0f;

	exchangeListDir[164][0] = 68;	 exchangeListDir[12][1] = 1.0;	      exchangeListDir[12][2] = 0.0;    exchangeListDir[12][3] = 0.0f;

	exchangeListDir[165][0] = 68;	 exchangeListDir[13][1] = 0.0;	      exchangeListDir[13][2] = 1.0;    exchangeListDir[13][3] = 0.0f;
	//					    				 	 			    
	exchangeListDir[166][0] = 69;	 exchangeListDir[14][1] = 0.0;	      exchangeListDir[14][2] = 1.0;    exchangeListDir[14][3] = 0.0f;

	exchangeListDir[167][0] = 69;	 exchangeListDir[15][1] = 1.0;	      exchangeListDir[15][2] = 0.0;    exchangeListDir[15][3] = 0.0f;
	//					    				 	 			    
	exchangeListDir[168][0] = 70;	 exchangeListDir[16][1] = -1.0;	      exchangeListDir[16][2] = 2.0;    exchangeListDir[16][3] = 0.0f;

	exchangeListDir[169][0] = 70;	 exchangeListDir[17][1] = 1.0;	      exchangeListDir[17][2] = 0.0;    exchangeListDir[17][3] = 0.0f;

	exchangeListDir[170][0] = 71;	 exchangeListDir[18][1] = 1.0;	      exchangeListDir[18][2] = 0.0;    exchangeListDir[18][3] = 0.0f;

	exchangeListDir[171][0] = 71;	 exchangeListDir[19][1] = -1.0;	      exchangeListDir[19][2] = 2.0;    exchangeListDir[19][3] = 0.0f;
	//					    				 	 			    
	exchangeListDir[172][0] = 72;	 exchangeListDir[20][1] = 1.0;	      exchangeListDir[20][2] = 0.0;    exchangeListDir[20][3] = 0.0f;

	exchangeListDir[173][0] = 72;	 exchangeListDir[21][1] = 0.0;	      exchangeListDir[21][2] = 1.0;    exchangeListDir[21][3] = 0.0f;

	exchangeListDir[174][0] = 73;	 exchangeListDir[22][1] = 0.0;	      exchangeListDir[22][2] = 1.0;    exchangeListDir[22][3] = 0.0f;
	//					    				 	 			    
	exchangeListDir[175][0] = 73;	 exchangeListDir[23][1] = -1.0;	      exchangeListDir[23][2] = 1.0;    exchangeListDir[23][3] = 0.0f;

	exchangeListDir[176][0] = 73;	 exchangeListDir[24][1] = 1.0;	      exchangeListDir[24][2] = 0.0;    exchangeListDir[24][3] = 0.0f;
	//2장---------------------						            					    
	exchangeListDir[177][0] = 74;   exchangeListDir[25][1] = 1.0;	      exchangeListDir[25][2] = 0.0;    exchangeListDir[25][3] = 0.0f;

	exchangeListDir[178][0] = 74;   exchangeListDir[26][1] = 1.0;	      exchangeListDir[26][2] = 2.0;    exchangeListDir[26][3] = 0.0f;
	//					    						  	        
	exchangeListDir[179][0] = 75;   exchangeListDir[27][1] = 0.0;	      exchangeListDir[27][2] = 1.0;    exchangeListDir[27][3] = 0.0f;

	exchangeListDir[180][0] = 75;   exchangeListDir[28][1] = 2.0;	      exchangeListDir[28][2] = 1.0;    exchangeListDir[28][3] = 0.0f;
	//					    						 	        
	exchangeListDir[181][0] = 76;   exchangeListDir[29][1] = 0.0;	      exchangeListDir[29][2] = 1.0;    exchangeListDir[29][3] = 0.0f;

	exchangeListDir[182][0] = 76;   exchangeListDir[30][1] = 2.0;	      exchangeListDir[30][2] = 1.0;    exchangeListDir[30][3] = 0.0f;

	exchangeListDir[183][0] = 76;   exchangeListDir[31][1] = -2.0; 	      exchangeListDir[31][2] = 1.0;    exchangeListDir[31][3] = 0.0f;
	//					    						 	        
	exchangeListDir[184][0] = 77;   exchangeListDir[32][1] = 1.0;	      exchangeListDir[32][2] = 2.0;    exchangeListDir[32][3] = 0.0f;

	exchangeListDir[185][0] = 77;   exchangeListDir[33][1] = 1.0;	      exchangeListDir[33][2] = 0.0;    exchangeListDir[33][3] = 0.0f;
	//					   							 	        
	exchangeListDir[186][0] = 78;   exchangeListDir[34][1] = 1.0;	      exchangeListDir[34][2] = 0.0;    exchangeListDir[34][3] = 0.0f;

	exchangeListDir[187][0] = 78;   exchangeListDir[35][1] = -1.0;	      exchangeListDir[35][2] = 2.0;    exchangeListDir[35][3] = 0.0f;
	//					   							 	        
	exchangeListDir[188][0] = 79;   exchangeListDir[36][1] = -2.0;	      exchangeListDir[36][2] = 1.0;    exchangeListDir[36][3] = 0.0f;

	exchangeListDir[189][0] = 79;  exchangeListDir[37][1] = 2.0;	      exchangeListDir[37][2] = 1.0;    exchangeListDir[37][3] = 0.0f;
	//3장	   			   							      	  //6  		       
	exchangeListDir[190][0] = 80;  exchangeListDir[38][1] = 2.0;	      exchangeListDir[38][2] = 1.0;   exchangeListDir[38][3] = 0.0f;

	exchangeListDir[191][0] = 80;  exchangeListDir[39][1] = -2.0;	      exchangeListDir[39][2] = 1.0;   exchangeListDir[39][3] = 0.0f;
	//					   							  	    	   						  
	exchangeListDir[192][0] = 81;  exchangeListDir[40][1] = -1.0;	      exchangeListDir[40][2] = 2.0;   exchangeListDir[40][3] = 0.0f;

	exchangeListDir[193][0] = 81;  exchangeListDir[41][1] = 1.0;	      exchangeListDir[41][2] = 0.0;   exchangeListDir[41][3] = 0.0f;
	//					    						 		    						  
	exchangeListDir[194][0] = 82;  exchangeListDir[42][1] = 1.0;	      exchangeListDir[42][2] = 0.0;   exchangeListDir[42][3] = 0.0f;

	exchangeListDir[195][0] = 82;  exchangeListDir[43][1] = 1.0;	      exchangeListDir[43][2] = 2.0;   exchangeListDir[43][3] = 0.0f;
	//					   							  	    	   						  
	exchangeListDir[196][0] = 83;  exchangeListDir[44][1] = -2.0; 	      exchangeListDir[44][2] = 1.0;   exchangeListDir[44][3] = 0.0f;

	exchangeListDir[197][0] = 83;  exchangeListDir[45][1] = 2.0;	      exchangeListDir[45][2] = 1.0;   exchangeListDir[45][3] = 0.0f;

	exchangeListDir[198][0] = 83;  exchangeListDir[46][1] = 0.0;	      exchangeListDir[46][2] = 1.0;   exchangeListDir[46][3] = 0.0f;
	//					    						  	    	   						  
	exchangeListDir[199][0] = 84;  exchangeListDir[47][1] = 2.0;	      exchangeListDir[47][2] = 1.0;   exchangeListDir[47][3] = 0.0f;

	exchangeListDir[200][0] = 84;  exchangeListDir[48][1] = 0.0;	      exchangeListDir[48][2] = 1.0;   exchangeListDir[48][3] = 0.0f;
	//					    						  	    	   						  
	exchangeListDir[201][0] = 85;  exchangeListDir[49][1] = 1.0;	      exchangeListDir[49][2] = 2.0;   exchangeListDir[49][3] = 0.0f;

	exchangeListDir[202][0] = 85;  exchangeListDir[50][1] = 1.0;	      exchangeListDir[50][2] = 0.0;   exchangeListDir[50][3] = 0.0f;
	//4장-------------------- 					          	    		       	  
	exchangeListDir[203][0] = 86;  exchangeListDir[51][1] = 1.0;	      exchangeListDir[51][2] = 0.0;   exchangeListDir[51][3] = 0.0f;

	exchangeListDir[204][0] = 86;  exchangeListDir[52][1] = -2.0;	      exchangeListDir[52][2] = 1.0;   exchangeListDir[52][3] = 0.0f;

	exchangeListDir[205][0] = 86;  exchangeListDir[53][1] = 0.0;	      exchangeListDir[53][2] = 1.0;   exchangeListDir[53][3] = 0.0f;
	//					   							 	    	   						  
	exchangeListDir[206][0] = 87;  exchangeListDir[54][1] = 0.0;	      exchangeListDir[54][2] = 1.0;   exchangeListDir[54][3] = 0.0f;

	exchangeListDir[207][0] = 87;  exchangeListDir[55][1] = 1.0;	      exchangeListDir[55][2] = 0.0;   exchangeListDir[55][3] = 0.0f;
	//					   							  	    	   						  
	exchangeListDir[208][0] = 88;  exchangeListDir[56][1] = -1.0;	      exchangeListDir[56][2] = 2.0;   exchangeListDir[56][3] = 0.0f;

	exchangeListDir[209][0] = 88;  exchangeListDir[57][1] = 1.0;	      exchangeListDir[57][2] = 0.0;   exchangeListDir[57][3] = 0.0f;
	//					   							  		    
	exchangeListDir[210][0] = 89;  exchangeListDir[58][1] = 1.0;	      exchangeListDir[58][2] = 0.0;   exchangeListDir[58][3] = 0.0f;

	exchangeListDir[211][0] = 89;  exchangeListDir[59][1] = -1.0;	      exchangeListDir[59][2] = 2.0;   exchangeListDir[59][3] = 0.0f;
	//					    						 	  	    
	exchangeListDir[212][0] = 90;  exchangeListDir[60][1] = 1.0;	      exchangeListDir[60][2] = 0.0;   exchangeListDir[60][3] = 0.0f;

	exchangeListDir[213][0] = 90;  exchangeListDir[61][1] = 0.0;	      exchangeListDir[61][2] = 1.0;   exchangeListDir[61][3] = 0.0f;

	exchangeListDir[214][0] = 91;  exchangeListDir[62][1] = 0.0;	      exchangeListDir[62][2] = 1.0;   exchangeListDir[62][3] = 0.0f;

	exchangeListDir[215][0] = 91;  exchangeListDir[63][1] = 1.0;	       exchangeListDir[63][2] = 0.0;    exchangeListDir[63][3] = 0.0f;
	//					   							 	        
	exchangeListDir[216][0] = 92;  exchangeListDir[64][1] = -2.0;	      exchangeListDir[64][2] = 1.0;   exchangeListDir[64][3] = 0.0f;

	exchangeListDir[217][0] = 92;  exchangeListDir[65][1] = 0.0;	      exchangeListDir[65][2] = 1.0;   exchangeListDir[65][3] = 0.0f;
	//					   							 	        
	exchangeListDir[218][0] = 92;  exchangeListDir[66][1] = 2.0;	      exchangeListDir[66][2] = 1.0;   exchangeListDir[66][3] = 0.0f;

	exchangeListDir[219][0] = 93;  exchangeListDir[67][1] = 2.0;	      exchangeListDir[67][2] = 1.0;   exchangeListDir[67][3] = 0.0f;

	exchangeListDir[220][0] = 93;  exchangeListDir[68][1] = 1.0;	      exchangeListDir[68][2] = 2.0;   exchangeListDir[68][3] = 0.0f;
	//					    						 	        
	exchangeListDir[221][0] = 93;  exchangeListDir[69][1] = -1.0;	      exchangeListDir[69][2] = 2.0;   exchangeListDir[69][3] = 0.0f;

	exchangeListDir[222][0] = 93;  exchangeListDir[70][1] = -2.0;	      exchangeListDir[70][2] = 1.0;   exchangeListDir[70][3] = 0.0f;
	//					    						  	        
	exchangeListDir[223][0] = 94;  exchangeListDir[71][1] = 2.0;	      exchangeListDir[71][2] = 1.0;   exchangeListDir[71][3] = 0.0f;

	exchangeListDir[224][0] = 94;  exchangeListDir[72][1] = 0.0;	      exchangeListDir[72][2] = 1.0;   exchangeListDir[72][3] = 0.0f;
	//					    						  	        
	exchangeListDir[225][0] = 95;  exchangeListDir[73][1] = 0.0;	      exchangeListDir[73][2] = 1.0;   exchangeListDir[73][3] = 0.0f;

	exchangeListDir[226][0] = 95;  exchangeListDir[74][1] = 2.0;	      exchangeListDir[74][2] = 1.0;   exchangeListDir[74][3] = 0.0f;

	exchangeListDir[227][0] = 95;  exchangeListDir[75][1] = -2.0;	      exchangeListDir[75][2] = 1.0;    exchangeListDir[75][3] = 0.0f;
	//5장-------------------- 					      	      //7장  			       
	exchangeListDir[228][0] = 96;  exchangeListDir[76][1] = -2.0; 	      exchangeListDir[76][2] = 1.0;    exchangeListDir[76][3] = 0.0f;

	exchangeListDir[229][0] = 96;  exchangeListDir[77][1] = 0.0;	      exchangeListDir[77][2] = 1.0;    exchangeListDir[77][3] = 0.0f;
	//					   							     	    
	exchangeListDir[230][0] = 97;  exchangeListDir[78][1] = 0.0;	      exchangeListDir[78][2] = 1.0;    exchangeListDir[78][3] = 0.0f;

	exchangeListDir[231][0] = 97;  exchangeListDir[79][1] = 1.0;	      exchangeListDir[79][2] = 0.0;    exchangeListDir[79][3] = 0.0f;
	//					   							     	    
	exchangeListDir[232][0] = 98;  exchangeListDir[80][1] = 1.0;	      exchangeListDir[80][2] = 0.0;    exchangeListDir[80][3] = 0.0f;

	exchangeListDir[233][0] = 98;  exchangeListDir[81][1] = -1.0; 	      exchangeListDir[81][2] = 2.0;    exchangeListDir[81][3] = 0.0f;

	exchangeListDir[234][0] = 98; exchangeListDir[82][1] = 1.0;	         exchangeListDir[82][2] = 2.0;   exchangeListDir[82][3] = 0.0f;
	//					 							 		    
	exchangeListDir[235][0] = 99; exchangeListDir[83][1] = -1.0;	     exchangeListDir[83][2] = 2.0;   exchangeListDir[83][3] = 0.0f;

	exchangeListDir[236][0] = 99; exchangeListDir[84][1] = 1.0;	         exchangeListDir[84][2] = 0.0;   exchangeListDir[84][3] = 0.0f;
	//												 		    
	exchangeListDir[237][0] = 100; exchangeListDir[85][1] = 0.0;	     exchangeListDir[85][2] = 1.0;   exchangeListDir[85][3] = 0.0f;

	exchangeListDir[238][0] = 100; exchangeListDir[86][1] = 2.0;	     exchangeListDir[86][2] = 1.0;   exchangeListDir[86][3] = 0.0f;
	//					   						  			   
	exchangeListDir[239][0] = 101; exchangeListDir[87][1] = -1.0;	     exchangeListDir[87][2] = 2.0;   exchangeListDir[87][3] = 0.0f;

	exchangeListDir[240][0] = 101; exchangeListDir[88][1] = 1.0;	     exchangeListDir[88][2] = 0.0;   exchangeListDir[88][3] = 0.0f;
	//6장-------			  							  			   			       
	exchangeListDir[241][0] = 102; exchangeListDir[89][1] = -1.0; 	     exchangeListDir[89][2] = 2.0;   exchangeListDir[89][3] = 0.0f;

	exchangeListDir[242][0] = 102; exchangeListDir[90][1] = 1.0;	     exchangeListDir[90][2] = 2.0;   exchangeListDir[90][3] = 0.0f;

	exchangeListDir[243][0] = 102; exchangeListDir[91][1] = 1.0;	     exchangeListDir[91][2] = 0.0;   exchangeListDir[91][3] = 0.0f;
	//											  		   	    
	exchangeListDir[244][0] = 103;   exchangeListDir[92][1] = 2.0;	     exchangeListDir[92][2] = 1.0;   exchangeListDir[92][3] = 0.0f;

	exchangeListDir[245][0] = 103;   exchangeListDir[93][1] = 0.0;	     exchangeListDir[93][2] = 1.0;   exchangeListDir[93][3] = 0.0f;
	//										  		   		    
	exchangeListDir[246][0] = 104;   exchangeListDir[94][1] = -2.0;      exchangeListDir[94][2] = 1.0;   exchangeListDir[94][3] = 0.0f;

	exchangeListDir[247][0] = 104;   exchangeListDir[95][1] = 1.0;	     exchangeListDir[95][2] = 2.0;   exchangeListDir[95][3] = 0.0f;
	//												  		    
	exchangeListDir[248][0] = 104;   exchangeListDir[96][1] = -1.0;      exchangeListDir[96][2] = 2.0;   exchangeListDir[96][3] = 0.0f;

	exchangeListDir[249][0] = 104;   exchangeListDir[97][1] = 2.0;	     exchangeListDir[97][2] = 1.0;   exchangeListDir[97][3] = 0.0f;

	exchangeListDir[250][0] = 105;   exchangeListDir[98][1] = 0.0;	     exchangeListDir[98][2] = 1.0;   exchangeListDir[98][3] = 0.0f;
	//					 							 	  	    
	exchangeListDir[251][0] = 105;   exchangeListDir[99][1] = -2.0;	     exchangeListDir[99][2] = 1.0;   exchangeListDir[99][3] = 0.0f;

	exchangeListDir[252][0] = 106;  exchangeListDir[100][1] = 1.0;	    exchangeListDir[100][2] = 0.0;  exchangeListDir[100][3] = 0.0f;
	//					      						 			   			
	exchangeListDir[253][0] = 106;  exchangeListDir[101][1] = 0.0;	    exchangeListDir[101][2] = 1.0;  exchangeListDir[101][3] = 0.0f;

	exchangeListDir[254][0] = 107;  exchangeListDir[102][1] = 1.0;	    exchangeListDir[102][2] = 0.0;  exchangeListDir[102][3] = 0.0f;

	exchangeListDir[255][0] = 107;  exchangeListDir[103][1] = 1.0;	    exchangeListDir[103][2] = 2.0;  exchangeListDir[103][3] = 0.0f;

	exchangeListDir[256][0] = 107;  exchangeListDir[104][1] = -1.0;	    exchangeListDir[104][2] = 2.0;  exchangeListDir[104][3] = 0.0f;
	//					 									    
	exchangeListDir[257][0] = 108;  exchangeListDir[105][1] = -1.0;	    exchangeListDir[105][2] = 2.0;  exchangeListDir[104][3] = 0.0f;

	exchangeListDir[258][0] = 108;  exchangeListDir[106][1] = 1.0;	    exchangeListDir[106][2] = 2.0;  exchangeListDir[106][3] = 0.0f;
	//					 							 	 	    
	exchangeListDir[259][0] = 109;  exchangeListDir[107][1] = 2.0;	    exchangeListDir[107][2] = 1.0;  exchangeListDir[107][3] = 0.0f;

	exchangeListDir[260][0] = 109;  exchangeListDir[108][1] = 0.0;	    exchangeListDir[108][2] = 1.0;  exchangeListDir[108][3] = 0.0f;
	//					   							 	  	    
	exchangeListDir[261][0] = 110;  exchangeListDir[109][1] = 0.0;	    exchangeListDir[109][2] = 1.0;  exchangeListDir[109][3] = 0.0f;

	exchangeListDir[262][0] = 110;  exchangeListDir[110][1] = 1.0;	    exchangeListDir[110][2] = 1.0;  exchangeListDir[110][3] = 0.0f;
	//					   								 	    
	exchangeListDir[263][0] = 110;  exchangeListDir[111][1] = 1.0;	    exchangeListDir[111][2] = 0.0;  exchangeListDir[111][3] = 0.0f;

	exchangeListDir[264][0] = 111;  exchangeListDir[112][1] = 1.0;	    exchangeListDir[112][2] = 0.0;  exchangeListDir[112][3] = 0.0f;

	exchangeListDir[265][0] = 111;  exchangeListDir[113][1] = 0.0;	    exchangeListDir[113][2] = 1.0;  exchangeListDir[113][3] = 0.0f;
	//7장-------------------  						     		//8장   			       
	exchangeListDir[266][0] = 112;  exchangeListDir[114][1] = 0.0;	    exchangeListDir[114][2] = 1.0;  exchangeListDir[114][3] = 0.0f;

	exchangeListDir[267][0] = 112;  exchangeListDir[115][1] = 1.0;	    exchangeListDir[115][2] = 0.0;  exchangeListDir[115][3] = 0.0f;
	//					  							 	 	    
	exchangeListDir[268][0] = 113;  exchangeListDir[116][1] = 1.0;	    exchangeListDir[116][2] = 0.0;  exchangeListDir[116][3] = 0.0f;

	exchangeListDir[269][0] = 113;  exchangeListDir[117][1] = 1.0;	    exchangeListDir[117][2] = 1.0;  exchangeListDir[117][3] = 0.0f;
	//												 	 	    
	exchangeListDir[270][0] = 113;  exchangeListDir[118][1] = 0.0;	    exchangeListDir[118][2] = 1.0;  exchangeListDir[118][3] = 0.0f;

	exchangeListDir[271][0] = 114;  exchangeListDir[119][1] = 0.0;	    exchangeListDir[119][2] = 1.0;  exchangeListDir[119][3] = 0.0f;

	exchangeListDir[272][0] = 114;  exchangeListDir[120][1] = 2.0;	    exchangeListDir[120][2] = 1.0;  exchangeListDir[120][3] = 0.0f;
	//					 								 	    
	exchangeListDir[273][0] = 115;  exchangeListDir[121][1] = 1.0;	    exchangeListDir[121][2] = 2.0;  exchangeListDir[121][3] = 0.0f;

	exchangeListDir[274][0] = 115;  exchangeListDir[122][1] = -1.0;	    exchangeListDir[122][2] = 2.0;  exchangeListDir[122][3] = 0.0f;
	//					  								 	    
	exchangeListDir[275][0] = 116;  exchangeListDir[123][1] = -1.0;	    exchangeListDir[123][2] = 2.0;  exchangeListDir[123][3] = 0.0f;

	exchangeListDir[276][0] = 116;  exchangeListDir[124][1] = 1.0;	    exchangeListDir[124][2] = 2.0;  exchangeListDir[124][3] = 0.0f;
	//					  								  	    
	exchangeListDir[277][0] = 116;  exchangeListDir[125][1] = 1.0;	    exchangeListDir[125][2] = 0.0;  exchangeListDir[125][3] = 0.0f;

	exchangeListDir[278][0] = 117;  exchangeListDir[126][1] = 0.0;	    exchangeListDir[126][2] = 1.0;  exchangeListDir[126][3] = 0.0f;
	//8장-------------------  						     		   			       
	exchangeListDir[279][0] = 117;  exchangeListDir[127][1] = 1.0;	    exchangeListDir[127][2] = 0.0;  exchangeListDir[127][3] = 0.0f;

	exchangeListDir[280][0] = 118;  exchangeListDir[128][1] = -2.0;	    exchangeListDir[128][2] = 0.0;  exchangeListDir[128][3] = 0.0f;
	//				 								  		    
	exchangeListDir[281][0] = 118;  exchangeListDir[129][1] = 0.0;	    exchangeListDir[129][2] = 1.0;  exchangeListDir[129][3] = 0.0f;

	exchangeListDir[282][0] = 119;  exchangeListDir[130][1] = 2.0;	    exchangeListDir[130][2] = 1.0;  exchangeListDir[130][3] = 0.0f;

	exchangeListDir[283][0] = 119;  exchangeListDir[131][1] = -1.0;	    exchangeListDir[131][2] = 2.0;  exchangeListDir[131][3] = 0.0f;
	//					  								  	    
	exchangeListDir[284][0] = 119;  exchangeListDir[132][1] = 1.0;	    exchangeListDir[132][2] = 2.0;  exchangeListDir[132][3] = 0.0f;

	exchangeListDir[285][0] = 119;  exchangeListDir[133][1] = -2.0;	    exchangeListDir[133][2] = 1.0;  exchangeListDir[133][3] = 0.0f;

	exchangeListDir[286][0] = 120;  exchangeListDir[134][1] = 0.0;	    exchangeListDir[134][2] = 1.0;  exchangeListDir[134][3] = 0.0f;

	exchangeListDir[287][0] = 120;  exchangeListDir[135][1] = 2.0;	    exchangeListDir[135][2] = 1.0;  exchangeListDir[135][3] = 0.0f;
	//								   						    
	exchangeListDir[288][0] = 121;  exchangeListDir[136][1] = 1.0;	    exchangeListDir[136][2] = 0.0;  exchangeListDir[136][3] = 0.0f;

	exchangeListDir[289][0] = 121;  exchangeListDir[137][1] = 1.0;	    exchangeListDir[137][2] = 2.0;  exchangeListDir[137][3] = 0.0f;
	//				  								  		    
	exchangeListDir[290][0] = 121;  exchangeListDir[138][1] = -1.0;	    exchangeListDir[138][2] = 2.0;  exchangeListDir[138][3] = 0.0f;

	exchangeListDir[291][0] = 122;  exchangeListDir[139][1] = 1.0;	    exchangeListDir[139][2] = 0.0;  exchangeListDir[139][3] = 0.0f;

	exchangeListDir[292][0] = 122;  exchangeListDir[140][1] = -1.0; 	exchangeListDir[140][2] = 2.0;  exchangeListDir[140][3] = 0.0f;
	//									  	  				    
	exchangeListDir[293][0] = 123;  exchangeListDir[141][1] = 2.0;	    exchangeListDir[141][2] = 1.0;  exchangeListDir[141][3] = 0.0f;

	exchangeListDir[294][0] = 123;  exchangeListDir[142][1] = 0.0;	    exchangeListDir[142][2] = 1.0;  exchangeListDir[142][3] = 0.0f;

	exchangeListDir[295][0] = 124;  exchangeListDir[143][1] = 1.0;	    exchangeListDir[143][2] = 0.0;  exchangeListDir[143][3] = 0.0f;
	//					   								   	    
	exchangeListDir[296][0] = 124;  exchangeListDir[144][1] = -1.0;	    exchangeListDir[144][2] = 2.0;  exchangeListDir[144][3] = 0.0f;

	exchangeListDir[297][0] = 125;  exchangeListDir[145][1] = 1.0;	    exchangeListDir[145][2] = 2.0;  exchangeListDir[145][3] = 0.0f;
	//									  	  				    
	exchangeListDir[298][0] = 125;  exchangeListDir[146][1] = -1.0;	    exchangeListDir[146][2] = 2.0;  exchangeListDir[146][3] = 0.0f;

	exchangeListDir[299][0] = 125;  exchangeListDir[147][1] = 1.0;	    exchangeListDir[147][2] = 0.0;  exchangeListDir[147][3] = 0.0f;
	//					  								   	    
	exchangeListDir[300][0] = 126;  exchangeListDir[148][1] = 1.0;	    exchangeListDir[148][2] = 0.0;  exchangeListDir[148][3] = 0.0f;

	exchangeListDir[301][0] = 126;  exchangeListDir[149][1] = 0.0;	    exchangeListDir[149][2] = 1.0;  exchangeListDir[149][3] = 0.0f;
	//					   								   	    
	exchangeListDir[302][0] = 127;  exchangeListDir[150][1] = 0.0;	    exchangeListDir[150][2] = 1.0;  exchangeListDir[150][3] = 0.0f;

	exchangeListDir[303][0] = 127;  exchangeListDir[151][1] = -2.0;	    exchangeListDir[151][2] = 1.0;  exchangeListDir[151][3] = 0.0f;
}