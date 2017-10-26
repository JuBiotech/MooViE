/*
 * Color.h
 *
 *  Created on: 27.07.2017
 *      Author: beyss
 */

#ifndef COLOR_H_
#define COLOR_H_

#include <array>
#include "Triangle.h"

class Color
{
public:
	Color(double r = 0, double g = 0, double b = 0, double a = 1)
			: _r { limit(r) }, _g { limit(g) }, _b { limit(b) }, _a { limit(a) }
	{
	}
	const double& r() const
	{
		return _r;
	}
	const double& g() const
	{
		return _g;
	}
	const double& b() const
	{
		return _b;
	}
	const double& a() const
	{
		return _a;
	}
	void set_alpha(double alpha)
	{
		_a = limit(alpha);
	}
	Color set_alpha(double alpha) const
	{
		Color out(*this);
		out.set_alpha(alpha);
		return out;

	}
private:
	double limit(const double& val)
	{
		double temp_val = val;
		if (uint8_t(temp_val) == temp_val && temp_val > 1.0)
			temp_val /= 255.0;
		return std::max(std::min(temp_val, 1.0), 0.0);
	}
	double _r, _g, _b, _a;

public:
	static const std::array<Color, 10> GLOW_10;

	static const Triangle<Color, 12> SET3;

	static const Color BLACK;

	static const Color SET2_3_1;
	static const Color SET2_3_2;
	static const Color SET2_3_3;

};

#endif /* COLOR_H_ */
