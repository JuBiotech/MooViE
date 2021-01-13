#ifndef CONFINTWIDGET_H
#define CONFINTWIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <limits.h>

namespace Ui
{
  class ConfIntWidget;
}

/** A widget that displays a integer-typed configuration
 * value. The value can be changed by the user.
 *
 * @brief widget for int conf values
 *
 * @date
 * @author stratmann
 */
class ConfIntWidget : public QWidget
{
Q_OBJECT

private:
  /** Qt generated user interface */
  Ui::ConfIntWidget* m_ui;

  /** Editable integer box */
  QSpinBox* m_value;

public:
  /** Creates a ConfIntWidget from its configuration
   * tag (identifier), initial value and restrictions.
   *
   * @param tag conf value name
   * @param init_val initial conf value
   * @param lower_restr lower bound of value
   * @param upper_restr upper bound of value
   * @param parent parent widget
   */
  explicit
  ConfIntWidget (const QString& tag, int init_val, int lower_restr = INT_MIN,
		 int upper_restr = INT_MAX, QWidget *parent = nullptr);

  /** Destructor.
   */
  ~ConfIntWidget ();

  /** Returns the current value of the spin box.
   *
   * @return set integer value
   */
  inline int
  get_value ()
  {
    return m_value->value ();
  }

  /** Sets the value of this widget.
   *
   * @param val value to set
   */
  inline void
  set_value (int val)
  {
    m_value->setValue (val);
  }
};

#endif // CONFINTWIDGET_H
