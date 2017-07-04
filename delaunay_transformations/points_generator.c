//
// Created by ed on 04.07.17.
//

#include "points_generator.h"

int dt_generate_random(IplImage* image, del_point2d_t* points, unsigned int points_num) {
	const int width = image->width;
	const int height = image->height;

	for (size_t i = 0; i < points_num; ++i) {
		points[i].x = rand() % width;
		points[i].y = rand() % height;
	}

	return 1;
}
