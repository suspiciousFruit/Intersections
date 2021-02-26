#pragma once
#include <iostream>
#include "point3d.h"



union cube3d
{
	struct {
		double x_down;
		double x_up;
		double y_down;
		double y_up;
		double z_down;
		double z_up;
	};
	double data[6];
public:
	cube3d(double xDown, double xUp, double yDown, double yUp, double zDown, double zUp) :
		x_up(xUp), x_down(xDown), y_up(yUp), y_down(yDown), z_up(zUp), z_down(zDown)
	{ }

	inline bool isfit(const point3d& p) const
	{
		return p.x <= x_up && p.x >= x_down &&
			p.y <= y_up && p.y >= y_down &&
			p.z <= z_up && p.z >= z_down;
	}

	template <typename IIterator>
	inline bool isfit(const IIterator pptr) const
	{
		const point3d& p = *pptr;
		return p.x <= x_up && p.x >= x_down &&
			p.y <= y_up && p.y >= y_down &&
			p.z <= z_up && p.z >= z_down;
	}

	void update(double xDown, double xUp, double yDown, double yUp, double zDown, double zUp)
	{
		x_up = xUp;
		x_down = xDown;
		y_up = yUp;
		y_down = yDown;
		z_up = zUp;
		z_down = zDown;
	}

	void print() const
	{
		printf("cube x:[%.1lf %.1lf] y:[%.1lf %.1lf] z:[%.1lf %.1lf]\n", x_down, x_up, y_down, y_up, z_down, z_up);
	}

	friend std::ostream& operator<< (std::ostream& s, const cube3d& cube)
	{
		s << "cube x:[" << cube.x_down << ", " << cube.x_up << "] y:["
			<< cube.y_down << ", " << cube.y_up << "] z:["
			<< cube.z_down << ", " << cube.z_up << "]";

		return s;
	}

	static cube3d make_cube(double size, const point3d& center = point3d(0,0,0))
	{
		return cube3d(0, size, 0, size, 0, size);
	}
};

