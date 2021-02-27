#pragma once
#include "./Tree/Tree3d.h"
#include "boundary.h"



/*
	Класс который ищет пересечение с необходимой точностью
	Его параметр - контейнер, который содержит точки и является итерируемый IArray
	Удовлетворяет всем тем же требованиям что и контейнер в класса Tree

	ArrayT::const_iterator содержит тип константного итератора
	(итератор который может быть изменен, однако то на что он указывает не может изменяться)
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

	Tree<IteratorT> tree_; // Возможно генерировать дерево в куче, для runtime изменения
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
		   Переписать чтобы дерево изначально принимало контейнер
		   который хранить итераторы на точки! Тогда можно будет оставить одну
		   пару функций sieve
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
			// Обновляем начальный куб дерева
			tree_.update_cube(collision.cube);

			// Просеиваем точки
			tree_.sieve_a_iterable(collision.apoints); // vector<const point3d*>
			tree_.sieve_b_iterable(collision.bpoints);

			// Загружаем полные контейнеры
			// <std::vector<collision3d<IteratorT>>>
			tree_.get_full_buffers(new_collisions_);
			// Очищаем дерево
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
		// Деалем первый проход
		make_first_iteration();

		// Очищаем остаточный буфферы дерева
		tree_.clean_buffers();

		for (size_t i = 0; i < number_of_iterations; ++i)
		{
			// Делаем итерацию
			make_iteration();
			// Очищаем остаточные буфферы
			tree_.clean_buffers();
		}

		return std::move(cur_collisions_);
	}

	void update_cube(const cube3d& cube)
	{
		tree_.update_cube(cube);
	}
};
