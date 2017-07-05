//
// Created by ed on 04.07.17.
//

#include "points_generator.h"

#define CANNY_CHECK_COLOR(r, g, b) ((r) > 250 && (b) > 250 && (g) > 250)

void shuffle(del_point2d_t* array, size_t n) {
	if (n > 1) {
		size_t i;
		for (i = 0; i < n - 1; i++) {
			size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
			del_point2d_t t = array[j];
			array[j] = array[i];
			array[i] = t;
		}
	}
}

unsigned int dt_generate_random(IplImage* image, del_point2d_t* points, unsigned int points_num) {
	const int width = image->width;
	const int height = image->height;

	for (size_t i = 0; i < points_num; ++i) {
		points[i].x = rand() % width;
		points[i].y = rand() % height;
	}

	return points_num;
}

unsigned int dt_generate_points_canny(IplImage* image, del_point2d_t* points, unsigned int points_num) {
	const int width = image->width;
	const int height = image->height;

	IplImage* gray = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	cvCvtColor(image, gray, CV_RGB2GRAY);

	IplImage* dst = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	cvCanny(image, dst, 10, 10, 3);
	cvReleaseImage(&gray);

	unsigned int count = 0;
	char* const dst_data = dst->imageData;
	const int dst_step = dst->widthStep;
	for (int y = 0; y < height; y += 3) {
		uchar* ptr = (uchar*) (dst_data + y * dst_step);
		for (int x = 0; x < dst->width; x += 3) {
			uchar blue = ptr[3 * x];
			uchar green = ptr[3 * x + 1];
			uchar red = ptr[3 * x + 2];

			count += CANNY_CHECK_COLOR(red, green, blue);
		}
	}

	del_point2d_t* p = (del_point2d_t*) malloc(count * sizeof(del_point2d_t));

	unsigned int i = 0;
	for (int y = 0; y < height; y += 3) {
		uchar* ptr = (uchar*) (dst_data + y * dst_step);
		for (int x = 0; x < width; x += 3) {
			uchar blue = ptr[3 * x];
			uchar green = ptr[3 * x + 1];
			uchar red = ptr[3 * x + 2];

			if (CANNY_CHECK_COLOR(red, green, blue)) {
				p[i].x = x;
				p[i].y = y;
				if (i == count) {
					break;
				}
				++i;
			}
		}
	}
	if (count < points_num) {
		points_num = count;
	} else {
		shuffle(p, count);
	}

	memcpy(points, p, points_num * sizeof(del_point2d_t));

	free(p);
	cvReleaseImage(&dst);

	return points_num;
}
