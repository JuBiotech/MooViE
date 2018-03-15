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

/** A Label is a formatted text that is stored as a text string
 * and a TextProperties object.
 * @brief The Label class
 */
class Label
{
public:
    /**
     * @brief Label
     * @param text
     * @param prop
     */
    Label(const std::string& text, const TextProperties& prop)
    : _text(text), _prop(prop)
    {
    }

    /** Access function for this Label's text.
     * @brief text
     * @return a reference to text
     */
    const std::string& text() const
    {
        return _text;
    }

    /** Access function for this Label's TextProperties.
     * @brief prop
     * @return a reference to prop
     */
    const TextProperties& prop() const
    {
        return _prop;
    }
private:
    /** The text of this Label */
    std::string _text;
    /** The TextProperties of this Label */
    TextProperties _prop;
};

/** Ticks are the .
 * @brief The Ticks class
 */
class Ticks
{
public:
    /**
     * @brief Ticks
     * @param ticks_major
     * @param ticks_minor
     * @param extreme_vals
     * @param label_prop
     * @param label_suffix
     */
    Ticks(size_t ticks_major, size_t ticks_minor,
          const std::pair<double, double>& extreme_vals,
          const TextProperties& label_prop, const std::string& label_suffix = "")
    : _ticks_major(ticks_major), _ticks_minor(ticks_minor), _extreme_vals(extreme_vals),
      _label_prop(label_prop), _label_suffix(label_suffix)
    {
    }

    virtual ~Ticks() {}

    /** Access function for the Ticks extreme values.
     * @brief extreme_vals
     * @return a reference to the extreme values
     */
    const std::pair<double,double> & extreme_vals() const
    {
        return _extreme_vals;
    }

    /**
     * @brief label
     * @return
     */
    std::vector<Label> get_labels() const
    {
        std::vector<Label> label;
        label.reserve(get_major_ticks() + 1);
        double step = (extreme_vals().second - extreme_vals().first)
                        / double(get_major_ticks());
        for (size_t i = 0; i <= _ticks_major; ++i)
        {
                double val = extreme_vals().first + i * step;
                std::stringstream ss;
                ss << val << _label_suffix;
                label.push_back(Label(ss.str(), _label_prop));
        }
        return label;
    }

    /**
     * @brief ticksmajor
     * @return
     */
    size_t get_major_ticks() const
    {
        return _ticks_major;
    }

    /**
     * @brief ticksminor
     * @return
     */
    size_t get_minor_ticks() const
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

/**
 * @brief create_axis
 * @param min
 * @param max
 * @return
 */
inline std::pair<double,double> create_axis(double min, double max)
{
	if (max < min)
	{
		std::pair<double,double> ret = create_axis(max, min);
		return std::make_pair(ret.second, ret.first);
	}
	else
	{
		double diff = std::floor(std::log10(std::abs(max-min))) + 1;
		double power_of_ten = std::pow(10, diff);
		bool shift = false;

		if (std::abs(std::abs(max - min) - power_of_ten) < 1.5 * power_of_ten)
		{
			diff -= 1;
			power_of_ten = std::pow(10, diff);
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
