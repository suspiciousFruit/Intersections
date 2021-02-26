#pragma once
#include "Leaf.h"
#include "./collision3d.h"



#include <iostream>
class LastLeaf : public Leaf
{
private:
	std::vector<const point3d*> base_points_;
	std::vector<const point3d*> other_points_;
public:
	LastLeaf(double xDown, double xUp, double yDown, double yUp, double zDown, double zUp) :
		Leaf(xDown, xUp, yDown, yUp, zDown, zUp) // Прооптимизировать процесс передачи
	{ }

	LastLeaf(const cube3d& cube) : Leaf(cube)
	{ }

	virtual ~LastLeaf()
	{ }

	virtual void sieve_base_point(const point3d* p) override
	{
		if (cube_.is_collide(p))
			base_points_.push_back(p);
	}

	virtual void sieve_other_point(const point3d* p) override
	{
		if (cube_.is_collide(p))
			other_points_.push_back(p);
	}

	virtual void make_childs(size_t) override
	{ }

	virtual void check_in_if_last(std::vector<LastLeaf*>& arr) override
	{
		arr.emplace_back(this);
	}

	virtual void print() const override
	{
		if (base_points_.size() == 0 && other_points_.size() == 0)
			return;

		cube_.print();
		std::cout << "Base points:" << std::endl;
		for (const auto& p : base_points_)
			std::cout << p << std::endl;
		std::cout << "Other points:" << std::endl;
		for (const auto& p : other_points_)
			std::cout << p << std::endl;
	}

	virtual void update_cube(double xDown, double xUp,
		double yDown, double yUp, double zDown, double zUp) override
	{
		cube_.update(xDown, xUp, yDown, yUp, zDown, zUp);
	}

	virtual void update_cube(const cube3d& cube)
	{
		cube_ = cube;
	}

	bool is_has_both_type() const
	{
		return base_points_.size() != 0 &&
			other_points_.size() != 0;
	}

	std::pair<std::vector<const point3d*>, std::vector<const point3d*>> get_arrays()
	{
		return { std::move(base_points_), std::move(other_points_) };
	}

	std::vector<const point3d*>&& get_base_points()
	{
		return std::move(base_points_);
	}

	std::vector<const point3d*>&& get_other_points()
	{
		return std::move(other_points_);
	}

	collision3d&& get_possible_collision()
	{
		return collision3d(std::move(base_points_),
			std::move(other_points_), cube_);
	}

	const cube3d& get_cube() const
	{
		return cube_;
	}

	void clear_arrays()
	{
		base_points_.clear();
		other_points_.clear();
	}
};
