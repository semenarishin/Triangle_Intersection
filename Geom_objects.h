#ifndef GEOM_OBJECTS_H
#define GEOM_OBJECTS_H
#include<iostream>
#include<cmath>

enum Orientation {ZERO, POSITIVE, NEGATIVE};

class CGLPoint {
private:
	double x;
	double y;
	double z;
public:
	CGLPoint() {};
	CGLPoint(float x, float y, float z)
		:x(x), y(y), z(z) {}
	CGLPoint(double x, double y, double z){
		this->x = x;
		this->y = y;
		this->z = z;
		double eps = 3.55271e-15;
		if (abs(x) < eps)
			this->x = 0;
		if (abs(y) < eps)
			this->y = 0;
		if (abs(z) < eps)
			this->z = 0;
	}
	CGLPoint(float* f, int index) {
		x = *(f + index);
		y = *(f + index + 1);
		z = *(f + index + 2);
	};
	~CGLPoint() {}
	double getx() {
		return x;
	}
	double gety() {
		return y;
	}
	double getz() {
		return z;
	}
	bool is_same(CGLPoint p) {
		double eps = 3.55271e-15;
		if ((abs(x - p.getx()) < eps) && (abs(y - p.gety()) < eps) && (abs(z - p.getz()) < eps))
			return true;
		else return false;
	}
	friend const bool operator !=(CGLPoint &p1, CGLPoint &p2){
		if ((p1.getx() != p2.getx()) || (p1.gety() != p2.gety()) || (p1.getz() != p2.getz()))
			return true;
		else return false;
	}
	friend const std::istream& operator >> (std::istream& in, CGLPoint& P) {
	float x, y, z;
	in >> x >> y >> z;
	if (in)
	P = CGLPoint(x, y, z);
	return in;
	}
	friend const std::ostream& operator << (std::ostream& out, CGLPoint& P) {
	return out << P.x << " " << P.y << " " << P.z << " ";
	}
};

class CGLOrientation {
public:
	Orientation coplanar_orientation(CGLPoint P, CGLPoint Q, CGLPoint R) {
		double px = P.getx();
		double py = P.gety();
		double pz = P.getz();
		double qx = Q.getx();
		double qy = Q.gety();
		double qz = Q.getz();
		double rx = R.getx();
		double ry = R.gety();
		double rz = R.getz();
		Orientation oxy_pqr = orient_2d(px, py, qx, qy, rx, ry);
		if (oxy_pqr !=ZERO)
			return oxy_pqr;
		Orientation oyz_pqr = orient_2d(py, pz, qy, qz, ry, rz);
		if (oyz_pqr != ZERO)
			return oyz_pqr;
		return orient_2d(px, pz, qx, qz, rx, rz);
	}
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
public:
	double min_x, max_x;
	double min_y, max_y;
	double min_z, max_z;
	CGLBox() {}
	CGLBox(double x1, double x2, double y1, double y2, double z1, double z2)
		:min_x(x1), max_x(x2), min_y(y1), max_y(y2), min_z(z1), max_z(z2) {}
	~CGLBox() {}
	bool is_box_intersect(CGLBox B) {
		if (B.max_x<min_x || B.min_x>max_x)
			return false;
		if (B.max_y<min_y || B.min_y>max_y)
			return false;
		if (B.max_z<min_z || B.min_z>max_z)
			return false;
		return true;
	}
};


class CGLVector {
private:
	double x;
	double y;
	double z;
public:
	CGLVector() {}
	CGLVector(CGLPoint p1, CGLPoint p2) {
		x = p2.getx() - p1.getx();
		y = p2.gety() - p1.gety();
		z = p2.getz() - p1.getz();
	}
	CGLVector(double x, double y, double z)
		:x(x), y(y), z(z) {}
	~CGLVector() {}
	bool is_parallel(CGLVector v) {
		double eps = 3.55271e-15;
		if (1- (this->dot(v)*this->dot(v)/(this->quad()*v.quad())) < eps)
			return true;
		else
			return false;
	}
	double quad() {
		return x*x + y*y + z*z;
	}
	double getx() {
		return x;
	}
	double gety() {
		return y;
	}
	double getz() {
		return z;
	}
	CGLVector cross(CGLVector v) {
		double i = this->y*v.getz() - this->z*v.gety();
		double j = -(this->x*v.getz() - this->z*v.getx());
		double k = this->x*v.gety() - this->y*v.getx();
		return CGLVector(i, j, k);
	}
	double dot(CGLVector v) {
		return x*v.getx() + y*v.gety() + z*v.getz();
	}
};

