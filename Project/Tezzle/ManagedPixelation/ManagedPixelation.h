// ManagedPixelation.h

#pragma once
#include "..\Pixelated_abstraction2_1\main.h"
using namespace System;

namespace ManagedPixelation {

	public ref class MainWrap
	{
		// TODO: ���⿡ �� Ŭ������ ���� �޼��带 �߰��մϴ�.
	protected:
		Main* m_pMain;

	public:
		MainWrap();
		virtual ~MainWrap();

		void start(int resol, int process, char* fileName, char *destName);
	};
}
