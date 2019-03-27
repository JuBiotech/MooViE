#ifndef MOOVIEVIEW_H_
#define MOOVIEVIEW_H_

#include <QWebView>
#include <QKeyEvent>
#include <QWebFrame>

class MooViEView : public QWebView
{
    Q_OBJECT

private:
    static constexpr double START_ZOOM_DIV = 600.;
    static constexpr double ZOOM_FACTOR = 0.1;

public:
    explicit MooViEView(QWidget *parent = 0);

    void adjust_zoom(int width, int height);

private slots:

    void keyPressEvent(QKeyEvent* event);

    void keyReleaseEvent(QKeyEvent* event);

private:
    bool zoom_active;
};

#endif // MOOVIEVIEW_H_
