/*
 * Mapper.h
 *
 *  Created on: 05.07.2017
 *      Author: beyss
 */

#ifndef MAPPER_H_
#define MAPPER_H_

/**
 * Class that creates a liner Mapping [a b] <-> [c d]
 */
class Mapper
{
public:
	Mapper(const std::pair<double, double>& in,
			const std::pair<double, double> &out)
			: _in { in }, _out { out }
	{
	}
	double toIn(const double& out) const
	{
		return transform(_out, _in, out);
	}
	double toOut(const double& in) const
	{
		return transform(_in, _out, in);
	}
private:
	double transform(const std::pair<double, double>& in,
			const std::pair<double, double>& out, const double& val) const
	{
		return (out.second - out.first) / (in.second - in.first)
				* (val - in.first) + out.first;
	}
	std::pair<double, double> _in;
	std::pair<double, double> _out;
};

#endif /* MAPPER_H_ */
