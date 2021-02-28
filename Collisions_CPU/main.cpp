#include <iostream>
#include <vector>
//#include "./Intersector/algoritm_point6d.h"
#include "Intersector/point6d.h"
#include "Intersector/Intersector3d.h"

std::vector<point3d> bpoints = {
	{1, 1, 0.03},
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

std::vector<point3d> apoints = {
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

#include "Test/CompileTest.h"


int main()
{
	//test__runall();
	Intersector3d inter(apoints, bpoints);
	const auto [xprec, yprec, zprec] = inter.get_real_precision(0.5);
	std::cout << "xPresssion: " << xprec << std::endl;
	std::cout << "yPresssion: " << yprec << std::endl;
	std::cout << "zPresssion: " << zprec << std::endl;

	const auto colls = inter.intesect(0.5);
	for (const auto& col : colls)
		std::cout << col << std::endl;

	return 0;
}

