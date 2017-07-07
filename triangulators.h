//
// Created by ed on 07.07.17.
//

#ifndef DELAUNAY_TRIANGULATOR_TRIANGULATORS_H
#define DELAUNAY_TRIANGULATOR_TRIANGULATORS_H

#include <stdio.h>

#include <cv.h>

#include "delaunay_transformations/drawer.h"
#include "delaunay_transformations/triangulator.h"

enum Source {
	IMAGE,
	CAMERA
} source;

typedef struct Arguments {
	const char* file_name;
	DtTrianglesOptions options;
	enum Source source;

	DtTriangles* (* generator)(DtTrianglesOptions);
	int (* drawer)(IplImage* dst, const IplImage* source, const DtTriangles* triangles);
} Arguments;

void test(Arguments arguments);

#endif //DELAUNAY_TRIANGULATOR_TRIANGULATORS_H
