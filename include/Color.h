/*
 * Color.h
 *
 *  Created on: 27.07.2017
 *      Author: beyss
 */

#ifndef COLOR_H_
#define COLOR_H_

#include <array>
#include <Utils.h>

/** Color class represents a color by RGB and alpha value.
 * @brief The Color class
 * @author beyss
 * @date 27.07.2017
 */
class Color
{
public:
	/** A Color constant representing black (0,0,0,1) */
	static const Color 					BLACK;
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

    Color(const Color& c, double a)
    : _r{ limit(c._r) }, _g { limit(c._g) }, _b { limit(c._b) }, _a { limit(a) }
    {}

    /** Access function for the color's red value.
     *
     * @brief r
     *
     * @return a reference to the colors red value
     */
    const double& r() const
    {
        return _r;
    }

    /** Access function for the color's green value.
     *
     * @brief g
     *
     * @return a reference to the colors green value
     */
    const double& g() const
    {
        return _g;
    }

    /** Access function for the color's blue value.
     *
     * @brief b
     *
     * @return a reference to the colors blue value
     */
    const double& b() const
    {
        return _b;
    }

    /** Access function for the color's alpha value.
     *
     * @brief a
     *
     * @return a reference to the colors alpha value
     */
    const double& a() const
    {
        return _a;
    }

    /** Checks whether or not two colors are equal.
     * This is the case if RGBA values are the same.
     *
     * @brief this == color
     *
     * @param color the other color
     *
     * @return equal or not
     */
    bool operator==(const Color& color) const
    {
    	return Util::double_equal(_r, color._r)
    			&& Util::double_equal(_g, color._g)
    			&& Util::double_equal(_b, color._b)
    			&& Util::double_equal(_a, color._a);
    }

    /** Checks whether or not two colors are not equal.
     * Two colors would be equal if their RGBA values
     * were the same.
     *
     * @brief this != color
     *
     * @param color the other color
     *
     * @return not equal or not
     */
    bool operator!=(const Color& color) const
    {
    	return not Util::double_equal(_r, color._r)
    			|| not Util::double_equal(_g, color._g)
    			|| not Util::double_equal(_b, color._b)
    			|| not Util::double_equal(_a, color._a);
    }

	/** Sets the red value of this Color.
	 * Input values from 0 to 255 will be automatically corrected
	 * to values from [0,1].
	 *
	 * @brief set red value
	 *
	 * @param red the red value to set
	 */
	void set_red(double red)
	{
		_r = limit(red);
	}

	/** Sets the green value of this Color.
	 * Input values from 0 to 255 will be automatically corrected
	 * to values from [0,1].
	 *
	 * @brief set green value
	 *
	 * @param green the green value to set
	 */
	void set_green(double green)
	{
		_g = limit(green);
	}

	/** Sets the blue value of this Color.
	 * Input values from 0 to 255 will be automatically corrected
	 * to values from [0,1].
	 *
	 * @brief set blue value
	 *
	 * @param blue the blue value to set
	 */
	void set_blue(double blue)
	{
		_b = limit(blue);
	}

    /** Sets the alpha value of this Color.
     * Input values from 0 to 255 will be automatically corrected
	 * to values from [0,1].
     *
     * @brief set alpha value
     *
     * @param alpha the alpha value to set
     */
    void set_alpha(double alpha)
    {
        _a = limit(alpha);
    }

    /** Puts string representation of Color c to the output stream o.
     *
     * @brief ostream operator
     *
     * @param o the ostream to put into
     * @param c the color to put
     */
    friend std::ostream& operator<<(std::ostream& o, const Color& c)
    {
    	return o << "[r=" << c._r << ", g=" << c._g << ", b=" << c._b
    			<< ", a=" << c._a << "]";
    }

private:
    /** Corrects an input value to be from [0,1].
     * Used for correcting alpha values.
     *
     * @brief limit
     *
     * @param val the value to correct
     *
     * @return the corrected value
     */
    double limit(const double& val)
    {
        double temp_val = val;
        if (uint8_t(temp_val) == temp_val && temp_val > 1.0)
                temp_val /= 255.0;
        return std::max(std::min(temp_val, 1.0), 0.0);
    }

    /** double constants representing RGBA value. */
    double _r, _g, _b, _a;
};

#endif /* COLOR_H_ */
