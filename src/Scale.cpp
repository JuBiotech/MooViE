#include <Scale.h>
#include <Configuration.h>

std::pair<double, double>
create_rounded_interval (double min, double max)
{
  double MIN_FILL = Configuration::get_instance().get_min_grid_fill_ratio(); // add as a configuration parameter?!
  if (std::fabs(MIN_FILL - 1.) < std::numeric_limits<double>::epsilon())
    return std::make_pair(min, max);

  if (max < min)
  {
    std::pair<double, double> ret = create_rounded_interval (max, min);
    return std::make_pair (ret.second, ret.first);
  }
  else
  {
    double diff = std::floor (std::log10 (std::abs (max - min)));
    double power_of_ten = std::pow (10, diff);
    double upper_val;
    double lower_val;

    do
    {
      upper_val = std::round (max / power_of_ten) * power_of_ten;
      if (upper_val < max)
        upper_val += power_of_ten;
      lower_val = std::round (min / power_of_ten) * power_of_ten;
      if (lower_val > min)
        lower_val -= power_of_ten;

      diff -= 1;
      power_of_ten = std::pow (10, diff);
    } while (std::abs(max - min) / std::abs(lower_val -  upper_val) < MIN_FILL);
    return std::make_pair (lower_val, upper_val);
  }
}


std::vector<Label>
SimpleScale::make_labels (void) const
{
  std::vector<Label> label;
  label.reserve (get_major_intersections () + 1);
  double step = (get_extremes ().second - get_extremes ().first)
      / double (get_major_intersections ());
  for (size_t i = 0; i <= m_major_intersections; ++i)
    {
      double val = get_extremes ().first + i * step;
      std::stringstream ss;
      ss << val << m_label_suffix;
      label.emplace_back (ss.str (), m_label_prop);
    }
  return label;
}

std::vector<Label>
MultiScale::make_labels (size_t i) const {
  std::vector<Label> label;
  label.reserve (get_major_intersections () + 1);
  double step = (get_extremes (i).second - get_extremes (i).first)
      / double (get_major_intersections ());
  for (size_t j = 0; j <= m_major_intersections; ++j)
  {
    double val = get_extremes (i).first + j * step;
    std::stringstream ss;
    ss << val << m_label_suffix;
    label.emplace_back (ss.str (), m_label_prop);
  }
  return label;
}