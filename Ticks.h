/*
 * Ticks.h
 *
 *  Created on: 22.08.2017
 *      Author: beyss
 */

#ifndef TICKS_H_
#define TICKS_H_

#include <cstddef>
#include <string>
#include <vector>
#include <sstream>
#include "DrawerProperties.h"

class Label
{
public:
	Label(const std::string& text, const TextProperties& prop)
			: _text(text), _prop(prop)
	{
	}
	const std::string& text() const
	{
		return _text;
	}
	const TextProperties& prop() const
	{
		return _prop;
	}
private:
	std::string _text;
	TextProperties _prop;
};

class Ticks
{
public:
	Ticks(size_t ticks_major, size_t ticks_minor,
			const std::pair<double, double>& extreme_vals,
			const TextProperties& label_prop, const std::string& label_suffix = "")
			: _ticks_major(ticks_major), _ticks_minor(ticks_minor), _extreme_vals(
					extreme_vals), _label_prop(label_prop), _label_suffix(label_suffix)
	{
	}

	virtual ~Ticks()
	{
	}
	;

	const std::pair<double, double>& extreme_vals() const
	{
		return _extreme_vals;
	}

	std::vector<Label> label() const
	{
		std::vector<Label> label;
		label.reserve(ticksmajor() + 1);
		double step = (extreme_vals().second - extreme_vals().first)
				/ double(ticksmajor());
		for (size_t i = 0; i <= _ticks_major; ++i)
		{
			double val = extreme_vals().first + i * step;
			std::stringstream ss;
			ss << val << _label_suffix;
			label.push_back(Label(ss.str(), _label_prop));
		}
		return label;
	}

	size_t ticksmajor() const
	{
		return _ticks_major;
	}

	size_t ticksminor() const
	{
		return _ticks_minor;
	}

private:
	size_t _ticks_major;
	size_t _ticks_minor;
	std::pair<double, double> _extreme_vals;
	TextProperties _label_prop;
	std::string _label_suffix;
};

inline std::pair<double,double> create_axis(double min, double max)
{
	if (max > min)
	{
		std::pair<double,double> ret = create_axis(max, min);
		return std::make_pair(ret.second, ret.first);
	}
	else
	{
		size_t digits_in_dif = std::floor(std::log10(std::abs(max-min)));
		size_t power_of_ten = std::pow(10,digits_in_dif);
		bool shift = false;

		if (std::abs(std::abs(max - min) - power_of_ten) < 1.5 * power_of_ten)
		{
			digits_in_dif -= 1;
			power_of_ten = std::pow(10,digits_in_dif);
			shift = true;
		}

		double upper_val = std::round(max/power_of_ten)*power_of_ten;
		if (upper_val < max)
			upper_val += power_of_ten;
		if ((upper_val - 0.5*power_of_ten >= max) && !shift)
			upper_val -= 0.5*power_of_ten;

		double lower_val = std::round(min/power_of_ten) * power_of_ten;
		if (lower_val > min)
			lower_val -= power_of_ten;
		if ((lower_val + 0.5*power_of_ten <= min) && !shift)
			lower_val += 0.5*power_of_ten;
		return std::make_pair(lower_val, upper_val);
	}
}

#endif /* TICKS_H_ */
