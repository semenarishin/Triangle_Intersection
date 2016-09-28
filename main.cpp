#include "geom_objects.h"
#include "intersection.h"
#include <iostream>

using namespace std;

int main() {
	/*float f[] = { -0.23387014772742987, 0.51576417125761509, - 0.94283433258533478, - 0.23387014772742987, 0.51576417125761509, - 0.94283433258533478, - 0.23387014772742987, 0.51576417125761509, - 0.94283433258533478,
		- 0.22177217062562704, 0.6342452485114336, 0.53645038604736328, 0.48698166385293007, 0.36138747073709965, 0.8473226111382246, 0.89880591165274382, - 0.18703385163098574, 0.36222409456968307,
		0.80122884176671505, 0.5579549316316843, - 0.38984065130352974, - 0.75229252129793167, - 0.45774985756725073, - 0.91460688132792711, 0.84752658847719431, 0.76262033171951771, 0.96778011787682772,
		- 0.86271896027028561, - 0.4205366550013423, - 0.29304531868547201, - 0.15778046473860741, 0.31035543419420719, - 0.76522185187786818, - 0.98073739279061556, - 0.85805401857942343, 0.23671759944409132,
		0.21695174276828766, 0.52004669141024351, - 0.41049789078533649, 0.33822660800069571, - 0.48476908728480339, - 0.45631814934313297, - 0.99325979873538017, - 0.39482945576310158, 0.68310892302542925,
		0.64706522040069103, 0.37597482278943062, 0.83709257375448942, 0.59178035520017147, - 0.57171380333602428, - 0.44549135770648718, 0.02933723758906126, - 0.79570241831243038, - 0.079932044260203838,
		-0.62750499602407217, 0.29624816589057446, - 0.3586333217099309, - 0.97918341495096684, - 0.96518470905721188, 0.96828581392765045, - 0.061115194112062454, 0.48867659643292427, 0.64704497344791889,
		- 0.93772094696760178, 0.80566393863409758, - 0.60725640039891005, - 0.65731576643884182, - 0.027184804901480675, - 0.60858374927192926, - 0.84231293667107821, - 0.30525741167366505, 0.76050507463514805,
		0.44579031877219677, 0.4484728816896677, - 0.77035037335008383, - 0.098480274900794029, - 0.35220413748174906, 0.0438017463311553, - 0.99089097138494253, - 0.44518457073718309, 0.32719461154192686,
		0.34583100397139788, 0.64581762347370386, - 0.387538967654109, 0.75826548598706722, - 0.77495390456169844, 0.99434433691203594, - 0.4828643761575222, 0.63003566861152649, - 0.54110724478960037};*/
	/*   TESTS FOR COPLANAR TRIANGLES
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
				 0, -0.1, 0, 0, 0.9, 0, -1, 0, 0}; //exactly one vertex of each triangle contributes 
	float f[] = { -10,0,0,10,0,0,0,-3,0, -8,0,0,12,0,0,1,5,0 }; //exactly one vertex of each triangle contributes test2
	float f[] = {0,0,0,1,0,0,0.5,1.5,0, 0,1,0,1,1,0,0.5,-0.5,0 };//David star		  
	float f[] = { 0,0,0,1,0,0,0.5,1,0,0,1,0,1,1,0,0.5,0,0 }; //intersection of two triangle corners
	float f[] = { 0, 0, 0,1, 0, 0,0, 1, 0,-0.1, 0.1, 0,-0.1, 0.2, 0,0.5, 0.8, 0 }; //t2 pierces two edges of t1
	float f[] = { 0, 0, 0,1, 0, 0,0, 1, 0, -0.1,-0.1,0,-0.1,-0.9,0,-1,-0.1,0 }; no intersection
	float f[] = { 0, 0, 0,1, 0, 0,0, 1, 0, 1, 1, 0, 0.5, -0.5, 0, -0.5, 0.5, 0 }; //5 vertex polygon (David star when one vertex on edge other)*/
	float f[] = { 0,0,0,0,1,0,1,0,0,0.1,0.1,1,0.2,0.1,1,0.25,0.25,-1 };
	int size = 9;
	std::cout << is_triangles_intersect(f, f, 0, 3, 6, size, size + 3, size + 6) << std::endl;
	Result<CGLPoint>* r = &Result<CGLPoint>();
	triangles_intersection(f, f, 0, 3, 6, size, size + 3, size + 6, r);
	r->print();
	std::cout << is_triangles_intersect(f, f, size, size + 3, size + 6, 0, 3, 6) << std::endl;
	r = &Result<CGLPoint>();
	triangles_intersection(f, f, size, size + 3, size + 6, 0, 3, 6, r);
	r->print();
	std::system("pause");
	return 0;
}