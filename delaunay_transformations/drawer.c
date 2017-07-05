//
// Created by ed on 04.07.17.
//

#include "drawer.h"
#include "delaunay/delaunay.h"
#include "triangulator.h"

CvScalar calc_triangle_color(const IplImage* image, const CvPoint triangle[3]) {
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

CvScalar calc_line_color(const IplImage* image, CvPoint a, CvPoint b) {
	const int width_step = image->widthStep;
	char* const image_data = image->imageData;

	uchar* p[2] = {
		(uchar*) (image_data + a.y * width_step),
		(uchar*) (image_data + b.y * width_step),
	};

	uchar blue[2] = {
		p[0][3 * a.x],
		p[1][3 * b.x],
	};
	uchar green[2] = {
		p[0][3 * a.x + 1],
		p[1][3 * b.x + 1],
	};
	uchar red[2] = {
		p[0][3 * a.x + 2],
		p[1][3 * b.x + 2],
	};

	CvScalar point = {
		blue[0] / 2 + blue[1] / 2,
		green[0] / 2 + green[1] / 2,
		red[0] / 2 + red[1] / 2,
	};
	return point;
}

double calc_perimeter(const CvPoint triangle[3]) {
	const double a = (triangle[0].x - triangle[1].x) * (triangle[0].x - triangle[1].x) +
		(triangle[0].y - triangle[1].y) * (triangle[0].y - triangle[1].y);
	const double b = (triangle[2].x - triangle[1].x) * (triangle[2].x - triangle[1].x) +
		(triangle[2].y - triangle[1].y) * (triangle[2].y - triangle[1].y);
	const double c = (triangle[2].x - triangle[0].x) * (triangle[2].x - triangle[0].x) +
		(triangle[2].y - triangle[0].y) * (triangle[2].y - triangle[0].y);
	return a + b + c;
}

int dt_draw_edges(IplImage* dst, const IplImage* source, const DtTriangles* triangles) {
	for (unsigned int i = 0; i < triangles->num_triangles; i++) {
		CvPoint rook_points[3];
		CvPoint* p = rook_points;
		for (int j = 0; j < 3; j++) {
			int p0 = triangles->tris[i * 3 + j];

			rook_points[j].x = (int) triangles->points[p0].x;
			rook_points[j].y = (int) triangles->points[p0].y;
		}

		const int npt[] = {3};
		CvScalar color = {0, 0, 0, 1};
		cvFillPoly(dst, &p, npt, 1, color, 8, 0);

		cvLine(dst,
		       rook_points[0],
		       rook_points[1],
		       calc_line_color(source, rook_points[0], rook_points[1]),
		       1,
		       8,
		       0);
		cvLine(dst,
		       rook_points[0],
		       rook_points[2],
		       calc_line_color(source, rook_points[0], rook_points[2]),
		       1,
		       8,
		       0);
		cvLine(dst,
		       rook_points[2],
		       rook_points[1],
		       calc_line_color(source, rook_points[2], rook_points[1]),
		       1,
		       8,
		       0);
	}

	return 1;
}

int dt_draw_filled(IplImage* dst, const IplImage* source, const DtTriangles* triangles) {
	for (unsigned int i = 0; i < triangles->num_triangles; i++) {
		CvPoint rook_points[3];
		CvPoint* p = rook_points;
		for (int j = 0; j < 3; j++) {
			int p0 = triangles->tris[i * 3 + j];

			rook_points[j].x = (int) triangles->points[p0].x;
			rook_points[j].y = (int) triangles->points[p0].y;
		}

		const int npt[] = {3};
		CvScalar color = calc_triangle_color(source, rook_points);
		cvFillPoly(dst, &p, npt, 1, color, 8, 0);
	}

	return 1;
}

int dt_draw_edges_thickness(IplImage* dst, const IplImage* source, const DtTriangles* triangles) {
	for (unsigned int i = 0; i < triangles->num_triangles; i++) {
		CvPoint rook_points[3];
		CvPoint* p = rook_points;
		for (int j = 0; j < 3; j++) {
			int p0 = triangles->tris[i * 3 + j];

			rook_points[j].x = (int) triangles->points[p0].x;
			rook_points[j].y = (int) triangles->points[p0].y;
		}

		const int npt[] = {3};
		CvScalar color = {0, 0, 0, 1};
		cvFillPoly(dst, &p, npt, 1, color, 8, 0);

		const int thickness = ((const int) (calc_perimeter(rook_points) / 2000)) % 15 + 1;

		cvLine(dst,
		       rook_points[0],
		       rook_points[1],
		       calc_line_color(source, rook_points[0], rook_points[1]),
		       thickness,
		       8,
		       0);
		cvLine(dst,
		       rook_points[0],
		       rook_points[2],
		       calc_line_color(source, rook_points[0], rook_points[2]),
		       thickness,
		       8,
		       0);
		cvLine(dst,
		       rook_points[2],
		       rook_points[1],
		       calc_line_color(source, rook_points[2], rook_points[1]),
		       thickness,
		       8,
		       0);
	}

	return 1;
}
