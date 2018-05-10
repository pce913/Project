#include "stdafx.h"
#include "Puzzle.h"
#include <time.h>
using namespace std;



//=======================================================
// ���� ������ �پ��� �Լ���
//=======================================================


void bigPicture::init(int w, int h)
{
	srand((unsigned int)time(NULL));

	pWidth = w;
	pHeight = h;

	setBlockSet(bS);
	setTileSet(tS);

	bN = (pWidth*pHeight) / 4;
	bColor = new int[bN];
	bIdx = new int[bN];
	bPos = new int*[bN];
	origbColor = new int[bN];
	origbIdx = new int[bN];
	origbPos = new int*[bN];
	for (int i = 0; i < bN; i++)
	{
		bPos[i] = new int[2];
		origbPos[i] = new int[2];
	}


	BP = new int*[w];
	BPcolor = new V3DF*[w];
	origBP = new int*[w];
	origBPcolor = new V3DF*[w];
	for (int i = 0; i < w; i++){
		BP[i] = new int[h];
		BPcolor[i] = new V3DF[h];
		origBP[i] = new int[h];
		origBPcolor[i] = new V3DF[h];
	}

}

//4x4�� 0~15
//8x8�� 16~18
void bigPicture::getNumOfTile()
{
	//srand((unsigned int)time(NULL));

	int wN4;
	int hN4;

	wN4 = pWidth / 4;
	hN4 = pHeight / 4;
	//cout << wN4 << " " << hN4 << endl;
	if (pWidth % 4 != 0 || pHeight % 4 != 0)
	{
		return;
	}
	tN = wN4 * hN4;

	tIdx = new int[tN];
	tPos = new int*[tN];

	for (int i = 0; i < tN; i++)
	{
		tPos[i] = new int[2];
	}
	for (int i = 0; i < tN; i++)
	{
		tIdx[i] = rand() % 16;
	}
	for (int i = 0; i < hN4; i++)
	{
		for (int j = 0; j < wN4; j++)
		{
			tPos[i*wN4 + j][0] = j * 4;
			tPos[i*wN4 + j][1] = i * 4;
			//cout << i*wN4 + j << " x " << j << " y " << i << endl;
		}
	}

	//Ÿ�� ��ġ ���
	//for (int i = 0; i < tN; i++)
	//{
	//	cout << i << " : " << tIdx[i] << "  " << tPos[i][0] << " , " << tPos[i][1] << endl;
	//}

}

void bigPicture::getNumOfBlock()
{
	int wN4;
	int hN4;

	wN4 = pWidth / 4;
	hN4 = pHeight / 4;



	int x, y;
	int ct = 0;

	for (int i = 0; i < hN4; i++)
	{
		for (int j = 0; j < wN4; j++)
		{
			for (int k = 0; k < 4; k++){
				bIdx[ct] = tS[tIdx[i*wN4 + j]].bIdx[k];	//BP�� ��� �ε����� , Ÿ�Ͼ��� ��� �ε����� �Ҵ�


				x = tPos[i*wN4 + j][0] + tS[tIdx[i*wN4 + j]].bPos[k][0];	//Ÿ���� ��ġ + �ش� Ÿ�� �ε����� ��� ��ġ
				y = tPos[i*wN4 + j][1] + tS[tIdx[i*wN4 + j]].bPos[k][1];

				bPos[ct][0] = x;
				bPos[ct][1] = y;
				ct++;
			}
		}
	}

	for (int i = 0; i < bN; i++){
		origbIdx[i] = bIdx[i];
		origbPos[i][0] = bPos[i][0];
		origbPos[i][1] = bPos[i][1];
	}

	//��� ��ġ ���
	//for (int i = 0; i < bN; i++)
	//{
	//	cout << i << " : " << bIdx[i] << "  " << bPos[i][0] << " , " << bPos[i][1] << endl;
	//}
}

void bigPicture::getNumBlk()
{
	int bIdxNum[19][21] = { 0, };

	for (int i = 0; i < bN; i++) {
		if (bIdx[i] == 0)  bIdxNum[0][bColor[i]]++;
		if (bIdx[i] == 1)  bIdxNum[1][bColor[i]]++;
		if (bIdx[i] == 2)  bIdxNum[2][bColor[i]]++;
		if (bIdx[i] == 3)  bIdxNum[3][bColor[i]]++;
		if (bIdx[i] == 4)  bIdxNum[4][bColor[i]]++;
		if (bIdx[i] == 5)  bIdxNum[5][bColor[i]]++;
		if (bIdx[i] == 6)  bIdxNum[6][bColor[i]]++;
		if (bIdx[i] == 7)  bIdxNum[7][bColor[i]]++;
		if (bIdx[i] == 8)  bIdxNum[8][bColor[i]]++;
		if (bIdx[i] == 9)  bIdxNum[9][bColor[i]]++;
		if (bIdx[i] == 10) bIdxNum[10][bColor[i]]++;
		if (bIdx[i] == 11) bIdxNum[11][bColor[i]]++;
		if (bIdx[i] == 12) bIdxNum[12][bColor[i]]++;
		if (bIdx[i] == 13) bIdxNum[13][bColor[i]]++;
		if (bIdx[i] == 14) bIdxNum[14][bColor[i]]++;
		if (bIdx[i] == 15) bIdxNum[15][bColor[i]]++;
		if (bIdx[i] == 16) bIdxNum[16][bColor[i]]++;
		if (bIdx[i] == 17) bIdxNum[17][bColor[i]]++;
		if (bIdx[i] == 18) bIdxNum[18][bColor[i]]++;
	}

	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 21; j++) {
			if (bIdxNum[i][j] != 0)
				cout << "���Ÿ��: " << i << ", ��: " << j << ", ����: " << bIdxNum[i][j] << endl;
		}
	}
}

