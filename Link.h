/*
 * Link.h
 *
 *  Created on: 05.07.2017
 *      Author: beyss
 */

#ifndef LINK_H_
#define LINK_H_

#include "PolarCartesian.h"

class Link
{
public:
	Link(const Polar& origin1, const Polar& origin2, const Polar& target1,
			const Polar& target2)
			: _origin1 { origin1 }, _origin2 { origin2 }, _target1 { target1 }, _target2 {
					target2 }
	{
	}
	const Polar& origin1() const
	{
		return _origin1;
	}
	const Polar& origin2() const
	{
		return _origin2;
	}
	const Polar& target1() const
	{
		return _target1;
	}
	const Polar& target2() const
	{
		return _target2;
	}

private:
	Polar _origin1, _origin2, _target1, _target2;
};

#endif /* LINK_H_ */
