#ifndef COORDINATES_H_
#define COORDINATES_H_

#include <cmath>
#include <ostream>
#include <cassert>
#include <Utils.h>

/** A namespace for converter functions. */
namespace angle_helper
{
  /** Converts degree to radian value.
   *
   * @param deg the degree value to be converted
   *
   * @return the matching radian value
   */
  inline double
  deg_to_rad (double deg)
  {
    return deg / 180.0 * M_PI;
  }

  /** Converts radian to degree value.
   *
   * @param rad the radian value to be converted
   *
   * @return the matching degree value
   */
  inline double
  rad_to_deg (double rad)
  {
    return rad / M_PI * 180.0;
  }

  inline double
  rad_dist (double rad0, double rad1)
  {
    return (rad0 > rad1) ? (2 * M_PI - rad0 + rad1) : (rad1 - rad0);
  }
}

/** Angle is a wrapper class for angle values. Angles are stored as radian values.
 * For consistence, its value needs to be in [0,2*pi].
 *
 * @brief Mathmatical angle representation
 *
 * @author beyss
 * @date 03.07.2017
 */
class Angle
{
private:
  /** The angle value in radian */
  double m_angle;
public:
  /** Creates a Angle from an angle value. If necessary, the value is corrected
   * to be consistent.
   *
   * @brief constructor
   *
   * @param angle the angle value
   */
  Angle (double angle) :
      m_angle
	{ adjust_angle (angle) }
  {
  }

  /** Returns the value of this angle.
   *
   * @return the angle value
   */
  double
  value () const
  {
    return m_angle;
  }

  /** Assignment operator setting this Angle's value. If necessary,
   * the value is corrected to be consistent.
   *
   * @param angle the angle value in radians
   *
   * @return the adjusted angle value
   */
  double
  operator= (double angle)
  {
    m_angle = adjust_angle (angle);
    return m_angle;
  }

  /** Equal to operator checking wether this Angle's value
   * is equal to the other Angle's value.
   *
   * @param rhs the other Angle
   *
   * @return if equal or not
   */
  bool
  operator== (const Angle& rhs) const
  {
    return Util::double_equal (m_angle, rhs.m_angle);
  }

  /** Smaller than operator checking wether this Angle's value
   * is smaller than the other Angle's value.
   *
   * @param rhs the other Angle
   *
   * @return if smaller than or not
   */
  bool
  operator< (const Angle& rhs) const
  {
    return m_angle < rhs.m_angle;
  }

  /** Smaller than or equal to operator checking wether this Angle's
   * value is smaller than or equal to the other Angle's value.
   *
   * @param rhs the other Angle
   *
   * @return if smaller than or equal or not
   */
  bool
  operator<= (const Angle& rhs) const
  {
    return m_angle <= rhs.m_angle;
  }

  /** Greater than operator checking wether this Angle's value
   * is greater than the other Angle's value.
   *
   * @param rhs the other Angle
   *
   * @return if greater than or not
   */
  bool
  operator> (const Angle& rhs) const
  {
    return m_angle > rhs.m_angle;
  }

  /** Greater than or equal to operator checking wether this Angle's
   * value is smaller than or equal to the other Angle's value.
   *
   * @param rhs the other Angle
   *
   * @return if greater than or equal or not
   */
  bool
  operator>= (const Angle& rhs) const
  {
    return m_angle >= rhs.m_angle;
  }

  /** Addition assignment operator increasing this Angle's value by
   * the other Angle's value. If necessary, the value is corrected
   * to be consistent.
   *
   * @param rhs the other Angle
   *
   * @return a reference to this angle
   */
  Angle&
  operator+= (const Angle& rhs)
  {
    m_angle = adjust_angle (m_angle + rhs.m_angle);
    return *this;
  }

  /** Friend addition operator returning an Angle equal to the return of this += rhs.
   * It operates on a copy of lhs so that the original object is not changed.
   *
   * @brief this + rhs
   *
   * @param rhs the right operand Angle
   *
   * @return a new Angle equal to this + rhs
   */
  Angle
  operator+ (const Angle& rhs) const
  {
    return m_angle + rhs.m_angle;
  }

  /** Subtraction assignment operator decreasing this Angle's value by
   * the other Angle's value. If necessary, the value is corrected
   * to be consistent.
   *
   * @param rhs the other angle
   *
   * @return a reference to this angle
   */
  Angle&
  operator-= (const Angle& rhs)
  {
    m_angle = adjust_angle (m_angle - rhs.m_angle);
    return *this;
  }

  /** Friend addition operator returning an Angle equal to the return of this - rhs.
   * It operates on a copy of lhs so that the original object is not changed.
   *
   * @brief this - rhs
   *
   * @param rhs the right operand Angle
   *
   * @return a new Angle equal to this - rhs
   */
  Angle
  operator- (const Angle& rhs) const
  {
    return m_angle - rhs.m_angle;
  }

