#include "intersection.h"
#include <cassert>

double eps = 3.55271e-15;

bool is_collinear_seg_intersect(CGLPoint x1, CGLPoint x2, CGLPoint y1, CGLPoint y2) {
	if (x1.getx() > x2.getx()) {
		CGLPoint p = x1;
		x1 = x2;
		x2 = p;
	}
	if (y1.getx() > y2.getx()) {
		CGLPoint p = y1;
		y1 = y2;
		y2 = p;
	}
	if (x1.getx() != x2.getx()) {
		if (x1.getx() > y2.getx())
			return false;
		if (x2.getx() < y1.getx())
			return false;
		if ((x1.getx() <= y1.getx()) && (x2.getx() >= y2.getx()))
			return true;
		if ((x1.getx() < y1.getx()) && (x2.getx() < y2.getx()) && (x2.getx() >= y1.getx()))
			return true;
		if ((x1.getx() > y1.getx()) && (x1.getx() <= y2.getx()) && (x2.getx() > y2.getx()))
			return true;
		if ((x1.getx() > y1.getx()) && (x2.getx() < y2.getx()))
			return true;
	}
	else
		if (x1.gety() != x2.gety()) {
			if (x1.gety() > y2.gety())
				return false;
			if (x2.gety() < y1.gety())
				return false;
			if ((x1.gety() <= y1.gety()) && (x2.gety() >= y2.gety()))
				return true;
			if ((x1.gety() < y1.gety()) && (x2.gety() < y2.gety()) && (x2.gety() >= y1.gety()))
				return true;
			if ((x1.gety() > y1.gety()) && (x1.gety() <= y2.gety()) && (x2.gety() > y2.gety()))
				return true;
			if ((x1.gety() > y1.gety()) && (x2.gety() < y2.gety()))
				return true;
		}
		else {
			if (x1.getz() > y2.getz())
				return false;
			if (x2.getz() < y1.getz())
				return false;
			if ((x1.getz() <= y1.getz()) && (x2.getz() >= y2.getz()))
				return true;
			if ((x1.getz() < y1.getz()) && (x2.getz() < y2.getz()) && (x2.getz() >= y1.getz()))
				return true;
			if ((x1.getz() > y1.getz()) && (x1.getz() <= y2.getz()) && (x2.getz() > y2.getz()))
				return true;
			if ((x1.getz() > y1.getz()) && (x2.getz() < y2.getz()))
				return true;
		}
		return false;
}

bool is_segments_intersect(CGLPoint x1, CGLPoint x2, CGLPoint y1, CGLPoint y2) {
	CGLSegment s1(x1, x2);
	CGLSegment s2(y1, y2);
	if (!s1.get_box().is_box_intersect(s2.get_box()))
		return false;
	CGLVector x(x1, x2);
	CGLVector y(y1, y2);
	CGLVector xy(x1, y1);
	if (x.is_parallel(y)) {
		if (x.is_parallel(xy)) {
			return is_collinear_seg_intersect(x1, x2, y1, y2);
		}
		else
			return false;
	}
	double u = ((x1.getx() - x2.getx())*(y2.gety() - x2.gety()) - (x1.gety() - x2.gety())*(y2.getx() - x2.getx())) / ((x1.gety() - x2.gety())*(y1.getx() - y2.getx()) - (x1.getx() - x2.getx())*(y1.gety() - y2.gety()));
	double v = ((y1.getx() - y2.getx()) * u + y2.getx() - x2.getx()) / (x1.getx() - x2.getx());
	if (((x1.getz() - x2.getz())*v + x2.getz()) == ((y1.getz() - y2.getz())*u + y2.getz()))
		if ((u <= 1.0) && (u >= 0.0) && (v <= 1.0) && (v >= 0.0))
			return true;
	return false;
};

