//
// Created by ed on 04.07.17.
//

#include "dt.h"

int dt_triangulate_random(IplImage* image, unsigned int points_num) {
	del_point2d_t* points = (del_point2d_t*) malloc(points_num * sizeof(del_point2d_t));
	dt_generate_random(image, points, points_num);
	delaunay2d_t* res = delaunay2d_from(points, points_num);
	tri_delaunay2d_t* tdel = tri_delaunay2d_from(res);
	dt_draw_tri(image, tdel);
	tri_delaunay2d_release(tdel);
	delaunay2d_release(res);
	free(points);
}
