//
// Created by ed on 04.07.17.
//

#include <cv.h>
#include <stdio.h>
#include <time.h>

#include "delaunay_transformations/triangulator.h"
#include "delaunay_transformations/drawer.h"

DtTriangles* (* generator)(const IplImage* image, unsigned int points_num) = NULL;
int (* drawer)(IplImage* dst, const IplImage* source, const DtTriangles* triangles) = NULL;

unsigned int count = 0;

void recognize_arguments(int argc, const char* argv[]) {
	// default
	generator = dt_triangles_random;
	drawer = dt_draw_edges_thickness;
	count = 10000000;
}

int triangulate(const IplImage* source, IplImage* dst) {
	DtTriangles* triangles = generator(source, count);
	if (triangles == NULL) {
		printf("Error\n");
		return 1;
	}
	printf("[i] points number:    %5d\n", triangles->num_points);
	printf("[i] triangles number: %5d\n", triangles->num_triangles);
	printf("\n");

	drawer(dst, source, triangles);
	dt_free_triangles(triangles);

	return 1;
}

void testCamera() {
	CvCapture* capture = cvCreateCameraCapture(CV_CAP_ANY);
	assert(capture);

	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 1280);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 960);

	cvNamedWindow("capture", CV_WINDOW_NORMAL);

	printf("[i] press Enter for capture image and Esc for quit!\n\n");

	while (1) {
		IplImage* source = cvQueryFrame(capture);

		IplImage* dst = cvCreateImage(cvSize(source->width, source->height), 8, 3);

		DtTriangles* triangles = dt_triangles_canny(source, 15000);
		if (triangles == NULL) {
			printf("Error\n");
			cvReleaseImage(&source);
			return;
		}
		printf("[i] points number:    %4d\n", triangles->num_points);
		printf("[i] triangles number: %4d\n", triangles->num_triangles);
		printf("\n");

		dt_draw_edges_thickness(dst, source, triangles);
		dt_free_triangles(triangles);

		cvShowImage("original", dst);

		cvReleaseImage(&dst);

		char c = (char) cvWaitKey(33);
		if (c == 27) { // ESC
			break;
		}
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("capture");
}

void testImage(const char* file_name) {
	IplImage* source = cvLoadImage(file_name, 1);
	IplImage* dst = cvCreateImage(cvGetSize(source), 8, 3);

	if (triangulate(source, dst)) {
		cvNamedWindow("original", CV_WINDOW_NORMAL);
		cvShowImage("original", dst);
		cvWaitKey(0);
	}
	cvReleaseImage(&dst);
	cvReleaseImage(&source);
	cvDestroyWindow("original");
}

int main(int argc, const char* argv[]) {
	srand((unsigned int) time(NULL));

	recognize_arguments(argc, argv);

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