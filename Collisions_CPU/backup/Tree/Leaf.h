#pragma once
#include <vector>
#include <iostream>
#include "./cube3d.h"



class LastLeaf;

// Базовый лист октодерева
class Leaf
{
protected:
	cube3d cube_;
public:
	Leaf(double xDown, double xUp, double yDown, double yUp, double zDown, double zUp) :
		cube_(xDown, xUp, yDown, yUp, zDown, zUp) // Стоит прооптимизировать процесс передачи
	{ }

	Leaf(const cube3d& cube) : cube_(cube) { }
	virtual ~Leaf() { }
	// Sieve functions
	virtual void sieve_base_point(const point3d*) = 0;
	virtual void sieve_other_point(const point3d*) = 0;


	virtual void make_childs(size_t depth) = 0; // recurrent
	virtual void check_in_if_last(std::vector<LastLeaf*>&) = 0; // recurrent

	virtual void print() const = 0; // recurrent

	virtual void update_cube(double xDown, double xUp, double yDown, double yUp, double zDown, double zUp) = 0; // recurrent
	virtual void update_cube(const cube3d&) = 0;

	inline bool is_collide(const point3d& p) const { return cube_.is_collide(p); }
};
