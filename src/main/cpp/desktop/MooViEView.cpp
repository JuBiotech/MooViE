#include "MooViEView.h"
#include <iostream>
#include <qmath.h>
#include <QDebug>

#include <memory>

MooViEView::MooViEView (QWidget *parent) :
    QGraphicsView (parent), m_min_gui_size(0), m_svgItem(nullptr),
    m_child(nullptr)
{
    setScene(new QGraphicsScene(this));
    setTransformationAnchor(AnchorUnderMouse);
    setDragMode(ScrollHandDrag);
    setViewportUpdateMode(FullViewportUpdate);

    QSize size = this->size();
    m_min_gui_size = std::min (size.width(), size.height());

}

void
MooViEView::adjust_zoom_by_svg_size (int width, int height)
{
  // Using smaller dim sizes (the smaller, the more zoom)
  double max_svg_size = std::max (width, height);

  // calculate zoom_factor so that the longest axis of the images takes u
  // ZOOM_INIT portion of the shortest axis of the image field
  double zoom_factor = ZOOM_INIT * m_min_gui_size / max_svg_size;

  scale (zoom_factor, zoom_factor);
}

void
MooViEView::adjust_zoom ()
{
  // new size of the gui
  QSize size = this->size();
  double min_gui_size = std::min (size.width(), size.height());

  // calculate relative size change of the gui and rescale
  double zoom_factor = min_gui_size/m_min_gui_size;
  scale (zoom_factor, zoom_factor);

  // update the new gui size
  m_min_gui_size = min_gui_size;
}

bool MooViEView::eventFilter(QObject* obj, QEvent* event)
{
  if (event->type() == QEvent::Wheel)
  {
    QWheelEvent* wheel = static_cast<QWheelEvent*>(event);
    qreal factor = qPow(1.2, wheel->angleDelta().y() / 240.0);
    zoomBy(factor);
    return true;
  }
  else
  {
    QGraphicsView::eventFilter(obj, event);
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
  return QGraphicsView::event(ev);
}

void MooViEView::resizeEvent(QResizeEvent *event)
{
  QGraphicsView::resizeEvent(event);

  adjust_zoom();
}

void MooViEView::openFile(const QString &fileName)
{
    QGraphicsScene *s = scene();

    auto svgItem = std::make_unique<QGraphicsSvgItem>(fileName);
    if (!svgItem->renderer()->isValid())
        return;

    s->clear();
    resetTransform();

    m_svgItem = svgItem.release();
    m_svgItem->setFlags(QGraphicsItem::ItemClipsToShape);
    m_svgItem->setCacheMode(QGraphicsItem::NoCache);
    m_svgItem->setZValue(0);

    s->addItem(m_svgItem);
}

void MooViEView::zoomBy(qreal factor)
{
    const qreal currentZoom = transform().m11();
    if ((factor < 1 && currentZoom < ZOOM_MIN) || (factor > 1 && currentZoom > ZOOM_MAX))
        return;
    scale(factor, factor);
}


