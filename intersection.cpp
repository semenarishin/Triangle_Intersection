#include "intersection.h"
//#include <iostream>
#include <cassert>

bool is_segments_intersect(CGLPoint x1, CGLPoint x2, CGLPoint y1, CGLPoint y2) {
	CGLSegment s1(x1, x2);
	CGLSegment s2(y1, y2);
	if (!s1.get_box().is_box_intersect(s2.get_box()))
		return false;
	CGLVector x(x2, x1);
	CGLVector y(y2, y1);
	CGLVector xy(x1, y1);
	if (x.is_parallel(y)) {
		if (x.is_parallel(xy)) {
			if ((x1.x > y1.x) && (x1.x < y2.x) || ((x1.x < y1.x) && (x1.x > y1.x)))
				return true;
			if ((x2.x > y1.x) && (x2.x < y2.x) || ((x2.x < y1.x) && (x2.x > y1.x)))
				return true;
			if ((y1.x > x1.x) && (y1.x < x2.x) || ((y1.x < x1.x) && (y1.x > x2.x)))
				return true;
			if ((y2.x > x1.x) && (y2.x < x2.x) || ((y2.x < x1.x) && (y2.x > x2.x)))
				return true;
		}
		else
			return false;
	}
	else
		return false;
	double u = ((x1.x - x2.x)*(y2.y - x2.y) - (x1.y - x2.y)*(y2.x - x2.x)) / ((x1.y - x2.y)*(y1.x - y2.x) - (x1.x - x2.x)*(y1.y - y2.y));
	double v = ((y1.x - y2.x) / u + y2.x - x2.x) / (x1.x - x2.x);
	if (((x1.z - x2.z)*v + x2.z) == ((y1.z - y2.z)*u + y2.z))
		if (abs(u) <= 1.0 && abs(v) <= 1.0)
			return true;
	return false;
};

bool is_coplanar_tr_intersect(CGLTriangle &t1, CGLTriangle &t2) {
	for (int i = 1; i < 4; i++)
		for (int j = 1; j < 4; j++)
			if (is_segments_intersect(t1.get_point(i), t1.get_point(i + 1), t2.get_point(j), t1.get_point(j + 1)))
				return true;
	CGLOrientation or;
	CGLPoint A = t1.get_point(1);
	CGLPoint B = t1.get_point(2);
	CGLPoint C = t1.get_point(3);
	CGLPoint P = t2.get_point(1);
	CGLPoint Q = t2.get_point(2);
	CGLPoint R = t2.get_point(3);

	CGLPoint * p = &P;
	CGLPoint * q = &Q;
	CGLPoint * r = &R;
	CGLPoint * a = &A;
	CGLPoint * b = &B;
	CGLPoint * c = &C;
	if (or.coplanar_orientation(P, Q, R) == NEGATIVE) {
		q = &R;
		r = &Q;
	}
	if (or.coplanar_orientation(A, B, C) == NEGATIVE) {
		b = &C;
		c = &B;
	}
	if (or.coplanar_orientation(*a, *b, *p) != NEGATIVE)
		if (or.coplanar_orientation(*b, *c, *p) != NEGATIVE)
			if (or.coplanar_orientation(*c, *a, *p) != NEGATIVE)
				return true;
	if (or .coplanar_orientation(*p, *q, *a) != NEGATIVE)
		if (or .coplanar_orientation(*q, *r, *a) != NEGATIVE)
			if (or .coplanar_orientation(*q, *p, *a) != NEGATIVE)
				return true;
	return false;
};

bool is_triangles_intersect(float* vertices1, float* vertices2, int index_v11, int index_v12, int index_v13,
	int index_v21, int index_v22, int index_v23) {
	CGLTriangle t1(vertices1, index_v11, index_v12, index_v13);
	CGLTriangle t2(vertices2, index_v21, index_v22, index_v23);
	if (t1.is_degenerate()) {
		std::cout << "Triangle with indexes " << index_v11 << " " << index_v12 << " " << index_v13 << " is_degenerate\n";
		return false;
	}
	if (t2.is_degenerate()) {
		std::cout << "Triangle with indexes " << index_v21 << " " << index_v22 << " " << index_v23 << " is_degenerate\n";
		return false;
	}
	if (!t1.get_box().is_box_intersect(t2.get_box()))
		return false;
	if (!t1.get_plane().is_parallel(t2.get_plane())) {
		CGLVector n2 = t2.get_plane().get_normal();
		CGLVector u(t1.get_point(2), t1.get_point(1)), v(t1.get_point(3), t1.get_point(1));
		CGLVector ap(t2.get_point(1), t1.get_point(1));
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