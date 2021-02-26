#pragma once
#include <vector>
#include <iostream>
#include "./cube3d.h"
#include "./point3d.h"

struct collision3d
{
	std::vector<const point3d*> base_points; // Rewrite with abstract container
	std::vector<const point3d*> other_points;
	cube3d cube;

	collision3d(std::vector<const point3d*>&& base, std::vector<const point3d*>&& other, const cube3d& c) :
		base_points(base), other_points(other), cube(c)
	{ }

	friend std::ostream& operator<< (std::ostream& st, const collision3d& p)
	{
		st << "Possible collision " << p.cube << std::endl;

		st << "Base points:" << std::endl;
		for (auto p : p.base_points)
			std::cout << "    " << *p << std::endl;
		st << "Other points:" << std::endl;
		for (auto p : p.other_points)
			std::cout << "    " << *p << std::endl;

		return st;
	}
};
//
//#include <limits>
//
//cube3d find_boundaries(const std::vector<point3d>& base_points, const std::vector<point3d>& other_points)
//{
//	double x_max, x_min, y_max, y_min, z_max, z_min;
//
//	x_max = std::numeric_limits<double>::min();
//	x_min = std::numeric_limits<double>::max();
//
//	y_max = std::numeric_limits<double>::min();
//	y_min = std::numeric_limits<double>::max();
//
//	z_max = std::numeric_limits<double>::min();
//	z_min = std::numeric_limits<double>::max();
//
//	const point3d* points = base_points.data();
//
//	for (size_t i = 0; i < base_points.size(); ++i)
//	{
//		if (points[i].x > x_max)
//			x_max = points[i].x;
//		else if (points[i].x < x_min)
//			x_min = points[i].x;
//
//		if (points[i].y > y_max)
//			y_max = points[i].y;
//		else if (points[i].y < y_min)
//			y_min = points[i].y;
//
//		if (points[i].z > z_max)
//			z_max = points[i].z;
//		else if (points[i].z < z_min)
//			z_min = points[i].z;
//	}
//
//	points = other_points.data();
//
//	for (size_t i = 0; i < other_points.size(); ++i)
//	{
//		if (points[i].x > x_max)
//			x_max = points[i].x;
//		else if (points[i].x < x_min)
//			x_min = points[i].x;
//
//		if (points[i].y > y_max)
//			y_max = points[i].y;
//		else if (points[i].y < y_min)
//			y_min = points[i].y;
//
//		if (points[i].z > z_max)
//			z_max = points[i].z;
//		else if (points[i].z < z_min)
//			z_min = points[i].z;
//	}
//
//	return Cube(x_min, x_max, y_min, y_max, z_min, z_max);
//}
//

