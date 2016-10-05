#include "intersection.h"
#include <cassert>


	bool CGLIntersection::is_triangles_intersect(float* vertices1, float* vertices2, int index_v11, int index_v12, int index_v13,
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
		Result<CGLPoint>* res = &Result<CGLPoint>();
		if (!t1.get_box().is_box_intersect(t2.get_box()))
			return false;
		if (!t1.get_plane().is_parallel(t2.get_plane(), eps)) {
			CGLSegment seg1;
			if (!out_of_plane_trs_intersect(t1, t2, &seg1, res))
				return false;
			CGLSegment seg2;
			if (!out_of_plane_trs_intersect(t2, t1, &seg2, res))
				return false;
			return is_collinear_seg_intersect(seg1.getpoint0(), seg1.getpoint1(), seg2.getpoint0(), seg2.getpoint1());
		}
		else {
			CGLPlane p1 = t1.get_plane();
			CGLPlane p2 = CGLPlane();
			if (!((t1.get_point(0) != t2.get_point(0)) && (t1.get_point(1) != t2.get_point(1)) && (t1.get_point(2) != t2.get_point(2))))
				return coplanar_tr_intersect(t1, t2, res);
			else
				p2 = CGLPlane(t1.get_point(0), t2.get_point(0), t1.get_point(1));
			if (p1.is_parallel(p2, eps))
				return is_coplanar_tr_intersect(t1, t2);
			else
				return false;
			if (p1.is_parallel(p2, eps))
				return is_coplanar_tr_intersect(t1, t2);
			else
				return false;
		}
		return false;
	};

	bool CGLIntersection::triangles_intersection(float* vertices1, float* vertices2, int index_v11, int index_v12, int index_v13,
		int index_v21, int index_v22, int index_v23, Result<CGLPoint>* res) {
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
		if (!t1.get_plane().is_parallel(t2.get_plane(), eps)) {
			CGLSegment seg1;
			if (!out_of_plane_trs_intersect(t1, t2, &seg1, res))
				return false;
			CGLSegment seg2;
			if (!out_of_plane_trs_intersect(t2, t1, &seg2, res))
				return false;
			return collinear_seg_intersect(seg1.getpoint0(), seg1.getpoint1(), seg2.getpoint0(), seg2.getpoint1(), res);
		}
		else {
			CGLPlane p1 = t1.get_plane();
			CGLPlane p2 = CGLPlane();
			if (!((t1.get_point(0) != t2.get_point(0)) && (t1.get_point(1) != t2.get_point(1)) && (t1.get_point(2) != t2.get_point(2))))
				return coplanar_tr_intersect(t1, t2, res);
			else
				p2 = CGLPlane(t1.get_point(0), t2.get_point(0), t1.get_point(1));
			if (p1.is_parallel(p2, eps))
				return coplanar_tr_intersect(t1, t2, res);
			else
				return false;
		}
		return false;
	};

	bool CGLIntersection::is_collinear_seg_intersect(CGLPoint x1, CGLPoint x2, CGLPoint y1, CGLPoint y2) {
		if (x1 != x2) {
			if (x1.getx() != x2.getx()) {
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
				if (x1.getx() > y2.getx())
					return false;
				if (x2.getx() < y1.getx())
					return false;
				if ((x1.getx() <= y1.getx()) && (x2.getx() >= y2.getx()))
					return true;
				if ((x1.getx() <= y1.getx()) && (x2.getx() < y2.getx()) && (x2.getx() >= y1.getx()))
					return true;
				if ((x1.getx() > y1.getx()) && (x1.getx() <= y2.getx()) && (x2.getx() > y2.getx()))
					return true;
				if ((x1.getx() > y1.getx()) && (x2.getx() < y2.getx()))
					return true;
			}
			else
				if (x1.gety() != x2.gety()) {
					if (x1.gety() > x2.gety()) {
						CGLPoint p = x1;
						x1 = x2;
						x2 = p;
					}
					if (y1.gety() > y2.gety()) {
						CGLPoint p = y1;
						y1 = y2;
						y2 = p;
					}
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
					if ((x1.gety() > y1.gety()) && (x2.gety() < y2.gety())) {
						return true;
					}
				}
				else {
					if (x1.getz() > x2.getz()) {
						CGLPoint p = x1;
						x1 = x2;
						x2 = p;
					}
					if (y1.getz() > y2.getz()) {
						CGLPoint p = y1;
						y1 = y2;
						y2 = p;
					}
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
		}
		else if (y1 != y2) {
			if (y1.getx() != y2.getx()) {
				if (y1.getx() > y2.getx()) {
					CGLPoint p = y1;
					y1 = y2;
					y2 = p;
				}
				if (x1.getx() <= y2.getx() && x1.getx() >= y1.getx())
					return true;
			}
			else if (y1.gety() != y2.gety()) {
				if (y1.gety() > y2.gety()) {
					CGLPoint p = y1;
					y1 = y2;
					y2 = p;
				}
				if (x1.gety() <= y2.gety() && x1.gety() >= y1.gety())
					return true;
			}
			else {
				if (y1.getz() > y2.getz()) {
					CGLPoint p = y1;
					y1 = y2;
					y2 = p;
				}
				if (x1.getz() <= y2.getz() && x1.getz() >= y1.getz())
					return true;
			}

		}
		else if (x1 != y1)
			return false;
		else {
			return true;
		}
		return false;
	}

	bool CGLIntersection::is_segments_intersect(CGLPoint x1, CGLPoint x2, CGLPoint y1, CGLPoint y2) {
		CGLSegment s1(x1, x2);
		CGLSegment s2(y1, y2);
		if (!s1.get_box().is_box_intersect(s2.get_box()))
			return false;
		CGLVector x(x1, x2);
		CGLVector y(y1, y2);
		CGLVector xy(x1, y1);
		if (x.is_parallel(y, eps)) {
			if (x.is_parallel(xy, eps)) {
				return is_collinear_seg_intersect(x1, x2, y1, y2);
			}
			else
				return false;
		}
		double u;
		if ((x1.getx() - x2.getx() != 0) || (x1.gety() - x2.gety() != 0))
			u = ((x1.getx() - x2.getx())*(y2.gety() - x2.gety()) - (x1.gety() - x2.gety())*(y2.getx() - x2.getx())) / ((x1.gety() - x2.gety())*(y1.getx() - y2.getx()) - (x1.getx() - x2.getx())*(y1.gety() - y2.gety()));
		else
			u = ((x1.getx() - x2.getx())*(y2.getz() - x2.getz()) - (x1.getz() - x2.getz())*(y2.getx() - x2.getx())) / ((x1.getz() - x2.getz())*(y1.getx() - y2.getx()) - (x1.getx() - x2.getx())*(y1.getz() - y2.getz()));
		double v;
		if (x1.getx() - x2.getx() != 0)
			v = ((y1.getx() - y2.getx()) * u + y2.getx() - x2.getx()) / (x1.getx() - x2.getx());
		else if (x1.gety() - x2.gety() != 0)
			v = ((y1.gety() - y2.gety()) * u + y2.gety() - x2.gety()) / (x1.gety() - x2.gety());
		else
			v = ((y1.getz() - y2.getz()) * u + y2.getz() - x2.getz()) / (x1.getz() - x2.getz());
		if (((x1.getz() - x2.getz())*v + x2.getz()) == ((y1.getz() - y2.getz())*u + y2.getz()))
			if ((u <= 1.0) && (u >= 0.0) && (v <= 1.0) && (v >= 0.0))
				return true;
		return false;
	};

	bool CGLIntersection::collinear_seg_intersect(CGLPoint x1, CGLPoint x2, CGLPoint y1, CGLPoint y2, Result<CGLPoint>* res) {
		if (x1 != x2) {
			if (x1.getx() != x2.getx()) {
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
				if (x1.getx() > y2.getx())
					return false;
				if (x2.getx() < y1.getx())
					return false;
				if ((x1.getx() <= y1.getx()) && (x2.getx() >= y2.getx())) {
					res->add(y1, eps);
					res->add(y2, eps);
					return true;
				}
				if ((x1.getx() <= y1.getx()) && (x2.getx() < y2.getx()) && (x2.getx() >= y1.getx())) {
					res->add(y1, eps);
					res->add(x2, eps);
					return true;
				}
				if ((x1.getx() > y1.getx()) && (x1.getx() <= y2.getx()) && (x2.getx() > y2.getx())) {
					res->add(x1, eps);
					res->add(y2, eps);
					return true;
				}
				if ((x1.getx() > y1.getx()) && (x2.getx() < y2.getx())) {
					res->add(x1, eps);
					res->add(x2, eps);
					return true;
				}
			}
			else
				if (x1.gety() != x2.gety()) {
					if (x1.gety() > x2.gety()) {
						CGLPoint p = x1;
						x1 = x2;
						x2 = p;
					}
					if (y1.gety() > y2.gety()) {
						CGLPoint p = y1;
						y1 = y2;
						y2 = p;
					}
					if (x1.gety() > y2.gety())
						return false;
					if (x2.gety() < y1.gety())
						return false;
					if ((x1.gety() <= y1.gety()) && (x2.gety() >= y2.gety())) {
						res->add(y1, eps);
						res->add(y2, eps);
						return true;
					}
					if ((x1.gety() < y1.gety()) && (x2.gety() < y2.gety()) && (x2.gety() >= y1.gety())) {
						res->add(y1, eps);
						res->add(x2, eps);
						return true;
					}
					if ((x1.gety() > y1.gety()) && (x1.gety() <= y2.gety()) && (x2.gety() > y2.gety())) {
						res->add(x1, eps);
						res->add(y2, eps);
						return true;
					}
					if ((x1.gety() > y1.gety()) && (x2.gety() < y2.gety())) {
						res->add(x1, eps);
						res->add(x2, eps);
						return true;
					}
				}
				else {
					if (x1.getz() > x2.getz()) {
						CGLPoint p = x1;
						x1 = x2;
						x2 = p;
					}
					if (y1.getz() > y2.getz()) {
						CGLPoint p = y1;
						y1 = y2;
						y2 = p;
					}
					if (x1.getz() > y2.getz())
						return false;
					if (x2.getz() < y1.getz())
						return false;
					if ((x1.getz() <= y1.getz()) && (x2.getz() >= y2.getz())) {
						res->add(y1, eps);
						res->add(y2, eps);
						return true;
					}
					if ((x1.getz() < y1.getz()) && (x2.getz() < y2.getz()) && (x2.getz() >= y1.getz())) {
						res->add(y1, eps);
						res->add(x2, eps);
						return true;
					}
					if ((x1.getz() > y1.getz()) && (x1.getz() <= y2.getz()) && (x2.getz() > y2.getz())) {
						res->add(x1, eps);
						res->add(y2, eps);
						return true;
					}
					if ((x1.getz() > y1.getz()) && (x2.getz() < y2.getz())) {
						res->add(x1, eps);
						res->add(x2, eps);
						return true;
					}
				}
		}
		else if (y1 != y2) {
			if (y1.getx() != y2.getx()) {
				if (y1.getx() > y2.getx()) {
					CGLPoint p = y1;
					y1 = y2;
					y2 = p;
				}
				if (x1.getx() <= y2.getx() && x1.getx() >= y1.getx())
				{
					res->add(x1, eps);
					return true;
				}
			}
			else if (y1.gety() != y2.gety()) {
				if (y1.gety() > y2.gety()) {
					CGLPoint p = y1;
					y1 = y2;
					y2 = p;
				}
				if (x1.gety() <= y2.gety() && x1.gety() >= y1.gety())
				{
					res->add(x1, eps);
					return true;
				}
			}
			else {
				if (y1.getz() > y2.getz()) {
					CGLPoint p = y1;
					y1 = y2;
					y2 = p;
				}
				if (x1.getz() <= y2.getz() && x1.getz() >= y1.getz())
				{
					res->add(x1, eps);
					return true;
				}
			}

		}
		else if (x1 != y1)
			return false;
		else {
			res->add(x1, eps);
			return true;
		}
		return false;
	}

	bool CGLIntersection::segments_intersect(CGLPoint x1, CGLPoint x2, CGLPoint y1, CGLPoint y2, Result<CGLPoint>* res) {
		CGLSegment s1(x1, x2);
		CGLSegment s2(y1, y2);
		if (!s1.get_box().is_box_intersect(s2.get_box()))
			return false;
		CGLVector x(x1, x2);
		CGLVector y(y1, y2);
		CGLVector xy(x1, y1);
		if (x.is_parallel(y, eps)) {
			if (x.is_parallel(xy, eps)) {
				return collinear_seg_intersect(x1, x2, y1, y2, res);
			}
			else
				return false;
		}
		double u;
		if ((x1.getx() - x2.getx() != 0) || (x1.gety() - x2.gety() != 0))
			u = ((x1.getx() - x2.getx())*(y2.gety() - x2.gety()) - (x1.gety() - x2.gety())*(y2.getx() - x2.getx())) / ((x1.gety() - x2.gety())*(y1.getx() - y2.getx()) - (x1.getx() - x2.getx())*(y1.gety() - y2.gety()));
		else
			u = ((x1.getx() - x2.getx())*(y2.getz() - x2.getz()) - (x1.getz() - x2.getz())*(y2.getx() - x2.getx())) / ((x1.getz() - x2.getz())*(y1.getx() - y2.getx()) - (x1.getx() - x2.getx())*(y1.getz() - y2.getz()));
		double v;
		if (x1.getx() - x2.getx() != 0)
			v = ((y1.getx() - y2.getx()) * u + y2.getx() - x2.getx()) / (x1.getx() - x2.getx());
		else if (x1.gety() - x2.gety() != 0)
			v = ((y1.gety() - y2.gety()) * u + y2.gety() - x2.gety()) / (x1.gety() - x2.gety());
		else
			v = ((y1.getz() - y2.getz()) * u + y2.getz() - x2.getz()) / (x1.getz() - x2.getz());
		if (((x1.getz() - x2.getz())*v + x2.getz()) == ((y1.getz() - y2.getz())*u + y2.getz()))
			if ((u <= 1.0) && (u >= 0.0) && (v <= 1.0) && (v >= 0.0)) {
				if (fmax(u, v) < eps)
					res->add(CGLPoint(x2.getx(), x2.gety(), x2.getz(), eps), eps);
				else {
					if (abs(u) < abs(v))
						res->add(CGLPoint((x1.getx() - x2.getx())*v + x2.getx(), (x1.gety() - x2.gety())*v + x2.gety(), (x1.getz() - x2.getz())*v + x2.getz(), eps), eps);
					else
						res->add(CGLPoint((y1.getx() - y2.getx())*u + y2.getx(), (y1.gety() - y2.gety())*u + y2.gety(), (y1.getz() - y2.getz())*u + y2.getz(), eps), eps);
				}
				return true;
			}
		return false;
	};

	bool CGLIntersection::is_coplanar_tr_intersect(CGLTriangle t1, CGLTriangle t2) {
		CGLOrientation or ;
		CGLPoint *a = &t1.get_point(0);
		CGLPoint *b = &t1.get_point(1);
		CGLPoint *c = &t1.get_point(2);
		CGLPoint *p = &t2.get_point(0);
		CGLPoint *q = &t2.get_point(1);
		CGLPoint *r = &t2.get_point(2);
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (is_segments_intersect(t1.get_point(i), t1.get_point(i + 1), t2.get_point(j), t2.get_point(j + 1)))
					return true;

		if (or .coplanar_orientation(*a, *b, *p) != NEGATIVE)
			if (or .coplanar_orientation(*b, *c, *p) != NEGATIVE)
				if (or .coplanar_orientation(*c, *a, *p) != NEGATIVE)
					return true;
		if (or .coplanar_orientation(*p, *q, *a) != NEGATIVE)
			if (or .coplanar_orientation(*q, *r, *a) != NEGATIVE)
				if (or .coplanar_orientation(*q, *p, *a) != NEGATIVE)
					return true;
		return false;
	};

	bool CGLIntersection::coplanar_tr_intersect(CGLTriangle t1, CGLTriangle t2, Result<CGLPoint>* res) {
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
					res->add(*p, eps);
		if (or .coplanar_orientation(*a, *b, *q) != NEGATIVE)
			if (or .coplanar_orientation(*b, *c, *q) != NEGATIVE)
				if (or .coplanar_orientation(*c, *a, *q) != NEGATIVE)
					res->add(*q, eps);
		if (or .coplanar_orientation(*a, *b, *r) != NEGATIVE)
			if (or .coplanar_orientation(*b, *c, *r) != NEGATIVE)
				if (or .coplanar_orientation(*c, *a, *r) != NEGATIVE)
					res->add(*r, eps);
		if (or .coplanar_orientation(*p, *q, *a) != NEGATIVE)
			if (or .coplanar_orientation(*q, *r, *a) != NEGATIVE)
				if (or .coplanar_orientation(*r, *p, *a) != NEGATIVE)
					res->add(*a, eps);
		if (or .coplanar_orientation(*p, *q, *b) != NEGATIVE)
			if (or .coplanar_orientation(*q, *r, *b) != NEGATIVE)
				if (or .coplanar_orientation(*r, *p, *b) != NEGATIVE)
					res->add(*b, eps);
		if (or .coplanar_orientation(*p, *q, *c) != NEGATIVE)
			if (or .coplanar_orientation(*q, *r, *c) != NEGATIVE)
				if (or .coplanar_orientation(*r, *p, *c) != NEGATIVE)
					res->add(*c, eps);
		if (res->size() == 0)
			return false;
		else
			return true;
	};

	bool CGLIntersection::out_of_plane_trs_intersect(CGLTriangle t1, CGLTriangle t2, CGLSegment* seg, Result<CGLPoint>* res) {
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
		double left[3] = { -INFINITY, -INFINITY, -INFINITY }, right[3] = { INFINITY, INFINITY, INFINITY };
		double res_left = -INFINITY, res_right = INFINITY;
		if (coef12 > 0)
			left[0] = -coef11 / coef12;
		else if (coef12 < 0)
			right[0] = -coef11 / coef12;
		if (coef22 > 0)
			left[1] = -coef21 / coef22;
		else if (coef22 < 0)
			right[1] = -coef21 / coef22;
		if (coef32 > 0)
			left[2] = -coef31 / coef32;
		else if (coef32 < 0)
			right[2] = -coef31 / coef32;
		res_left = left[0];
		res_right = right[0];
		if (res_left > right[1])
			return false;
		if (res_right < left[1])
			return false;
		if ((res_left <= left[1]) && (res_right >= right[1])) {
			res_left = left[1];
			res_right = right[1];
		}
		if ((res_left < left[1]) && (res_right < right[1]) && (res_right >= left[1])) {
			res_left = left[1];
		}
		if ((res_left > left[1]) && (res_left <= right[1]) && (res_right > right[1])) {
			res_right = right[1];
		}
		if (res_left > right[2])
			return false;
		if (res_right < left[2])
			return false;
		if ((res_left <= left[2]) && (res_right >= right[2])) {
			res_left = left[2];
			res_right = right[2];
		}
		if ((res_left < left[2]) && (res_right < right[2]) && (res_right >= left[2])) {
			res_left = left[2];
		}
		if ((res_left > left[2]) && (res_left <= right[2]) && (res_right > right[2])) {
			res_right = right[2];
		}
		CGLPoint A = t1.get_point(0);
		double u1 = coef11 + res_left*coef12;
		double u2 = coef11 + res_right*coef12;
		double v1 = coef21 + res_left*coef22;
		double v2 = coef21 + res_right*coef22;
		if (res_left == res_right) {
			*seg = CGLSegment(CGLPoint(A.getx() + u1*u.getx() + v1*v.getx(), A.gety() + u1*u.gety() + v1*v.gety(), A.getz() + u1*u.getz() + v1*v.getz(), eps),
				CGLPoint(A.getx() + u1*u.getx() + v1*v.getx(), A.gety() + u1*u.gety() + v1*v.gety(), A.getz() + u1*u.getz() + v1*v.getz(), eps));
			return true;
		}
		else {
			*seg = CGLSegment(CGLPoint(A.getx() + u1*u.getx() + v1*v.getx(), A.gety() + u1*u.gety() + v1*v.gety(), A.getz() + u1*u.getz() + v1*v.getz(), eps),
				CGLPoint(A.getx() + u2*u.getx() + v2*v.getx(), A.gety() + u2*u.gety() + v2*v.gety(), A.getz() + u2*u.getz() + v2*v.getz(), eps));
			return true;
		}
		return true;
	}