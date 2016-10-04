#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H
#include "geom_objects.h"
#include <vector>

enum Cross_type {NO_INTERSECT, POINT, SEGMENT, POLYGON};

template<class T>
class Result {
private:
		std::vector<T> res;
public:
	Result() {
		res.clear();
	}
	Result(std::vector<T> v) {
		res = v;
	}
	Result(CGLPoint p) {
		res.push_back(p);
	}
	~Result() {}
	void add(CGLPoint p) {
		bool has = false;
		for (int i = 0; i < res.size(); i++)
			if (res[i].is_same(p))
				has = true;
		if(!has)
			res.push_back(p);
	}
	int size() {
		return res.size();
	}
	void print(std::ofstream &s) {
		int size = res.size();
		if (size == 2)
			s << "Segment " << std::endl;
		if (size == 1)
			s << "Point " << std::endl;
		if (size == 3)
			s << "Triangle " << std::endl;
		if (size > 3)
			s << "Set of points:" << std::endl;
			for (int i = 0; i < size; i++)
				s << res[i];
			s << std::endl;
	}
};
bool is_collinear_seg_intersect(CGLPoint x1, CGLPoint x2, CGLPoint y1, CGLPoint y2);

bool is_segments_intersect(CGLPoint x1, CGLPoint x2, CGLPoint y1, CGLPoint y2);

bool collinear_seg_intersect(CGLPoint x1, CGLPoint x2, CGLPoint y1, CGLPoint y2, Result<CGLPoint>* res);

bool segments_intersect(CGLPoint x1, CGLPoint x2, CGLPoint y1, CGLPoint y2, Result<CGLPoint>* res);

bool is_coplanar_tr_intersect(CGLTriangle t1, CGLTriangle t2);

bool coplanar_tr_intersect(CGLTriangle t1, CGLTriangle t2, Result<CGLPoint>* r);

bool out_of_plane_trs_intersect(CGLTriangle t1, CGLTriangle t2, CGLSegment* seg);

bool is_triangles_intersect(float* vertices1, float* vertices2, int index_v11, int index_v12, int index_v13,
	int index_v21, int index_v22, int index_v23);

bool triangles_intersection(float* vertices1, float* vertices2, int index_v11, int index_v12, int index_v13,
	int index_v21, int index_v22, int index_v23, Result<CGLPoint>* r);
#endif