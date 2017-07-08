//
// Created by ed on 07.07.17.
//

#ifndef DELAUNAY_TRIANGULATOR_TRIANGULATE_H
#define DELAUNAY_TRIANGULATOR_TRIANGULATE_H

#include <cv.h>

#include "filter.h"

void triangulate(
	IplImage* image,
	int egde_detect_value,
	double point_rate,
	int points_max_num,
	int blur_size,
	int edge_size,
	int pixel_limit
);

#endif //DELAUNAY_TRIANGULATOR_TRIANGULATE_H
