#ifndef GEOM_OBJECTS_H
#define GEOM_OBJECTS_H
#include<iostream>

class CGLPoint {
public:
	float *x;
	float *y;
	float *z;
	CGLPoint() {};
	CGLPoint(float* x, float* y, float* z)
		:x(x), y(y), z(z) {};
	CGLPoint(float* f, int index) {
		x = f + index;
		y = f + index + 1;
		z = f + index + 2;
	};
	~CGLPoint() {};
	friend const std::istream& operator >> (std::istream& in, CGLPoint& P) {
	float *x, *y, *z;
	in >> *x >> *y >> *z;
	if (in)
	P = CGLPoint(x, y, z);
	return in;
	}
	friend const std::ostream& operator << (std::ostream& out, CGLPoint& P) {
	return out << *P.x << ", " << *P.y << ", " << *P.z << std::endl;
	}
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
	float a;
	float b;
	float c;
	float d;
	CGLPlane(CGLPoint p1, CGLPoint p2, CGLPoint p3) {
		a = (*p2.y - *p1.y)*(*p3.z - *p1.z) - (*p3.y - *p1.y)*(*p2.z - *p1.z);
		b = -(*p2.x - *p1.x)*(*p3.z - *p1.z) + (*p3.x - *p1.x)*(*p2.z - *p1.z);
		c = (*p2.x - *p1.x)*(*p3.y - *p1.y) - (*p3.x - *p1.x)*(*p2.y - *p1.y);
		d = -*p1.x*a + *p1.y*b - *p1.z*c;
	};
	~CGLPlane() {};
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
	CGLTriangle(CGLPoint v1, CGLPoint v2, CGLPoint v3)
		: p1(v1), p2(v2), p3(v3) {};
	CGLTriangle(float* f, int index1, int index2, int index3) {
		p1 = CGLPoint(f, index1);
		p2 = CGLPoint(f, index2);
		p3 = CGLPoint(f, index3);
	};
	~CGLTriangle() {};
	bool is_degenerate() {
		if (((*p2.y - *p1.y)*(*p3.z - *p1.z) - (*p3.y - *p1.y)*(*p2.z - *p1.z) == 0) &&
			((*p2.x - *p1.x)*(*p3.z - *p1.z) - (*p3.x - *p1.x)*(*p2.z - *p1.z) == 0) &&
			((*p2.x - *p1.x)*(*p3.y - *p1.y) - (*p3.x - *p1.x)*(*p2.y - *p1.y) == 0))
			return true;
		else return false;
	};
	CGLPlane getPlane() {
		return CGLPlane(p1, p2, p3);
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