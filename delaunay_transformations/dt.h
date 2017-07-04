//
// Created by ed on 04.07.17.
//

#ifndef DELAUNAY_TRIANGULATOR_DT_H
#define DELAUNAY_TRIANGULATOR_DT_H

#include <cv.h>
#include <highgui.h>

#include <math.h>

#include "points_generator.h"
#include "drawer.h"

int dt_triangulate_random(IplImage* image, unsigned int points_num);

int dt_triangulate_canny(IplImage* image, unsigned int points_num);

#endif //DELAUNAY_TRIANGULATOR_DT_H
