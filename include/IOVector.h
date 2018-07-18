#ifndef RELATIONELEMENT_H_
#define RELATIONELEMENT_H_

#include <vector>
#include <Coordinates.h>
#include <InputAxis.h>
#include <Mapper.h>
#include <OutputGrid.h>

/** A point in a polar coordinate system. The point has
 * additional properties specifying how a curve starting
 * from its coordinate should be styled.
 *
 * @brief a coordinate with drawing information
 *
 * @author stratmann
 * @date 07.03.2018
 */
struct Point
{
	/* The coordinate */
	const Polar coord;

	/* The property with which to draw */
	const DrawerProperties<> prop;

	/** Creates a Point using a given Polar and DrawerProperties.
	 *
	 * @brief constructor
	 *
	 * @param _coord the coordinate
	 * @param _prop the DrawerProperties
	 */
	Point(Polar&& _coord, const DrawerProperties<>& _prop)
	: coord(_coord), prop(_prop)
	{}
};

/** An element of the relation R^n x R^m or a row of data consisting
 * of n inputs and m outputs.
 * It can be drawn using n links and m connectors using the style
 * specified for each Point. It is necessary to know the index i=n-1
 * to draw a IOVector.
 *
 * @brief a row of input/output data
 *
 * @author stratmann
 * @date 07.03.2018
 */
class IOVector
{
public:
	/** Returns a const-reference to the Point of the i-th
	 * position of this IOVector. There is no boundry
	 * check so that the result for i > IOVector#size
	 * is undefined.
	 *
	 * @brief access i-th point
	 *
	 * @param the index of the Point
	 *
	 * @return the Point
	 */
	const Point& operator[](std::size_t i) const
	{
		return points[i];
	}

	/** Returns the total number of Points n+m of this
	 * IOVector.
	 *
	 * @brief the number of Point
	 *
	 * @return the size
	 */
	inline std::size_t size(void) const
	{
		return points.size();
	}

	/** Constructs and adds Point in-place using the given
	 * arguments.
	 *
	 * @brief add Point from arguments
	 *
	 * @param args the arguments (Polar, DrawerProperties)
	 */
	template<typename... Arg>
	void emplace_back(Arg&&... args)
	{
		points.emplace_back(std::forward<Arg>(args)...);
	}
private:
	/* The Point data */
	std::vector<Point> points;
};

/** A class for constructing IOVectors. It follows the
 * factory pattern.
 *
 * @brief a factory for IOVectors
 *
 * @author stratmann
 * @date 07.03.2018
 */
class IOVectorFactory
{
public:
	/** Creates a new IOVector factory which needs
	 * the number of rows in the data set and the OutputGrid
	 * and the InputAxis' with wich the IOVector will
	 * be drawn.
	 *
	 * @brief constructor
	 *
	 * @param num_data_rows the number of rows of the data set
	 * @param grid the OutputGrid
	 * @param axis the InputAxis'
	 */
	IOVectorFactory(std::size_t num_data_rows,
			const OutputGrid& grid,
			const std::vector<InputAxis>& axis);

	/** Creates a new IOVector from a given DefDataRow
	 * with
	 *
	 * @brief creates a new IOVector
	 *
	 * @param row the DefDataRow
	 *
	 * @return the so created IOVector
	 */
	IOVector create(const DefDataRow& row) const;
private:

	/** Returns the color of the interval that the given value
	 * lies in.
	 *
	 * @brief gets the interval color
	 *
	 * @param the first output value
	 *
	 * @return the interval color
	 */
	const Color& get_color(double val) const;
private:
	/* Precalculated values that will be applied to the style of each point */
	double line_width, line_alpha, fill_alpha;

	/* The OutputGrid that fits the IOVector */
	const OutputGrid& grid;
	/* The InputAxis' that fit the IOVector */
	const std::vector<InputAxis>& axis;

	/* Mapper that convert value from data set to angle */
	std::vector<Mapper> input_mapper,
						output_mapper;
};

#endif /* RELATIONELEMENT_H_ */
