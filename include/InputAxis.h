#ifndef INPUTAXIS_H_
#define INPUTAXIS_H_

#include <Scale.h>
#include <DataSet.h>
#include <Configuration.h>
#include <Coordinates.h>

/** A InputAxis is an axis which displays the possible values
 * of a input variable. It is visualized as a ring segment
 * with a distinct color and has ticks for better readability.
 *
 * @brief InputAxis MooViE component representation
 *
 * @author stratmann
 * @date 12.12.2017
 */
class InputAxis
{
public:
  class Histogram
  {
  private:
      /** The variable whose frequencies to present */
      DefVariable m_variable;
      /** The number of intervals to use */
      std::size_t m_num_intervals;
      /** The stored frequencies for the intervals */
      std::vector<double> m_frequencies;
  public:
    /** Creates an empty Histogram for this variable with
     * the specified number of intervals.
     *
     * @param var the variable to present
     */
    Histogram (DefVariable var);

    /** Calculates equidistant data sections and stores
     * them.
     *
     * @param data the input values of this variable
     */
    void
    calculate (const std::vector<double> & data);

    /** Returns the value of the histogram graph in this
     * section. They are associated with the relative
     * frequency of the equidistant intervals.
     *
     * @param i index of the section
     *
     * @return the height
     */
    double
    get_section_frequency (std::size_t i) const;

    /** Returns the number of equidistant intervals the
     * domain of this Histogram's Variable is divided in.
     *
     * @return the interval count
     */
    inline std::size_t
    get_num_intervals (void) const
    {
      return m_num_intervals;
    }

    /** Sets the histogram to have a given number of equidistant
     * intervals. If values for an old number of intervals have
     * been stored, all data from is deleted and the frequencies
     * set to 0.
     *
     * @param num_interval the new interval count
     */
    inline void
    set_num_intervals (std::size_t num_intervals)
    {
      m_num_intervals = num_intervals;
      m_frequencies.clear ();
      for (std::size_t i = 0; i < m_num_intervals; ++i)
	m_frequencies.push_back (0);
    }
  };

private:
  /** The Variable this InputAxis represents */
  DefVariable m_variable;

  /** The ticks of this variable */
  SimpleScale m_scale;

  /** Start and end angle for drawing the InputAxis */
  Angle m_start, m_end;
  /** Start radius of the InputAxis */
  double m_radius;
  /** Height of the InputAxis */
  double m_height;

  /* Style defining how the InputAxis is drawn */
  DrawerProperties<> m_prop;

  /* The histogram describing the frequencies of the intervals */
  Histogram m_histogram;

public:
  /** Creates a InputAxis presenting a given variable and
   * is drawn between given angles with given radius, height
   * and properties.
   *
   * @brief constructor
   *
   * @param variable the variable to present
   * @param start the start angle
   * @param end the end angle
   * @param radius the radius from the center
   * @param height the height beginning at the radius
   * @param prop the DrawerProperties
   */
  InputAxis (DefVariable variable, const Angle& start, const Angle& end,
	     double radius, double height, const DrawerProperties<>& prop);

  /** Returns a const reference to the variable this
   * InputAxis presents.
   *
   * @return the Var
   */
  const DefVariable&
  get_var () const
  {
    return m_variable;
  }

  /** Returns a reference to its histogram. The
   * InputAxis#calculate_histogram function has to called
   * before drawing the histogram because it is empty by
   * default.
   *
   * @return the Histogram
   */
  const Histogram&
  get_histogram () const
  {
    return m_histogram;
  }

  /** Returns the start Angle of this InputAxis'
   * drawing span.
   *
   * @return the start Angle
   */
  const Angle&
  get_start () const
  {
    return m_start;
  }

  /** Starts the start Angle of this InputAxis'
   * drawing span.
   *
   * @param start the start Angle to set
   */
  void
  set_start (const Angle& start)
  {
    m_start = start;
  }

  /** Returns the end Angle of this InputAxis'
   * drawing span.
   *
   * @return the end Angle
   */
  const Angle&
  get_end () const
  {
    return m_end;
  }

  /** Sets the end Angle of this InputAxis'
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

  /** Returns the DrawerProperties that will be used
   * to draw this InputAxis.
   *
   * @return the DrawerProperties
   */
  const DrawerProperties<>&
  get_prop () const
  {
    return m_prop;
  }

  /** Sets the DrawerProperties that will be used to
   * draw this InputAxis.
   *
   * @param prop the DrawerProperties to set
   */
  void
  set_prop (const DrawerProperties<>& prop)
  {
    m_prop = prop;
  }

  /** Returns the SimpleScale of this InputAxis. This
   * scale instance defines how the graphical scale will
   * be drawn.
   *
   * @return the SimpleScale
   */
  const SimpleScale&
  get_scale () const
  {
    return m_scale;
  }

  /** Constructs a label using the given TextProperties'
   * style and this InputAxis' variable name.
   *
   * @param prop
   */
  Label
  make_label (const TextProperties& prop) const
  {
    return Label (m_variable.name, prop);
  }

  /** Calculates the frequencies of the Histogram.
   *
   * @param data the data used
   */
  void
  calculate_histogram (const std::vector<double>& data);
};

#endif /* INPUTAXIS_H_ */
