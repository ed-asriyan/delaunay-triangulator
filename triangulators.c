//
// Created by ed on 07.07.17.
//

#include "triangulators.h"

int triangulate(Arguments arguments, IplImage* dst) {
	DtTriangles* triangles = arguments.generator(arguments.options);
	if (triangles == NULL) {
		printf("Error\n");
		return 1;
	}
	printf("[i] points number:    %5d\n", triangles->num_points);
	printf("[i] triangles number: %5d\n", triangles->num_triangles);
	printf("\n");

	arguments.drawer(dst, arguments.options.image, triangles);
	dt_free_triangles(triangles);

	return 1;
}

void testCamera(Arguments arguments) {
	CvCapture* capture = cvCreateCameraCapture(CV_CAP_ANY);
	assert(capture);

	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 1280);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 960);

	cvNamedWindow("capture", CV_WINDOW_NORMAL);

	printf("[i] press Enter for capture image and Esc for quit!\n\n");

	while (1) {
		IplImage* source = cvQueryFrame(capture);
		arguments.options.image = source;
		IplImage* dst = cvCreateImage(cvSize(source->width, source->height), 8, 3);

		DtTriangles* triangles = arguments.generator(arguments.options);
		if (triangles == NULL) {
			printf("Error\n");
			cvReleaseImage(&source);
			return;
		}
		printf("[i] points number:    %4d\n", triangles->num_points);
		printf("[i] triangles number: %4d\n", triangles->num_triangles);
		printf("\n");

		arguments.drawer(dst, source, triangles);
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

void testImage(Arguments arguments) {
	IplImage* source = cvLoadImage(arguments.file_name, 1);

	filter_gray_scale_r(source);

	cvNamedWindow("original", CV_WINDOW_NORMAL);
	cvShowImage("original", source);
	cvWaitKey(0);

	cvReleaseImage(&source);
	cvDestroyWindow("original");
}

void test(Arguments arguments) {
	switch (arguments.source) {
		case CAMERA:
			testCamera(arguments);
			break;
		case IMAGE:
			testImage(arguments);
			break;
		default:
			fprintf(stderr, "No source\n");
			break;
	}
}
