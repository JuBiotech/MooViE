#ifndef COINPUTGRID_H_
#define COINPUTGRID_H_

#include <cstddef>
#include <vector>

#include "Scale.h"
#include "DataSet.h"
#include "Configuration.h"
#include "Coordinates.h"

/** A enum for drawer direction */
enum Direction
{
  COUNTER_CLOCKWISE, CLOCKWISE
};

/** Representing a coordinate grid by its dimensional constraints.
 *
 * @brief OutputGrid MooViE component representation
 *
 * @author beyss
 * @date 26.07.2017
 */
class OutputGrid
{
private:
  /** The output variables */
  std::vector<DefVariable> output_variables;
  /** The number of outputs */
  std::size_t m_num_outputs;

  /** The Scale information */
  MultiScale m_scale;

  /** Start and end angle for drawing the OutputGrid */
  Angle m_start, m_end;
  /** Radius of the OutputGrid */
  double m_radius;
  /** Height of the OutputGrid */
  double m_height;
  /** Direction of the OutputGrid's values */
  Direction m_direction;
public:
  /** Creates a OutputGrid presenting given variables and is drawn
   * between given angles with given radius and height.
   *
   * @param output_vars a vector containing the output variables
   * @param start the start angle
   * @param end the end angle
   * @param radius the radius from the center
   * @param height the height beginning at the radius
   * @param dir the Direction the outputs values increase
   */
  OutputGrid (const std::vector<DefVariable>& output_vars, const Angle & start,
	      const Angle & end, double radius, double height, Direction dir);

  /** Returns the i-th output variable. If num_output >= num_outputs
   * an exception is thrown.
   *
   * @param num_output the number of the output to return
   */
  const DefVariable&
  get_var (std::size_t num_output) const;

  /** Returns the total number of stored output variables.
   *
   * @return the number of outputs
   */
  std::size_t
  get_num_outputs () const
  {
    return m_num_outputs;
  }

  /** Returns the start Angle of this OutputGrid's
   * drawing span.
   *
   * @return the start Angle
   */
  const Angle&
  get_start () const
  {
    return m_start;
  }

  /** Starts the start Angle of this OutputGrid's
   * drawing span.
   *
   * @param start the start Angle to set
   */
  void
  set_start (const Angle& start)
  {
    m_start = start;
  }

  /** Returns the end Angle of this OutputGrid's
   * drawing span.
   *
   * @return the end Angle
   */
  const Angle&
  get_end () const
  {
    return m_end;
  }

  /** Sets the end Angle of this OutputGrid's
   * drawing span.
   *
   * @param end the end Angle to set
   */
  void
  set_end (const Angle& end)
  {
    m_end = end;
  }

  /** Returns the radius measured from the center
   * of the coordinate system.
   *
   * @return the radius
   */
  double
  get_radius () const
  {
    return m_radius;
  }

  /** Sets the radius measured from the center
   * of the coordinate system.
   *
   * @brief sets the radius
   *
   * @param radius the radius to set
   */
  void
  set_radius (double radius)
  {
    m_radius = radius;
  }

  /** Returns the height measured from the radius.
   *
   * @return the height
   */
  double
  get_height () const
  {
    return m_height;
  }

  /** Sets the height measured from the radius.
   *
   * @param height the height to set
   */
  void
  set_height (double height)
  {
    m_height = height;
  }

  /** Returns the direction this OutputGrid's output values
   * increase. The Direction is either COUNTER_CLOCKWISE (with
   * increasing Angle) or CLOCKWISE (with decreasing Angle).
   *
   * @return the Direction
   */
  Direction
  get_direction () const
  {
    return m_direction;
  }

  /** Sets the direction this OutputGrid's output values
   * increase. The Direction is either COUNTER_CLOCKWISE (with
   * increasing Angle) or CLOCKWISE (with decreasing Angle).
   *
   * @param direction the Direction to set
   */
  void
  set_direction (Direction direction)
  {
    m_direction = direction;
  }

  /** Returns the MultiScale of this OutputGrid. This
   * scale instance defines how the graphical scale will
   * be drawn for each output.
   *
   * @return the MultiScale
   */
  const MultiScale&
  get_scale () const
  {
    return m_scale;
  }
};

#endif /* COINPUTGRID_H_ */
