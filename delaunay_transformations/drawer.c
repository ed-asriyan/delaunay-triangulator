//
// Created by ed on 04.07.17.
//

#include "drawer.h"
#include "delaunay/delaunay.h"

CvScalar calc_average_color(IplImage* image, CvPoint triangle[3]) {
	const int width_step = image->widthStep;
	char* const image_data = image->imageData;

	uchar* p[3] = {
		(uchar*) (image_data + triangle[0].y * width_step),
		(uchar*) (image_data + triangle[1].y * width_step),
		(uchar*) (image_data + triangle[2].y * width_step),
	};

	uchar blue[3] = {
		p[0][3 * triangle[0].x],
		p[1][3 * triangle[0].x],
		p[2][3 * triangle[0].x],
	};
	uchar green[3] = {
		p[0][3 * triangle[0].x + 1],
		p[1][3 * triangle[0].x + 1],
		p[2][3 * triangle[0].x + 1],
	};
	uchar red[3] = {
		p[0][3 * triangle[0].x + 2],
		p[1][3 * triangle[0].x + 2],
		p[2][3 * triangle[0].x + 2],
	};

	CvScalar point = {
		blue[0] / 3 + blue[1] / 3 + blue[2] / 3,
		green[0] / 3 + green[1] / 3 + green[2] / 3,
		red[0] / 3 + red[1] / 3 + red[2] / 3,
	};
	return point;
}

int dt_draw_tri(IplImage* image, tri_delaunay2d_t* tdel) {
	IplImage* copy = cvCloneImage(image);

	for (unsigned int i = 0; i < tdel->num_triangles; i++) {
		CvPoint rook_points[3];
		CvPoint* p = rook_points;
		for (int j = 0; j < 3; j++) {
			int p0 = tdel->tris[i * 3 + j];

			rook_points[j].x = (int) tdel->points[p0].x;
			rook_points[j].y = (int) tdel->points[p0].y;
		}

		const int npt[] = {3};
		CvScalar color = calc_average_color(copy, rook_points);
		cvFillPoly(image, &p, npt, 1, color, 8, 0);
	}
	cvReleaseImage(&copy);

	return 1;
}
