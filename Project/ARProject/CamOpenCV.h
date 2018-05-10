#pragma once

#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

// OpenCV 2.3.1ÀÎ °æ¿ì
#pragma comment(lib,"opencv_calib3d2413d.lib")
#pragma comment(lib,"opencv_core2413d.lib") 
#pragma comment(lib,"opencv_highgui2413d.lib") 
#pragma comment(lib,"opencv_imgproc2413d.lib") 

class CCamOpenCV
{
public:
	CCamOpenCV(int cameraID = -1, int width = -1, int height = -1);
	virtual ~CCamOpenCV(void);

	IplImage *CaptureImage ();

private:
	BITMAPINFO _bitmapInfo;	
	CvCapture *_capture;	
};
