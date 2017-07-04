//
// Created by ed on 04.07.17.
//

#include <cv.h>
#include <stdio.h>
#include <time.h>

#include "delaunay_transformations/dt.h"

IplImage* image = 0;

IplImage* gray = 0;

IplImage* dst = 0;

int main(int argc, char* argv[]) {
	srand((unsigned int) time(NULL));

	const char* filename = argv[1];
	printf("[i] file: %s\n", filename);

	IplImage* image = cvLoadImage(filename, 1);

	dt_triangulate_canny(image, 100000);

	cvNamedWindow("original", CV_WINDOW_OPENGL);
	cvShowImage("original", image);

	cvWaitKey(0);
	cvDestroyWindow("original");

	cvReleaseImage(&image);
	return 0;
}