bool collinear_seg_intersect(CGLPoint x1, CGLPoint x2, CGLPoint y1, CGLPoint y2, Result<CGLPoint>* res) {
	if (x1.getx() > x2.getx()) {
		CGLPoint p = x1;
		x1 = x2;
		x2 = p;
	}
	if (y1.getx() > y2.getx()) {
		CGLPoint p = y1;
		y1 = y2;
		y2 = p;
	}
	if (x1.getx() != x2.getx()) {
		if (x1.getx() > y2.getx())
			return false;
		if (x2.getx() < y1.getx())
			return false;
		if ((x1.getx() <= y1.getx()) && (x2.getx() >= y2.getx())) {
			res->add(y1);
			res->add(y2);
			return true;
		}
		if ((x1.getx() < y1.getx()) && (x2.getx() < y2.getx()) && (x2.getx() >= y1.getx())) {
			res->add(y1);
			res->add(x2);
			return true;
		}
		if ((x1.getx() > y1.getx()) && (x1.getx() <= y2.getx()) && (x2.getx() > y2.getx())) {
			res->add(x1);
			res->add(y2);
			return true;
		}
		if ((x1.getx() > y1.getx()) && (x2.getx() < y2.getx())) {
			res->add(x1);
			res->add(x2);
			return true;
		}
	}
	else
		if (x1.gety() != x2.gety()) {
			if (x1.gety() > y2.gety())
				return false;
			if (x2.gety() < y1.gety())
				return false;
			if ((x1.gety() <= y1.gety()) && (x2.gety() >= y2.gety())) {
				res->add(y1);
				res->add(y2);
				return true;
			}
			if ((x1.gety() < y1.gety()) && (x2.gety() < y2.gety()) && (x2.gety() >= y1.gety())) {
				res->add(y1);
				res->add(x2);
				return true;
			}
			if ((x1.gety() > y1.gety()) && (x1.gety() <= y2.gety()) && (x2.gety() > y2.gety())) {
				res->add(x1);
				res->add(y2);
				return true;
			}
			if ((x1.gety() > y1.gety()) && (x2.gety() < y2.gety())) {
				res->add(x1);
				res->add(x2);
				return true;
			}
		}
		else {
			if (x1.getz() > y2.getz())
				return false;
			if (x2.getz() < y1.getz())
				return false;
			if ((x1.getz() <= y1.getz()) && (x2.getz() >= y2.getz())) {
				res->add(y1);
				res->add(y2);
				return true;
			}
			if ((x1.getz() < y1.getz()) && (x2.getz() < y2.getz()) && (x2.getz() >= y1.getz())) {
				res->add(y1);
				res->add(x2);
				return true;
			}
			if ((x1.getz() > y1.getz()) && (x1.getz() <= y2.getz()) && (x2.getz() > y2.getz())) {
				res->add(x1);
				res->add(y2);
				return true;
			}
			if ((x1.getz() > y1.getz()) && (x2.getz() < y2.getz())) {
				res->add(x1);
				res->add(x2);
				return true;
			}
		}
	return false;
}

bool segments_intersect(CGLPoint x1, CGLPoint x2, CGLPoint y1, CGLPoint y2, Result<CGLPoint>* res) {
	CGLSegment s1(x1, x2);
	CGLSegment s2(y1, y2);
	if (!s1.get_box().is_box_intersect(s2.get_box()))
		return false;
	CGLVector x(x1, x2);
	CGLVector y(y1, y2);
	CGLVector xy(x1, y1);
	if (x.is_parallel(y)) {
		if (x.is_parallel(xy)) {
			return collinear_seg_intersect(x1, x2, y1, y2, res);
		}
	}
	double u;
	if ((x1.getx() - x2.getx() != 0) || (x1.gety() - x2.gety() != 0))
		u = ((x1.getx() - x2.getx())*(y2.gety() - x2.gety()) - (x1.gety() - x2.gety())*(y2.getx() - x2.getx())) / ((x1.gety() - x2.gety())*(y1.getx() - y2.getx()) - (x1.getx() - x2.getx())*(y1.gety() - y2.gety()));
	else
		u = ((x1.getx() - x2.getx())*(y2.getz() - x2.getz()) - (x1.getz() - x2.getz())*(y2.getx() - x2.getx())) / ((x1.getz() - x2.getz())*(y1.getx() - y2.getx()) - (x1.getx() - x2.getx())*(y1.getz() - y2.getz()));
	double v;
	if(x1.getx() - x2.getx() != 0)
		v = ((y1.getx() - y2.getx()) * u + y2.getx() - x2.getx()) / (x1.getx() - x2.getx());
	else if (x1.gety() - x2.gety() != 0)
		v = ((y1.gety() - y2.gety()) * u + y2.gety() - x2.gety()) / (x1.gety() - x2.gety());
	else
		v = ((y1.getz() - y2.getz()) * u + y2.getz() - x2.getz()) / (x1.getz() - x2.getz());
	if (((x1.getz() - x2.getz())*v + x2.getz()) == ((y1.getz() - y2.getz())*u + y2.getz()))
		if ((u <= 1.0) && (u >= 0.0) && (v <= 1.0) && (v >= 0.0)) {
			if (fmax(u, v) < eps)
				res->add(CGLPoint(x2.getx(), x2.gety(), x2.getz()));
			else {
				if (abs(u) < abs(v))
					res->add(CGLPoint((x1.getx() - x2.getx())*v + x2.getx(), (x1.gety() - x2.gety())*v + x2.gety(), (x1.getz() - x2.getz())*v + x2.getz()));
				else
					res->add(CGLPoint((y1.getx() - y2.getx())*u + y2.getx(), (y1.gety() - y2.gety())*u + y2.gety(), (y1.getz() - y2.getz())*u + y2.getz()));
			}
			return true;
		}
	return false;
};