void bigPicture::OrigBLtoBP()
{
	V3DF ColorPalette[18] = {
		{ 0.854f, 0.854f, 0.854f }, { 1.0f, 1.0f, 1.0f }, { 0.862f, 0.152f, 0.086f },
		{ 0.996f, 0.611f, 0.184f }, { 1.0f, 0.929f, 0.003f }, { 0.588f, 0.788f, 0.192f },
		{ 0.082f, 0.082f, 1.0f }, { 0.086f, 0.176f, 0.450f }, { 0.4f, 0.031f, 0.807f },
		{ 0.741f, 0.937f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.996f, 0.776f, 0.819f },
		{ 0.329f, 0.180f, 0.090f }, { 0.662f, 0.376f, 0.090f }, { 1.0f, 0.886f, 0.772f },
		{ 0.172f, 0.698f, 0.172f }, { 0.8f, 0.949f, 0.329f }, { 0.521f, 0.047f, 0.556f } };
	//   18 R  // 19 G  // 20 B   //

	int bType;

	for (int i = 0; i < bN; i++){
		bType = bIdx[i];
		//cout << i << " " << bType << endl;

		BP[bPos[i][0] + bS[bType].bRange[0][0]][bPos[i][1] + bS[bType].bRange[0][1]] = i;
		BP[bPos[i][0] + bS[bType].bRange[1][0]][bPos[i][1] + bS[bType].bRange[1][1]] = i;
		BP[bPos[i][0] + bS[bType].bRange[2][0]][bPos[i][1] + bS[bType].bRange[2][1]] = i;
		BP[bPos[i][0] + bS[bType].bRange[3][0]][bPos[i][1] + bS[bType].bRange[3][1]] = i;

		vassign(BPcolor[bPos[i][0] + bS[bType].bRange[0][0]][bPos[i][1] + bS[bType].bRange[0][1]], ColorPalette[bColor[i]]);
		vassign(BPcolor[bPos[i][0] + bS[bType].bRange[1][0]][bPos[i][1] + bS[bType].bRange[1][1]], ColorPalette[bColor[i]]);
		vassign(BPcolor[bPos[i][0] + bS[bType].bRange[2][0]][bPos[i][1] + bS[bType].bRange[2][1]], ColorPalette[bColor[i]]);
		vassign(BPcolor[bPos[i][0] + bS[bType].bRange[3][0]][bPos[i][1] + bS[bType].bRange[3][1]], ColorPalette[bColor[i]]);

		//
		//cout << "x:" << bPos[i][0] + bS[bType].bRange[0][0] << " y:" << bPos[i][1] + bS[bType].bRange[0][1] << endl;
		//cout << "x:" << bPos[i][0] + bS[bType].bRange[1][0] << " y:" << bPos[i][1] + bS[bType].bRange[1][1] << endl;
		//cout << "x:" << bPos[i][0] + bS[bType].bRange[2][0] << " y:" << bPos[i][1] + bS[bType].bRange[2][1] << endl;
		//cout << "x:" << bPos[i][0] + bS[bType].bRange[3][0] << " y:" << bPos[i][1] + bS[bType].bRange[3][1] << endl;
	}

	for (int i = 0; i < pWidth; i++){
		for (int j = 0; j < pHeight; j++){
			origBP[i][j] = BP[i][j];
			vassign(origBPcolor[i][j], BPcolor[i][j]);
		}
	}

}

void bigPicture::BLtoBP()
{
	V3DF ColorPalette[18] = {
		{ 0.854f, 0.854f, 0.854f }, { 1.0f, 1.0f, 1.0f }, { 0.862f, 0.152f, 0.086f },
		{ 0.996f, 0.611f, 0.184f }, { 1.0f, 0.929f, 0.003f }, { 0.588f, 0.788f, 0.192f },
		{ 0.082f, 0.082f, 1.0f }, { 0.086f, 0.176f, 0.450f }, { 0.4f, 0.031f, 0.807f },
		{ 0.741f, 0.937f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.996f, 0.776f, 0.819f },
		{ 0.329f, 0.180f, 0.090f }, { 0.662f, 0.376f, 0.090f }, { 1.0f, 0.886f, 0.772f },
		{ 0.172f, 0.698f, 0.172f }, { 0.8f, 0.949f, 0.329f }, { 0.521f, 0.047f, 0.556f } };
	//   18 R  // 19 G  // 20 B   //

	int bType;

	for (int i = 0; i < bN; i++){
		bType = bIdx[i];
		//cout << i << " " << bType << endl;

		BP[bPos[i][0] + bS[bType].bRange[0][0]][bPos[i][1] + bS[bType].bRange[0][1]] = i;
		BP[bPos[i][0] + bS[bType].bRange[1][0]][bPos[i][1] + bS[bType].bRange[1][1]] = i;
		BP[bPos[i][0] + bS[bType].bRange[2][0]][bPos[i][1] + bS[bType].bRange[2][1]] = i;
		BP[bPos[i][0] + bS[bType].bRange[3][0]][bPos[i][1] + bS[bType].bRange[3][1]] = i;

		vassign(BPcolor[bPos[i][0] + bS[bType].bRange[0][0]][bPos[i][1] + bS[bType].bRange[0][1]], ColorPalette[bColor[i]]);
		vassign(BPcolor[bPos[i][0] + bS[bType].bRange[1][0]][bPos[i][1] + bS[bType].bRange[1][1]], ColorPalette[bColor[i]]);
		vassign(BPcolor[bPos[i][0] + bS[bType].bRange[2][0]][bPos[i][1] + bS[bType].bRange[2][1]], ColorPalette[bColor[i]]);
		vassign(BPcolor[bPos[i][0] + bS[bType].bRange[3][0]][bPos[i][1] + bS[bType].bRange[3][1]], ColorPalette[bColor[i]]);

		//
		//cout << "x:" << bPos[i][0] + bS[bType].bRange[0][0] << " y:" << bPos[i][1] + bS[bType].bRange[0][1] << endl;
		//cout << "x:" << bPos[i][0] + bS[bType].bRange[1][0] << " y:" << bPos[i][1] + bS[bType].bRange[1][1] << endl;
		//cout << "x:" << bPos[i][0] + bS[bType].bRange[2][0] << " y:" << bPos[i][1] + bS[bType].bRange[2][1] << endl;
		//cout << "x:" << bPos[i][0] + bS[bType].bRange[3][0] << " y:" << bPos[i][1] + bS[bType].bRange[3][1] << endl;
	}

	//for (int i = 0; i < pWidth; i++){
	//	for (int j = 0; j < pHeight; j++){
	//		origBP[i][j] = BP[i][j];
	//		vassign(origBPcolor[i][j], BPcolor[i][j]);
	//	}
	//}

}

