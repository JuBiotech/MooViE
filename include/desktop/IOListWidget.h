#ifndef IOLISTWIDGET_H
#define IOLISTWIDGET_H

#include <QWidget>
#include <Scene.h>

namespace Ui
{
  class IOListWidget;
}

/** A widget that displays  properties of a MooViE
 * input/output variable that can be changed by the user.
 * In the MooViE desktop application this widget enables
 * interactivity with the MooViE scene. The user can change
 * if the corresponding input/output variable should be
 * active or its domain.
 *
 * @brief list item for a MooviE io variable
 *
 * @date
 * @author stratmann
 */
class IOListWidget : public QWidget
{
Q_OBJECT

private:
  /** Qt generated user interface */
  Ui::IOListWidget* m_ui;

  /** Indicates change of the on/of switch */
  bool m_toggle_dirty;

  /** Indicates change of the var boundries */
  bool m_bounds_dirty;

public:
  /** Creates an IOListWidget by a given MooViE
   * input/output variable. Reads its properties and
   * paste the values in subwidgets.
   *
   * @param var the MooViE io variable
   * @param parent parent widget
   */
  explicit
  IOListWidget (const DefVariable& var, QWidget *parent = 0);

  /** Destructor.
   */
  ~IOListWidget ();

  /** Returns the name of this MooViE input/output
   * variable.
   *
   * @return the io variable name
   */
  QString
  get_name () const;

  /** Returns whether or not this MooViE input/output
   * variable is active.
   *
   * @return is io variable active
   */
  bool
  get_toggle () const;

  /** Returns the lower bound of this MooViE
   * input/output variable.
   *
   * @return minimum io variable value
   */
  double
  get_min () const;

  /** Returns the upper bound of this MooViE
   * input/output variable.
   *
   * @return maximum io variable value
   */
  double
  get_max () const;

  /** Checks if the user has altered the state
   * of the on/off switch.
   *
   * @return if switch is changed
   */
  bool
  is_toggle_dirty () const;

  /** Checks if the user has altered the bounds.
   *
   * @return if bounds are changed
   */
  bool
  are_bounds_dirty () const;

  /** Sets the dirty status of the on/off switch
   * to false. Should be called if changes have
   * been applied to the MooViE scene.
   */
  void
  set_toggle_not_dirty ();

  /** Sets the dirty status of the bounds to false.
   * Should be called if changes have been applied
   * to the MooViE scene.
   */
  void
  set_bounds_not_dirty ();

private slots:
  /** Is called when the on/off switch (radiobutton)
   * is clicked.
   */
  void
  on_toggle_rbtn_clicked ();

  /** Is called if the lower bound (double
   * spinbox) has been changed.
   *
   * @param min new min value of io variable
   */
  void
  on_lower_dbox_valueChanged (double min);

  /** Is called if the upper bound (double
   * spinbox) has been changed.
   *
   * @param max new max value of io variable
   */
  void
  on_upper_dbox_valueChanged (double max);
};

#endif // IOLISTWIDGET_H
