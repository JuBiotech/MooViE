#ifndef CONFSTRINGWIDGET_H
#define CONFSTRINGWIDGET_H

#include <QWidget>
#include <QLineEdit>

namespace Ui
{
  class ConfStringWidget;
}

/** A widget that displays a string-typed configuration
 * value. The value can be changed by the user.
 *
 * @brief widget for string conf values
 *
 * @date
 * @author stratmann
 */
class ConfStringWidget : public QWidget
{
Q_OBJECT

private:
  /** Qt generated user interface */
  Ui::ConfStringWidget* m_ui;

  /** Editable text box */
  QLineEdit* m_text;

public:
  /** Creates a ConfStringWidget from its configuration
   * tag (identifier) and the initial value.
   *
   * @param tag conf value name
   * @param init_val initial text
   * @param parent parent widget
   */
  explicit
  ConfStringWidget (const QString& tag, const QString& init_val,
		    QWidget *parent = nullptr);

  /** Destructor.
   */
  ~ConfStringWidget ();

  /** Returns the current content of the text box.
   *
   * @return set text value
   */
  inline QString
  get_text ()
  {
    return m_text->text ();
  }

  /** Sets the value of this widget.
   *
   * @param txt value to set
   */
  inline void
  set_text (const QString& txt)
  {
    m_text->setText (txt);
  }
};

#endif // CONFSTRINGWIDGET_H
