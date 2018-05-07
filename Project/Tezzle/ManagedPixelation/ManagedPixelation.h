// ManagedPixelation.h

#pragma once
#include "..\Pixelated_abstraction2_1\main.h"
using namespace System;

namespace ManagedPixelation {

	public ref class MainWrap
	{
		// TODO: 여기에 이 클래스에 대한 메서드를 추가합니다.
	protected:
		Main* m_pMain;

	public:
		MainWrap();
		virtual ~MainWrap();

		void start(int resol, int process, char* fileName, char *destName);
	};
}
