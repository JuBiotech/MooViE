#include <MooViEView.h>
#include <iostream>
#include <qmath.h>
#include <QDebug>

MooViEView::MooViEView (QWidget *parent) :
    QWebEngineView (parent), m_zoom_active (false), m_cumulative_zoom(0.),
    m_child(nullptr)
{
}

void
MooViEView::adjust_zoom_by_svg_size (int width, int height)
{
  // Using smaller dim sizes (the smaller, the more zoom)
  m_max_svg_size = std::max (width, height);

  // Use svg dims to adjust zoom
  adjust_zoom();
}

void
MooViEView::adjust_zoom ()
{
  QSize size = this->size();
  double min_gui_size = std::min (size.width(), size.height());
  double zoom_factor = ZOOM_ADJUST_FACTOR * min_gui_size / m_max_svg_size + m_cumulative_zoom;

  setZoomFactor (zoom_factor);
}

bool MooViEView::eventFilter(QObject* obj, QEvent* event)
{
  if (event->type()==QEvent::KeyPress)
  {
    bool handled = false;
    QKeyEvent* key = static_cast<QKeyEvent*>(event);
    switch (key->key ())
    {
    case Qt::Key_Control:
      m_zoom_active = true;
      break;
    case Qt::Key_Plus:
      // Only increase if CTRL is pressed
      if (m_zoom_active)
	{
	  setZoomFactor (zoomFactor () + ZOOM_DELTA);
	  m_cumulative_zoom += ZOOM_DELTA;
	}
      break;
    case Qt::Key_Minus:
      // Only decrease if CTRL is pressed
      if (m_zoom_active)
	{
	  setZoomFactor (zoomFactor () - ZOOM_DELTA);
      m_cumulative_zoom -= ZOOM_DELTA;
	}
      break;
    default:
      break;
    }
    return handled ? true : QWebEngineView::eventFilter(obj, event);
  }
  else if (event->type()==QEvent::KeyRelease)
  {
    QKeyEvent* key = static_cast<QKeyEvent*>(event);
    if (key->key() == Qt::Key_Control)
    {
      m_zoom_active = false;
      return true;
    }
    else
    {
      return QWebEngineView::eventFilter(obj, event);
    }
  }
  else if (m_zoom_active && event->type() == QEvent::Wheel)
  {
    QWheelEvent* wheel = static_cast<QWheelEvent*>(event);
    qreal factor = qPow(1.2, wheel->delta() / 240.0);
    qreal zoom = zoomFactor() * factor;
    m_cumulative_zoom += (zoom - zoomFactor());
    setZoomFactor(zoom);
    return true;
  }
  // we do not want the context menu, therefore we disable the right mouse button
  else if (event->type() == QEvent::MouseButtonPress)
  {
    QMouseEvent* mouse = static_cast<QMouseEvent*>(event);
    if (mouse->button() == Qt::RightButton)
    {
      return true;
    }
    return QWebEngineView::eventFilter(obj, event);
  }
  else if (event->type() == QEvent::MouseButtonDblClick)
  {
    return true;
  }
  else
  {
    QWebEngineView::eventFilter(obj, event);
  }
  return false;
}

bool MooViEView::event(QEvent* ev)
{
  if (ev->type() == QEvent::ChildPolished)
  {
    //install event filter on every child, so we can steel their events
    QChildEvent *child_ev = static_cast<QChildEvent*>(ev);
    m_child = child_ev->child();

    if (m_child)
    {
      m_child->installEventFilter(this);
    }
  }
  return QWebEngineView::event(ev);
}

void MooViEView::resizeEvent(QResizeEvent *event)
{
  QWebEngineView::resizeEvent(event);

  adjust_zoom();
}
