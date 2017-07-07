//
// Created by ed on 04.07.17.
//

#include <cv.h>
#include <time.h>

#include "argparse/argparse/argparse.h"

#include "delaunay_transformations/triangulator.h"
#include "delaunay_transformations/drawer.h"

#include "triangulators.h"

#define STRINGIZE_DETAIL(v) #v
#define STRINGIZE(v) STRINGIZE_DETAIL(v)

#define ARG_DEFAULT_SOURCE "camera"
#define ARG_DEFAULT_POINTS_NUM 5000
#define ARG_DEFAULT_GENERATOR "rand"

#define ARG_DEFAULT_DRAWER "filled"

#define ARG_DEFAULT_GEN_CANNY_TH1 10

#define ARG_DEFAULT_GEN_CANNY_TH2 50

#define ARG_DEFAULT_GEN_EDGE_E 8

static const char* const usage[] = {
	"delaunay_triangulator [options] [[--] args]",
	"delaunay_triangulator [options]",
	NULL,
};

int main(int argc, const char* argv[]) {
	srand((unsigned int) time(NULL));

	const char* source = ARG_DEFAULT_SOURCE;
	int points_num = ARG_DEFAULT_POINTS_NUM;
	const char* generator = ARG_DEFAULT_GENERATOR;
	const char* drawer = ARG_DEFAULT_DRAWER;

	int canny_threshold1 = ARG_DEFAULT_GEN_CANNY_TH1;
	int canny_threshold2 = ARG_DEFAULT_GEN_CANNY_TH2;

	int edge_value = ARG_DEFAULT_GEN_EDGE_E;

	struct argparse_option options[] = {
		OPT_HELP(),
		OPT_GROUP("Basic options"),
		OPT_STRING('s', "source", &source, "[ camera ] or file path; default: "
			STRINGIZE(ARG_DEFAULT_SOURCE)),
		OPT_INTEGER('c', "count", &points_num, "points number; default: "
			STRINGIZE(ARG_DEFAULT_POINTS_NUM)),
		OPT_STRING('g', "generator", &generator, "[ rand, canny, edges ] points generator; default: "
			STRINGIZE(ARG_DEFAULT_GENERATOR)),
		OPT_STRING('d', "drawer", &generator, "[ filled, edges, edges_thick ] drawer method; default: "
			STRINGIZE(ARG_DEFAULT_DRAWER)),

		OPT_GROUP("Generator canny options"),
		OPT_INTEGER(NULL, "th1", &canny_threshold1, "threshold1; default: "
			STRINGIZE(ARG_DEFAULT_GEN_CANNY_TH1)),
		OPT_INTEGER(NULL, "th2", &canny_threshold2, "threshold2; default: "
			STRINGIZE(ARG_DEFAULT_GEN_CANNY_TH2)),

		OPT_GROUP("Generator edges options"),
		OPT_INTEGER(NULL, "edge_value", &edge_value, "edge detect value; default: "
			STRINGIZE(ARG_DEFAULT_GEN_EDGE_E)),

		OPT_END(),
	};

	struct argparse argparse;
	argparse_init(&argparse, options, usage, 0);
	argc = argparse_parse(&argparse, argc, argv);


	Arguments arguments;

	arguments.source =  CAMERA;
	if (strcmp("camera", source) != 0){
		arguments.source = IMAGE;
	}

	if (!strcmp("rand", generator)){
		arguments.generator = dt_triangles_random;
	} else if (!strcmp("canny", generator)) {
		arguments.generator = dt_triangles_canny;
		arguments.options.canny.threshold1 = canny_threshold1;
		arguments.options.canny.threshold2 = canny_threshold2;
	} else if (!strcmp("edges", generator)) {
		arguments.generator = dt_triangles_edges;
		arguments.options.edges.e = edge_value;
	} else {
		fprintf(stderr, "unknown generator\n");
	}

	if (!strcmp("filled", drawer)){
		arguments.drawer = dt_draw_filled;
	} else if (!strcmp("edges", drawer)) {
		arguments.drawer = dt_draw_edges;
	} else if (!strcmp("edges_thick", drawer)) {
		arguments.drawer = dt_draw_edges_thickness;
	} else {
		fprintf(stderr, "unknown drawer\n");
	}

	arguments.options.points_num = (unsigned int) points_num;
	arguments.file_name = source;

	test(arguments);


	return 0;
}