/*
 * PolarCartesian.h
 *
 *  Created on: 03.07.2017
 *      Author: beyss
 */

#ifndef POLARCARTESIAN_H_
#define POLARCARTESIAN_H_

#include <cmath>
#include <ostream>
#include <iostream>

/** A namespace for converter functions. */
namespace angle_helper
{
    /** Converts degree to radian value.
     * @brief deg_to_rad
     * @param deg the degree value to be converted
     * @return the matching radian value
     */
    inline double deg_to_rad(double deg)
    {
        return deg / 180.0 * M_PIl;
    }

    /** Converts radian to degree value.
     * @brief rad_to_deg
     * @param rad the radian value to be converted
     * @return the matching degree value
     */
    inline double rad_to_deg(double rad)
    {
        return rad / M_PIl * 180.0;
    }
}

/** Angle is a wrapper class for angle values. Angles are stored as radian values.
 * For consistence, its value needs to be in [0,2*pi].
 * @brief The Angle class
 * @author beyss
 * @date 03.07.2017
 */
class Angle
{
public:
    /** Creates a Angle from an angle value. If necessary, the value is corrected
     * to be consistent.
     * @brief Angle
     * @param angle the angle value
     */
    Angle(double angle)
    : _angle { angle }
    {
        wrap();
    }

    /** Returns the value of this angle.
     * @brief get
     * @return the angle value
     */
    double get() const
    {
        return _angle;
    }

    /** Assignment operator setting this Angle's value. If necessary,
     * the value is corrected to be consistent.
     * @brief operator =
     * @param angle
     * @return
     */
    double operator=(const double& angle)
    {
        _angle = angle;
        wrap();
        return _angle;
    }

    /** Equal to operator checking wether this Angle's value
     * is equal to the other Angle's value.
     * @brief operator ==
     * @param rhs the other Angle
     * @return if equal or not
     */
    bool operator==(const Angle& rhs) const
    {
        return (get() == rhs.get());
    }

    /** Smaller than operator checking wether this Angle's value
     * is smaller than the other Angle's value.
     * @brief operator <
     * @param rhs the other Angle
     * @return if smaller than or not
     */
    bool operator<(const Angle& rhs) const
    {
        return ((*this - rhs).get() < 0) ;
    }

    /** Smaller than or equal to operator checking wether this Angle's
     * value is smaller than or equal to the other Angle's value.
     * @brief operator <=
     * @param rhs the other Angle
     * @return if smaller than or equal or not
     */
    bool operator<=(const Angle& rhs) const
    {
        return ((*this - rhs).get() <= 0) ;
    }

    /** Greater than operator checking wether this Angle's value
     * is greater than the other Angle's value.
     * @brief operator ==
     * @param rhs the other Angle
     * @return if greater than or not
     */
    bool operator>(const Angle& rhs) const
    {
        return ((*this - rhs).get() > 0) ;
    }

    /** Greater than or equal to operator checking wether this Angle's
     * value is smaller than or equal to the other Angle's value.
     * @brief operator >=
     * @param rhs the other Angle
     * @return if greater than or equal or not
     */
    bool operator>=(const Angle& rhs) const
	{
		return ((*this - rhs).get() >= 0) ;
	}

    /** Addition assignment operator increasing this Angle's value by
     * the other Angle's value. If necessary, the value is corrected
     * to be consistent.
     * @brief operator +=
     * @param rhs the other Angle
     * @return a reference to this angle
     */
    Angle& operator+=(const Angle& rhs)
    {
        _angle += rhs.get();
        wrap();
        return *this;
    }

    /** Friend addition operator returning an Angle equal to the return of rhs += lhs.
     * It operates on a copy of lhs so that the original object is not changed.
     * @brief operator +
     * @param lhs the left operand Angle
     * @param rhs the right operand Angle
     * @return a new Angle equal to lhs+=rhs
     */
    friend Angle operator+(Angle lhs, const Angle& rhs)
    {
        lhs += rhs; // reuse compound assignment
        return lhs; // return the result by value (uses move constructor)
    }

    /** Subtraction assignment operator decreasing this Angle's value by
     * the other Angle's value. If necessary, the value is corrected
     * to be consistent.
     * @brief operator +=
     * @param rhs the other angle
     * @return a reference to this angle
     */
    Angle& operator-=(const Angle& rhs)
    {
        _angle -= rhs.get();
        wrap();
        return *this;
    }

    /** Friend addition operator returning an Angle equal to the return of rhs -= lhs.
     * It operates on a copy of lhs so that the original object is not changed.
     * @brief operator +
     * @param lhs the left operand Angle
     * @param rhs the right operand Angle
     * @return a new Angle equal to lhs-=rhs
     */
    friend Angle operator-(Angle lhs, const Angle& rhs)
    {
        lhs -= rhs; // reuse compound assignment
        return lhs; // return the result by value (uses move constructor)
    }

