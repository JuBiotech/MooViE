#ifndef IOLIST_H
#define IOLIST_H

#include <QListWidget>
#include <QDropEvent>
#include <QMouseEvent>
#include <vector>
#include <IOListWidget.h>

class IOList : public QListWidget
{
public:
    struct Swap
    {
        int before_pos;
        int after_pos;

        Swap (int before_pos_, int after_pos_)
        : before_pos (before_pos_), after_pos (after_pos_) {}
    };

private:
    std::vector<Swap> swaps;
    int before_pos;
    bool dirty;

public:
    IOList ();

    inline const std::vector<Swap>& get_swaps() const
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

    virtual void mousePressEvent(QMouseEvent* event);

    virtual void dropEvent(QDropEvent* event);
};

#endif // IOLIST_H
