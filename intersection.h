#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H
#include "geom_objects.h"

enum Cross_type {no_intersect, v_v_point, v_e_point, e_e_point, f_v_point, 
	e_e_seg, f_e_seg, f_f_seg, polygon };

struct Result {
};

bool is_triangles_intersect(float* vertices1, float* vertices2, int index_v11, int index_v12, int index_v13,
	int index_v21, int index_v22, int index_v23);

bool triangles_intersection(float* vertices1, float* vertices2, int index_v11, int index_v12, int index_v13,
	int index_v21, int index_v22, int index_v23, Cross_type* cr, Result* r);

bool plane_plane_intersection(CGLPlane p1, CGLPlane p2);
#endif