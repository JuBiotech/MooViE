#include "MooViEView.h"
#include <iostream>
#include <qmath.h>
#include <QDebug>

#include <memory>

MooViEView::MooViEView (QWidget *parent) :
    QGraphicsView (parent), m_zoom_active (false),
	m_cumulative_zoom(0.), m_renderer(Native), m_svgItem(nullptr),
    m_child(nullptr)
{
    setScene(new QGraphicsScene(this));
    setTransformationAnchor(AnchorUnderMouse);
    setDragMode(ScrollHandDrag);
    setViewportUpdateMode(FullViewportUpdate);

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
    if ((factor < 1 && currentZoom < 0.1) || (factor > 1 && currentZoom > 10))
        return;
    scale(factor, factor);
    std::cout << "Zooming by" << factor << std::endl;
}

void MooViEView::paintEvent(QPaintEvent *event)
{
    if (m_renderer == Image) {
        if (m_image.size() != viewport()->size()) {
            m_image = QImage(viewport()->size(), QImage::Format_ARGB32_Premultiplied);
        }

        QPainter imagePainter(&m_image);
        QGraphicsView::render(&imagePainter);
        imagePainter.end();

        QPainter p(viewport());
        p.drawImage(0, 0, m_image);

    } else {
        QGraphicsView::paintEvent(event);
    }
}

