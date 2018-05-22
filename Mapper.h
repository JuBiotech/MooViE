/*
 * Mapper.h
 *
 *  Created on: 05.07.2017
 *      Author: beyss
 */

#ifndef MAPPER_H_
#define MAPPER_H_

/** Mapper represent a mapping of from one
 * interval to another: [a,b] -> [c,d]. It solves
 * the linear equations
 * 1. f(a) = r*a + s = c
 * 2. f(b) = r*b + s = d
 * for r and s so that it can determine f.
 *
 * @brief Mapper is a bijective function f: [a,b] -> [c,d]
 *
 * @author beyss
 * @date 26.07.2017
 */
class Mapper
{
public:
    /** Creates a Mapper from two given intervals.
     *
     * @brief constructor
     *
     * @param in the first interval
     * @param out the second interval
     */
    Mapper(const std::pair<double, double>& _in, const std::pair<double, double>& _out)
    : in { _in }, out { _out }
    {
    }

    /** Returns the value associated to the given input using its linear
     * mapping function.
     *
     * @brief maps [a,b] -> [c,d]
     *
     * @param out_val the value to map
     *
     * @return the mapped value
     */
    double map(const double& out_val) const
    {
        return transform(in, out, out_val);
    }

    /** Returns the value associated to the given input using the inverse
     * of its linear mapping function.
     *
     * @brief maps [c,d] -> [a,b]
     *
     * @param in_val the value to map
     *
     * @return the mapped value
     */
    double inverse(const double& in_val) const
    {
        return transform(out, in, in_val);
    }
private:
    /** Performs the actual linear transformation between two given intervals.
     *
     * @brief calculate f(val) using bijective f: IN -> OUT
     *
     * @param in the interval to map from
     * @param out the interval to map to
     * @param val the value to transform
     *
     * @return the tranformed value
     */
    double transform(const std::pair<double, double>& in,
                     const std::pair<double, double>& out, const double& val) const
    {
        return (out.second - out.first) / (in.second - in.first)
				* (val - in.first) + out.first;
    }
    /** The domain of the mapping function */
    std::pair<double, double> in;
    /** The image of the mapping function */
    std::pair<double, double> out;
};

#endif /* MAPPER_H_ */
