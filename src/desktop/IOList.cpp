#include <IOList.h>

IOList::IOList()
    : QListWidget(), before_pos(0), dirty(false)
{}

void IOList::dragLeaveEvent(QDragLeaveEvent* event)
{
    QListWidget::dragLeaveEvent(event);

    IOListWidget* sel = dynamic_cast<IOListWidget*>(this->itemWidget(this->currentItem()));
    for (int i = 0; i < this->count(); ++i)
    {
        IOListWidget* wid = dynamic_cast<IOListWidget*>(this->itemWidget(this->item(i)));
        if (wid->get_name().compare(sel->get_name()) == 0)
        {
            before_pos = i;
            return;
        }
    }
}

void IOList::dropEvent(QDropEvent* event)
{
    QListWidget::dropEvent(event);

    IOListWidget* chng = dynamic_cast<IOListWidget*>(this->itemWidget(this->itemAt(event->pos())));
    for (int i = 0; i < this->count(); ++i)
    {
        IOListWidget* wid = dynamic_cast<IOListWidget*>(this->itemWidget(this->item(i)));
        if (wid->get_name().compare(chng->get_name()) == 0)
        {
            if (before_pos < i)
            {
                int pos = before_pos;

                swaps.push_back(Swap{before_pos, ++pos});
                while (pos < i)
                {
                    swaps.push_back(Swap{pos, pos + 1});
                    ++pos;
                }
                dirty = true;
            }
            else if (before_pos > i)
            {
                int pos = before_pos;

                swaps.push_back(Swap{before_pos, --pos});
                while (pos > i)
                {
                    swaps.push_back(Swap{pos, pos - 1});
                    --pos;
                }
                dirty = true;
            }
            else {
                swaps.pop_front();
            }
            return;
        }
    }
}
