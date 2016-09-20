#include "geom_objects.h"
#include "intersection.h"
#include <iostream>

using namespace std;

int main() {
	float f[] = { 0, 0, 0, 1, 1, 1, 2, 2, 2 };
	triangle_triangle_intersection(f, f, 0, 2, 6, 0, 2, 4, false, 0, 0);
	system("pause");
	return 0;
}