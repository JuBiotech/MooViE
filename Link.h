/*
 * Link.h
 *
 *  Created on: 05.07.2017
 *      Author: beyss
 */

#ifndef LINK_H_
#define LINK_H_

#include "PolarCartesian.h"

/** A Link is a connection curve from a data identifier to its mapped
 * coordinate grid coordinates.
 * It needs four coordinates due to its filled shape. Cairo draws this
 * link like origin1->origin2->target1->target2->origin1.
 * @brief The Link class
 * @author beyss
 * @date 05.07.2017
 */
class Link
{
public:
    /** Creates a link from the given four coordinates.
     * @brief Link
     * @param origin1 the first origin coordinate
     * @param origin2 the second origin coordinate
     * @param target1 the first target coordinate
     * @param target2 the second target coordinate
     */
    Link(const Polar& origin1, const Polar& origin2, const Polar& target1, const Polar& target2)
    : _origin1 { origin1 }, _origin2 { origin2 }, _target1 { target1 }, _target2 { target2 }
    {
    }

    /** Returns the first origin coordinate.
     * @brief origin1
     * @return a reference to the first origin coordinate
     */
    const Polar& origin1() const
    {
        return _origin1;
    }

    /** Returns the second origin coordinate.
     * @brief origin2
     * @return a reference to the second origin coordinate
     */
    const Polar& origin2() const
    {
        return _origin2;
    }

    /** Returns the first target coordinate.
     * @brief target1
     * @return a reference to the first target coordinate
     */
    const Polar& target1() const
    {
        return _target1;
    }

    /** Returns the second target coordinate.
     * @brief target2
     * @return a reference to the second target coordinate
     */
    const Polar& target2() const
    {
        return _target2;
    }

private:
    /** Coordinates of the to start and end vertices */
    Polar _origin1, _origin2, _target1, _target2;
};

#endif /* LINK_H_ */
