#include "Scale.h"

std::vector<Label> SimpleScale::make_labels(void) const
{
	std::vector<Label> label;
	label.reserve(get_major_intersections() + 1);
	double step = (get_extremes().second - get_extremes().first)
			/ double(get_major_intersections());
	for (size_t i = 0; i <= major_intersections; ++i)
	{
		double val = get_extremes().first + i * step;
		std::stringstream ss;
		ss << val << label_suffix;
		label.emplace_back(ss.str(), label_prop);
	}
	return label;
}

std::pair<double,double> create_rounded_interval(double min, double max)
{
	if (max < min)
	{
		std::pair<double,double> ret = create_rounded_interval(max, min);
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