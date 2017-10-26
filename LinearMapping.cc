/*
 * LinearMapping.cc
 *
 *  Created on: 26.07.2017
 *      Author: beyss
 */

#include "LinearMapping.h"


LinearMapping::LinearMapping(const std::pair<double, double>& p1,
		const std::pair<double, double>& p2)
{
	_fwd_slope = (p1.second - p2.second) / (p1.first - p2.first);
	_fwd_intercept = p1.second - _fwd_slope * p1.first;

	_bwd_slope = 1.0/_fwd_slope;
	_bwd_intercept = - _fwd_intercept/_fwd_slope;
}

double LinearMapping::map(double in) const
{
	return _fwd_slope * in + _fwd_intercept;
}

double LinearMapping::inv_map(double out) const
{
	return _bwd_slope * out + _bwd_intercept;
}

LinearMapping::~LinearMapping()
{
	// TODO Auto-generated destructor stub
}

