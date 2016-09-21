#include "intersection.h"
#include <iostream>
#include <cassert>

bool is_triangles_intersect(float* vertices1, float* vertices2, int index_v11, int index_v12, int index_v13,
	int index_v21, int index_v22, int index_v23) {
	CGLTriangle t1(vertices1, index_v11, index_v12, index_v13);
	CGLTriangle t2(vertices2, index_v21, index_v22, index_v23);
	assert(!t1.is_degenerate() && !t2.is_degenerate());
	if (!t1.get_box().is_box_intersect(t2.get_box()))
		return false;
	if (!t1.get_plane().is_parallel(t2.get_plane())) {
		CGLVector n2 = t2.get_plane().get_normal();
		CGLVector u(t1.get_point(1), t1.get_point(0)), v(t1.get_point(2), t1.get_point(0));
		CGLVector ap(t2.get_point(0), t1.get_point(0));
		double coef11 = ap.dot(n2) * u.dot(n2) / (u.dot(n2)*u.dot(n2) + v.dot(n2)*v.dot(n2));
		double coef12 = v.dot(n2);
		double coef21 = ap.dot(n2) * v.dot(n2) / (u.dot(n2)*u.dot(n2) + v.dot(n2)*v.dot(n2));
		double coef22 = -u.dot(n2);
		double coef31 = 1 - coef11 - coef21;
		double coef32 = -coef12 - coef22;
		if ((coef12 == 0 && coef11 < 0) || (coef22 == 0 && coef21 < 0) || (coef32 == 0 && coef31 < 0))
			return false;
		if (coef12 > 0 && coef22 > 0 && coef32 > 0) return true;
		if (coef12 < 0 && coef22 < 0 && coef32 < 0) return true;
		double coef1 = -coef11 / coef12;
		double coef2 = -coef21 / coef22;
		double coef3 = -coef31 / coef32;
		if (coef12 > 0 && coef22 > 0 && coef32 < 0)
			if (fmin(coef1, coef2) > coef3) return false;
		if (coef12 > 0 && coef22 < 0 && coef32 > 0)
			if (fmin(coef1, coef3) > coef2) return false;
		if (coef12 < 0 && coef22 > 0 && coef32 > 0)
			if (fmin(coef2, coef3) > coef1) return false;
		if (coef12 > 0 && coef22 < 0 && coef32 < 0)
			if (fmax(coef2, coef3) < coef1) return false;
		if (coef12 < 0 && coef22 > 0 && coef32 < 0)
			if (fmax(coef1, coef3) < coef2) return false;
		if (coef12 < 0 && coef22 < 0 && coef32 > 0)
			if (fmax(coef1, coef2) < coef3) return false;
		return true;
	}
	else {};
	return false;
};

bool triangles_intersection(float* vertices1, float* vertices2, int index_v11, int index_v12, int index_v13,
	int index_v21, int index_v22, int index_v23, Cross_type* cr, Result* r) {
	if (!is_triangles_intersect(vertices1, vertices2, index_v11, index_v12, index_v13,
		index_v21, index_v22, index_v23))
		return false;
	CGLTriangle t1(vertices1, index_v11, index_v12, index_v13);
	CGLTriangle t2(vertices2, index_v21, index_v22, index_v23);
	CGLPlane p = t2.get_plane();
	return false;
};

bool plane_plane_intersection(CGLPlane p1, CGLPlane p2) {
	return false;
};