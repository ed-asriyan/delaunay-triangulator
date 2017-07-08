//
// Created by ed on 08.07.17.
//

#include "filter.h"

#define MIN2(a, b) ((a) < (b) ? (a) : (b))
#define MIN3(a, b, c) (MIN2((a), (b)), (c))

#define MAX2(a, b) ((a) > (b) ? (a) : (b))
#define MAX3(a, b, c) (MAX2((a), (b)), (c))

void filter_gray_scale_r(IplImage* image) {
	const int width = image->width;
	const int height = image->height;
	const int width_step = image->widthStep;
	char* const data = image->imageData;

	for (int i = 0; i < height; ++i) {
		char* ptr = data + (i * width_step);
		for (int j = 0; j < width; ++j) {
			char r = ptr[j * 3];
			char g = ptr[j * 3 + 1];
			char b = ptr[j * 3 + 2];

			ptr[j * 3] = (MAX3(r, g, b) >> 2) + (MIN3(r, g, b) >> 2);
		}
	}
}