void bigPicture::printBP()
{
	FILE* fp;
	fp = fopen("puz.txt", "w");

	for (int i = 0; i < pWidth; i++)
	{
		for (int j = 0; j < pHeight; j++){
			fprintf(fp, "%d ", BP[i][j]);
			cout << "i " << i << " j " << j << " " << BP[i][j] << endl;
		}
		fprintf(fp, "\n");
	}

}

void bigPicture::BPcolorMatching(int** PIXcolor)
{

	long long bType;
	long long x, y, ax, ay, X, Y;
	int arr[4][2]; //[l][0] = �������ؽ� ����, [l][1] = ���� Ƚ�� ����
	int c = 0;
	int min = 0;
	int minc = -1;
	for (int i = 0; i < bN; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			arr[k][0] = -1;
			arr[k][1] = 0;
		}
		bType = bIdx[i];
		x = bPos[i][0];
		y = bPos[i][1];
		minc = -1;
		for (int k = 0; k < 4; k++){
			ax = bS[bType].bRange[k][0];
			ay = bS[bType].bRange[k][1];

			X = x + ax;
			Y = y + ay;   
		
			//���� �ش��ϴ� �ȼ��� ���� �߿� ���� ���� ������ ��� ��ϻ��� �Ҵ���
			c = 0;
			min = 0;
			for (int l = 0; l < 4; l++){
				if (arr[l][0] == PIXcolor[X][Y])
				{
					arr[l][1]++;
					c = 1;
					break;
				}
			}
			if (c == 0)
			{
				for (int l = 0; l < 4; l++)
				{
					if (arr[l][0] == -1)
					{
						arr[l][0] = PIXcolor[X][Y];
						arr[l][1]++;
						break;
					}
				}
			}
		}

		for (int l = 0; l < 4; l++)
		{
			if (min < arr[l][1])
			{
				min = arr[l][1];
				minc = arr[l][0];
			}
		}

		bColor[i] = minc;
		//cout << "i " << i << " " << bColor[i] << endl;
	}

	for (int i = 0; i < bN; i++){
		origbColor[i] = bColor[i];
	}
}



void bigPicture::getNumOfTile8()
{
	//srand((unsigned int)time(NULL));

	int wN8;
	int hN8;
	int wN4;
	int hN4;
	int n8;
	int n4;

	int idx = 0;

	if (pWidth % 4 != 0 || pHeight % 4 != 0)
	{
		return;
	}

	wN8 = pWidth / 8;
	hN8 = pHeight / 8;
	wN4 = (pWidth - (wN8 * 8)) / 4;
	hN4 = (pHeight - (hN8 * 8)) / 4;

	n8 = wN8 * hN8;
	n4 = ((wN4 * hN8) + (hN4 * wN8)) * 2 + (wN4 * wN4);

	tN = n8 + n4;

	tIdx = new int[tN];
	tPos = new int*[tN];
	for (int i = 0; i < n8 + n4; i++)
	{
		tPos[i] = new int[2];
	}


	for (int i = 0; i < n8; i++)
	{
		tIdx[i] = rand() % 3 + 16;
	}
	for (int i = 0; i < n4; i++)
	{
		tIdx[n8 + i] = rand() % 16;
	}


	for (int i = 0; i < hN8; i++)
	{
		for (int j = 0; j < wN8; j++)
		{
			tPos[i*wN8 + j][0] = j * 8;
			tPos[i*wN8 + j][1] = i * 8;
			idx = i*wN8 + j;
		}
	}

	idx++;
	int temp = 0;
	if (pHeight % 8 != 0){
		for (int i = 0; i < wN8 * 2; i++)
		{
			tPos[idx][0] = temp;
			tPos[idx][1] = 8 * wN8;
			temp += 4;
			//cout << tPos[idx][0] << " " << tPos[idx][1] << endl;
			idx++;

		}
	}

	if (pWidth % 8 != 0){
		temp = 0;
		for (int i = 0; i < hN8 * 2; i++)
		{
			tPos[idx][0] = 8 * hN8;
			tPos[idx][1] = temp;

			temp += 4;
			idx++;
		}
	}

	if (wN4 == 1 && hN4 == 1){
		tPos[idx][0] = 8 * wN8;
		tPos[idx][1] = 8 * hN8;
	}

	//Ÿ�� ��ġ ���
	//cout << "Ÿ�� ��ġ ���" << endl;
	//for (int i = 0; i < tN; i++)
	//{
	//	cout << i << " : " << tIdx[i] << "  " << tPos[i][0] << " , " << tPos[i][1] << endl;
	//}
}
void bigPicture::getNumOfBlock8()
{
	int wN4;
	int hN4;
	int wN8, hN8;

	wN8 = pWidth / 8;
	hN8 = pHeight / 8;

	wN4 = (pWidth - (wN8 * 8)) / 4;
	hN4 = (pHeight - (hN8 * 8)) / 4;

	int x, y;
	int ct = 0;
	int idx = 0;

	for (int i = 0; i < tN; i++){
		if (tIdx[i] < 16)
		{
			//44Ÿ��
			for (int j = 0; j < 4; j++){
				bIdx[ct] = tS[tIdx[i]].bIdx[j];
				x = tPos[i][0] + tS[tIdx[i]].bPos[j][0];
				y = tPos[i][1] + tS[tIdx[i]].bPos[j][1];

				bPos[ct][0] = x;
				bPos[ct][1] = y;
				ct++;
			}
		}
		else
		{
			//88Ÿ��
			for (int j = 0; j < 16; j++){
				bIdx[ct] = tS[tIdx[i]].bIdx[j];
				x = tPos[i][0] + tS[tIdx[i]].bPos[j][0];
				y = tPos[i][1] + tS[tIdx[i]].bPos[j][1];

				bPos[ct][0] = x;
				bPos[ct][1] = y;
				ct++;
			}
		}
	}

	for (int i = 0; i < bN; i++){
		origbIdx[i] = bIdx[i];
		origbPos[i][0] = bPos[i][0];
		origbPos[i][1] = bPos[i][1];
	}

	/*
	for (int i = 0; i < hN8; i++)
	{
	for (int j = 0; j < wN8; j++)
	{
	for (int k = 0; k < 16; k++){
	bIdx[ct] = tS[tIdx[i*wN8 + j]].bIdx[k];	//BP�� ��� �ε����� , Ÿ�Ͼ��� ��� �ε����� �Ҵ�

	//cout << i*wN8 + j << " : " << tIdx[i*wN8 + j] << endl;

	x = tPos[i*wN8 + j][0] + tS[tIdx[i*wN8 + j]].bPos[k][0];	//Ÿ���� ��ġ + �ش� Ÿ�� �ε����� ��� ��ġ
	y = tPos[i*wN8 + j][1] + tS[tIdx[i*wN8 + j]].bPos[k][1];

	bPos[ct][0] = x;
	bPos[ct][1] = y;
	ct++;
	}
	idx = i*wN8 + j;
	}
	}

	if (pHeight % 8 != 0){
	for (int i = 0; i < hN8 * 2; i++)
	{

	for (int k = 0; k < 4; k++){
	bIdx[ct] = tS[tIdx[idx]].bIdx[k];	//BP�� ��� �ε����� , Ÿ�Ͼ��� ��� �ε����� �Ҵ�


	x = tPos[idx][0] + tS[tIdx[idx]].bPos[k][0];	//Ÿ���� ��ġ + �ش� Ÿ�� �ε����� ��� ��ġ
	y = tPos[idx][1] + tS[tIdx[idx]].bPos[k][1];

	bPos[ct][0] = x;
	bPos[ct][1] = y;

	ct++;

	}
	idx++;
	}
	}

	if (pWidth % 8 != 0){
	for (int i = 0; i < wN8 * 2; i++)
	{
	for (int k = 0; k < 4; k++){
	bIdx[ct] = tS[tIdx[idx]].bIdx[k];	//BP�� ��� �ε����� , Ÿ�Ͼ��� ��� �ε����� �Ҵ�


	x = tPos[idx][0] + tS[tIdx[idx]].bPos[k][0];	//Ÿ���� ��ġ + �ش� Ÿ�� �ε����� ��� ��ġ
	y = tPos[idx][1] + tS[tIdx[idx]].bPos[k][1];

	bPos[ct][0] = x;
	bPos[ct][1] = y;

	ct++;

	}
	idx++;
	}
	}

	if (wN4 == 1 && hN4 == 1){
	for (int k = 0; k < 4; k++){
	bIdx[ct] = tS[tIdx[idx]].bIdx[k];	//BP�� ��� �ε����� , Ÿ�Ͼ��� ��� �ε����� �Ҵ�


	x = tPos[idx][0] + tS[tIdx[idx]].bPos[k][0];	//Ÿ���� ��ġ + �ش� Ÿ�� �ε����� ��� ��ġ
	y = tPos[idx][1] + tS[tIdx[idx]].bPos[k][1];

	bPos[ct][0] = x;
	bPos[ct][1] = y;

	ct++;
	}
	}
	*/

	//cout << "��� ��ġ ���" << endl;
	//for (int i = 0; i<bN; i++)
	//{
	//	cout << i << " : " << bIdx[i] << "  " << bPos[i][0] << " , " << bPos[i][1] << endl;
	//}
}


