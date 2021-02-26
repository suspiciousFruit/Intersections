#pragma once
#include <vector>
#include "MiddleLeaf.h"
#include "LastLeaf.h"
#include "./collision3d.h"



class Tree
{
private:
	Leaf* root_;
	std::vector<LastLeaf*> lasts_;
public:
	Tree(const cube3d& space, size_t depth);

	~Tree();

	void update_cube(const cube3d&);

	void clean_buffers();
	template <typename Container>
	void get_full_buffers(Container& container);

	template <typename Container>
	void sieve_base(const Container&);
	template <typename Container>
	void sieve_other(const Container&);

	template <typename First, typename Last>
	void sieve_base(First, Last);
	template <typename First, typename Last>
	void sieve_other(First, Last);

	// Debug functions
	void print_buffers()
	{
		for (const auto last : lasts_)
			last->print();
	}
};

template <typename Container>
void Tree::sieve_base(const Container& array)
{
	for (size_t i = 0; i < array.size(); ++i)
		root_->sieve_base_point(array[i]);
}

template <typename Container>
void Tree::sieve_other(const Container& array)
{
	for (size_t i = 0; i < array.size(); ++i)
		root_->sieve_other_point(array[i]);
}

template <typename First, typename Last>
void Tree::sieve_base(const First first, const Last last)
{
	for (auto iter = first; iter != last; ++iter)
		root_->sieve_base_point(*iter);
}

template <typename First, typename Last>
void Tree::sieve_other(const First first, const Last last)
{
	for (auto iter = first; iter != last; ++iter)
		root_->sieve_other_point(*iter);
}



Tree::Tree(const cube3d& cube, size_t depth)
{
	if (depth == 0) throw std::exception("Depth can't be 0!");

	root_ = new MiddleLeaf(cube);
	root_->make_childs(depth);
	root_->check_in_if_last(lasts_);
}

Tree::~Tree()
{
	delete root_;
}


void Tree::update_cube(const cube3d& cube)
{
	root_->update_cube(cube);
}

void Tree::clean_buffers()
{
	for (const auto last : lasts_)
		last->clear_arrays();
}

template <typename Container>
void Tree::get_full_buffers(Container& cont)
{
	for (auto last : lasts_)
		if (last->is_has_both_type())
		{
			cont.push_back(collision3d(
				last->get_base_points(),
				last->get_other_points(),
				last->get_cube()));
		}
}
