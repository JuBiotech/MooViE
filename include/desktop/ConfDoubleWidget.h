#ifndef CONFDOUBLEWIDGET_H
#define CONFDOUBLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QDoubleSpinBox>
#include <float.h>

namespace Ui
{
  class ConfDoubleWidget;
}

/** A widget that displays a double-typed configuration
 * value. The value can be changed by the user.
 *
 * @brief widget for double conf values
 *
 * @date
 * @author stratmann
 */
class ConfDoubleWidget : public QWidget
{
Q_OBJECT

private:
  /** Qt generated user interface */
  Ui::ConfDoubleWidget* m_ui;

  /** Editable double box */
  QDoubleSpinBox* m_value;

public:
  /** Creates a ConfDoubleWidget from its configuration
   * tag (identifier), initial value and restrictions. Also,
   * the number of possible decimal places and the spin box
   * step size are set.
   *
   * @param tag conf value name
   * @param init_val initial conf value
   * @param lower_restr lower bound of value
   * @param upper_restr upper bound of value
   * @param decimals number of editable decimal places
   * @param step default increase/decrease step
   * @param parent parent widget
   */
  explicit
  ConfDoubleWidget (const QString& tag, double init_val, double lower_restr =
			DBL_MIN,
		    double upper_restr = DBL_MAX, int decimals = 1,
		    double step = 0.1, QWidget *parent = nullptr);
  ~ConfDoubleWidget ();

  /** Returns the current value of the spin box.
   *
   * @return set double value
   */
  inline double
  get_value ()
  {
    return m_value->value ();
  }

  /** Sets the value of this widget.
   *
   * @param val value to set
   */
  inline void
  set_value (double val)
  {
    m_value->setValue (val);
  }
};

#endif // CONFDOUBLEWIDGET_H