// ���;ƾƤ��Ӿƾƾƾƾ� ==============================================


void BPmodify()
{

}

void bigPicture::findBlock()
{
	//======================== �ȼ��� �����ϰ� ���� �� ��
	//======================== �� �ȼ��� ���� ����� �ε����� �����ϰ�
	//======================== �� �ȼ��� ������ ����� �ε����� ���� ������ ���� �� �Ʒ� 4������ �����Ѵ�

	//static int flag = 1;
	//if (flag == 1) srand((unsigned int)time(NULL)),flag=0;
	float R[3] = { 1.0f, 0.0f, 0.0f };

	int x, y;		//�����ϰ� ���� BP�� x,y��ǥ
	//int pickIdx;	//�����ϰ� ���� ��ǥ�� ����� �ε���

	int tx, ty;		//translate XY, �ٸ� ����� ã������ �̵��ϴ� ��ǥ

	int findIdx;	//������ �ٸ� ����� �ε���	-2 �⺻��  -1 �ش��ϴ� ��� ������
	closeIdx[0] = -1, closeIdx[1] = -1, closeIdx[2] = -1, closeIdx[3] = -1;	//���� ��ǥ�� ������ �����ʿ������Ʒ� ����� �ε��� ����


	//srand((unsigned int)time(NULL));
	x = rand() % pWidth;
	//srand((unsigned int)time(NULL));
	y = rand() % pHeight;

	//cout << endl;
	//cout << "�����ϰ� ���� ��ǥ : " << x << " / " << y << endl;

	pickIdx = BP[x][y];		//���� ���� �ε����� ����

	//cout << "���� ����� �ε��� : " << pickIdx << endl;

	//bColor[pickIdx] = 20;			//���õ� �ȼ��� ����� �Ķ������� �ٲٰ�
	//BLtoBP();						//���õ� �ȼ��� ����� �Ķ������� �ٲٰ�
	//vassign(BPcolor[x][y], R);		//���õ� �ȼ��� ���������� �ٲ�

	//������ �˻�
	tx = x;
	ty = y;
	findIdx = -2;
	while (pickIdx == BP[tx][ty]){		//�ε����� ���� ���ȿ� �˻��� �ȼ��� ��ĭ�� �̵���, ���� ���� ������ ���ٰ� ħ.
		//cout << "tx : " << tx << " / ty : " << ty << " / t pick Idx : " << BP[tx][ty] << endl;
		tx = tx + 1;
		if (tx >= pWidth){
			findIdx = -1;			//��ã�� ����
			break;
		}
	}
	if (findIdx != -1){					//-1�� �ƴҶ� = ���� ������ �ʾ��� ��, �ε����� ������
		findIdx = BP[tx][ty];
		if (origbColor[pickIdx] == origbColor[findIdx])
			closeIdx[0] = findIdx;
		else
			findIdx = -1;
	}

	//���� �˻�
	tx = x;
	ty = y;
	findIdx = -2;
	while (pickIdx == BP[tx][ty]){
		//cout << "tx : " << tx << " / ty : " << ty << " / t pick Idx : " << BP[tx][ty] << endl;
		tx = tx - 1;
		if (tx <= -1){
			findIdx = -1;			//��ã�� ����
			break;
		}
	}
	if (findIdx != -1){
		findIdx = BP[tx][ty];
		if (origbColor[pickIdx] == origbColor[findIdx])
			closeIdx[1] = findIdx;
		else
			findIdx = -1;
	}

	//���� �˻�
	tx = x;
	ty = y;
	findIdx = -2;
	while (pickIdx == BP[tx][ty]){
		//cout << "tx : " << tx << " / ty : " << ty << " / t pick Idx : " << BP[tx][ty] << endl;
		ty = ty - 1;
		if (ty <= -1){
			findIdx = -1;			//��ã�� ����
			break;
		}
	}
	if (findIdx != -1){
		findIdx = BP[tx][ty];
		if (origbColor[pickIdx] == origbColor[findIdx])
			closeIdx[2] = findIdx;
		else
			findIdx = -1;
	}

	//�Ʒ��� �˻�
	tx = x;
	ty = y;
	findIdx = -2;
	while (pickIdx == BP[tx][ty]){
		//cout << "tx : " << tx << " / ty : " << ty << " / t pick Idx : " << BP[tx][ty] << endl;
		ty = ty + 1;
		if (ty >= pHeight){
			findIdx = -1;			//��ã�� ����
			break;
		}
	}
	if (findIdx != -1){
		findIdx = BP[tx][ty];
		if (origbColor[pickIdx] == origbColor[findIdx])
			closeIdx[3] = findIdx;
		else
			findIdx = -1;
	}

	//cout << "������ ��� �ε��� : right " << closeIdx[0] << " / left " << closeIdx[1] << " / up " << closeIdx[2] << " / down " << closeIdx[3] << endl;

	BLtoBP();
	//vassign(BPcolor[x][y], R);



	//======================== ã�� ��� �ε����� ����
	//======================== ExchangeList�� �ִ� ������ Ȯ���ϰ�
	//======================== ExchangeList�� �����ϸ� ExchangeListPos�� Ȯ���ؼ� Ȯ���� Ȯ���Ѵ�

	int Ox, Oy;		//�����ġ�� ������ ������
	int savei, savej;

	isFIND = 0; //�÷��� : 0��ã�� 1ã��
	Ox = 0; Oy = 0;
	savei = 0; savej = 0;
	for (int i = 0; i < MAXELN; i++){
		if (bIdx[pickIdx] == exchangeList[i][1]){			//���� ���� �ε����� 1�� ��ϰ� ���ٸ�
			for (int j = 0; j < 4; j++){			//������ ��� 4�� �˻��ؼ�
				if (bIdx[closeIdx[j]] == exchangeList[i][2]){		//���࿡ ������ ����ϰ� 2�� ��ϰ� ���ٸ�
					// i< ��� �� ����Ʈ�� �ε���
					// i< ��� ��(�� ��������) ��ġ ����Ʈ�� �ε���
					Ox = bPos[pickIdx][0] - exchangeListPos[i][1];
					Oy = bPos[pickIdx][1] - exchangeListPos[i][2];
					//cout << Ox << "/" << Oy << endl;
					// bPos[pickIdx] ���� ����� �������� ��ġ....���� 1�� ����� ��ġ�� ���� �׷� ������ ���´�?
					// ��ư ������ ���ؼ� ������ �ι�° ����� ��ġ�� �����ָ� ���� ���� ����� ��ġ�� ���´�!
					// �װ� ������ �´°Ű� �ƴ� �ƴѰŰ�..
					if ((Ox + exchangeListPos[i][3]) == bPos[closeIdx[j]][0] && (Oy + exchangeListPos[i][4]) == bPos[closeIdx[j]][1])
					{
						isFIND = 1;	//������ ã�Ҵ�!
						savei = i; savej = j;
						swapRb = exchangeList[savei][0];
						swapIdx = savei;
						closePickIdx = closeIdx[savej];
					}
				}
			}
		}
		else if (bIdx[pickIdx] == exchangeList[i][2]){	//���� ���� �ε����� 2�� ��ϰ� ���ٸ�
			for (int j = 0; j < 4; j++){
				if (bIdx[closeIdx[j]] == exchangeList[i][1]){		//���࿡ ������ ����ϰ� 2�� ��ϰ� ���ٸ�
					// i< ��� �� ����Ʈ�� �ε���
					// i< ��� ��(�� ��������) ��ġ ����Ʈ�� �ε���
					Ox = bPos[pickIdx][0] - exchangeListPos[i][3];
					Oy = bPos[pickIdx][1] - exchangeListPos[i][4];
					// bPos[pickIdx] ���� ����� �������� ��ġ....���� 1�� ����� ��ġ�� ���� �׷� ������ ���´�?
					// ��ư ������ ���ؼ� ������ �ι�° ����� ��ġ�� �����ָ� ���� ���� ����� ��ġ�� ���´�!
					// �װ� ������ �´°Ű� �ƴ� �ƴѰŰ�..
					if ((Ox + exchangeListPos[i][1]) == bPos[closeIdx[j]][0] && (Oy + exchangeListPos[i][2]) == bPos[closeIdx[j]][1])
					{
						isFIND = 1;	//������ ã�Ҵ�!
						savei = i; savej = j;
						swapRb = exchangeList[savei][0];
						swapIdx = savei;
						int tmp = pickIdx;
						pickIdx = closeIdx[savej];
						closePickIdx = tmp;
					}
				}
			}
		}
	}

	if (isFIND == 1){
		//cout << endl;
		//cout << "�ش��ϴ� �ҷ� �� �ε��� : " << savei <<"/"<<savej<< endl;
		//cout <<"�� : " << exchangeList[savei][0] << " 1����� : " << exchangeList[savei][1] << " 2����� : " << exchangeList[savei][2] << endl;
		//cout << "1����� �ε��� : " << pickIdx << " 2����� �ε��� : " << closePickIdx << endl;

	}
	else{
		//cout << "�ش��ϴ� ��� �� ����" << endl;
	}
}
void bigPicture::findBlockVerNew(int _x, int _y)
{
	//======================== �ȼ��� �����ϰ� ���� �� ��
	//======================== �� �ȼ��� ���� ����� �ε����� �����ϰ�
	//======================== �� �ȼ��� ������ ����� �ε����� ���� ������ ���� �� �Ʒ� 4������ �����Ѵ�

	float R[3] = { 1.0f, 0.0f, 0.0f };

	int x, y;		//�����ϰ� ���� BP�� x,y��ǥ
	int tx, ty;		//translate XY, �ٸ� ����� ã������ �̵��ϴ� ��ǥ
	int findIdx;	//������ �ٸ� ����� �ε���	-2 �⺻��  -1 �ش��ϴ� ��� ������

	closeIdx[0] = -1, closeIdx[1] = -1, closeIdx[2] = -1, closeIdx[3] = -1;	//���� ��ǥ�� ������ �����ʿ������Ʒ� ����� �ε��� ����

	x = _x;
	y = _y;

	pickIdx = BP[x][y];		//���� ���� �ε����� ����

	//������ �˻�
	tx = x;
	ty = y;
	findIdx = -2;
	while (pickIdx == BP[tx][ty]){		//�ε����� ���� ���ȿ� �˻��� �ȼ��� ��ĭ�� �̵���, ���� ���� ������ ���ٰ� ħ.
		tx = tx + 1;
		if (tx >= pWidth){
			findIdx = -1;			//��ã�� ����
			break;
		}
	}
	if (findIdx != -1){					//-1�� �ƴҶ� = ���� ������ �ʾ��� ��, �ε����� ������
		findIdx = BP[tx][ty];
		if (origbColor[pickIdx] == origbColor[findIdx]) { //��Ͻ� �� ���� �ٸ��� ������ ���� ��� ������ �ʿ� ����
			//cout << "�� ���Ƽ� �Ѿ�ϴ�." << endl;
			findIdx = -1;
		}
		else {
			//cout << "�� �޶� ����[������]" << endl;
			closeIdx[0] = findIdx;
		}
	}

	//���� �˻�
	tx = x;
	ty = y;
	findIdx = -2;
	while (pickIdx == BP[tx][ty]){
		tx = tx - 1;
		if (tx <= -1){
			findIdx = -1;			//��ã�� ����
			break;
		}
	}
	if (findIdx != -1){
		findIdx = BP[tx][ty];
		if (origbColor[pickIdx] == origbColor[findIdx]) { //��Ͻ� �� ���� �ٸ��� ������ ���� ��� ������ �ʿ� ����
			//cout << "�� ���Ƽ� �Ѿ�ϴ�." << endl;
			findIdx = -1;
		}
		else {
			//cout << "�� �޶� ����[������]" << endl;
			closeIdx[0] = findIdx;
		}
	}

	//���� �˻�
	tx = x;
	ty = y;
	findIdx = -2;
	while (pickIdx == BP[tx][ty]){
		ty = ty - 1;
		if (ty <= -1){
			findIdx = -1;			//��ã�� ����
			break;
		}
	}
	if (findIdx != -1){
		findIdx = BP[tx][ty];
		if (origbColor[pickIdx] == origbColor[findIdx]) { //��Ͻ� �� ���� �ٸ��� ������ ���� ��� ������ �ʿ� ����
			//cout << "�� ���Ƽ� �Ѿ�ϴ�." << endl;
			findIdx = -1;
		}
		else {
			//cout << "�� �޶� ����[������]" << endl;
			closeIdx[0] = findIdx;
		}
	}

	//�Ʒ��� �˻�
	tx = x;
	ty = y;
	findIdx = -2;
	while (pickIdx == BP[tx][ty]){
		ty = ty + 1;
		if (ty >= pHeight){
			findIdx = -1;			//��ã�� ����
			break;
		}
	}
	if (findIdx != -1){
		findIdx = BP[tx][ty];
		if (origbColor[pickIdx] == origbColor[findIdx]) { //��Ͻ� �� ���� �ٸ��� ������ ���� ��� ������ �ʿ� ����
			//cout << "�� ���Ƽ� �Ѿ�ϴ�." << endl;
			findIdx = -1;
		}
		else {
			//cout << "�� �޶� ����[������]" << endl;
			closeIdx[0] = findIdx;
		}
	}

	BLtoBP();

	//======================== ã�� ��� �ε����� ����
	//======================== ExchangeList�� �ִ� ������ Ȯ���ϰ�
	//======================== ExchangeList�� �����ϸ� ExchangeListPos�� Ȯ���ؼ� Ȯ���� Ȯ���Ѵ�

	int Ox, Oy;		//�����ġ�� ������ ������
	int savei, savej;

	isFIND = 0; //�÷��� : 0��ã�� 1ã��
	Ox = 0; Oy = 0;
	savei = 0; savej = 0;
	for (int i = 0; i < MAXELN; i++){
		if (bIdx[pickIdx] == exchangeList[i][1]){			//���� ���� �ε����� 1�� ��ϰ� ���ٸ�
			for (int j = 0; j < 4; j++){			//������ ��� 4�� �˻��ؼ�
				if (bIdx[closeIdx[j]] == exchangeList[i][2]){		//���࿡ ������ ����ϰ� 2�� ��ϰ� ���ٸ�
					// i< ��� �� ����Ʈ�� �ε���
					// i< ��� ��(�� ��������) ��ġ ����Ʈ�� �ε���
					Ox = bPos[pickIdx][0] - exchangeListPos[i][1];
					Oy = bPos[pickIdx][1] - exchangeListPos[i][2];
					//cout << Ox << "/" << Oy << endl;
					// bPos[pickIdx] ���� ����� �������� ��ġ....���� 1�� ����� ��ġ�� ���� �׷� ������ ���´�?
					// ��ư ������ ���ؼ� ������ �ι�° ����� ��ġ�� �����ָ� ���� ���� ����� ��ġ�� ���´�!
					// �װ� ������ �´°Ű� �ƴ� �ƴѰŰ�..
					if ((Ox + exchangeListPos[i][3]) == bPos[closeIdx[j]][0] && (Oy + exchangeListPos[i][4]) == bPos[closeIdx[j]][1])
					{
						isFIND = 1;	//������ ã�Ҵ�!
						savei = i; savej = j;
						swapRb = exchangeList[savei][0];
						swapIdx = savei;
						closePickIdx = closeIdx[savej];
					}
				}
			}
		}
		else if (bIdx[pickIdx] == exchangeList[i][2]){	//���� ���� �ε����� 2�� ��ϰ� ���ٸ�
			for (int j = 0; j < 4; j++){
				if (bIdx[closeIdx[j]] == exchangeList[i][1]){		//���࿡ ������ ����ϰ� 2�� ��ϰ� ���ٸ�
					// i< ��� �� ����Ʈ�� �ε���
					// i< ��� ��(�� ��������) ��ġ ����Ʈ�� �ε���
					Ox = bPos[pickIdx][0] - exchangeListPos[i][3];
					Oy = bPos[pickIdx][1] - exchangeListPos[i][4];
					// bPos[pickIdx] ���� ����� �������� ��ġ....���� 1�� ����� ��ġ�� ���� �׷� ������ ���´�?
					// ��ư ������ ���ؼ� ������ �ι�° ����� ��ġ�� �����ָ� ���� ���� ����� ��ġ�� ���´�!
					// �װ� ������ �´°Ű� �ƴ� �ƴѰŰ�..
					if ((Ox + exchangeListPos[i][1]) == bPos[closeIdx[j]][0] && (Oy + exchangeListPos[i][2]) == bPos[closeIdx[j]][1])
					{
						isFIND = 1;	//������ ã�Ҵ�!
						savei = i; savej = j;
						swapRb = exchangeList[savei][0];
						swapIdx = savei;
						int tmp = pickIdx;
						pickIdx = closeIdx[savej];
						closePickIdx = tmp;
					}
				}
			}
		}
	}
}

