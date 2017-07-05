//
// Created by ed on 04.07.17.
//

#ifndef DELAUNAY_TRIANGULATOR_DT_H
#define DELAUNAY_TRIANGULATOR_DT_H

#include <cv.h>
#include <highgui.h>

#include <math.h>

#include "delaunay/delaunay.h"

typedef tri_delaunay2d_t DtTriangles;

/**
 * Generates random points.
 * @param image Pointer to the source image.
 * @param points_num Points number.
 * @return pointer to the DtPoints struct.
 */
DtTriangles* dt_triangles_random(const IplImage* image, unsigned int points_num);

DtTriangles* dt_triangles_canny(const IplImage* image, unsigned int points_num);

void dt_free_triangles(DtTriangles* triangles);

#endif //DELAUNAY_TRIANGULATOR_DT_H
