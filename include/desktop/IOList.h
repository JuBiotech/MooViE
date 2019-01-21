#ifndef IOLIST_H
#define IOLIST_H

#include <QListWidget>
#include <QDropEvent>
#include <QDragLeaveEvent>
#include <QList>
#include <iostream>
#include <IOListWidget.h>

class IOList : public QListWidget
{
public:
    struct Swap
    {
        int before_pos;
        int after_pos;
    };

private:
    QList<Swap> swaps;
    int before_pos;
    bool dirty;

public:
    IOList ();

    inline const QList<Swap>& get_swaps() const
    {
        return swaps;
    }

    inline bool is_dirty() const
    {
        return dirty;
    }

    inline void not_dirty()
    {
        swaps.clear();
        dirty = false;
    }

    virtual void dragLeaveEvent(QDragLeaveEvent* event);

    virtual void dropEvent(QDropEvent* event);
};

#endif // IOLIST_H
