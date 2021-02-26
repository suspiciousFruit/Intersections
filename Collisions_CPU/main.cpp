#include <iostream>
#include <vector>
//#include "./Intersector/algoritm_point6d.h"
#include "Intersector/point6d.h"
#include "Intersector/Intersector3d.h"

std::vector<point3d> other_points = {
	{1, 1, 0.9},
	{1, 1, 0.5},
	{1, 1, 2.1},
	{1, 1, 1.9},
	{1, 1, 1.1},
	{1, 1, 0.8},
	{1, 1, 1.5},
	{1, 1, 0.2},

	{1, 4, 3.1},

	{0.1, 0.4, 0.7},
	{6.7, 6.7, 5.1},
	{6.7, 7, 5.1},
	{6.7, 6.7, 5},
	{6.7, 7, 5}
};

std::vector<point3d> base_points = {
	{1, 1, 0},
	{1, 4, 3},
	{7, 7, 5}
};

std::vector<point6d> other6d = {
	{1, 1, 0.9, 3, 3, 3},
	{1, 1, 0.5, 3.1, 2.9, 3},
	{1, 1, 2.1, 3, 3, 3},
	{1, 1, 1.9, 3.1, 3, 2.8},
	{1, 1, 1.1, 3.1, 3, 2.8},
	{1, 1, 0.8, 3.1, 3, 2.8},
	{1, 1, 1.5, 3.1, 3, 2.8},
	{1, 4, 3.1, 3.1, 2.9, 3},
	{0.1, 0.4, 0.7, 3.1, 2.9, 3},
	{6.7, 6.7, 5.1, 2.7, 3.3, 3.5},
	{7, 7, 5, 2.9, 3, 3.1},
	{6.7, 6.7, 5, 2.7, 3.1, 3.5},
	{6.7, 7, 5, 2.9, 3.3, 3.6},
	{1, 1, 0.2, 2.7, 3.3, 3.5}
};

std::vector<point6d> base6d = {
	{1, 1, 0, 3.1, 2.9, 3},
	{1, 4, 3, 3.1, 2.8, 3},
	{7, 7, 5, 3.1, 2.8, 3.1}
};

#include "Intersector/Tree/Tree3d.h"
#include "npoint_iterator.h"

void test_tree()
{
	cube3d cube(0, 1, 0, 1, 0, 1);
	// Test for npoint3d vector
	std::vector<npoint3d> vec_t1(4);
	Tree<typename VectorAdapter::const_iterator> tree_t1(cube, 1);
	TreeAdapter a(vec_t1);
	tree_t1.sieve_a(TreeAdapter(vec_t1));


	// Test for point3d vector
	std::vector<point3d> vec_t2(4);
	Tree<std::vector<point3d>::const_iterator> tree_t2(cube, 1);
	tree_t2.sieve_b(vec_t2);
}




int main()
{
	//maintest();
	test_tree();

	std::vector<npoint3d> a(4);
	std::vector<npoint3d> b(4);
	cube3d cube(0, 10, 0, 10, 0, 10);

	Intersector3d inter(
		base_points,
		other_points,
		cube);
	
	const auto colls = inter.make_iterations(4);
	for (const auto& col : colls)
		std::cout << col << std::endl;


	return 0;
}

