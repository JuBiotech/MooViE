#ifndef CONFBOOLWIDGET_H
#define CONFBOOLWIDGET_H

#include <QWidget>
#include <QRadioButton>
#include <limits.h>

namespace Ui
{
  class ConfBoolWidget;
}

/** A widget that displays a integer-typed configuration
 * value. The value can be changed by the user.
 *
 * @brief widget for int conf values
 *
 * @date
 * @author stratmann
 */
class ConfBoolWidget : public QWidget
{
Q_OBJECT

private:
  /** Qt generated user interface */
  Ui::ConfBoolWidget* m_ui;

  /** Editable integer box */
  QRadioButton* m_value;

public:
  /** Creates a ConfBoolWidget from its configuration
   * tag (identifier) and initial value.
   *
   * @param tag conf value name
   * @param init_val initial conf value
   * @param parent parent widget
   */
  explicit
  ConfBoolWidget (const QString& tag, bool init_val, QWidget *parent = nullptr);

  /** Destructor.
   */
  ~ConfBoolWidget ();

  /** Returns the current value of the radio button.
   *
   * @return set boolean value
   */
  inline bool
  get_value ()
  {
    return m_value->isChecked ();
  }

  /** Sets the value of this widget.
   *
   * @param val value to set
   */
  inline void
  set_value (bool val)
  {
    m_value->setChecked (val);
  }
};

#endif // CONFBOOLWIDGET_H
