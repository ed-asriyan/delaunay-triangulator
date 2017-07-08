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

#define ARG_DEFAULT_EDGE_DETECT_VALUE 80
#define ARG_DEFAULT_POINT_RATE 0.075
#define ARG_DEFAULT_POINTS_MAX_NUM 5000
#define ARG_DEFAULT_BLUR_SIZE 2
#define ARG_DEFAULT_EDGE_SIZE 6
#define ARG_DEFAULT_PIXEL_LIMIT 8000000

int egde_detect_value = ARG_DEFAULT_EDGE_DETECT_VALUE;

double point_rate = ARG_DEFAULT_POINT_RATE;

int points_max_num = ARG_DEFAULT_POINTS_MAX_NUM;

int blur_size = ARG_DEFAULT_BLUR_SIZE;

int edge_size = ARG_DEFAULT_EDGE_SIZE;

int pixel_limit = ARG_DEFAULT_PIXEL_LIMIT;

static const char* const usage[] = {
	"delaunay_triangulator [options] [[--] args]",
	"delaunay_triangulator [options]",
	NULL,
};

int main(int argc, const char* argv[]) {
	srand((unsigned int) time(NULL));

	const char* source = NULL;

	struct argparse_option options[] = {
		OPT_HELP(),
		OPT_GROUP("Required options"),
		OPT_STRING('s', "source", &source, "file path"),

		OPT_GROUP("Expanding options"),
		OPT_INTEGER('d', "detect", &egde_detect_value, "edge detect; default: "
			STRINGIZE(ARG_DEFAULT_EDGE_DETECT_VALUE)),
		OPT_INTEGER('c', "count", &points_max_num, "point max num; default: "
			STRINGIZE(ARG_DEFAULT_POINTS_MAX_NUM)),
		OPT_INTEGER('b', "blur", &blur_size, "blur size; default: "
			STRINGIZE(ARG_DEFAULT_BLUR_SIZE)),
		OPT_INTEGER('e', "edge", &blur_size, "edge size; default: "
			STRINGIZE(ARG_DEFAULT_EDGE_SIZE)),
		OPT_INTEGER('p', "pixel", &blur_size, "pixel limit; default: "
			STRINGIZE(ARG_DEFAULT_PIXEL_LIMIT)),

		OPT_END(),
	};

	struct argparse argparse;
	argparse_init(&argparse, options, usage, 0);
	argc = argparse_parse(&argparse, argc, argv);

	if (source == NULL) {
		fprintf(stderr, "source is not set. Type\n\tdelaunay_triangulator --help\nfor more details.\n");
		return -1;
	}

	return 0;
}