void bigPicture::swapBlock(int** BPPXcolor)
{
	int origIdx1 = pickIdx;			//���� 1�����
	int origIdx2 = closePickIdx;	//���� 2�����
	int newSwapIdx;					//���ο� ��Ͻ��ε���

	int Ox, Oy;						//��Ͻ� ������ġ

	if (isFIND != 1)				//���ο� �� ��ã������ ��
	{
		return;
	}


	if (swapIdx == MAXELN - 1){
		newSwapIdx = swapIdx - 1;
	}
	else if (exchangeList[swapIdx][0] == exchangeList[swapIdx + 1][0]){
		newSwapIdx = swapIdx + 1;
	}
	else{
		newSwapIdx = swapIdx - 1;
	}
	//cout << "���� ������ ��Ͻ� �ε��� : " << swapIdx << " / ����� : " << newSwapIdx << endl;

	if (bIdx[origIdx1] == exchangeList[swapIdx][1]){
		Ox = bPos[origIdx1][0] - exchangeListPos[swapIdx][1];
		Oy = bPos[origIdx1][1] - exchangeListPos[swapIdx][2];
	}
	//���� ���� ��ġ�� ã�´�. ( BP���� ������ġ == x+0, y+0 )


	//cout << "���� ��ġ " << Ox << " / " << Oy << endl;

	bIdx[origIdx1] = exchangeList[newSwapIdx][1];	//���ο� ��� ���� �Ҵ�
	bIdx[origIdx2] = exchangeList[newSwapIdx][2];	//���ο� ��� ���� �Ҵ�

	bPos[origIdx1][0] = Ox + exchangeListPos[newSwapIdx][1];
	bPos[origIdx1][1] = Oy + exchangeListPos[newSwapIdx][2];
	//cout << "1 ����� ��� ��ġ " << bPos[origIdx1][0] << " / " << bPos[origIdx1][1] << endl;

	bPos[origIdx2][0] = Ox + exchangeListPos[newSwapIdx][3];
	bPos[origIdx2][1] = Oy + exchangeListPos[newSwapIdx][4];
	//cout << "2 ����� ��� ��ġ " << bPos[origIdx2][0] << " / " << bPos[origIdx2][1] << endl;

	//cout << endl;
	//cout << "swapIdx: " << swapIdx << ", newSwapIdx: " << newSwapIdx << endl;
	//cout << "���ο� �� : " << exchangeList[newSwapIdx][0] << " 1����� : " << bIdx[origIdx1] << " 2����� : " << bIdx[origIdx2] << endl;
	//cout << "1����� �ε��� : " << origIdx1 << " 2����� �ε��� : " << origIdx2 << endl;

	BPcolorMatching(BPPXcolor);
	BLtoBP();

}

