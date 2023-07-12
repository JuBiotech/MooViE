#include "lib/Coordinates.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Coordinates test"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(angle_helper_test)

BOOST_AUTO_TEST_CASE(rad_to_deg)
{
	BOOST_CHECK_EQUAL(angle_helper::deg_to_rad(0), 0);

	BOOST_CHECK_EQUAL(angle_helper::deg_to_rad(180), M_PI);
}

BOOST_AUTO_TEST_CASE(deg_to_rad)
{
	BOOST_CHECK_EQUAL(angle_helper::rad_to_deg(0), 0);

	BOOST_CHECK_EQUAL(angle_helper::rad_to_deg(M_PI), 180);
}

BOOST_AUTO_TEST_CASE(reflexivity)
{
	double radians = 0.5;
	BOOST_CHECK_EQUAL(
			angle_helper::rad_to_deg(angle_helper::deg_to_rad(radians)),
			radians
	);

	double degree = 75;
	BOOST_CHECK_EQUAL(
			angle_helper::deg_to_rad(angle_helper::rad_to_deg(degree)),
			degree
	);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(angle_helper_distance)

BOOST_AUTO_TEST_CASE(dist_to_0)
{
	BOOST_CHECK_EQUAL(angle_helper::rad_dist(0, M_PI), M_PI);
}

BOOST_AUTO_TEST_CASE(dist_to_negative)
{
	BOOST_CHECK_EQUAL(angle_helper::rad_dist(M_PI, 0), M_PI);
}

BOOST_AUTO_TEST_CASE(offset)
{
	double angle1 = M_PI_2;
	double angle2 = M_PI;
	double offset = 10;
	BOOST_CHECK_EQUAL(angle_helper::rad_dist(angle1, angle2),
			angle_helper::rad_dist(angle1 + offset, angle2 + offset));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(angle_test)

BOOST_AUTO_TEST_CASE(constructor)
{
	double angle = 0.5;
	BOOST_CHECK_EQUAL(Angle(angle).value(), angle);

	double angle_wrapped = 0.5;
	angle = angle_wrapped + 2.0 * M_PI;
	BOOST_CHECK_EQUAL(Angle(angle).value(), angle_wrapped);

	angle_wrapped = 0.5;
	angle = angle_wrapped - 2.0 * M_PI;
	BOOST_CHECK_EQUAL(Angle(angle).value(), angle_wrapped);

	angle = 43;
	Angle a = angle;
	Angle b = angle;
	BOOST_CHECK_EQUAL(a, b);

	angle = 21;
	a = angle;
	b = angle + 2 * M_PI;
	BOOST_CHECK_EQUAL(a, b);
}

BOOST_AUTO_TEST_CASE(assignment_operator)
{
	double angle = 127.3;
	Angle a(angle);
	Angle b(0);
	b = angle;
	BOOST_CHECK_EQUAL(a, b);
}

BOOST_AUTO_TEST_CASE(arithmetic_operators)
{
	double angle = 0.5;
	double add = 0.2;
	Angle a(angle);
	Angle b(add);
	BOOST_CHECK_EQUAL((a + b).value(), angle + add);

	angle = M_PI;
	add = M_PI;
	a = angle;
	b = add;
	BOOST_CHECK_EQUAL((a + b).value(), 0);

	angle = 17;
	add = 33;
	a = angle;
	b = add;
	BOOST_CHECK_EQUAL(a + b, Angle(angle + add));

	angle = 0.0123;
	add = M_PI;
	a = angle;
	b = add;
	BOOST_CHECK_EQUAL(a + b, Angle(angle + add));

	angle = 0.7;
	double minus = 0.2;
	a = angle;
	b = minus;
	BOOST_CHECK_EQUAL((a - b).value(), angle - minus);

	angle = M_PI;
	minus = 3.0 * M_PI;
	a = angle;
	b = minus;
	BOOST_CHECK_EQUAL((a - b).value(), 0);

	angle = 17;
	minus = 33;
	a = angle;
	b = minus;
	BOOST_CHECK_EQUAL(a - b, Angle(angle - minus));

	angle = 0.5;
	double times = 2;
	a = angle;
	BOOST_CHECK_EQUAL((a * times).value(), angle * times);

	angle = M_PI;
	times = 2;
	a = angle;
	BOOST_CHECK_EQUAL((a * times).value(), 0);

	angle = 17;
	times = 33;
	a = angle;
	BOOST_CHECK_CLOSE((a * times).value(), Angle(angle * times).value(), 0.000001);

	angle = 0;
	times = -100.645;
	a = angle;
	BOOST_CHECK_EQUAL(a * times, Angle(angle * times));

	angle = 0.8;
	double by = 2.0;
	a = angle;
	BOOST_CHECK_EQUAL((a / by).value(), angle / by);

	angle = 0;
	by = -100.1;
	a = angle;
	BOOST_CHECK_EQUAL(a / by, Angle(angle / by));
}

BOOST_AUTO_TEST_CASE(center)
{
	double angle1 = 0.5;
	double angle2 = 1;
	Angle a(angle1);
	Angle b(angle2);
	Angle c = Angle::center(a, b);
	BOOST_CHECK_EQUAL(c - a, b - c);

	angle1 = -4.0 * M_PI + 0.0123;
	angle2 = 4.0 * M_PI - 0.0234;
	a = angle1;
	b = angle2;
	c = Angle::center(a, b);
	BOOST_CHECK_CLOSE((c - a).value(), (b - c).value(), 0.00001);
}

BOOST_AUTO_TEST_CASE(interpolate)
{
	double angle1 = 0.5;
	double angle2 = 1;
	Angle a(angle1);
	Angle b(angle2);
	BOOST_CHECK_EQUAL(Angle::interpolate(a, b, 0), a);
	BOOST_CHECK_EQUAL(Angle::interpolate(a, b, 1), b);

	angle1 = 1;
	angle2 = 0.5;
	a = angle1;
	b = angle2;
	BOOST_CHECK_EQUAL(Angle::interpolate(a, b, 0), a);
	BOOST_CHECK_EQUAL(Angle::interpolate(a, b, 1), b);

	angle1 = 0.5;
	angle2 = 1;
	a = angle1;
	b = angle2;
	double p = 0.1;
	Angle c = Angle::interpolate(a, b, p);
	BOOST_CHECK_CLOSE((c - a).value(), (b - a).value() * p, 0.00001);
	BOOST_CHECK_CLOSE((b - c).value(), (b - a).value() * (1 - p), 0.00001);

	angle1 = 1;
	angle2 = 0.5;
	a = angle1;
	b = angle2;
	p = 0.9;
	c = Angle::interpolate(a, b, p);
	BOOST_CHECK_CLOSE((a - c).value(), (a - b).value() * p, 0.00001);
	BOOST_CHECK_CLOSE((c - b).value(), (a - b).value() * (1 - p), 0.00001);
}

BOOST_AUTO_TEST_SUITE_END()
