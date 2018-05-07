#include "stdafx.h"
#include "marker_recog.h"
#include "marker_recogDlg.h"

// The one and only Cmarker_recogApp object
Cmarker_recogApp theApp;

BOOL Cmarker_recogApp::InitInstance()
{
	CWinAppEx::InitInstance();
	Cmarker_recogDlg dlg;
	dlg.DoModal();
	return FALSE;
}
