#include <MooViEView.h>
#include <iostream>

MooViEView::MooViEView (QWidget *parent) :
    QWebEngineView (parent), m_zoom_active (false)
{
}

void
MooViEView::adjust_zoom (int width, int height)
{
  // Using smaller dim sizes (the smaller, the more zoom)
  int min = std::min (width, height);

  setZoomFactor (START_ZOOM_DIV / min);
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
