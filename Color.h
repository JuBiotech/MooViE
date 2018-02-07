/*
 * Color.h
 *
 *  Created on: 27.07.2017
 *      Author: beyss
 */

#ifndef COLOR_H_
#define COLOR_H_

#include <array>
#include "Triangle.h"

/** Color class represents a color by RGB and alpha values.
 * @brief The Color class
 * @author beyss
 * @date 27.07.2017
 */
class Color
{
public:
    /** Creates a Color from RGB and Alpha values.
    * @brief Color
    * @param r the red value
    * @param g the green value
    * @param b the blue value
    * @param a the alpha value
    */
    Color(double r = 0, double g = 0, double b = 0, double a = 1)
    : _r { limit(r) }, _g { limit(g) }, _b { limit(b) }, _a { limit(a) }
    {}

    /** Access function for the color's red value.
     * @brief r
     * @return a reference to the colors red value
     */
    const double& r() const
    {
        return _r;
    }

    /** Access function for the color's green value.
     * @brief g
     * @return a reference to the colors green value
     */
    const double& g() const
    {
        return _g;
    }

    /** Access function for the color's blue value.
     * @brief b
     * @return a reference to the colors blue value
     */
    const double& b() const
    {
        return _b;
    }

    /** Access function for the color's alpha value.
     * @brief a
     * @return a reference to the colors alpha value
     */
    const double& a() const
    {
        return _a;
    }

    /** Sets the alpha value of this Color.
     * set_alpha automatically corrects the given input value
     * to be in the range from 0 to 1.
     * @brief set_alpha
     * @param alpha the alpha value to set
     */
    void set_alpha(double alpha)
    {
        _a = limit(alpha);
    }

    /** Returns Color with the same RGB values as this Color,
     * but with given alpha value. set_alpha automatically corrects
     * the given input value to be in the range from 0 to 1.
     * @brief set_alpha
     * @param alpha the alpha value to set
     */
    Color set_alpha(double alpha) const
    {
        Color out(*this);
        out.set_alpha(alpha);
        return out;
    }

private:
    /** Corrects an input value to be from [0,1].
     * Used for correcting alpha values.
     * @brief limit
     * @param val the value to correct
     * @return the corrected value
     */
    double limit(const double& val)
    {
        double temp_val = val;
        if (uint8_t(temp_val) == temp_val && temp_val > 1.0)
                temp_val /= 255.0;
        return std::max(std::min(temp_val, 1.0), 0.0);
    }

    /** double constants representing RGBA value.
    * _a should be from [0,1].
    */
    double _r, _g, _b, _a;

public:
    /** An array of Colors */
    static const std::array<Color, 10> 	GLOW_10;

    /** A Triangular storage which contains i+1
     * matching colors at the i-th index.
     */
    static const Triangle<Color, 12> 	SET3;

    /** A Color constant representing black (0,0,0,1) */
    static const Color 			BLACK;

    /** Further color constants */
    static const Color 			SET2_3_1;
    static const Color 			SET2_3_2;
    static const Color 			SET2_3_3;

};

#endif /* COLOR_H_ */
