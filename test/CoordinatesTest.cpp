#include <Coordinates.h>

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

	angle = 0;
	double step = 0.0123;
	double wrap_arround = 0;
	while (angle < 2 * M_PI)
	{
		while (wrap_arround < 10)
		{
			a = angle;
			b = angle + wrap_arround * 2.0 * M_PI;
			BOOST_CHECK_EQUAL(a, b);
			wrap_arround += 1;
		}
		angle += step;
	}
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

	angle = 0;
	add = 0;
	double step = 0.0123;
	while (angle < 2 * M_PI)
	{
		add = 0;
		while (add < 2 * M_PI)
		{
			a = angle;
			b = add;
			BOOST_CHECK_EQUAL(a + b, Angle(angle + add));
			add += step;
		}
		angle += step;
	}

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

	angle = 0;
	minus = 0;
	step = 0.0123;
	while (angle < 2.0 * M_PI)
	{
		minus = 0;
		while (minus < 2.0 * M_PI)
		{
			a = angle;
			b = minus;
			BOOST_CHECK_EQUAL(a - b, Angle(angle - minus));
			minus += step;
		}
		angle += step;
	}

	double angle1 = 0;
	double angle2 = 0;
	double step1 = 0.0123;
	double step2 = 0.0456 / 2.0;

	while (angle1 < 4.0 * M_PI)
	{
		while (angle2 < 4.0 * M_PI)
		{
			a = angle1;
			b = angle2;
			BOOST_CHECK_EQUAL((a + b) - b, a);
			angle2 += step2;
		}
		angle1 += step1;
	}

	angle1 = 0;
	angle2 = 0;
	step1 = 0.0123;
	step2 = 0.0456 / 2.0;

	while (angle1 < 4.0 * M_PI)
	{
		while (angle2 < 4.0 * M_PI)
		{
			a = angle1;
			b = angle2;
			BOOST_CHECK_EQUAL((a - b) + b, a);
			angle2 += step2;
		}
		angle1 += step1;
	}

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
	times = -100;
	step = 0.0123;
	double step_times = 0.645;
	while (angle < 2 * M_PI)
	{
		times = -100;
		while (times < 100)
		{
			a = angle;
			BOOST_CHECK_EQUAL(a * times, Angle(angle * times));
			times += step_times;
		}
		angle += step;
	}

	angle = 0.8;
	double by = 2.0;
	a = angle;
	BOOST_CHECK_EQUAL((a / by).value(), angle / by);

	angle = 0;
	by = -100;
	step = 0.0123;
	while (angle < 2.0 * M_PI)
	{
		by = -100;
		while (by < 100)
		{
			if (by == 0)
				by += 0.1;
			a = angle;
			BOOST_CHECK_EQUAL(a / by, Angle(angle / by));
			by += step;
		}
		angle += step;
	}

	angle = 0;
	times = -100;
	double step_angle = 0.0123;
	step_times = 0.0456 / 2.0;

	while (angle < 4.0 * M_PI)
	{
		while (times < 100)
		{
			a = angle;
			BOOST_CHECK_EQUAL((a * times) / times, a);
			times += step_times;
		}
		angle += step_angle;
	}

	angle = 0;
	by = -100;
	step_angle = 0.0123;
	step_times = 0.0456 / 2.0;

	while (angle < 4.0 * M_PI)
	{
		while (by < 100)
		{
			a = angle;
			BOOST_CHECK_EQUAL((a / by) * by, a);
			by += step_times;
		}
		angle += step_angle;
	}
}

BOOST_AUTO_TEST_CASE(center)
{
	double angle1 = 0.5;
	double angle2 = 1;
	Angle a(angle1);
	Angle b(angle2);
	Angle c = Angle::center(a, b);
	BOOST_CHECK_EQUAL(c - a, b - c);

	angle1 = -4.0 * M_PI;
	angle2 = 4.0 * M_PI;
	double step1 = 0.0123;
	double step2 = 0.0234;
	while (angle1 < 4.0 * M_PI)
	{
		angle2 = 4.0 * M_PI;
		while (angle2 > -4.0 * M_PI)
		{
			a = angle1;
			b = angle2;
			Angle c = Angle::center(a, b);
			BOOST_CHECK_CLOSE((c - a).value(), (b - c).value(), 0.00001);
			angle2 -= step2;
		}
		angle1 += step1;
	}
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
	double p = 0;
	double step = 0.1;
	p += step;
	while (p < 0.95)
	{
		Angle c = Angle::interpolate(a, b, p);
		BOOST_CHECK_CLOSE((c - a).value(), (b - a).value() * p, 0.00001);
		BOOST_CHECK_CLOSE((b - c).value(), (b - a).value() * (1 - p), 0.00001);
		p += step;
	}

	angle1 = 1;
	angle2 = 0.5;
	a = angle1;
	b = angle2;
	p = 0;
	step = 0.1;
	p += step;
	while (p < 0.95)
	{
		Angle c = Angle::interpolate(a, b, p);
		BOOST_CHECK_CLOSE((a - c).value(), (a - b).value() * p, 0.00001);
		BOOST_CHECK_CLOSE((c - b).value(), (a - b).value() * (1 - p), 0.00001);
		p += step;
	}
}

BOOST_AUTO_TEST_SUITE_END()
