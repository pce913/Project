
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "vmg_math.h"

#pragma warning (disable:4996)

#define TRANSLATE	1
#define ROTATE		2
#define ZOOMIN		3
#define ZOOMOUT		4

#define NONE		0
#define LEFT		1
#define RIGHT		2

#ifndef _MAIN_H
#define _MAIN_H

class Main{
private:
	void lighting();
	void display();
	void init();
	void puzzlePreprocess();
	void puzzlePreprocess8();
	void puzzleSwap();
public:
	void setImg(char *fileName);
	void abstraction(int resol);
	void puzzleProcessing(int n);
	void saveImg(char* filename);
	void start(int resol, int process, char* fileName, char *destName);
	void test();
};
#endif