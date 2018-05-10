#include "stdafx.h"
#include "CamOpenCV.h"

CCamOpenCV::CCamOpenCV(int cameraID, int width, int height){
	_capture = cvCaptureFromCAM(cameraID);
}

CCamOpenCV::~CCamOpenCV(void){
	if (_capture) {
		cvReleaseCapture(&_capture);
	}
}

IplImage *CCamOpenCV::CaptureImage(){
	if (_capture) {                                       //_capture가 null null이 리턴 된다.
		if (cvGrabFrame (_capture)) {
			IplImage *cvImage = cvRetrieveFrame (_capture);
			return cvImage;
		}
	}
	return NULL;
}

