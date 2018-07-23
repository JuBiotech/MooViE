#ifndef COLOR_H_
#define COLOR_H_

#include <array>
#include <Utils.h>

/** Color class represents a color by RGB and alpha value.
 *
 * @brief RGB color representation
 *
 * @authors beyss, stratmann
 * @date 27.07.2017
 */
class Color
{
public:
  /** A Color constant representing black (0,0,0,1) */
  static const Color BLACK;
private:
  /** double constants representing RGBA value. */
  double m_r, m_g, m_b, m_a;
public:
  /** Creates a Color from RGB and Alpha values.
   *
   * @param r the red value
   * @param g the green value
   * @param b the blue value
   * @param a the alpha value
   */
  Color (double r = 0, double g = 0, double b = 0, double a = 1) :
      m_r
	{ limit (r) }, m_g
	{ limit (g) }, m_b
	{ limit (b) }, m_a
	{ limit (a) }
  {
  }

  Color (const Color& c, double a) :
      m_r
	{ limit (c.m_r) }, m_g
	{ limit (c.m_g) }, m_b
	{ limit (c.m_b) }, m_a
	{ limit (a) }
  {
  }

  /** Access function for the color's red value.
   *
   * @return a reference to the colors red value
   */
  const double&
  r () const
  {
    return m_r;
  }

  /** Access function for the color's green value.
   *
   * @return a reference to the colors green value
   */
  const double&
  g () const
  {
    return m_g;
  }

  /** Access function for the color's blue value.
   *
   * @return a reference to the colors blue value
   */
  const double&
  b () const
  {
    return m_b;
  }

  /** Access function for the color's alpha value.
   *
   * @return a reference to the colors alpha value
   */
  const double&
  a () const
  {
    return m_a;
  }

  /** Checks whether or not two colors are equal.
   * This is the case if RGBA values are the same.
   *
   * @param color the other color
   *
   * @return equal or not
   */
  bool
  operator== (const Color& color) const
  {
    return Util::double_equal (m_r, color.m_r)
	&& Util::double_equal (m_g, color.m_g)
	&& Util::double_equal (m_b, color.m_b)
	&& Util::double_equal (m_a, color.m_a);
  }

  /** Checks whether or not two colors are not equal.
   * Two colors would be equal if their RGBA values
   * were the same.
   *
   * @param color the other color
   *
   * @return not equal or equal
   */
  bool
  operator!= (const Color& color) const
  {
    return not Util::double_equal (m_r, color.m_r)
	|| not Util::double_equal (m_g, color.m_g)
	|| not Util::double_equal (m_b, color.m_b)
	|| not Util::double_equal (m_a, color.m_a);
  }

  /** Sets the red value of this Color.
   * Input values from 0 to 255 will be automatically corrected
   * to values from [0,1].
   *
   * @param red the red value to set
   */
  void
  set_red (double red)
  {
    m_r = limit (red);
  }

  /** Sets the green value of this Color.
   * Input values from 0 to 255 will be automatically corrected
   * to values from [0,1].
   *
   * @param green the green value to set
   */
  void
  set_green (double green)
  {
    m_g = limit (green);
  }

  /** Sets the blue value of this Color.
   * Input values from 0 to 255 will be automatically corrected
   * to values from [0,1].
   *
   * @param blue the blue value to set
   */
  void
  set_blue (double blue)
  {
    m_b = limit (blue);
  }

  /** Sets the alpha value of this Color.
   * Input values from 0 to 255 will be automatically corrected
   * to values from [0,1].
   *
   * @param alpha the alpha value to set
   */
  void
  set_alpha (double alpha)
  {
    m_a = limit (alpha);
  }

  /** Puts string representation of Color c to the output stream o.
   *
   * @param o the ostream to put into
   * @param c the color to put
   */
  friend std::ostream&
  operator<< (std::ostream& o, const Color& c)
  {
    return o << "[r=" << c.m_r << ", g=" << c.m_g << ", b=" << c.m_b << ", a="
	<< c.m_a << "]";
  }

private:
  /** Corrects an input value to be from [0,1].
   * Used for correcting alpha values.
   *
   * @param val the value to correct
   *
   * @return the corrected value
   */
  double
  limit (const double& val)
  {
    double temp_val = val;
    if (uint8_t (temp_val) == temp_val && temp_val > 1.0)
      temp_val /= 255.0;
    return std::max (std::min (temp_val, 1.0), 0.0);
  }
};

#endif /* COLOR_H_ */
