#pragma once
#include "./Tree/Tree3d.h"
#include "boundary.h"



/*
	����� ������� ���� ����������� � ����������� ���������
	��� �������� - ���������, ������� �������� ����� � �������� ����������� IArray
	������������� ���� ��� �� ����������� ��� � ��������� � ������ Tree

	ArrayT::const_iterator �������� ��� ������������ ���������
	(�������� ������� ����� ���� �������, ������ �� �� ��� �� ��������� �� ����� ����������)
*/

template <typename T>
auto __get_const_iterator()
{
	const T t;
	return std::begin(t);
}



template <typename ArrayT>
class Intersector3d
{
private:
	const ArrayT& apoints_;
	const ArrayT& bpoints_;

	typedef decltype(__get_const_iterator<ArrayT>()) IteratorT;

	std::vector<collision3d<IteratorT>> cur_collisions_;
	std::vector<collision3d<IteratorT>> new_collisions_;

	Tree<IteratorT> tree_; // �������� ������������ ������ � ����, ��� runtime ���������
public:
	Intersector3d(const ArrayT& apoints, const ArrayT& bpoints, size_t depth = 1)
		: tree_(depth), apoints_(apoints), bpoints_(bpoints)
	{
		tree_.update_cube(get_boundary_cube3d(apoints, bpoints));
	}
private:
	void make_first_iteration()
	{
		/*
		   ���������� ����� ������ ���������� ��������� ���������
		   ������� ������� ��������� �� �����! ����� ����� ����� �������� ����
		   ���� ������� sieve
		*/

		tree_.sieve_a(apoints_); // vector<point3d>
		tree_.sieve_b(bpoints_);

		//tree_.print_buffers();

		tree_.get_full_buffers(cur_collisions_);
	}

	void make_iteration()
	{
		for (const auto& collision : cur_collisions_)
		{
			// ��������� ��������� ��� ������
			tree_.update_cube(collision.cube);

			// ���������� �����
			tree_.sieve_a_iterable(collision.apoints); // vector<const point3d*>
			tree_.sieve_b_iterable(collision.bpoints);

			// ��������� ������ ����������
			// <std::vector<collision3d<IteratorT>>>
			tree_.get_full_buffers(new_collisions_);
			// ������� ������
			tree_.clean_buffers();
		}

		cur_collisions_.clear();
		std::swap(new_collisions_, cur_collisions_);
	}

	void print_iteration(size_t i) const
	{
		printf("##################### Iteration %d ####################################\n", i);
		for (const auto& ps : cur_collisions_)
			std::cout << ps << std::endl;
	}
public:
	std::vector<collision3d<IteratorT>>&& make_iterations(size_t number_of_iterations)
	{
		// ������ ������ ������
		make_first_iteration();

		// ������� ���������� ������� ������
		tree_.clean_buffers();

		for (size_t i = 0; i < number_of_iterations; ++i)
		{
			// ������ ��������
			make_iteration();
			// ������� ���������� �������
			tree_.clean_buffers();
		}

		return std::move(cur_collisions_);
	}

	void update_cube(const cube3d& cube)
	{
		tree_.update_cube(cube);
	}
};
