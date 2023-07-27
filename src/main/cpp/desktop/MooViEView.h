#ifndef MOOVIEVIEW_H
#define MOOVIEVIEW_H

#include <QGraphicsView>
#include <QSvgRenderer>
#include <QGraphicsSvgItem>
#include <QKeyEvent>
#include <QEvent>
#include <QChildEvent>
#include <QPointer>

QT_BEGIN_NAMESPACE
class QPaintEvent;
QT_END_NAMESPACE


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
class MooViEView : public QGraphicsView
{
Q_OBJECT

private:
  /** Initial Zoom value (ratio of image to vie area) */
  static constexpr double ZOOM_INIT = 0.9;
  /** Increase/Decrease factor of the zoom */
  static constexpr double ZOOM_DELTA = 0.1;
  /** Minimum Zoom factor */
  static constexpr double ZOOM_MIN = 0.1;
  /** Maximum Zoom factor */
  static constexpr double ZOOM_MAX = 20;


  /** The maximum of width/height of the last rendered svg */
  double m_min_gui_size;

  QGraphicsSvgItem *m_svgItem;

  QImage m_image;

  /** child of the QGraphicsView (needed to steel events */
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

  void openFile(const QString &fileName);

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


  void zoomBy(qreal factor);




};

#endif // MOOVIEVIEW_H
