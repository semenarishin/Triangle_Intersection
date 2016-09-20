#include "intersection.h"
#include <iostream>
#include <cassert>

bool triangle_triangle_intersection(float* vertices1, float* vertices2, int vertex11, int vertex12, int vertex13,
	int vertex21, int vertex22, int vertex23, bool is_scale_require, Cross_type* cr, Result* r) {
	CGLTriangle t1(vertices1, vertex11, vertex12, vertex13);
	CGLTriangle t2(vertices2, vertex21, vertex22, vertex23);
	assert(!t1.is_degenerate() && !t2.is_degenerate());
	CGLPlane p = t2.getPlane();
	return false;
};

bool plane_plane_intersection(CGLPlane p1, CGLPlane p2) {

};