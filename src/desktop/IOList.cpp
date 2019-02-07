#include <IOList.h>

IOList::IOList()
    : QListWidget(), before_pos(0), dirty(false)
{}

void IOList::mousePressEvent(QMouseEvent* event)
{
    QListWidget::mousePressEvent(event);

    IOListWidget* selected = dynamic_cast<IOListWidget*>(this->itemWidget(this->currentItem()));
    for (int i = 0; i < this->count(); ++i)
    {
        IOListWidget* widget = dynamic_cast<IOListWidget*>(this->itemWidget(this->item(i)));
        if (widget->get_name().compare(selected->get_name()) == 0)
        {
            before_pos = i;
            return;
        }
    }
}

void IOList::dropEvent(QDropEvent* event)
{
    IOListWidget* selected = dynamic_cast<IOListWidget*>(this->itemWidget(this->currentItem()));

    if (selected)
    {
    	QListWidget::dropEvent(event);
    }
    else
    {
    	return;
    }

    for (int i = 0; i < this->count(); ++i)
    {
        IOListWidget* widget = dynamic_cast<IOListWidget*>(this->itemWidget(this->item(i)));
        if (widget->get_name().compare(selected->get_name()) == 0)
        {
            if (before_pos < i)
            {
                int pos = before_pos;

                swaps.emplace_back(before_pos, ++pos);
                while (pos < i)
                {
                    swaps.emplace_back(pos, pos + 1);
                    ++pos;
                }
                dirty = true;
            }
            else if (before_pos > i)
            {
                int pos = before_pos;

                swaps.emplace_back(before_pos, --pos);
                while (pos > i)
                {
                    swaps.emplace_back(pos, pos - 1);
                    --pos;
                }
                dirty = true;
            }

            return;
        }
    }
}