    /** Multiplication assignment operator multiplying this Angle's value with the given
     * double value. If necessary, the value is corrected to be consistent.
     * @brief operator *=
     * @param rhs the factor
     * @return a reference to this angle
     */
    Angle& operator*=(const double& rhs)
    {
        _angle *= rhs;
        wrap();
        return *this;
    }

    /** Friend multiplication operator returning an Angle equal to the return of rhs *= lhs.
     * It operates on a copy of lhs so that the original object is not changed.
     * @brief operator *
     * @param lhs the Angle to multiply
     * @param rhs the factor
     * @return a new Angle equal to lhs*=rhs
     */
    friend Angle operator*(Angle lhs, const double& rhs)
    {
        lhs *= rhs; // reuse compound assignment
        return lhs; // return the result by value (uses move constructor)
    }

    /** Division assignment operator divides this Angle's value by the given
     * double value. If necessary, the value is corrected to be consistent.
     * @brief operator /=
     * @param rhs the dividend
     * @return a reference to this angle
     */
    Angle& operator/=(const double& rhs)
    {
        _angle /= rhs;
        wrap();
        return *this;
    }

    /** Friend division operator returning an Angle equal to the return of rhs /= lhs.
     * It operates on a copy of lhs so that the original object is not changed.
     * @brief operator /=
     * @param lhs the Angle to divide
     * @param rhs the dividend
     * @return a new Angle equal to lhs/=rhs
     */
    friend Angle operator/(Angle lhs, const double& rhs)
    {
        lhs /= rhs; // reuse compound assignment
        return lhs; // return the result by value (uses move constructor)
    }

    /** Returns an Angle that is (1-p) percent of a1 and p percent
     * of a2. To be consistent, p should be in [0,1].
     * @brief interpolate
     * @param a1 the first angle
     * @param a2 the second angle
     * @param p the percentage
     * @return the interpolated Angle
     */
    static Angle interpolate(const Angle& a1, const Angle& a2, double p)
    {
        //p has to be between 0 (p1) and 1(p2)
        double phi = (1-p) * a1.get() + p * a2.get();
        Angle temp(phi);
        if (std::abs((a1 - temp).get()) > std::abs((a1 - (temp + M_PI)).get()))
        {
                return temp + M_PI;
        }
        else
                return temp;
	}

    /** Returns the Angle in the center of two given Angles.
     * @brief center
     * @param a1 the first Angle
     * @param a2 the second Angle
     * @return the centered Angle
     */
    static Angle center(const Angle& a1, const Angle& a2)
    {
        return interpolate(a1, a2, 0.5);
    }

private:
        /** Assures the consistence of this Angle's value (in [0, 2*pi]).
         * @brief wrap
         */
	void wrap()
	{
//		double old = _angle;
		_angle = std::remainder(_angle, 2.0 * M_PI);
//		if (old != _angle)
//			std::cout << "wrap: " << angle_helper::rad_to_deg(old) << " -> " << angle_helper::rad_to_deg(_angle) << std::endl;
	}

        /** The angle value in radian */
	double _angle;
};

/** Polar represents a tupel from the R² in polar coordinate form.
 * @brief The Polar class
 */
class Polar
{
public:
    /** Creates a Polar coordinate from a given radius and angle.
     * @brief Polar
     * @param r the radius
     * @param phi the angle
     */
    Polar(double r = 0, Angle phi = 0)
    : _r { r }, _phi { phi }
    {
    }

    /** Equal to operator checking for equality of radius and angle.
     * @brief operator ==
     * @param rhs the other Polar
     * @return if equal or not
     */
    bool operator==(const Polar& rhs) const
    {
        return (r() == rhs.r()) && (phi() == rhs.phi());
    }

    /** Access function for this Polar's radius as readonly.
     * @brief r
     * @return a constant reference to this Polar's radius
     */
    const double& r() const
    {
        return _r;
    }

    /** Access function for this Polar's radius.
     * @brief r
     * @return a reference to this Polar's radius
     */
    double& r()
    {
        return _r;
    }

    /** Access function for this Polar's angle readonly.
     * @brief phi
     * @return a constant reference to the Angle
     */
    const Angle& phi() const
    {
        return _phi;
    }

    /** Access function for this Polar's angle.
     * @brief phi
     * @return a reference to the Angle
     */
    Angle& phi()
    {
        return _phi;
    }

    /** Returns an Polar whose radius and Angle are (1-p) percent of p1's
     * and p percent of p2's radius and Angle. To be consistent, p should be in [0,1].
     * @brief interpolate
     * @param p1 the first Polar
     * @param p2 the second Polar
     * @param p the percentage
     * @return the interpolated Polar
     */
    static Polar interpolate(const Polar& p1, const Polar& p2, double p)
    {
        //p has to be between 0 (p1) and 1(p2)
        double r = (1-p) * p1.r() + p * p2.r();
        return Polar(r,Angle::interpolate(p1.phi(), p2.phi(), p));
    }

