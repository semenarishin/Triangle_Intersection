#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H
#include "geom_objects.h"

enum Cross_type {no_intersect, v_v_point, v_e_point, e_e_point, f_v_point, 
	e_e_seg, f_e_seg, f_f_seg, polygon };

struct Result {
	float scale;
};

bool triangle_triangle_intersection(float* vertices1, float* vertices2, int vertex11, int vertex12, int vertex13,
	int vertex21, int vertex22, int vertex23, bool is_scale_require, Cross_type* cr, Result* r);

bool plane_plane_intersection(CGLPlane p1, CGLPlane p2);
#endif