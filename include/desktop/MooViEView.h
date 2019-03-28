#ifndef MOOVIEVIEW_H
#define MOOVIEVIEW_H

#include <QWebView>
#include <QKeyEvent>
#include <QWebFrame>

/** A Viewer that is able to display the SVG
 * output files of MooViE. Unfortunately, QtSvg does
 * not support the full SVG standard and is therefore
 * not able to display MooViE scenes correctly.
 * QWebView is used instead.
 * MooViEView implements a zoom function using Qt events.
 * The user can set the zoom factor by pressing
 * "CTRL" + "+".
 *
 * @brief viewer widget for MooViE scenes
 *
 * @date
 * @author stratmann
 */
class MooViEView : public QWebView
{
Q_OBJECT

private:
  /** Parameter to calculate the adjusted zoom */
  static constexpr double START_ZOOM_DIV = 600.;
  /** Increase/Decrease summand of the zoom */
  static constexpr double ZOOM_DELTA = 0.1;

  /** Enabled if CTRL is pressed */
  bool m_zoom_active;

public:
  /** Creates a MooViE viewer.
   *
   * @param parent parent widget
   */
  explicit
  MooViEView (QWidget *parent = 0);

  /** Sets the zoom factor so that the size
   * of the displayed MooViE scene is adjusted
   * to the current size of the display.
   *
   * @param width width of the MooViE scene
   * @param height height of the MooViE scene
   */
  void
  adjust_zoom (int width, int height);

private slots:
  /** Is called when a key is pressed while
   * this widget is selected.
   *
   * @param event holds the pressed key's ID
   */
  void
  keyPressEvent (QKeyEvent* event);

  /** Is called when a key is released while
   * this widget is selected.
   *
   * @param event holds the released key's ID
   */
  void
  keyReleaseEvent (QKeyEvent* event);
};

#endif // MOOVIEVIEW_H