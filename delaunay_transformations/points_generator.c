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

int dt_generate_random(IplImage* image, del_point2d_t* points, unsigned int points_num) {
	const int width = image->width;
	const int height = image->height;

	for (size_t i = 0; i < points_num; ++i) {
		points[i].x = rand() % width;
		points[i].y = rand() % height;
	}

	return 1;
}

int dt_generate_points_canny(IplImage* image, del_point2d_t* points, unsigned int points_num) {
	const int width = image->width;
	const int height = image->height;

	IplImage* gray = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	IplImage* dst = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);

	// преобразуем в градации серого
	cvCvtColor(image, gray, CV_RGB2GRAY);

	// получаем границы
	cvCanny(gray, dst, 5, 10, 3);

	unsigned int count = 0;
	char* const dst_data = dst->imageData;
	const int dst_step = dst->widthStep;
	for (int y = 0; y < height; ++y) {
		uchar* ptr = (uchar*) (dst_data + y * dst_step);
		for (int x = 0; x < dst->width; ++x) {
			uchar blue = ptr[3 * x];
			uchar green = ptr[3 * x + 1];
			uchar red = ptr[3 * x + 2];

			count += CANNY_CHECK_COLOR(red, green, blue);
		}
	}

	del_point2d_t* p = (del_point2d_t*) malloc(count * sizeof(del_point2d_t));

	unsigned int i = 0;
	for (int y = 0; y < height; ++y) {
		uchar* ptr = (uchar*) (dst_data + y * dst_step);
		for (int x = 0; x < width; ++x) {
			uchar blue = ptr[3 * x];
			uchar green = ptr[3 * x + 1];
			uchar red = ptr[3 * x + 2];

			if (CANNY_CHECK_COLOR(red, green, blue)) {
				p[i].x = x;
				p[i].y = y;
				if (i == count)break;
				++i;
			}
		}
	}

	shuffle(p, count);

	memcpy(points, p, points_num * sizeof(del_point2d_t));

	free(p);
	cvReleaseImage(&dst);
	cvReleaseImage(&gray);

	return 1;
}
