#ifndef IOVECTOR_H_
#define IOVECTOR_H_

#include <vector>
#include "Coordinates.h"
#include "InputAxis.h"
#include "Mapper.h"
#include "OutputGrid.h"

/** A point in a polar coordinate system. The point has
 * additional properties specifying how a curve starting
 * from its coordinate should be styled.
 *
 * @brief Styled polar coordinate
 *
 * @author stratmann
 * @date 07.03.2018
 */
struct Point
{
  /** The coordinate */
  const Polar coord;

  /** The property with which to draw */
  const DrawerProperties<> prop;

  /** Creates a Point using a given Polar and DrawerProperties.
   *
   * @brief constructor
   *
   * @param coord_ the coordinate
   * @param prop_ the DrawerProperties
   */
  Point (Polar&& coord_, const DrawerProperties<>& prop_) :
      coord (coord_), prop (prop_)
  {
  }
};

/** An element of the relation R^n x R^m or a row of data consisting
 * of n inputs and m outputs.
 * It can be drawn using n links and m connectors using the style
 * specified for each Point. It is necessary to know the index i=n-1
 * to draw a IOVector.
 *
 * @brief IOVector MooViE component representation
 *
 * @author stratmann
 * @date 07.03.2018
 */
class IOVector
{
private:
  /* The Point data */
  std::vector<Point> m_points;
public:
  /** Returns a const-reference to the Point of the i-th
   * position of this IOVector. There is no boundry
   * check so that the result for i > IOVector#size
   * is undefined.
   *
   * @param the index of the Point
   *
   * @return the Point
   */
  const Point&
  operator[] (std::size_t i) const
  {
    return m_points[i];
  }

  /** Returns the total number of Points n+m of this
   * IOVector.
   *
   * @return the size
   */
  inline std::size_t
  size (void) const
  {
    return m_points.size ();
  }

  /** Constructs and adds Point in-place using the given
   * arguments.
   *
   * @param args the arguments (Polar, DrawerProperties)
   */
  template<typename ... Arg>
    void
    emplace_back (Arg&&... args)
    {
      m_points.emplace_back (std::forward<Arg>(args)...);
    }
};

/** A class for constructing IOVectors. It follows the
 * factory pattern.
 *
 * @author stratmann
 * @date 07.03.2018
 */
class IOVectorFactory
{
private:
  /** Precalculated values that will be applied to the style of each point */
  double m_line_width, m_line_alpha, m_fill_alpha, m_round_factor;

  /** The OutputGrid that fits the IOVector */
  const OutputGrid& m_grid;
  /** The InputAxis' that fit the IOVector */
  const std::vector<InputAxis>& m_axis;

  /** Mapper that convert value from data set to angle */
  std::vector<Mapper> m_input_mapper, m_output_mapper;

public:
  /** Creates a new IOVector factory which needs
   * the number of rows in the data set and the OutputGrid
   * and the InputAxis' with wich the IOVector will
   * be drawn.
   *
   * @param num_data_rows the number of rows of the data set
   * @param grid the OutputGrid
   * @param axis the InputAxis'
   */
  IOVectorFactory (std::size_t num_data_rows, const OutputGrid& grid,
		   const std::vector<InputAxis>& axis);

  /** Creates a new IOVector from a given DefDataRow. If an input value
   * is too close to zero (as defined by moovie.epsilon_places), an invalid
   * coordinate is added that needs to be ignored by the Drawer.
   *
   * @param row the DefDataRow
   *
   * @return the so created IOVector
   */
  IOVector
  create (const DefDataRow& row) const;

private:
  /** Rounds the given value based on the configured
   * decimal places.
   *
   * @param grid if value is output grid
   * @param i index of the column variables
   * @param val value to round
   *
   * @return rounded value
   */
  double
  round (bool grid, std::size_t i, double val) const;

  /** Returns the color of the interval that the given value
   * lies in.
   *
   * @param the first output value
   *
   * @return the interval color
   */
  const Color&
  get_color (double val) const;
};

#endif /* IOVECTOR_H_ */
