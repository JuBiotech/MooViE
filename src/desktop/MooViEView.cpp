#include <MooViEView.h>
#include <iostream>

MooViEView::MooViEView(QWidget *parent) :
    QWebView(parent),
    zoom_active(false)
{
}

void MooViEView::adjust_zoom(int width, int height)
{
    int min = std::min(width, height);

    setZoomFactor(START_ZOOM_DIV / min);
}

void MooViEView::keyPressEvent (QKeyEvent* event)
{
    switch (event->key())
    {
	case Qt::Key_Control:
	    zoom_active = true;
	    break;
	case Qt::Key_Plus:
	    if (zoom_active)
	    {
		setZoomFactor(zoomFactor() + ZOOM_FACTOR);
	    }
	    break;
	case Qt::Key_Minus:
	  if (zoom_active)
	  {
		setZoomFactor(zoomFactor() - ZOOM_FACTOR);
	  }
	  break;
	default:
	    break;
    }
}

void MooViEView::keyReleaseEvent (QKeyEvent* event)
{
    if (event->key() == Qt::Key_Control)
    {
	zoom_active = false;
    }
}
