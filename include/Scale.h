#ifndef SCALE_H_
#define SCALE_H_

#include <cmath>
#include <cstddef>
#include <vector>
#include <sstream>
#include <Label.h>

/** The Scale class represents a graphical scale of an axis
 * by its extreme values and intersections counts.
 *
 * @brief a scale
 *
 * @author beyss
 * @date 22.08.2017
 */
class Scale
{
public:
    /** Creates a Scale from major (big) and minor intersections,
     * label properties and a label suffix (unit).
     *
     * @brief constructor
     *
     * @param major_intersections number of big intersection lines
     * @param minor_intersections number of small intersection lines
     * @param label_prop the style of the label text
     * @param label_suffix the unit of the presented data
     */
    Scale(size_t _major_intersections, size_t _minor_intersections,
          const TextProperties& _label_prop, const std::string& _label_suffix = "")
    : major_intersections(_major_intersections), minor_intersections(_minor_intersections),
      label_prop(_label_prop), label_suffix(_label_suffix)
    {}

    virtual ~Scale() {}

    /** Returns the number of major intersection lines
     * of this scale.
     *
     * @brief number of big intersection lines
     *
     * @return number of major intersections
     */
    size_t get_major_intersections(void) const
    {
        return major_intersections;
    }

    /** Returns the number of major intersection lines
     * of this scale.
     *
     * @brief number of small intersection lines
     *
     * @return number of minor intersections
     */
	size_t get_minor_intersections(void) const
	{
		return minor_intersections;
	}
protected:
	size_t major_intersections;
	size_t minor_intersections;
	TextProperties label_prop;
	std::string label_suffix;
};

/** A Scale that represents a graphical axis that can
 * display data from the real numbers with two given
 * extremes.
 *
 * @brief a 1-dimensional scale
 *
 * @author stratmann
 * @date 15.05.2018
 */
class SimpleScale: public Scale
{
public:
	/** Creates a new SimpleScale from major (big) and minor intersections,
     * label properties, label suffix (unit) and extreme values.
	 *
	 * @brief constructor
     *
     * @param major_intersections number of big intersection lines
     * @param minor_intersections number of small intersection lines
     * @param extremes the extreme values of the scale
     * @param label_prop the style of the label text
     * @param label_suffix the unit of the presented data
	 */
	SimpleScale(size_t _major_intersections, size_t _minor_intersections,
			  const std::pair<double, double>& _extremes,
			  const TextProperties& _label_prop, const std::string& _label_suffix = "")
	    : Scale(_major_intersections, _minor_intersections, _label_prop, _label_suffix),
		  extremes(_extremes)
	{}

	/** Access function for the Ticks extreme values.
	 *
	 * @brief extreme_vals
	 *
	 * @return a reference to the extreme values
	 */
	inline const std::pair<double,double> & get_extremes() const
	{
		return extremes;
	}

	/** Constructs description labels from the
	 *
	 * @brief make description labels
	 *
	 * @return the labels
	 */
	std::vector<Label> make_labels(void) const;

private:
	std::pair<double, double> extremes;
};

/** A Scale that represents a graphical axis that can
 * display data from the R^n with two given extremes for
 * each entry.
 *
 * @brief a n-dimensional scale
 *
 * @author stratmann
 * @date 15.05.2018
 */
class MultiScale: public Scale
{
public:
	/** Creates a new MultiScale from major (big) and minor intersections,
	 * label properties, label suffix (unit) and extreme values.
	 * To use MultiScale, extreme values of each entry need to be
	 * added.
	 *
	 * @brief constructor
	 *
	 * @param major_intersections number of big intersection lines
	 * @param minor_intersections number of small intersection lines
	 * @param label_prop the style of the label text
	 * @param label_suffix the unit of the presented data
	 */
	MultiScale(size_t ticks_major, size_t ticks_minor,
	          const TextProperties& label_prop, const std::string& label_suffix = "")
	: Scale(ticks_major, ticks_minor, label_prop, label_suffix)
	{}

	/** Adds extreme value of another scalable entry to this MultiScale.
	 *
	 * @brief adds scale
	 *
	 * @param extremes the extreme values
	 */
	inline void add_scale(const std::pair<double, double>& extremes)
	{
		_extremes.push_back(extremes);
	}

	/** Returns the number of scales of this MultiScale.
	 *
	 * @brief gets the number of scales
	 *
	 * @return number of scales
	 */
	inline size_t get_scale_number(void) const
	{
		return _extremes.size();
	}

	/** Returns the extreme values of the i-th entry.
	 *
	 * @brief gets the i-th extremes
	 *
	 * @return the extremes
	 */
	inline const std::pair<double, double> get_extremes(size_t i) const
	{
		return _extremes[i];
	}

	/** Constructs description labels from the
	 *
	 * @brief make description labels
	 *
	 * @return the labels
	 */
	std::vector<Label> make_labels(size_t i) const;

private:
	std::vector<std::pair<double, double>> _extremes;
};

/** Creates an interval with rounded values. For this
 * pair (a,b) is a <= min, max <= b.
 *
 * @brief rounded interval
 *
 * @param min the lowest value
 * @param max the largest value
 *
 * @return the rounded interval
 */
std::pair<double, double> create_rounded_interval(double min, double max);

#endif /* TICKS_H_ */
