#ifndef GEOM_OBJECTS_H
#define GEOM_OBJECTS_H
#include<iostream>
#include<cmath>

enum Orientation {ZERO, POSITIVE, NEGATIVE, COLLINEAR};

class CGLPoint {
public:
	double x;
	double y;
	double z;
	CGLPoint() {};
	CGLPoint(float x, float y, float z)
		:x(x), y(y), z(z) {};
	CGLPoint(float* f, int index) {
		x = *(f + index);
		y = *(f + index + 1);
		z = *(f + index + 2);
	};
	~CGLPoint() {};
	friend const std::istream& operator >> (std::istream& in, CGLPoint& P) {
	float x, y, z;
	in >> x >> y >> z;
	if (in)
	P = CGLPoint(x, y, z);
	return in;
	}
	friend const std::ostream& operator << (std::ostream& out, CGLPoint& P) {
	return out << P.x << ", " << P.y << ", " << P.z << std::endl;
	}
};

class CGLOrientation {
public:
	Orientation coplanar_orientation(CGLPoint &P, CGLPoint &Q, CGLPoint &R) {
		double px = P.x;
		double py = P.y;
		double pz = P.z;
		double qx = Q.x;
		double qy = Q.y;
		double qz = Q.z;
		double rx = R.x;
		double ry = R.y;
		double rz = R.z;
		Orientation oxy_pqr = orient_2d(px, py, qx, qy, rx, ry);
		if (oxy_pqr != COLLINEAR)
			return oxy_pqr;
		Orientation oyz_pqr = orient_2d(py, pz, qy, qz, ry, rz);
		if (oyz_pqr != COLLINEAR)
			return oyz_pqr;
		return orient_2d(px, pz, qx, qz, rx, rz);
	};
private:
	Orientation orient_2d(double px, double py, double qx, double qy, double rx, double ry)
	{
		double pqx = qx - px;
		double pqy = qy - py;
		double prx = rx - px;
		double pry = ry - py;

		double det = pqx*pry - pqy*prx;
		double maxx = abs(px);
		double maxy = abs(py);
		double aqx = abs(qx);
		double aqy = abs(qy);
		double arx = abs(rx);
		double ary = abs(ry);

		if (maxx < aqx) maxx = aqx;
		if (maxx < arx) maxx = arx;
		if (maxy < aqy) maxy = aqy;
		if (maxy < ary) maxy = ary;
		double eps = 3.55271e-15 * maxx * maxy;

		if (det > eps)  return POSITIVE;
		if (det < -eps) return NEGATIVE;
		return ZERO;
	}
};

class CGLBox {
private:
	double min_x, max_x;
	double min_y, max_y;
	double min_z, max_z;
public:
	CGLBox() {};
	CGLBox(double x1, double x2, double y1, double y2, double z1, double z2)
		:min_x(x1), max_x(x2), min_y(y1), max_y(y2), min_z(z1), max_z(z2) {};
	~CGLBox() {};
	bool is_box_intersect(CGLBox& B) {
		if (B.max_x<min_x || B.min_x>max_x)
			return false;
		if (B.max_y<min_y || B.min_y>max_y)
			return false;
		if (B.max_z<min_z || B.min_z>max_z)
			return false;
		return true;
	};
};


class CGLVector {
private:
	double x;
	double y;
	double z;
public:
	CGLVector() {};
	CGLVector(CGLPoint p1, CGLPoint p2) {
		x = p2.x - p1.x;
		y = p2.y - p1.y;
		z = p2.z - p1.z;
	};
	CGLVector(double x, double y, double z)
		:x(x), y(y), z(z) {};
	~CGLVector() {};
	bool is_parallel(CGLVector v) {
		if (dot(v)/(quad()*v.quad()) == 1)
			return true;
		else
			return false;
	};
	double quad() {
		return x*x + y*y + z*z;
	};
	CGLVector cross(CGLVector v) {
		double i = y*v.z - z*v.y;
		double j = -(x*v.z - z*v.x);
		double k = x*v.y - y*v.x;
		return CGLVector(i, j, k);
	};
	double dot(CGLVector v) {
		return x*v.x + y*v.y + z*v.z;
	};
};