bool is_coplanar_tr_intersect(CGLTriangle t1, CGLTriangle t2) {
	CGLOrientation or ;
	CGLPoint *a = &t1.get_point(0);
	CGLPoint *b = &t1.get_point(1);
	CGLPoint *c = &t1.get_point(2);
	CGLPoint *p = &t2.get_point(0);
	CGLPoint *q = &t2.get_point(1);
	CGLPoint *r = &t2.get_point(2);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (is_segments_intersect(t1.get_point(i), t1.get_point(i + 1), t2.get_point(j), t1.get_point(j + 1)))
				return true;
	
	if (or.coplanar_orientation(*a, *b, *p) != NEGATIVE)
		if (or.coplanar_orientation(*b, *c, *p) != NEGATIVE)
			if (or.coplanar_orientation(*c, *a, *p) != NEGATIVE)
				return true;
	if (or.coplanar_orientation(*p, *q, *a) != NEGATIVE)
		if (or.coplanar_orientation(*q, *r, *a) != NEGATIVE)
			if (or.coplanar_orientation(*q, *p, *a) != NEGATIVE)
				return true;
	return false;
};

bool coplanar_tr_intersect(CGLTriangle t1, CGLTriangle t2, Result<CGLPoint>* res) {
	CGLOrientation or ;
	CGLPoint *a = &t1.get_point(0);
	CGLPoint *b = &t1.get_point(1);
	CGLPoint *c = &t1.get_point(2);
	CGLPoint *p = &t2.get_point(0);
	CGLPoint *q = &t2.get_point(1);
	CGLPoint *r = &t2.get_point(2);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			segments_intersect(t1.get_point(i), t1.get_point(i + 1), t2.get_point(j), t2.get_point(j + 1), res);

		if (or .coplanar_orientation(*a, *b, *p) != NEGATIVE)
			if (or .coplanar_orientation(*b, *c, *p) != NEGATIVE)
				if (or .coplanar_orientation(*c, *a, *p) != NEGATIVE)
					res->add(*p);
		if (or .coplanar_orientation(*a, *b, *q) != NEGATIVE)
			if (or .coplanar_orientation(*b, *c, *q) != NEGATIVE)
				if (or .coplanar_orientation(*c, *a, *q) != NEGATIVE)
					res->add(*q);
		if (or .coplanar_orientation(*a, *b, *r) != NEGATIVE)
			if (or .coplanar_orientation(*b, *c, *r) != NEGATIVE)
				if (or .coplanar_orientation(*c, *a, *r) != NEGATIVE)
					res->add(*r);
		if (or .coplanar_orientation(*p, *q, *a) != NEGATIVE)
			if (or .coplanar_orientation(*q, *r, *a) != NEGATIVE)
				if (or .coplanar_orientation(*r, *p, *a) != NEGATIVE)
					res->add(*a);
		if (or .coplanar_orientation(*p, *q, *b) != NEGATIVE)
			if (or .coplanar_orientation(*q, *r, *b) != NEGATIVE)
				if (or .coplanar_orientation(*r, *p, *b) != NEGATIVE)
					res->add(*b);
		if (or .coplanar_orientation(*p, *q, *c) != NEGATIVE)
			if (or .coplanar_orientation(*q, *r, *c) != NEGATIVE)
				if (or .coplanar_orientation(*r, *p, *c) != NEGATIVE)				
					res->add(*c);
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
	CGLOrientation or ;
	CGLPoint A = t1.get_point(0);
	CGLPoint B = t1.get_point(1);
	CGLPoint C = t1.get_point(2);
	CGLPoint P = t2.get_point(0);
	CGLPoint Q = t2.get_point(1);
	CGLPoint R = t2.get_point(2);

	CGLPoint * p = &P;
	CGLPoint * q = &Q;
	CGLPoint * r = &R;
	CGLPoint * a = &A;
	CGLPoint * b = &B;
	CGLPoint * c = &C;
	if (or .coplanar_orientation(P, Q, R) == NEGATIVE) {
		q = &R;
		r = &Q;
	}
	if (or .coplanar_orientation(A, B, C) == NEGATIVE) {
		b = &C;
		c = &B;
	}
	t1 = CGLTriangle(*a, *b, *c);
	t2 = CGLTriangle(*p, *q, *r);
	if (!t1.get_box().is_box_intersect(t2.get_box()))
		return false;
	if (!t1.get_plane().is_parallel(t2.get_plane())) {
		CGLVector n2 = t2.get_plane().get_normal();
		CGLVector u(t1.get_point(0), t1.get_point(1)), v(t1.get_point(0), t1.get_point(2));
		CGLVector ap(t1.get_point(0), t2.get_point(0));
		double coef11 = ap.dot(n2) * u.dot(n2) / (u.dot(n2)*u.dot(n2) + v.dot(n2)*v.dot(n2));
		double coef12 = v.dot(n2);
		double coef21 = ap.dot(n2) * v.dot(n2) / (u.dot(n2)*u.dot(n2) + v.dot(n2)*v.dot(n2));
		double coef22 = -u.dot(n2);
		double coef31 = 1 - coef11 - coef21;
		double coef32 = -coef12 - coef22;
		if ((coef12 == 0 && coef11 < 0) || (coef22 == 0 && coef21 < 0) || (coef32 == 0 && coef31 < 0))
			return false;
		double coef1 = INFINITY;
		double coef2 = INFINITY;
		double coef3 = INFINITY;
		if (coef12 != 0)
			coef1 = -coef11 / coef12;
		else if (coef12 < 0)
			coef1 = -INFINITY;
		if (coef22 != 0)
			coef2 = -coef21 / coef22;
		else if (coef22 < 0)
			coef2 = -INFINITY;
		if (coef32 != 0)
			coef3 = -coef31 / coef32;
		else if (coef32 < 0)
			coef3 = -INFINITY;
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
	else {
		return is_coplanar_tr_intersect(t1, t2);
	};
	return false;
};

bool triangles_intersection(float* vertices1, float* vertices2, int index_v11, int index_v12, int index_v13,
	int index_v21, int index_v22, int index_v23, Result<CGLPoint>* res) {
	/*if (!is_triangles_intersect(vertices1, vertices2, index_v11, index_v12, index_v13,
		index_v21, index_v22, index_v23))
		return false;*/
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
	CGLOrientation or ;
	CGLPoint A = t1.get_point(0);
	CGLPoint B = t1.get_point(1);
	CGLPoint C = t1.get_point(2);
	CGLPoint P = t2.get_point(0);
	CGLPoint Q = t2.get_point(1);
	CGLPoint R = t2.get_point(2);

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
	if (or .coplanar_orientation(A, B, C) == NEGATIVE) {
		b = &C;
		c = &B;
	}
	t1 = CGLTriangle(*a, *b, *c);
	t2 = CGLTriangle(*p, *q, *r);
	if (!t1.get_box().is_box_intersect(t2.get_box()))
		return false;
	if (!t1.get_plane().is_parallel(t2.get_plane())) {
		CGLVector n2 = t2.get_plane().get_normal();
		CGLVector u(t1.get_point(0), t1.get_point(1)), v(t1.get_point(0), t1.get_point(2));
		CGLVector ap(t1.get_point(0), t2.get_point(0));
		double coef11 = ap.dot(n2) * u.dot(n2) / (u.dot(n2)*u.dot(n2) + v.dot(n2)*v.dot(n2));
		double coef12 = v.dot(n2);
		double coef21 = ap.dot(n2) * v.dot(n2) / (u.dot(n2)*u.dot(n2) + v.dot(n2)*v.dot(n2));
		double coef22 = -u.dot(n2);
		double coef31 = 1 - coef11 - coef21;
		double coef32 = -coef12 - coef22;
		double coef1 = INFINITY;
		double coef2 = INFINITY;
		double coef3 = INFINITY;
		if (coef12 != 0)
			coef1 = -coef11 / coef12;
		else if (coef12 < 0)
			coef1 = -INFINITY;
		if (coef22 != 0)
			coef2 = -coef21 / coef22;
		else if (coef22 < 0)
			coef2 = -INFINITY;
		if (coef32 != 0)
			coef3 = -coef31 / coef32;
		else if (coef32 < 0)
			coef3 = -INFINITY;
		double left = -INFINITY;
		double right =  INFINITY;
		if (coef12 > 0 && coef22 > 0 && coef32 < 0)
			if (fmin(coef1, coef2) > coef3) return false;
			else {
				if (fmin(coef1, coef2) == coef3)
					left = right = coef3;
				else {
					left = fmin(coef1, coef2);
					right = coef3;
				}
			}
		if (coef12 > 0 && coef22 < 0 && coef32 > 0)
			if (fmin(coef1, coef3) > coef2) return false;
			else {
				if (fmin(coef1, coef3) == coef2)
					left = right = coef2;
				else {
					left = fmin(coef1, coef3);
					right = coef2;
				}
			}
		if (coef12 < 0 && coef22 > 0 && coef32 > 0)
			if (fmin(coef2, coef3) > coef1) return false;
			else {
				if (fmin(coef2, coef3) == coef1)
					left = right = coef1;
				else {
					left = fmin(coef2, coef3);
					right = coef1;
				}
			}
		if (coef12 > 0 && coef22 < 0 && coef32 < 0)
			if (fmax(coef2, coef3) < coef1) return false;
			else {
				if (fmax(coef2, coef3) == coef1)
					left = right = coef1;
				else {
					left = coef1;
					right = fmax(coef2, coef3);
				}
			}
		if (coef12 < 0 && coef22 > 0 && coef32 < 0)
			if (fmax(coef1, coef3) < coef2) return false;
			else {
				if (fmax(coef1, coef3) == coef2)
					left = right = coef2;
				else {
					left = coef2;
					right = fmax(coef1, coef3);
				}
			}
		if (coef12 < 0 && coef22 < 0 && coef32 > 0)
			if (fmax(coef1, coef2) < coef3) return false;
			else {
				if (fmax(coef1, coef2) == coef3)
					left = right = coef3;
				else {
					left = coef3;
					right = fmax(coef1, coef2);
				}
			}
			CGLPoint A = t1.get_point(0);
			double u1 = coef11 + left*coef12;
			double u2 = coef11 + right*coef12;
			double v1 = coef21 + left*coef22;
			double v2 = coef21 + right*coef22;
			if(left == right)
				res->add(CGLPoint(A.getx() + u1*u.getx() + v1*v.getx(), A.gety() + u1*u.gety() + v1*v.gety(), A.getz() + u1*u.getz() + v1*v.getz()));
			else {
				res->add(CGLPoint(A.getx() + u1*u.getx() + v1*v.getx(), A.gety() + u1*u.gety() + v1*v.gety(), A.getz() + u1*u.getz() + v1*v.getz()));
				res->add(CGLPoint(A.getx() + u2*u.getx() + v2*v.getx(), A.gety() + u2*u.gety() + v2*v.gety(), A.getz() + u2*u.getz() + v2*v.getz()));
			}
			return true;
	}
	else
		return coplanar_tr_intersect(t1, t2, res);
	return false;
};