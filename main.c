//
// Created by ed on 04.07.17.
//

#include <cv.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "delaunay_transformations/triangulator.h"
#include "delaunay_transformations/drawer.h"

DtTriangles* (* generator)(const IplImage* image, unsigned int points_num) = NULL;
int (* drawer)(IplImage* dst, const IplImage* source, const DtTriangles* triangles) = NULL;

const char* file_name = NULL;

unsigned int count = 0;

int recognize_count(const char* name, const char* value) {
	if (!strcmp(name, "--count") ||
		!strcmp(name, "-c")) {
		count = (unsigned int) atoi(value);
		return 1;
	}

	return 0;
}

int recognize_generator(const char* name, const char* value) {
	if (!strcmp(name, "--generator") ||
		!strcmp(name, "-g")) {

		if (!strcmp(value, "random") ||
			!strcmp(value, "rand")) {
			generator = dt_triangles_random;
		}
		if (!strcmp(value, "canny")) {
			generator = dt_triangles_canny;
		}

		return 1;
	}

	return 0;
}

int recognize_drawer(const char* name, const char* value) {
	if (!strcmp(name, "--drawer") ||
		!strcmp(name, "-d")) {

		if (!strcmp(value, "fill")) {
			drawer = dt_draw_filled;
		}
		if (!strcmp(value, "edges")) {
			drawer = dt_draw_edges;
		}
		if (!strcmp(value, "edges_thickness")) {
			drawer = dt_draw_edges_thickness;
		}

		return 1;
	}

	return 0;
}

void recognize_arguments(int argc, const char* argv[]) {
	// default
	generator = dt_triangles_random;
	drawer = dt_draw_filled;
	count = 5000;

	for (int i = 0; i < argc; i += 2) {
		if (recognize_count(argv[i], argv[i + 1])) continue;
		if (recognize_generator(argv[i], argv[i + 1])) continue;
		if (recognize_drawer(argv[i], argv[i + 1])) continue;
		file_name = argv[i--];
	}
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

void testImage() {
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

	if (file_name == NULL){
		testCamera();
	} else {
		testImage();
	}

	return 0;
}