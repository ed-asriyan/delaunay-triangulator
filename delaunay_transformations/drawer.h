//
// Created by ed on 04.07.17.
//

#ifndef DELAUNAY_TRIANGULATOR_TRAINGULATOR_H
#define DELAUNAY_TRIANGULATOR_TRAINGULATOR_H

#include <cv.h>

#include "delaunay/delaunay.h"
#include "triangulator.h"

int dt_draw_edges(IplImage* dst, const IplImage* source, const DtTriangles* triangles);

int dt_draw_edges_thickness(IplImage* dst, const IplImage* source, const DtTriangles* triangles);

int dt_draw_filled(IplImage* dst, const IplImage* source, const DtTriangles* triangles);

#endif //DELAUNAY_TRIANGULATOR_TRAINGULATOR_H
