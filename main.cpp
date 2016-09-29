#include "geom_objects.h"
#include "intersection.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
/* TESTS FOR COPLANAR TRIANGLES
	float f[] = {0, 0, 0, 0, 1, 0, 1, 0, 0, // This tests for coplanar triangles(all tests make with triangle indexes 1-9(this line) and triangle in other lines)
				 0, 0, 0, 0, 1, 0, 1, 0, 0, //same triangles
				 0, 0, 0, 0, 2, 0, 2, 0, 0, //three vertices of t2 on edges of t1, two edges of t2 included into edges of t1
				 0.25, 0.25, 0, 0, 0.25, 0, 0.25, 0, 0, //two vertices of t2 on edges of t1
				 0.5, 0.5, 0, 0, 0.25, 0, 0.25, 0, 0, //three vertices of t2 on edges of t1 (no inclusion of edges)
				 0.25, 0.25, 0, 0.25, 0.3, 0, 0.3, 0.25, 0, //t2 is in the interior of t1
				 0, 0, 0, 0, 1, 0, 0.1, 0.1, 0, //one edge is common
				 0, 0, 0, 0, 0.9, 0, 0.1, 0.1, 0, //one edge of t2 included into an edge of t1, one common vertex
				 0, 0.1, 0, 0, 0.9, 0, 0.1, 0.1, 0, //one edge of t2 included into an edge of t1, no common point 
				 0.25, 0.25, 0, 0, -1, 0, 1, -1, 0, //only one vertex of t2 included by t1
				 0, -1, 0, 0, 0.25, 0, 1, -1, 0, //only one vertex of t2 included by t1 and one vertex of t1 included in t2
				 -1, -1, 0, 0.25, 0.25, 0, 0.25, -1, 0, //one vertex of t1 on edges of t2
				 -1, -1, 0, 0.5, 0.5, 0, 2, -1, 0, //two vertices of t1 on edges of t2
				 0, 0, 0, -0.25, 0, 0, 0, -0.25, 0, //edges  are collinear, one vertex in common
				 0, 0, 0, -1, 1, 0, -1, -1, 0, //edges  are non-collinear, one vertex in common
				 0, 0.1, 0, -0.25, 0.1, 0, -0.25, -0.1, 0, //one vertex of a triangle on an edge of another
				 0, 0, 0, 0, 1, 0, -1, 0, 0, //triangles have a common edge
				 0, 0.1, 0, 0, 0.9, 0, -1, 0, 0, //one triangle edge is included into an edge of the other triangle
				 0, 0, 0, 0, 0.9, 0, -1, 0, 0, //one triangle edge is included into an edge of the other triangle + share a vertex 
				 0, -0.1, 0, 0, 0.9, 0, -1, 0, 0}; //exactly one vertex of each triangle contributes */
	//float f[] = { -10,0,0,10,0,0,0,-3,0, -8,0,0,12,0,0,1,5,0 }; //exactly one vertex of each triangle contributes test2
	//float f[] = {0,0,0,1,0,0,0.5,1.5,0, 0,1,0,1,1,0,0.5,-0.5,0 };//David star		  
	//float f[] = { 0,0,0,1,0,0,0.5,1,0,0,1,0,1,1,0,0.5,0,0 }; //intersection of two triangle corners
	//float f[] = { 0, 0, 0,1, 0, 0,0, 1, 0,-0.1, 0.1, 0,-0.1, 0.2, 0,0.5, 0.8, 0 }; //t2 pierces two edges of t1
	//float f[] = { 0, 0, 0,1, 0, 0,0, 1, 0, -0.1,-0.1,0,-0.1,-0.9,0,-1,-0.1,0 }; //no intersection
	//float f[] = { 0, 0, 0,1, 0, 0,0, 1, 0, 1, 1, 0, 0.5, -0.5, 0, -0.5, 0.5, 0 }; //5 vertex polygon (David star when one vertex on edge other)
	//float f[] = { 0,0,0,0,1,0,1,0,0,0.1,0.1,1,0.2,0.1,1,0.25,0.25,-1 };   //Intersection is a segment(normal)
	//float f[] = { 0,0,0,0,1,0,1,0,0, 0, 0, 0, 1,0,0,0,0,1 }; //Intersection is a segment(common edge)
	//float f[] = { 0,0,0,0,1,0,1,0,0, 0.1, 0, 0, 0.9, 0, 0,0, 0, 1 }; //Intersection is a segment (edge included in other)
	//float f[] = { 0,0,0,0,1,0,1,0,0, 0, 0, 0,0.9, 0, 0,0, 0, 1 }; // Intersection is a segment, inclusion into an edge, on common vertex
	//float f[] = { 0,0,0,0,1,0,1,0,0,-0.1,0,0,0.9,0,0,0,0,1 }; //one vertex from each triangle
	//float f[] = { 0,0,0,0,1,0,1,0,0,0,0,0,0.9,0,1,0,0,1 }; //Intersection is a point(common vertex)
	//float f[] = { 0,0,0,0,1,0,1,0,0, 0.1,0,0,0.9,0,1,0,0,1 }; // Intersection is a point(vertex in edge)
	//float f[] = { 0,0,0,0,1,0,1,0,0,0.1,0.1,0,0.9,0,1,0,0,1 }; //Intersection is a point(vertex in interior) 
	//float f[] = { 0,0,0,0,1,0,1,0,0, 0,0,1,1,0,1,0,1,1 }; //No intersection(parallel plane)
	//float f[] = { 0,0,0,0,1,0,1,0,0, 0,0,1,1,0,2,0,1,1 }; //No intersection (general)
	float f[] = { 0, 0, 0 ,0, 1, 1,0, 1, 0,-1, -1, 0,0, -1, 0,-1, 0, 0 }; //No intersection(general) 
	/*float f[] = { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0,0, 0, 0, 0, 2, 0, 2, 0, 0, 0.25, 0.25, 0, 0, 0.25, 0, 0.25, 0, 0, 0.5, 0.5, 0, 0, 0.25, 0, 0.25, 0, 0,
		0.25, 0.25, 0, 0.25, 0.3, 0, 0.3, 0.25, 0,0, 0, 0, 0, 1, 0, 0.1, 0.1, 0, 0, 0, 0, 0, 0.9, 0, 0.1, 0.1, 0,0, 0.1, 0, 0, 0.9, 0, 0.1, 0.1, 0,	0.25, 0.25, 0, 0, -1, 0, 1, -1, 0, 
		0, -1, 0, 0, 0.25, 0, 1, -1, 0, -1, -1, 0, 0.25, 0.25, 0, 0.25, -1, 0,-1, -1, 0, 0.5, 0.5, 0, 2, -1, 0, 0, 0, 0, -0.25, 0, 0, 0, -0.25, 0, 0, 0, 0, -1, 1, 0, -1, -1, 0, 
		0, 0.1, 0, -0.25, 0.1, 0, -0.25, -0.1, 0, 0, 0, 0, 0, 1, 0, -1, 0, 0, 0, 0.1, 0, 0, 0.9, 0, -1, 0, 0, 0, 0, 0, 0, 0.9, 0, -1, 0, 0, 0, -0.1, 0, 0, 0.9, 0, -1, 0, 0 }; */
	int size = 18;
	int i = 9;
	std::ofstream f1(argv[1], std::ios::app);
	std::ofstream f2(argv[2], std::ios::app);
	while (i < size) {
		f1 << is_triangles_intersect(f, f, 0, 3, 6, i, i + 3, i + 6) << std::endl;
		Result<CGLPoint>* r = &Result<CGLPoint>();
		triangles_intersection(f, f, 0, 3, 6, i, i + 3, i + 6, r);
		r->print(f1);
		f2<< is_triangles_intersect(f, f, i, i + 3, i + 6, 0, 3, 6) << std::endl;
		r = &Result<CGLPoint>();
		triangles_intersection(f, f, i, i + 3, i + 6, 0, 3, 6, r);
		r->print(f2);
		i += 9;
	}
	std::system("pause");
	return 0;
}