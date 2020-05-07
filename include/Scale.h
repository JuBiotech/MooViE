#ifndef SCALE_H_
#define SCALE_H_

#include <cmath>
#include <cstddef>
#include <vector>
#include <sstream>
#include <Label.h>

/** Creates an interval with rounded values. For this
 * pair (a,b) is a <= min, max <= b.
 *
 * @param min the lowest value
 * @param max the largest value
 *
 * @return the rounded interval
 */
std::pair<double, double>
create_rounded_interval (double min, double max);


/** The Scale class represents a graphical scale of an axis
 * by its extreme values and intersections counts.
 *
 * @brief Ticked scale
 *
 * @author beyss
 * @date 22.08.2017
 */
class Scale
{
protected:
  size_t m_major_intersections;
  size_t m_minor_intersections;
  TextProperties m_label_prop;
  std::string m_label_suffix;
public:
  /** Creates a Scale from major (big) and minor intersections,
   * label properties and a label suffix (unit).
   *
   * @param major_intersections number of big intersection lines
   * @param minor_intersections number of small intersection lines
   * @param label_prop the style of the label text
   * @param label_suffix the unit of the presented data
   */
  Scale (size_t major_intersections, size_t minor_intersections,
	 const TextProperties& label_prop, const std::string& label_suffix = "") :
      m_major_intersections (major_intersections), m_minor_intersections (
	  minor_intersections), m_label_prop (label_prop), m_label_suffix (
	  label_suffix)
  {
  }

  virtual
  ~Scale ()
  {
  }

  /** Returns the number of major intersection lines
   * of this scale.
   *
   * @return number of major intersections
   */
  size_t
  get_major_intersections (void) const
  {
    return m_major_intersections;
  }

  /** Returns the number of major intersection lines
   * of this scale.
   *
   * @return number of minor intersections
   */
  size_t
  get_minor_intersections (void) const
  {
    return m_minor_intersections;
  }
};

/** A Scale that represents a graphical axis that can
 * display data from the real numbers with two given
 * extremes.
 *
 * @author stratmann
 * @date 15.05.2018
 */
class SimpleScale : public Scale
{
private:
  std::pair<double, double> m_extremes;
public:
  /** Creates a new SimpleScale from major (big) and minor intersections,
   * label properties, label suffix (unit) and extreme values.
   *
   * @param major_intersections number of big intersection lines
   * @param minor_intersections number of small intersection lines
   * @param extremes the extreme values of the scale
   * @param label_prop the style of the label text
   * @param label_suffix the unit of the presented data
   */
  SimpleScale (size_t major_intersections, size_t minor_intersections,
	       const std::pair<double, double>& extremes,
	       const TextProperties& label_prop,
	       const std::string& label_suffix = "") :
      Scale (major_intersections, minor_intersections, label_prop,
	     label_suffix), m_extremes (create_rounded_interval(extremes.first, extremes.second))
  {
  }

  /** Access function for the Ticks extreme values.
   *
   * @return a reference to the extreme values
   */
  inline const std::pair<double, double> &
  get_extremes () const
  {
    return m_extremes;
  }

  /** Constructs description labels from the
   *
   * @return the labels
   */
  std::vector<Label>
  make_labels (void) const;
};

/** A Scale that represents a graphical axis that can
 * display data from the R^n with two given extremes for
 * each entry.
 *
 * @author stratmann
 * @date 15.05.2018
 */
class MultiScale : public Scale
{
private:
  std::vector<std::pair<double, double>> m_extremes;
public:
  /** Creates a new MultiScale from major (big) and minor intersections,
   * label properties, label suffix (unit) and extreme values.
   * To use MultiScale, extreme values of each entry need to be
   * added.
   *
   * @param major_intersections number of big intersection lines
   * @param minor_intersections number of small intersection lines
   * @param label_prop the style of the label text
   * @param label_suffix the unit of the presented data
   */
  MultiScale (size_t ticks_major, size_t ticks_minor,
	      const TextProperties& label_prop,
	      const std::string& label_suffix = "") :
      Scale (ticks_major, ticks_minor, label_prop, label_suffix)
  {
  }

  /** Adds extreme value of another scalable entry to this MultiScale.
   *
   * @param extremes the extreme values
   */
  inline void
  add_scale (const std::pair<double, double>& extremes)
  {
    m_extremes.push_back (create_rounded_interval(extremes.first, extremes.second));
  }

  /** Returns the number of scales of this MultiScale.
   *
   * @return number of scales
   */
  inline size_t
  get_scale_number (void) const
  {
    return m_extremes.size ();
  }

  /** Returns the extreme values of the i-th entry.
   *
   * @return the extremes
   */
  inline const std::pair<double, double> &
  get_extremes (size_t i) const
  {
    return m_extremes[i];
  }

  /** Constructs description labels using the scale with the given index.
   *
   * @return the labels
   */
  std::vector<Label>
  make_labels (size_t i) const;
};

#endif /* TICKS_H_ */
