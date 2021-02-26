#pragma once
#include <limits>
#include <utility>




std::pair<double, double> findminmax( // in words
	const double* data, size_t offset, size_t rsize, size_t fullsize)
{
	double min = std::numeric_limits<double>::max();
	double max = std::numeric_limits<double>::min();

	const double* base = data + offset;
	for (size_t i = 0; i < fullsize; ++i)
	{
		if (*base > max)
			max = *base;
		else if (*base < min)
			min = *base;

		base += rsize;
	}

	return { min, max };
}

template <size_t Offset, size_t Rsize>
std::pair<double, double> findmm(const double* data, size_t size)
{
	double min = *(data + Offset);
	double max = *(data + Offset);

	const double* base = data + Offset;
	for (size_t i = 0; i < size; ++i)
	{
		if (*base > max)
			max = *base;
		else if (*base < min)
			min = *base;

		base += Rsize;
	}

	return { min, max };
}


#include "cube6d.h"

//template <typename IArray>
cube6d getcube6d(const point6d* arr, size_t size)
{
	const point6d* data = arr;
	double cube[12];

	for (size_t i = 0; i < size; ++i)
	{
		const double* d = data[i].data;
		
		for (size_t j = 0; i < 6; ++i)
		{
			if (cube[j] < d[j])
				cube[j] = d[j];
			else if (cube[j + 1] > d[j])
				cube[j + 1] = d[j];
		}
	}

	return cube6d(cube);
}