class CGLSegment {
private:
	CGLPoint p0;
	CGLPoint p1;
public:
	CGLSegment() {};
	CGLSegment(const CGLPoint& v1, const CGLPoint& v2)
		:p0(v1), p1(v2) {};
	~CGLSegment() {};
	CGLBox get_box() {
		return CGLBox(std::fmin(p0.x, p1.x), std::fmax(p0.x, p1.x),
			std::fmin(p0.y, p1.y), std::fmax(p0.y, p1.y),
			std::fmin(p0.z, p1.z), std::fmax(p0.z, p1.z));
	};
	friend const std::istream& operator >> (std::istream& in, CGLSegment &S) {
		CGLPoint p0, p1;
		in >> p0;
		in >> p1;
		if (in)
			S = CGLSegment(p0, p1);
		return in;
	}
	friend const std::ostream& operator << (std::ostream& out, CGLSegment &S) {
		out << "V1: " << S.p0;
		return out << "V2: " << S.p1;
	}
};

class CGLPlane {
public:
	double a;
	double b;
	double c;
	double d;
	CGLPlane(CGLPoint p1, CGLPoint p2, CGLPoint p3) {
		a = (p2.y - p1.y)*(p3.z - p1.z) - (p3.y - p1.y)*(p2.z - p1.z);
		b = -(p2.x - p1.x)*(p3.z - p1.z) + (p3.x - p1.x)*(p2.z - p1.z);
		c = (p2.x - p1.x)*(p3.y - p1.y) - (p3.x - p1.x)*(p2.y - p1.y);
		d = -p1.x*a + p1.y*b - p1.z*c;
	};
	~CGLPlane() {};
	CGLVector get_normal() {
		return CGLVector(a, b, c);
	};
	bool is_parallel(CGLPlane p) {
		CGLVector v(a, b, c);
		return v.is_parallel(CGLVector(p.a, p.b, p.c));
	};
	bool is_equal(CGLPlane p) {
		if (is_parallel(p))
			if ((d == 0 && p.d != 0) || (d != 0 && p.d == 0))
				return false;
			else
				if ((a*p.d == d*p.a) || (b*p.d == d*p.b) || (c*p.d == d*p.c))
					return true;
		return false;				 
	};
	void print() {
		std::cout << a << ' ' << b << ' ' << c << ' ' << d;
	};
};

class CGLTriangle {
private:
	CGLPoint p1;
	CGLPoint p2;
	CGLPoint p3;
public:
	CGLTriangle() {};
	CGLTriangle(CGLPoint v1, CGLPoint   v2, CGLPoint v3)
		: p1(v1), p2(v2), p3(v3) {};
	CGLTriangle(float* f, int index1, int index2, int index3) {
		p1 = CGLPoint(f, index1);
		p2 = CGLPoint(f, index2);
		p3 = CGLPoint(f, index3);
	};
	~CGLTriangle() {};
	CGLPoint get_point(int i) {  
		switch (i) {
		case 1:
			return p2;
		case 2:
			return p3;
		default:
			return p1;
		}
	};
	bool is_degenerate() {
		if (((p2.y - p1.y)*(p3.z - p1.z) - (p3.y - p1.y)*(p2.z - p1.z) == 0) &&
			((p2.x - p1.x)*(p3.z - p1.z) - (p3.x - p1.x)*(p2.z - p1.z) == 0) &&
			((p2.x - p1.x)*(p3.y - p1.y) - (p3.x - p1.x)*(p2.y - p1.y) == 0))
			return true;
		else return false;
	};
	CGLPlane get_plane() {
		return CGLPlane(p1, p2, p3);
	};
	CGLBox get_box() {
		return CGLBox(std::fmin(std::fmin(p1.x, p2.x), p3.x), std::fmax(std::fmax(p1.x, p2.x), p3.x),
			std::fmin(std::fmin(p1.y, p2.y), p3.y), std::fmax(std::fmax(p1.y, p2.y), p3.y),
			std::fmin(std::fmin(p1.z, p2.z), p3.z), std::fmax(std::fmax(p1.z, p2.z), p3.z));
	};
	friend const std::istream& operator >> (std::istream& in, CGLTriangle &T) {
		CGLPoint p1, p2, p3;
		in >> p1;
		in >> p2;
		in >> p3;
		if (in)
			T = CGLTriangle(p1, p2, p3);
		return in;
	}
	friend const std::ostream& operator << (std::ostream& out, CGLTriangle &T) {
		out << "V1: " << T.p1;
		out << "V2: " << T.p2;
		return out << "V3: " << T.p3;
	}
};
#endif