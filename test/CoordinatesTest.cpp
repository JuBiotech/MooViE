#include "../Coordinates.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Coordinates test"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(angle_helper_conversion)

BOOST_AUTO_TEST_CASE(deg_to_rad_0)
{
	BOOST_CHECK_EQUAL(angle_helper::deg_to_rad(0), 0);
}

BOOST_AUTO_TEST_CASE(deg_to_rad_180)
{
	BOOST_CHECK_EQUAL(angle_helper::deg_to_rad(180), M_PI);
}

BOOST_AUTO_TEST_CASE(rad_to_deg_0)
{
	BOOST_CHECK_EQUAL(angle_helper::rad_to_deg(0), 0);
}

BOOST_AUTO_TEST_CASE(rad_to_deg_pi)
{
	BOOST_CHECK_EQUAL(angle_helper::rad_to_deg(M_PI), 180);
}

BOOST_AUTO_TEST_CASE(rad_to_deg_to_rad)
{
	double radians = 0.5;
	BOOST_CHECK_EQUAL(
			angle_helper::rad_to_deg(angle_helper::deg_to_rad(radians)),
			radians);
}

BOOST_AUTO_TEST_CASE(deg_to_rad_to_deg)
{
	double degree = 75;
	BOOST_CHECK_EQUAL(
			angle_helper::deg_to_rad(angle_helper::rad_to_deg(degree)), degree);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(angle_helper_distance)

BOOST_AUTO_TEST_CASE(dist_to_0)
{
	BOOST_CHECK_EQUAL(angle_helper::rad_dist(0,M_PI), M_PI);
}

BOOST_AUTO_TEST_CASE(dist_to_negative)
{
	BOOST_CHECK_EQUAL(angle_helper::rad_dist(M_PI,0), M_PI);
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

BOOST_AUTO_TEST_SUITE(Angle_base_test)

BOOST_AUTO_TEST_CASE(constructor)
{
	double angle = 0.5;
	BOOST_CHECK_EQUAL(Angle(angle).value(), angle);
}

BOOST_AUTO_TEST_CASE(constructor_wrap_large)
{
	double angle_wrapped = 0.5;
	double angle = angle_wrapped + 2.0 * M_PI;
	BOOST_CHECK_EQUAL(Angle(angle).value(), angle_wrapped);
}

BOOST_AUTO_TEST_CASE(constructor_wrap_negative)
{
	double angle_wrapped = 0.5;
	double angle = angle_wrapped - 2.0 * M_PI;
	BOOST_CHECK_EQUAL(Angle(angle).value(), angle_wrapped);
}

BOOST_AUTO_TEST_CASE(equality)
{
	double angle = 43;
	Angle a(angle);
	Angle b(angle);
	BOOST_CHECK_EQUAL(a, b);
}

BOOST_AUTO_TEST_CASE(equality_wrap)
{
	double angle = 21;
	Angle a(angle);
	Angle b(angle + 2 * M_PI);
	BOOST_CHECK_EQUAL(a, b);
}

BOOST_AUTO_TEST_CASE(equality_programatic)
{
	double angle = 0;
	double step = 0.0123;
	double wrap_arround = 0;
	while (angle < 2 * M_PI)
	{
		while (wrap_arround < 10)
		{
			Angle a(angle);
			Angle b(angle + wrap_arround * 2.0 * M_PI);
			BOOST_CHECK_EQUAL(a, b);
			wrap_arround += 1;
		}
		angle += step;
	}
}

BOOST_AUTO_TEST_CASE(assign_operator)
{
	double angle = 127.3;
	Angle a(angle);
	Angle b(0);
	b = angle;
	BOOST_CHECK_EQUAL(a, b);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Angle_inequality_test)

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Angle_arithmetic_test)

BOOST_AUTO_TEST_CASE(addition)
{
	double angle = 0.5;
	double add = 0.2;
	Angle a(angle);
	Angle b(add);
	BOOST_CHECK_EQUAL((a + b).value(), angle + add);
}

BOOST_AUTO_TEST_CASE(addition_wrap_to_0)
{
	double angle = M_PI;
	double add = M_PI;
	Angle a(angle);
	Angle b(add);
	BOOST_CHECK_EQUAL((a + b).value(), 0);
}

BOOST_AUTO_TEST_CASE(addition_wrap)
{
	double angle = 17;
	double add = 33;
	Angle a(angle);
	Angle b(add);
	BOOST_CHECK_EQUAL(a + b, Angle(angle + add));
}

BOOST_AUTO_TEST_CASE(addition_programatic)
{
	double angle = 0;
	double add = 0;
	double step = 0.0123;
	while (angle < 2 * M_PI)
	{
		add = 0;
		while (add < 2 * M_PI)
		{
			Angle a(angle);
			Angle b(add);
			BOOST_CHECK_EQUAL(a + b, Angle(angle + add));
			add += step;
		}
		angle += step;
	}
}

BOOST_AUTO_TEST_CASE(substraction)
{
	double angle = 0.7;
	double minus = 0.2;
	Angle a(angle);
	Angle b(minus);
	BOOST_CHECK_EQUAL((a - b).value(), angle - minus);
}

BOOST_AUTO_TEST_CASE(substraction_wrap_to_0)
{
	double angle = M_PI;
	double minus = 3.0 * M_PI;
	Angle a(angle);
	Angle b(minus);
	BOOST_CHECK_EQUAL((a - b).value(), 0);
}

BOOST_AUTO_TEST_CASE(substraction_wrap)
{
	double angle = 17;
	double minus = 33;
	Angle a(angle);
	Angle b(minus);
	BOOST_CHECK_EQUAL(a - b, Angle(angle - minus));
}

BOOST_AUTO_TEST_CASE(substraction_programatic)
{
	double angle = 0;
	double minus = 0;
	double step = 0.0123;
	while (angle < 2.0 * M_PI)
	{
		minus = 0;
		while (minus < 2.0 * M_PI)
		{
			Angle a(angle);
			Angle b(minus);
			BOOST_CHECK_EQUAL(a - b, Angle(angle - minus));
			minus += step;
		}
		angle += step;
	}
}

BOOST_AUTO_TEST_CASE(add_subs_programmatic)
{
	double angle1 = 0;
	double angle2 = 0;
	double step1 = 0.0123;
	double step2 = 0.0456 / 2.0;

	while (angle1 < 4.0 * M_PI)
	{
		while (angle2 < 4.0 * M_PI)
		{
			Angle a(angle1);
			Angle b(angle2);
			BOOST_CHECK_EQUAL((a + b) - b, a);
			angle2 += step2;
		}
		angle1 += step1;
	}
}

BOOST_AUTO_TEST_CASE(subs_add_programmatic)
{
	double angle1 = 0;
	double angle2 = 0;
	double step1 = 0.0123;
	double step2 = 0.0456 / 2.0;

	while (angle1 < 4.0 * M_PI)
	{
		while (angle2 < 4.0 * M_PI)
		{
			Angle a(angle1);
			Angle b(angle2);
			BOOST_CHECK_EQUAL((a - b) + b, a);
			angle2 += step2;
		}
		angle1 += step1;
	}
}

BOOST_AUTO_TEST_CASE(multiplication)
{
	double angle = 0.5;
	double times = 2;
	Angle a(angle);
	BOOST_CHECK_EQUAL((a * times).value(), angle * times);
}

BOOST_AUTO_TEST_CASE(multiplication_wrap_to_0)
{
	double angle = M_PI;
	double times = 2;
	Angle a(angle);
	BOOST_CHECK_EQUAL((a * times).value(), 0);
}

BOOST_AUTO_TEST_CASE(multiplication_wrap)
{
	double angle = 17;
	double times = 33;
	Angle a(angle);
	BOOST_CHECK_CLOSE((a * times).value(), Angle(angle * times).value(), 0.000001);
}

BOOST_AUTO_TEST_CASE(multiplication_programatic)
{
	double angle = 0;
	double times = -100;
	double step = 0.0123;
	double step_times = 0.645;
	while (angle < 2 * M_PI)
	{
		times = -100;
		while (times < 100)
		{
			Angle a(angle);
			BOOST_CHECK_EQUAL(a * times, Angle(angle * times));
			times += step_times;
		}
		angle += step;
	}
}

BOOST_AUTO_TEST_CASE(division)
{
	double angle = 0.8;
	double by = 2.0;
	Angle a(angle);
	BOOST_CHECK_EQUAL((a / by).value(), angle / by);
}

BOOST_AUTO_TEST_CASE(division_programatic)
{
	double angle = 0;
	double by = -100;
	double step = 0.0123;
	double step_by = 0.645;
	while (angle < 2.0 * M_PI)
	{
		by = -100;
		while (by < 100)
		{
			if (by == 0)
				by += 0.1;
			Angle a(angle);
			BOOST_CHECK_EQUAL(a / by, Angle(angle / by));
			by += step;
		}
		angle += step;
	}
}

BOOST_AUTO_TEST_CASE(times_by_programmatic)
{
	double angle = 0;
	double times = -100;
	double step_angle = 0.0123;
	double step_times = 0.0456 / 2.0;

	while (angle < 4.0 * M_PI)
	{
		while (times < 100)
		{
			Angle a(angle);
			BOOST_CHECK_EQUAL((a * times) / times, a);
			times += step_times;
		}
		angle += step_angle;
	}
}

BOOST_AUTO_TEST_CASE(by_times_programmatic)
{
	double angle = 0;
	double by = -100;
	double step_angle = 0.0123;
	double step_times = 0.0456 / 2.0;

	while (angle < 4.0 * M_PI)
	{
		while (by < 100)
		{
			Angle a(angle);
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
}

BOOST_AUTO_TEST_CASE(center_programatic)
{
	double angle1 = -4.0 * M_PI;
	double angle2 = 4.0 * M_PI;
	double step1 = 0.0123;
	double step2 = 0.0234;
	while (angle1 < 4.0 * M_PI)
	{
		angle2 = 4.0 * M_PI;
		while (angle2 > -4.0 * M_PI)
		{
			Angle a(angle1);
			Angle b(angle2);
			Angle c = Angle::center(a, b);
			BOOST_CHECK_CLOSE((c - a).value(), (b - c).value(), 0.00001);
			angle2 -= step2;
		}
		angle1 += step1;
	}
}

BOOST_AUTO_TEST_CASE(interpolate_asc_extremes)
{
	double angle1 = 0.5;
	double angle2 = 1;
	Angle a(angle1);
	Angle b(angle2);
	BOOST_CHECK_EQUAL(Angle::interpolate(a, b, 0), a);
	BOOST_CHECK_EQUAL(Angle::interpolate(a, b, 1), b);
}

BOOST_AUTO_TEST_CASE(interpolate_desc_extremes)
{
	double angle1 = 1;
	double angle2 = 0.5;
	Angle a(angle1);
	Angle b(angle2);
	BOOST_CHECK_EQUAL(Angle::interpolate(a, b, 0), a);
	BOOST_CHECK_EQUAL(Angle::interpolate(a, b, 1), b);
}

BOOST_AUTO_TEST_CASE(interpolate_asc_programatic)
{
	double angle1 = 0.5;
	double angle2 = 1;
	Angle a(angle1);
	Angle b(angle2);
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
}

BOOST_AUTO_TEST_CASE(interpolate_desc_programatic)
{
	double angle1 = 1;
	double angle2 = 0.5;
	Angle a(angle1);
	Angle b(angle2);
	double p = 0;
	double step = 0.1;
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
