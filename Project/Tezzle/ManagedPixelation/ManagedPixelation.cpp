// 기본 DLL 파일입니다.

#include "stdafx.h"

#include "ManagedPixelation.h"

namespace ManagedPixelation {

	MainWrap::MainWrap() :m_pMain(new Main){};
	MainWrap::~MainWrap(){
		if (m_pMain){
			delete m_pMain;
			m_pMain = 0;
		}
	}

	void MainWrap::start(int resol, int process, char* fileName, char *destName){
		m_pMain->start(resol, process, fileName, destName);
	}
}

