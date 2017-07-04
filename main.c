//
// Created by ed on 04.07.17.
//

#include <cv.h>
#include <stdio.h>
#include <time.h>

#include "delaunay_transformations/dt.h"


int main(int argc, char* argv[]) {
	srand((unsigned int) time(NULL));

	const char* filename = argv[1];
	printf("[i] file: %s\n", filename);

	IplImage* image = cvLoadImage(filename, 1);

	dt_triangulate_random(image, (unsigned int) ((image->width * image->height) * 0.00065));

	cvNamedWindow("original", CV_WINDOW_OPENGL);
	cvShowImage("original", image);

	cvWaitKey(0);
	cvDestroyWindow("original");

	cvReleaseImage(&image);
	return 0;
}
