//
// Created by ed on 04.07.17.
//

#ifndef DELAUNAY_TRIANGULATOR_POINTS_GENERATOR_H
#define DELAUNAY_TRIANGULATOR_POINTS_GENERATOR_H

#include <stdlib.h>

#include <cv.h>

#include "delaunay/delaunay.h"

/**
 * Generates random .oints
 * @param image Pointer to the source image.
 * @param points Output array.
 * @param points_num Points number.
 * @return 1 if success; otherwise 0.
 */
int dt_generate_random(IplImage* image, del_point2d_t* points, unsigned int points_num);

int dt_generate_points_canny(IplImage* image, del_point2d_t* points, unsigned int points_num);

#endif //DELAUNAY_TRIANGULATOR_POINTS_GENERATOR_H
