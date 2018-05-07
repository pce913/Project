
// marker_recogDlg.h : header file
//

#pragma once

#include "CamOpenCV.h"
#include "MarkerDetection.h"
#include "OpenGlDraw.h"

// Cmarker_recogDlg dialog
class Cmarker_recogDlg : public CDialog
{
public:
	Cmarker_recogDlg(CWnd *pParent = NULL);	// standard constructor

	CCamOpenCV *_camera;
	CMarkerDetection  *_markRecog;
	COpenGlDraw	*_oglDraw;

	CRect _dispRect;

// Dialog Data
	enum { IDD = IDD_MARKER_RECOG_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange *pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};
