//
// Created by ed on 04.07.17.
//

#include "triangulator.h"

#define MIN_RADIUS 3
#define CANNY_CHECK_COLOR(r, g, b) ((r) > 250 && (b) > 250 && (g) > 250)

DtTriangles* dt_triangulate(del_point2d_t* points, unsigned int points_num) {
	delaunay2d_t* res = delaunay2d_from(points, points_num);
	tri_delaunay2d_t* tdel = tri_delaunay2d_from(res);
	delaunay2d_release(res);
	return tdel;
}

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

DtTriangles* dt_triangles_random(const IplImage* image, unsigned int points_num) {
	const int width = image->width;
	const int height = image->height;

	const int x_width = width / MIN_RADIUS;
	const int y_height = height / MIN_RADIUS;
	const unsigned int count = (const unsigned int) (x_width * y_height);

	del_point2d_t* all = (del_point2d_t*) malloc(count * sizeof(del_point2d_t));
	for (int y = 0; y < y_height; ++y) {
		for (int x = 0; x < x_width; ++x) {
			all[y * x_width + x].x = MIN_RADIUS * x;
			all[y * x_width + x].y = MIN_RADIUS * y;
		}
	}

	if (count < points_num) {
		points_num = count;
	} else {
		shuffle(all, count);
	}

	del_point2d_t* points = (del_point2d_t*) malloc(points_num * sizeof(del_point2d_t));
	memcpy(points, all, points_num * sizeof(del_point2d_t));
	free(all);

	return dt_triangulate(points, points_num);
}

DtTriangles* dt_triangles_canny(const IplImage* image, unsigned int points_num) {
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
	for (int y = 0; y < height; y += MIN_RADIUS) {
		uchar* ptr = (uchar*) (dst_data + y * dst_step);
		for (int x = 0; x < width; x += MIN_RADIUS) {
			uchar blue = ptr[3 * x];
			uchar green = ptr[3 * x + 1];
			uchar red = ptr[3 * x + 2];

			count += CANNY_CHECK_COLOR(red, green, blue);
		}
	}

	if (count < 3) {
		cvReleaseImage(&dst);
		return NULL;
	}

	del_point2d_t* p = (del_point2d_t*) malloc(count * sizeof(del_point2d_t));

	unsigned int i = 0;
	for (int y = 0; y < height; y += MIN_RADIUS) {
		uchar* ptr = (uchar*) (dst_data + y * dst_step);
		for (int x = 0; x < width; x += MIN_RADIUS) {
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

	del_point2d_t* points = (del_point2d_t*) malloc(points_num * sizeof(del_point2d_t));
	memcpy(points, p, points_num * sizeof(del_point2d_t));

	free(p);
	cvReleaseImage(&dst);

	DtTriangles* result = dt_triangulate(points, points_num);
	return result;
}

void dt_free_triangles(DtTriangles* triangles) {
	tri_delaunay2d_release(triangles);
}