class CGLSegment {
private:
	CGLPoint p0;
	CGLPoint p1;
public:
	CGLSegment() {};
	CGLSegment(const CGLPoint v1, const CGLPoint v2)
		:p0(v1), p1(v2) {}
	~CGLSegment() {}
	CGLBox get_box() {
		return CGLBox(std::fmin(p0.getx(), p1.getx()), std::fmax(p0.getx(), p1.getx()),
			std::fmin(p0.gety(), p1.gety()), std::fmax(p0.gety(), p1.gety()),
			std::fmin(p0.getz(), p1.getz()), std::fmax(p0.getz(), p1.getz()));
	}
	CGLPoint getpoint0() {
		return p0;
	}
	CGLPoint getpoint1() {
		return p1;
	}
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
	CGLPlane() {}
	CGLPlane(CGLPoint p1, CGLPoint p2, CGLPoint p3) {
		CGLVector edge1(p1, p2);
		CGLVector edge2(p1, p3);
		CGLVector cr = edge1.cross(edge2);
		a = cr.getx();
		b = cr.gety();
		c = cr.getz();
		d = -p1.getx()*a + p1.gety()*b - p1.getz()*c;
	}
	~CGLPlane() {}
	CGLVector get_normal() {
		return CGLVector(a, b, c);
	}
	bool is_parallel(CGLPlane p) {
		CGLVector v(a, b, c);
		return v.is_parallel(CGLVector(p.a, p.b, p.c));
	}
	bool is_equal(CGLPlane p) {
		if (is_parallel(p))
			if ((d == 0 && p.d != 0) || (d != 0 && p.d == 0))
				return false;
			else
				if ((a*p.d == d*p.a) || (b*p.d == d*p.b) || (c*p.d == d*p.c))
					return true;
		return false;				 
	}
	void print() {
		std::cout << a << ' ' << b << ' ' << c << ' ' << d;
	}
};

class CGLTriangle {
private:
	CGLPoint p1;
	CGLPoint p2;
	CGLPoint p3;
public:
	CGLTriangle() {}
	CGLTriangle(CGLPoint v1, CGLPoint   v2, CGLPoint v3)
		: p1(v1), p2(v2), p3(v3) {}
	CGLTriangle(float* f, int index1, int index2, int index3) {
		p1 = CGLPoint(f, index1);
		p2 = CGLPoint(f, index2);
		p3 = CGLPoint(f, index3);
	}
	~CGLTriangle() {}
	CGLPoint get_point(int i) {  
		switch (i%3) {
		case 0:
			return p1;
		case 1:
			return p2;
		case 2:
			return p3;
		}
	}
	bool is_degenerate() {
		if (((p2.gety() - p1.gety())*(p3.getz() - p1.getz()) - (p3.gety() - p1.gety())*(p2.getz() - p1.getz()) == 0) &&
			((p2.getx() - p1.getx())*(p3.getz() - p1.getz()) - (p3.getx() - p1.getx())*(p2.getz() - p1.getz()) == 0) &&
			((p2.getx() - p1.getx())*(p3.gety() - p1.gety()) - (p3.getx() - p1.getx())*(p2.gety() - p1.gety()) == 0))
			return true;
		else return false;
	}
	CGLPlane get_plane() {
		return CGLPlane(p1, p2, p3);
	}
	CGLBox get_box() {
		return CGLBox(std::fmin(std::fmin(p1.getx(), p2.getx()), p3.getx()), std::fmax(std::fmax(p1.getx(), p2.getx()), p3.getx()),
			std::fmin(std::fmin(p1.gety(), p2.gety()), p3.gety()), std::fmax(std::fmax(p1.gety(), p2.gety()), p3.gety()),
			std::fmin(std::fmin(p1.getz(), p2.getz()), p3.getz()), std::fmax(std::fmax(p1.getz(), p2.getz()), p3.getz()));
	}
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
		out << T.get_point(0);
		out << T.get_point(1);
		out << T.get_point(2);
		return out << std::endl;
	}
};
#endif