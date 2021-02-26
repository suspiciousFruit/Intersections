#pragma once
#include "./Tree/Tree3d.h"



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
public:
	typedef decltype(__get_const_iterator<ArrayT>()) IteratorT;

	std::vector<collision3d<IteratorT>> cur_collisions_;
	std::vector<collision3d<IteratorT>> new_collisions_;

	Tree<IteratorT> tree_; // �������� ������������ ������ � ����, ��� runtime ���������
public:
	Intersector3d(const ArrayT& base, const ArrayT& other,
		const cube3d& cube, size_t depth = 1)
		: tree_(cube, depth), apoints_(base), bpoints_(other)
	{ }

	void make_first_iteration()
	{
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
};


/*
class IContT
{
public:
	// ������ �������
	size_t size() const;

	// ��������� �� �����, ������� �����������
	const point3d* operator[] (size_t) const;
};


template <typename ContT>
std::vector<collision3d> _find3ptr(
	const ContT& a, const ContT& b, const cube3d& cube,
	size_t iteration_number = 1,
	size_t tree_depth = 1)
{
	Lily lily(a, b, cube, tree_depth);

	return lily.make_iterations(iteration_number);
}



template <typename Container>
class Point3dAdapter
{
	const Container& array_;
public:
	Point3dAdapter(const Container& array) : array_(array)
	{ }

	inline const point3d* operator[] (size_t index) const
	{
		return (const point3d*)(array_.data() + index);
	}

	inline size_t size() const
	{
		return array_.size();
	}
};
*/
//template <typename Container>
//class PointAdapter
//{
//private:
//	const point3d* data_;
//	const size_t size_;
//public:
//	Point3dAdapter(const Container& cont) :
//		data_(cont.data()), size_(cont.size())
//	{ }
//
//	inline const point3d* operator[] (size_t index) const
//	{
//		return (data_ + index);
//	}
//
//	inline size_t size() const
//	{
//		return size_;
//	}
//};

/*
	class IArray
	{
		const point3d* data() const;
		size_t size() const;
	};

std::vector<collision3d> _find3d(
	const std::vector<point3d>& base,
	const std::vector<point3d>& other,
	const size_t iteration_number,
	const cube3d& cube
)
{
	Point3dAdapter b(base);
	Point3dAdapter o(other);

	Intersector3d lily(b, o, cube, 3);

	return lily.make_iterations(iteration_number);
}
*/
