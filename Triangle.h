/*
 * Triangle.h
 *
 *  Created on: 23.08.2017
 *      Author: beyss
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <cstddef>
#include <vector>
#include <cassert>

template<typename T, size_t dim>
class Triangle
{
public:
	Triangle()
	:_data(dim * (dim + 1) / 2, T())
	{

	}
	Triangle(const std::vector<T> data)
	: _data(data)
	{
		assert(_data.size() == dim * (dim + 1) / 2);
	}
	virtual ~Triangle()
	{

	}
	const T& at(size_t i, size_t j) const
	{
		assert(i < dim);
		assert(j <= i);
		return _data.at(i*(i+1)/2 + j);
	}
	T& at(size_t i, size_t j)
	{
		assert(i < dim);
		assert(j <= i);
		return _data.at(i*(i+1)/2 + j);
	}
private:
	typename std::vector<T> _data;
};

#endif /* TRIANGLE_H_ */