void bigPicture::swapBlockVerNew(V3DF **dir, int** BPPXcolor, int w, int h)
{
	int origIdx1 = pickIdx;			//���� 1�����
	int origIdx2 = closePickIdx;	//���� 2�����
	int newSwapIdx;					//���ο� ��Ͻ��ε���
	int MPx, MPy;									//�������� ���� ��Ī��
	float bMPx, bMPy;								//��Ͻֿ� ���� ��Ī���� ��������
	int Ox, Oy;						//��Ͻ� ������ġ
	float MP;										//�������� ���� �������Ⱚ ����
	float bMP;										//��Ͻֿ� ���� �������� �� ����
	float newBMP;									//newSwapIdx�� ���� �������Ⱚ ����

	float SIZE = (h*1.0f) / (pHeight * 1.0f);

	for (int _x = 0; _x < pWidth; _x++) {
		for (int _y = 0; _y < pHeight; _y++) {
			//0. ��ü�� ��Ͻ� �����ؼ� ã�� (�����Ϳ� �����ϴ� ��Ͻ�, ���� ���� �ٸ� ��Ͻ����� ���õǸ� isFIND = 1)
			findBlockVerNew(_x, _y);

			if (isFIND == 1) {
				origIdx1 = pickIdx;
				origIdx2 = closePickIdx;

				if (bIdx[origIdx1] == exchangeList[swapIdx][1]){
					Ox = bPos[origIdx1][0] - exchangeListPos[swapIdx][1];
					Oy = bPos[origIdx1][1] - exchangeListPos[swapIdx][2];
				}

				MPx = (Ox + exchangeListMatchPos[swapIdx][1]) * SIZE;
				MPy = (Oy + exchangeListMatchPos[swapIdx][2]) * SIZE;
				bMPx = exchangeListDir[swapIdx][1];
				bMPy = exchangeListDir[swapIdx][2];

				Vector2Ang(dir[MPx][MPy], &MP);					//���������� �������� ���Ͱ��� ������ ��ȯ�ؼ� ��
				Vector2Ang(exchangeListDir[swapIdx], &bMP);     //��Ͻ��� �������� ���Ͱ��� ������ ��ȯ�ؼ� ��

				//2. �������� ���ؼ� ��Ͻ� ��ü ���� ����
				if (swapIdx == MAXELN - 1){
					newSwapIdx = swapIdx - 1;
					Vector2Ang(exchangeListDir[newSwapIdx], &newBMP);

					if (abs(GetSimpleBlkDeg(MP) - GetSimpleBlkDeg(bMP)) == abs(GetSimpleBlkDeg(MP) - GetSimpleBlkDeg(newBMP))) { //��̵� ����� �κ� (���� ����)
						//cout << "�ٲ��ʿ� ����" << endl;		//���� ����-->�������ⰰ�� 
						newSwapIdx = swapIdx;				//-->�ٲ��ʿ����
					}
					else {
						//abs(GetSimpleBlkDeg(MP) - GetSimpleBlkDeg(bMP)) > abs(GetSimpleBlkDeg(MP) - GetSimpleBlkDeg(newBMP)) ? cout << "���� �����ϱ� ���ο�ɷ� �ٲ����" << endl : cout << "�̹� Ư¡���� �ǰ� ������ �ٲ��ʿ� ����" << endl;
						abs(GetSimpleBlkDeg(MP) - GetSimpleBlkDeg(bMP)) > abs(GetSimpleBlkDeg(MP) - GetSimpleBlkDeg(newBMP)) ? newSwapIdx = swapIdx - 1 : newSwapIdx = swapIdx;
					}
				}
				else if (exchangeList[swapIdx][0] == exchangeList[swapIdx + 1][0]){
					newSwapIdx = swapIdx + 1;
					Vector2Ang(exchangeListDir[newSwapIdx], &newBMP);

					if (abs(GetSimpleBlkDeg(MP) - GetSimpleBlkDeg(bMP)) == abs(GetSimpleBlkDeg(MP) - GetSimpleBlkDeg(newBMP))) { //��̵� ����� �κ� (���� ����)
						//cout << "�ٲ��ʿ� ����" << endl;		//���� ����-->�������ⰰ�� 
						newSwapIdx = swapIdx;				//-->�ٲ��ʿ����
					}
					else {
						//abs(GetSimpleBlkDeg(MP) - GetSimpleBlkDeg(bMP)) > abs(GetSimpleBlkDeg(MP) - GetSimpleBlkDeg(newBMP)) ? cout << "���� �����ϱ� ���ο�ɷ� �ٲ����" << endl : cout << "�̹� Ư¡���� �ǰ� ������ �ٲ��ʿ� ����" << endl;
						abs(GetSimpleBlkDeg(MP) - GetSimpleBlkDeg(bMP)) > abs(GetSimpleBlkDeg(MP) - GetSimpleBlkDeg(newBMP)) ? newSwapIdx = swapIdx + 1 : newSwapIdx = swapIdx;
					}
				}
				else{
					newSwapIdx = swapIdx - 1;
					Vector2Ang(exchangeListDir[newSwapIdx], &newBMP);

					if (abs(GetSimpleBlkDeg(MP) - GetSimpleBlkDeg(bMP)) == abs(GetSimpleBlkDeg(MP) - GetSimpleBlkDeg(newBMP))) { //��̵� ����� �κ� (���� ����)
						//cout << "�ٲ��ʿ� ����" << endl;		//���� ����-->�������ⰰ�� 
						newSwapIdx = swapIdx;				//-->�ٲ��ʿ����
					}
					else {
						//abs(GetSimpleBlkDeg(MP) - GetSimpleBlkDeg(bMP)) > abs(GetSimpleBlkDeg(MP) - GetSimpleBlkDeg(newBMP)) ? cout << "���� �����ϱ� ���ο�ɷ� �ٲ����" << endl : cout << "�̹� Ư¡���� �ǰ� ������ �ٲ��ʿ� ����" << endl;
						abs(GetSimpleBlkDeg(MP) - GetSimpleBlkDeg(bMP)) > abs(GetSimpleBlkDeg(MP) - GetSimpleBlkDeg(newBMP)) ? newSwapIdx = swapIdx - 1 : newSwapIdx = swapIdx;
					}
				}

				bIdx[origIdx1] = exchangeList[newSwapIdx][1];	//���ο� ��� ���� �Ҵ�
				bIdx[origIdx2] = exchangeList[newSwapIdx][2];	//���ο� ��� ���� �Ҵ�

				bPos[origIdx1][0] = Ox + exchangeListPos[newSwapIdx][1];
				bPos[origIdx1][1] = Oy + exchangeListPos[newSwapIdx][2];
				bPos[origIdx2][0] = Ox + exchangeListPos[newSwapIdx][3];
				bPos[origIdx2][1] = Oy + exchangeListPos[newSwapIdx][4];

				BPcolorMatching(BPPXcolor);
				BLtoBP();
			}
		}
	}
}