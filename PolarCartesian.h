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

namespace angle_helper
{
	inline double deg_to_rad(double deg)
	{
		return deg/180.0 * M_PIl;
	}

	inline double rad_to_deg(double rad)
	{
		return rad/M_PIl * 180.0;
	}
}

class Angle
{
public:
	Angle(double angle)
			: _angle { angle }
	{
		wrap();
	}
	double get() const
	{
		return _angle;
	}
	;
	double operator=(const double& angle)
	{
		_angle = angle;
		wrap();
		return _angle;
	}

	bool operator==(const Angle& rhs) const
	{
		return (get() == rhs.get());
	}
	bool operator<(const Angle& rhs) const
	{
		return ((*this - rhs).get() < 0) ;
	}
	bool operator<=(const Angle& rhs) const
	{
		return ((*this - rhs).get() <= 0) ;
	}
	bool operator>(const Angle& rhs) const
	{
		return ((*this - rhs).get() > 0) ;
	}
	bool operator>=(const Angle& rhs) const
	{
		return ((*this - rhs).get() >= 0) ;
	}

	Angle& operator+=(const Angle& rhs)
	{
		_angle += rhs.get();
		wrap();
		return *this;
	}
	friend Angle operator+(Angle lhs, const Angle& rhs)
	{
		lhs += rhs; // reuse compound assignment
		return lhs; // return the result by value (uses move constructor)
	}

	Angle& operator-=(const Angle& rhs)
	{
		_angle -= rhs.get();
		wrap();
		return *this;
	}
	friend Angle operator-(Angle lhs, const Angle& rhs)
	{
		lhs -= rhs; // reuse compound assignment
		return lhs; // return the result by value (uses move constructor)
	}

	Angle& operator*=(const double& rhs)
	{
		_angle *= rhs;
		wrap();
		return *this;
	}
	friend Angle operator*(Angle lhs, const double& rhs)
	{
		lhs *= rhs; // reuse compound assignment
		return lhs; // return the result by value (uses move constructor)
	}

	Angle& operator/=(const double& rhs)
	{
		_angle /= rhs;
		wrap();
		return *this;
	}
	friend Angle operator/(Angle lhs, const double& rhs)
	{
		lhs /= rhs; // reuse compound assignment
		return lhs; // return the result by value (uses move constructor)
	}

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
	static Angle center(const Angle& a1, const Angle& a2)
	{
		return interpolate(a1, a2, 0.5);
	}

private:
	void wrap()
	{
//		double old = _angle;
		_angle = std::remainder(_angle, 2.0 * M_PI);
//		if (old != _angle)
//			std::cout << "wrap: " << angle_helper::rad_to_deg(old) << " -> " << angle_helper::rad_to_deg(_angle) << std::endl;
	}
	double _angle;
};

class Polar
{
public:
	Polar(double r = 0, Angle phi = 0)
			: _r { r }, _phi { phi }
	{
	}
	bool operator==(const Polar& rhs) const
	{
		return (r() == rhs.r()) && (phi() == rhs.phi());
	}
	const double& r() const
	{
		return _r;
	}
	double& r()
	{
		return _r;
	}
	const Angle& phi() const
	{
		return _phi;
	}
	Angle& phi()
	{
		return _phi;
	}
	static Polar interpolate(const Polar& p1, const Polar& p2, double p)
	{
		//p has to be between 0 (p1) and 1(p2)
		double r = (1-p) * p1.r() + p * p2.r();
		return Polar(r,Angle::interpolate(p1.phi(), p2.phi(), p));
	}
	static Polar center(const Polar& p1, const Polar& p2)
	{
		return interpolate(p1, p2, 0.5);
	}
private:
	double _r;
	Angle _phi;
};
class Cartesian
{
public:
	Cartesian(double x = 0, double y = 0)
			: _x { x }, _y { y }
	{
	}
	bool operator==(const Cartesian& rhs) const
	{
		return (x() == rhs.x()) && (y() == rhs.y());
	}

	const double& x() const
	{
		return _x;
	}
	double& x()
	{
		return _x;
	}
	const double& y() const
	{
		return _y;
	}
	double& y()
	{
		return _y;
	}
	static Cartesian interpolate(const Cartesian& p1, const Cartesian& p2, double p)
	{
		//p has to be between 0 (p1) and 1(p2)
		return Cartesian((1-p) * p1.x() + p * p2.x(), (1-p) * p1.y() + p * p2.y());
	}
	static Cartesian center(const Cartesian& p1, const Cartesian& p2)
	{
		return interpolate(p1, p2, 0.5);
	}
private:
	double _x;
	double _y;
};

class PolarCartesian
{
public:
	PolarCartesian(size_t width, size_t height)
			: width { width }, height { height }, center_x { width / 2.0 }, center_y {
					height / 2.0 }
	{
	}
	;
	virtual ~PolarCartesian()
	{
	}
	;
	template<class FROM, class TO>
	void convert(const FROM& from, TO& to) const;
	Cartesian center() const
	{
		return Cartesian(center_x, center_y);
	}

private:
	const size_t width;
	const size_t height;
	const double center_x;
	const double center_y;
};

template<>
inline void PolarCartesian::convert(const Cartesian& from, Polar& to) const
{
	double x { from.x() - center_x };
	double y { from.y() - center_y };
	to.r() = std::hypot(x, y);
	to.phi() = std::atan2(y, x);
}
;

template<>
inline void PolarCartesian::convert(const Polar& from, Cartesian& to) const
{
	double x { from.r() * std::cos(from.phi().get()) };
	double y { from.r() * std::sin(from.phi().get()) };
	to.x() = x + center_x;
	to.y() = y + center_y;
}
;

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
;
inline std::ostream& operator<<(std::ostream& stream, const Cartesian& coord)
{
	stream << "[ x: " << coord.x() << ", y: " << coord.y() << " ]";
	return stream;
}
;

#endif /* POLARCARTESIAN_H_ */
