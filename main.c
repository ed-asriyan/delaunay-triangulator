//
// Created by ed on 04.07.17.
//

#include <cv.h>
#include <stdio.h>
#include <time.h>

#include "delaunay_transformations/dt.h"

void testCamera() {
	// получаем любую подключённую камеру
	CvCapture* capture = cvCreateCameraCapture(CV_CAP_ANY); //cvCaptureFromCAM( 0 );
	assert(capture);

	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 1280);//1280);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 960);//960);

	cvNamedWindow("capture", CV_WINDOW_NORMAL);

	printf("[i] press Enter for capture image and Esc for quit!\n\n");

	while (1) {
		IplImage* image = cvQueryFrame(capture);

		unsigned int points = dt_triangulate_canny(image, 10000);
		printf("[i] points number: %d\n", points);
		fflush(stdout);
		cvShowImage("capture", image);

		char c = (char) cvWaitKey(33);
		if (c == 27) { // ESC
			break;
		}
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("capture");
}

void testImage(const char* file_name) {
	IplImage* image = cvLoadImage(file_name, 1);
	assert(image);

	unsigned int points = dt_triangulate_canny(image, 40000);
	printf("[i] points number: %d\n", points);

	cvNamedWindow("original", CV_WINDOW_NORMAL);
	cvShowImage("original", image);
	cvWaitKey(0);

	cvReleaseImage(&image);
	cvDestroyWindow("original");
}

int main(int argc, const char* argv[]) {
	switch (argc) {
		case 1:
			testCamera();
			break;
		case 2:
			testImage(argv[1]);
			break;
		default:
			break;
	}

	return 0;
}