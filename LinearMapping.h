/*
 * LinearMapping.h
 *
 *  Created on: 26.07.2017
 *      Author: beyss
 */

#ifndef LINEARMAPPING_H_
#define LINEARMAPPING_H_

#include <utility>

class LinearMapping
{
public:
	LinearMapping(const std::pair<double,double>& p1, const std::pair<double,double>& p2);
	double map(double in) const;
	double inv_map(double out) const;
	virtual ~LinearMapping();
private:
	double _fwd_slope;
	double _fwd_intercept;
	double _bwd_slope;
	double _bwd_intercept;
};

#endif /* LINEARMAPPING_H_ */