  /** Multiplication assignment operator multiplying this Angle's value with the given
   * double value. If necessary, the value is corrected to be consistent.
   *
   * @param rhs the factor
   *
   * @return a reference to this angle
   */
  Angle&
  operator*= (double val)
  {
    m_angle = adjust_angle (m_angle * val);
    return *this;
  }

  /** Multiplication operator returning an Angle with the value of adjusted
   * this * val.
   *
   * @param val the factor
   *
   * @return a new Angle equal to this * val
   */
  Angle
  operator* (double val) const
  {
    return m_angle * val;
  }

  /** Division assignment operator divides this Angle's value by the given
   * double value. If necessary, the value is corrected to be consistent.
   *
   * @param val the dividend
   *
   * @return a reference to this angle
   */
  Angle&
  operator/= (double val)
  {
    m_angle = adjust_angle (m_angle / val);
    return *this;
  }

  /** Division operator returning an Angle with the value of adjusted
   * this / val.
   *
   * @param val the dividend
   *
   * @return a new Angle equal to this / val
   */
  Angle
  operator/ (double val)
  {
    return m_angle / val;
  }

  /** Returns an Angle that is (1-p) percent of a1 and p percent
   * of a2. To be consistent, p should be in [0,1].
   *
   * @param a1 the first angle
   * @param a2 the second angle
   * @param p the percentage
   *
   * @return the interpolated Angle
   */
  static Angle
  interpolate (const Angle& a1, const Angle& a2, double p)
  {
    //p has to be between 0 (p1) and 1(p2)
    double phi = (1 - p) * a1.value () + p * a2.value ();
    return Angle (phi);
  }

  /** Returns the Angle in the center of two given Angles.
   *
   * @param a1 the first Angle
   * @param a2 the second Angle
   *
   * @return the centered Angle
   */
  static Angle
  center (const Angle& a1, const Angle& a2)
  {
    return interpolate (a1, a2, 0.5);
  }

private:
  /** Assures the consistence of this Angle's value (in [0, 2*pi]).
   */
  static double
  adjust_angle (double angle)
  {
    angle = std::fmod (angle, 2.0 * M_PI);
    if (angle < 0)
      angle += 2.0 * M_PI;
    return angle;
  }
};

/** Polar represents a tupel from C in polar coordinate form.
 *
 * @brief Polar coordinate representation
 * 
 * @authors beyss, stratmann
 * @date 03.07.2018
 */
class Polar
{
private:
  /** Radius, the euclidian distance from the coordinate null */
  double m_radius;
  /** Angle (from x-achsis) */
  Angle m_angle;
public:
  /** Creates a Polar coordinate from a given radius and angle.
   *
   * @param r the radius
   * @param phi the angle
   */
  Polar (double radius = 0, Angle angle = 0) :
      m_radius
	{ radius }, m_angle
	{ angle }
  {
  }

  /** Equal to operator checking for equality of radius and angle.
   *
   * @param rhs the other Polar
   *
   * @return if equal or not
   */
  bool
  operator== (const Polar& rhs) const
  {
    return (m_radius == rhs.radius ()) && (m_angle == rhs.angle ());
  }

  /** Access function for this Polar's radius as readonly.
   *
   * @return a constant reference to this Polar's radius
   */
  const double&
  radius () const
  {
    return m_radius;
  }

  /** Access function for this Polar's radius.
   *
   * @return a reference to this Polar's radius
   */
  double&
  radius ()
  {
    return m_radius;
  }

  /** Access function for this Polar's m_angle readonly.
   *
   * @return a constant reference to the Angle
   */
  const Angle&
  angle () const
  {
    return m_angle;
  }

  /** Access function for this Polar's m_angle.
   *
   * @return a reference to the Angle
   */
  Angle&
  angle ()
  {
    return m_angle;
  }

  /** Returns an Polar whose radius and Angle are (1-p) percent of p1's
   * and p percent of p2's radius and Angle. To be consistent, p should be in [0,1].
   *
   * @brief interpolate
   *
   * @param p1 the first Polar
   * @param p2 the second Polar
   * @param p the percentage
   *
   * @return the interpolated Polar
   */
  static Polar
  interpolate (const Polar& p1, const Polar& p2, double p)
  {
    // p has to be between 0 (p1) and 1 (p2)
    assert(p >= 0 && p <= 1);

    double r = (1 - p) * p1.radius () + p * p2.radius ();
    return Polar (r, Angle::interpolate (p1.angle (), p2.angle (), p));
  }

  /** Returns a Polar centered between two given Polars.
   *
   * @brief center
   *
   * @param p1 the first Polar
   * @param p2 the second Polar
   *
   * @return the centered Polar
   */
  static Polar
  center (const Polar& p1, const Polar& p2)
  {
    return interpolate (p1, p2, 0.5);
  }
};

/** Cartesian represents a tupel from the R² as cartesian coordinate.
 *
 * @brief The Cartesian class
 */
