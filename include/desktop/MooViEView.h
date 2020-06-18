#ifndef MOOVIEVIEW_H
#define MOOVIEVIEW_H

#include <QWebEngineView>
#include <QKeyEvent>
#include <QWebEnginePage>
#include <QEvent>
#include <QChildEvent>
#include <QPointer>
#include <QOpenGLWidget>

/** A Viewer that is able to display the SVG
 * output files of MooViE. Unfortunately, QtSvg does
 * not support the full SVG standard and is therefore
 * not able to display MooViE scenes correctly.
 * QWebEngineView is used instead.
 * MooViEView implements a zoom function using Qt events.
 * The user can set the zoom factor by pressing
 * "CTRL" - "+"/"-" or  "CTRL" + mouse wheel.
 *
 * @brief viewer widget for MooViE scenes
 *
 * @date
 * @author stratmann
 */
class MooViEView : public QWebEngineView
{
Q_OBJECT

private:
  /** Parameter to calculate the adjusted zoom */
  static constexpr double ZOOM_ADJUST_FACTOR = 0.75;
  /** Increase/Decrease summand of the zoom */
  static constexpr double ZOOM_DELTA = 0.1;

  /** The maximum of width/height of the last rendered svg */
  double m_max_svg_size;

  /** Enabled if CTRL is pressed */
  bool m_zoom_active;
  
  /** child of the QWebEngineView (needed to steel events */
  QPointer<QObject> m_child;

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
  adjust_zoom_by_svg_size (int width, int height);

  /** Sets the zoom factor so that the size
   * of the displayed MooViE scene is adjusted
   * to the current size of the display.
   */
  void
  adjust_zoom ();
  
  bool
  event(QEvent * ev) override;

private slots:
  /** Is called when the widget is resized.
   *
   * @param event
   */
  void
  resizeEvent (QResizeEvent* event) override;
  
  
protected:
  /**
   * handles all kind of events. needed for zooming 
   */
  bool 
  eventFilter(QObject* obj, QEvent* event) override;


};

#endif // MOOVIEVIEW_H
