#include <MooViEView.h>
#include <iostream>

MooViEView::MooViEView (QWidget *parent) :
    QWebView (parent), m_zoom_active (false)
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

  setZoomFactor (ZOOM_ADJUST_FACTOR * min_gui_size / m_max_svg_size);
}

void
MooViEView::keyPressEvent (QKeyEvent* event)
{
  switch (event->key ())
    {
    case Qt::Key_Control:
      m_zoom_active = true;
      break;
    case Qt::Key_Plus:
      // Only increase if CTRL is pressed
      if (m_zoom_active)
	{
	  setZoomFactor (zoomFactor () + ZOOM_DELTA);
	}
      break;
    case Qt::Key_Minus:
      // Only decrease if CTRL is pressed
      if (m_zoom_active)
	{
	  setZoomFactor (zoomFactor () - ZOOM_DELTA);
	}
      break;
    default:
      break;
    }
}

void
MooViEView::keyReleaseEvent (QKeyEvent* event)
{
  if (event->key () == Qt::Key_Control)
    {
      m_zoom_active = false;
    }
}

void MooViEView::resizeEvent(QResizeEvent *event)
{
  QWebView::resizeEvent(event);

  adjust_zoom();
}