    /** Returns a Polar centered between two given Polars.
     * @brief center
     * @param p1 the first Polar
     * @param p2 the second Polar
     * @return the centered Polar
     */
    static Polar center(const Polar& p1, const Polar& p2)
    {
        return interpolate(p1, p2, 0.5);
    }
private:
    /** Radius, the euclidian distance from the coordinate null */
    double _r;
    /** Angle (from x-achsis) */
    Angle _phi;
};

/** Cartesian represents a tupel from the R² as cartesian coordinate.
 * @brief The Cartesian class
 */
class Cartesian
{
public:
    /** Creates a cartesian coordinate from given x and y value.
     * @brief Cartesian
     * @param x the x value
     * @param y the y value
     */
    Cartesian(double x = 0, double y = 0)
    : _x { x }, _y { y }
    {
    }

    /** Equal to operator checking for equality of x and y.
     * @brief operator ==
     * @param rhs the other Cartesian
     * @return if equal or not
     */
    bool operator==(const Cartesian& rhs) const
    {
        return (x() == rhs.x()) && (y() == rhs.y());
    }

    /** Access function for this Cartesian's x value as readonly.
     * @brief x
     * @return a constant reference to this Cartesians x value
     */
    const double& x() const
    {
        return _x;
    }

    /** Access function for this Cartesian's x value.
     * @brief x
     * @return a reference to this Cartesians x value
     */
    double& x()
    {
        return _x;
    }

    /** Access function for this Cartesian's y value as readonly.
     * @brief y
     * @return a constant reference to this Cartesians y value
     */
    const double& y() const
    {
        return _y;
    }

    /** Access function for this Cartesian's y value.
     * @brief y
     * @return a reference to this Cartesians y value
     */
    double& y()
    {
        return _y;
    }

    /** Returns an Cartesian whose radius and Angle are (1-p) percent of p1's
     * and p percent of p2's radius and Angle. To be consistent, p should be in [0,1].
     * @brief interpolate
     * @param p1 the first Cartesian
     * @param p2 the second Cartesian
     * @param p the percentage
     * @return the interpolated Cartesian
     */
    static Cartesian interpolate(const Cartesian& p1, const Cartesian& p2, double p)
    {
        //p has to be between 0 (p1) and 1(p2)
        return Cartesian((1-p) * p1.x() + p * p2.x(), (1-p) * p1.y() + p * p2.y());
    }

    /** Returns a Cartesian centered between two given Cartesian.
     * @brief center
     * @param p1 the first Cartesian
     * @param p2 the second Cartesian
     * @return the centered Cartesian
     */
    static Cartesian center(const Cartesian& p1, const Cartesian& p2)
    {
        return interpolate(p1, p2, 0.5);
    }
private:
    /** Positions on the x-/y-achsis */
    double _x, _y;
};

/** PolarCartesian simulates a fixed width/height coordinate system.
 * It can convert polar and cartesian coordinates.
 * @brief The PolarCartesian class
 */
class PolarCartesian
{
public:
    /** Creates a new coordinate system with given width and height.
     * The middle coordinate is (width / 2, height / 2).
     * @brief PolarCartesian
     * @param width the coordinate system width
     * @param height the coordinate system system
     */
    PolarCartesian(size_t width, size_t height)
    : width { width }, height { height }, center_x { width / 2.0 }, center_y { height / 2.0 }
    {
    }

    virtual ~PolarCartesian() {}

    /** Converts a cartesian coordinate to a polar coordinate.
     * @brief convert
     * @param from the Cartesian to convert
     * @param to the Polar to store
     */
    inline void convert(const Cartesian& from, Polar& to) const
    {
            double x { from.x() - center_x };
            double y { from.y() - center_y };
            to.r() = std::hypot(x, y);
            to.phi() = std::atan2(y, x);
    }

    /** Converts a polar coordinate to a cartesian coordinate.
     * @brief convert
     * @param from the Polar to convert
     * @param to the Polar to store
     */
    inline void convert(const Polar& from, Cartesian& to) const
    {
            double x { from.r() * std::cos(from.phi().get()) };
            double y { from.r() * std::sin(from.phi().get()) };
            to.x() = x + center_x;
            to.y() = y + center_y;
    }

    /** Returns the center as cartesian coordinate.
     * @brief center
     * @return the center coordinate
     */
    Cartesian center() const
    {
        return Cartesian(center_x, center_y);
    }
private:
    /** Width and height of the coordinate system */
    const size_t width, height;
    /** Center coordinate of the coordinate system */
    const double center_x, center_y;
};

/* ostream operatoren */

inline std::ostream& operator<<(std::ostream& stream, const Angle& angle)
{
	stream << angle_helper::rad_to_deg(angle.get()) << "°";
	return stream;
}

inline std::ostream& operator<<(std::ostream& stream, const Polar& coord)
{
	stream << "[ r: " << coord.r() << ", phi: " << coord.phi() << " ]";
	return stream;
}

inline std::ostream& operator<<(std::ostream& stream, const Cartesian& coord)
{
	stream << "[ x: " << coord.x() << ", y: " << coord.y() << " ]";
	return stream;
}


#endif /* POLARCARTESIAN_H_ */
