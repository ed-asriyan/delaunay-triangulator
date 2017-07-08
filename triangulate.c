//
// Created by ed on 07.07.17.
//

#include "triangulate.h"

void triangulate(
	IplImage* image,
	int egde_detect_value,
	double point_rate,
	int points_max_num,
	int blur_size,
	int edge_size,
	int pixel_limit
) {
	filter_gray_scale_r(image);
}