class Cartesian
{
private:
  /** Positions on the x-/y-achsis */
  double m_x, m_y;
public:
  /** Creates a cartesian coordinate from given x and y value.
   *
   * @brief Cartesian
   *
   * @param x the x value
   * @param y the y value
   */
  Cartesian (double x = 0, double y = 0) :
      m_x
	{ x }, m_y
	{ y }
  {
  }

  /** Equal to operator checking for equality of x and y.
   *
   * @brief operator ==
   *
   * @param rhs the other Cartesian
   *
   * @return if equal or not
   */
  bool
  operator== (const Cartesian& rhs) const
  {
    return (m_x == rhs.x ()) && (m_y == rhs.y ());
  }

  /** Access function for this Cartesian's x value as readonly.
   *
   * @brief x
   *
   * @return a constant reference to this Cartesians x value
   */
  const double&
  x () const
  {
    return m_x;
  }

  /** Access function for this Cartesian's x value.
   *
   * @brief x
   *
   * @return a reference to this Cartesians x value
   */
  double&
  x ()
  {
    return m_x;
  }

  /** Access function for this Cartesian's y value as readonly.
   *
   * @brief y
   *
   * @return a constant reference to this Cartesians y value
   */
  const double&
  y () const
  {
    return m_y;
  }

  /** Access function for this Cartesian's y value.
   *
   * @brief y
   *
   * @return a reference to this Cartesians y value
   */
  double&
  y ()
  {
    return m_y;
  }

  /** Returns an Cartesian whose radius and Angle are (1-p) percent of p1's
   * and p percent of p2's radius and Angle. To be consistent, p should be in [0,1].
   *
   * @brief interpolate
   *
   * @param p1 the first Cartesian
   * @param p2 the second Cartesian
   * @param p the percentage
   *
   * @return the interpolated Cartesian
   */
  static Cartesian
  interpolate (const Cartesian& p1, const Cartesian& p2, double p)
  {
    //p has to be between 0 (p1) and 1(p2)
    return Cartesian ((1 - p) * p1.x () + p * p2.x (),
		      (1 - p) * p1.y () + p * p2.y ());
  }

  /** Returns a Cartesian centered between two given Cartesian.
   *
   * @brief center
   *
   * @param p1 the first Cartesian
   * @param p2 the second Cartesian
   *
   * @return the centered Cartesian
   */
  static Cartesian
  center (const Cartesian& p1, const Cartesian& p2)
  {
    return interpolate (p1, p2, 0.5);
  }
};

/** CoordinateConverter simulates a fixed width/height coordinate system.
 * It can convert polar and cartesian coordinates.
 *
 * @brief Converter between polar and cartesian coordinates
 */
class CoordinateConverter
{
private:
  /** Width and height of the coordinate system */
  size_t m_width, m_height;
  /** Center coordinate of the coordinate system */
  double m_center_x, m_center_y;
public:
  /** Creates a new coordinate system with given width and height.
   * The center coordinate is at (width / 2, height / 2).
   *
   * @brief a converter for coordinates
   *
   * @param width the coordinate system width
   * @param height the coordinate system system
   */
  CoordinateConverter (size_t width, size_t height) :
      m_width
	{ width }, m_height
	{ height }, m_center_x
	{ width / 2.0 }, m_center_y
	{ height / 2.0 }
  {
  }

  /** Converts a Cartesian coordinate to a Polar coordinate.
   *
   * @param from the Cartesian to convert
   * @param to the Polar to store
   */
  inline void
  convert (const Cartesian& from, Polar& to) const
  {
    double x
      { from.x () - m_center_x };
    double y
      { m_center_y - from.y () };
    to.radius () = std::hypot (x, y);
    to.angle () = std::atan2 (y, x);
  }

  /** Converts a Polar coordinate to a Cartesian coordinate.
   *
   * @param from the Polar to convert
   * @param to the Polar to store
   */
  inline void
  convert (const Polar& from, Cartesian& to) const
  {

    double x
      { from.radius () * std::cos (from.angle ().value ()) };
    double y
      { -from.radius () * std::sin (from.angle ().value ()) };
    to.x () = x + m_center_x;
    to.y () = y + m_center_y;
  }

  /** Returns the x value of the center coordinate.
   *
   * @return the center's x value
   */
  double
  get_center_x () const
  {
    return m_center_x;
  }

  /** Returns the y value of the center coordinate.
   *
   * @return the center's y value
   */
  double
  get_center_y () const
  {
    return m_center_y;
  }
};

/* ostream operators */

inline std::ostream&
operator<< (std::ostream& stream, const Angle& angle)
{
  stream << angle_helper::rad_to_deg (angle.value ()) << "°";
  return stream;
}

inline std::ostream&
operator<< (std::ostream& stream, const Polar& coord)
{
  stream << "[ r: " << coord.radius () << ", phi: " << coord.angle () << " ]";
  return stream;
}

inline std::ostream&
operator<< (std::ostream& stream, const Cartesian& coord)
{
  stream << "[ x: " << coord.x () << ", y: " << coord.y () << " ]";
  return stream;
}


#endif /* POLARCARTESIAN_H_ */
