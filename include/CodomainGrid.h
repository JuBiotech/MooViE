#ifndef CODOMAINGRID_H_
#define CODOMAINGRID_H_

#include <cstddef>
#include <vector>

#include <Scale.h>
#include <DataSet.h>
#include <Configuration.h>
#include <Coordinates.h>

/** A enum for drawer direction */
enum Direction
{
	COUNTER_CLOCKWISE, CLOCKWISE
};

/** Representing a coordinate grid by its dimensional constraints.
 * ╟───┼───┼───┼───╫───┼───┼───┼───╢
 * ║   │   │   │   ║   │   │   │   ║
 * ╟───┼───┼───┼───╫───┼───┼───┼───╢
 * ║   │   │   │   ║   │   │   │   ║
 * ╟───┼───┼───┼───╫───┼───┼───┼───╢
 * ║   │   │   │   ║   │   │   │   ║
 * ╟───┼───┼───┼───╫───┼───┼───┼───╢
 * 4 outputs, 4 scale ticks
 * @brief The CoordGrid class
 * @author beyss
 * @date 26.07.2017
 */
class CodomainGrid
{
public:
    /** Creates a CodomainGrid presenting given variables and is drawn
     * between given angles with given radius and height.
     *
     * @brief constructor
     *
     * @param _output_vars a vector containing the output variables
     * @param _start the start angle
     * @param _end the end angle
     * @param _radius the radius from the center
     * @param _height the height beginning at the radius
     * @param _dir the Direction the outputs values increase
     */
    CodomainGrid(const std::vector<DefVariable>& _output_vars,
    		const Angle & _start, const Angle & _end,
			double _radius, double _height, Direction _dir);

    /** Returns the i-th output variable. If num_output >= num_outputs
     * an exception is thrown.
     *
     * @brief gets output variable
     *
     * @param num_output the number of the output to return
     */
    const DefVariable& get_var(std::size_t num_output) const;

    /** Returns the total number of stored output variables.
     *
     * @brief gets number of outputs
     *
     * @return the number of outputs
     */
    std::size_t get_num_outputs() const
    {
    	return num_outputs;
    }

    /** Returns the start Angle of this CodomainGrid's
     * drawing span.
     *
     * @brief gets the start Angle
     *
     * @return the start Angle
     */
    const Angle& get_start() const
    {
    	return start;
    }

    /** Starts the start Angle of this CodomainGrid's
     * drawing span.
     *
     * @brief sets the start Angle
     *
     * @param _start the start Angle to set
     */
    void set_start(const Angle& _start)
    {
    	start = _start;
    }

    /** Returns the end Angle of this CodomainGrid's
     * drawing span.
     *
     * @brief gets the end Angle
     *
     * @return the end Angle
     */
    const Angle& get_end() const
    {
    	return end;
    }

    /** Sets the end Angle of this CodomainGrid's
     * drawing span.
     *
     * @brief gets the end Angle
     *
     * @param _end the end Angle to set
     */
    void set_end(const Angle& _end)
    {
    	end = _end;
    }

    /** Returns the radius measured from the center
     * of the coordinate system.
     *
     * @brief gets the radius
     *
     * @return the radius
     */
    double get_radius() const
    {
    		return radius;
    }

    /** Sets the radius measured from the center
     * of the coordinate system.
     *
     * @brief sets the radius
     *
     * @param _radius the radius to set
     */
    void set_radius(double _radius)
    {
    	radius = _radius;
    }

    /** Returns the height measured from the radius.
     *
     * @brief gets the height
     *
     * @return the height
     */
	double get_height() const
	{
		return height;
	}

	/** Sets the height measured from the radius.
	 *
	 * @brief sets the height
	 *
	 * @param _height the height to set
	 */
	void set_height(double _height)
	{
		height = _height;
	}

	/** Returns the direction this CodomainGrid's output values
	 * increase. The Direction is either COUNTER_CLOCKWISE (with
	 * increasing Angle) or CLOCKWISE (with decreasing Angle).
	 *
	 * @brief gets the Direction
	 *
	 * @return the Direction
	 */
	Direction get_direction() const
	{
		return direction;
	}

	/** Sets the direction this CodomainGrid's output values
	 * increase. The Direction is either COUNTER_CLOCKWISE (with
	 * increasing Angle) or CLOCKWISE (with decreasing Angle).
	 *
	 * @brief sets the Direction
	 *
	 * @param _dir the Direction to set
	 */
	void set_direction(Direction _dir)
	{
		direction = _dir;
	}

	/** Returns the MultiScale of this CodomainGrid. This
	 * scale instance defines how the graphical scale will
	 * be drawn for each output.
	 *
	 * @brief gets the MultiScale
	 *
	 * @return the MultiScale
	 */
	const MultiScale& get_scale() const
	{
		return scale;
	}

private:
	/* The output variables */
	std::vector<DefVariable> output_variables;
    /** The number of outputs */
    std::size_t 		num_outputs;

    /** The Scale information */
    MultiScale			scale;

    /** Start and end angle for drawing the CoordGrid */
    Angle 				start, end;
    /** Radius of the CoordGrid */
    double 				radius;
    /** Height of the CoordGrid */
    double 				height;
    /** Direction of the CoordGrid's values */
    Direction 			direction;
};

#endif /* CODOMAINGRID_H_ */
