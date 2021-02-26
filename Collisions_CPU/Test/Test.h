#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "../Liner.h"

template <typename PointT>
auto readpts(const char* filename)
{
	std::vector<PointT> res;
	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cout << "Error: Can not open file" << std::endl;
		return res;
	}

	PointT p;
	while (1)
	{
		file >> p;
		res.emplace_back(p);

		if (file.eof() || !file.good())
			break;
	}

	return res;
}

#include <iomanip>
void maintest()
{
	std::ofstream file("Test/results.txt");
	cube3d c(0, 10, 0, 10, 0, 10);

	const auto a = readpts<point3d>("Test/numbers3d_1.txt");
	const auto b = readpts<point3d>("Test/numbers3d_2.txt");

	const auto collisions = _find3d(a, b, 5, c);

	file << std::setprecision(15);
	std::cout << std::setprecision(15);

	for (const auto& col : collisions)
	{
		const cube3d& cube = col.cube;
		const double xc = (cube.x_up + cube.x_down) / 2.0;
		const double yc = (cube.y_up + cube.y_down) / 2.0;
		const double zc = (cube.z_up + cube.z_down) / 2.0;

		file << xc << ',' << yc << ',' << zc << std::endl;
	}
}
