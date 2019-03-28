#include <IOList.h>

IOList::IOList (QWidget *parent) :
    QListWidget (parent), m_before_pos (0), m_dirty (false)
{
}

void
IOList::mousePressEvent (QMouseEvent* event)
{
  QListWidget::mousePressEvent (event);

  // Cache the position of last element that has been clicked on
  IOListWidget* selected = dynamic_cast<IOListWidget*> (this->itemWidget (
      this->currentItem ()));
  for (int i = 0; i < this->count (); ++i)
    {
      IOListWidget* widget = dynamic_cast<IOListWidget*> (this->itemWidget (
	  this->item (i)));
      if (widget->get_name ().compare (selected->get_name ()) == 0)
	{
	  m_before_pos = i;
	  return;
	}
    }
}

void
IOList::dropEvent (QDropEvent* event)
{
  IOListWidget* selected = dynamic_cast<IOListWidget*> (this->itemWidget (
      this->currentItem ()));

  // Execute drop event and continue if drop is on this list
  if (selected)
    {
      QListWidget::dropEvent (event);
    }
  else
    {
      return;
    }

  for (int i = 0; i < this->count (); ++i)
    {
      IOListWidget* widget = dynamic_cast<IOListWidget*> (this->itemWidget (
	  this->item (i)));
      if (widget->get_name ().compare (selected->get_name ()) == 0)
	{
	  /* Calculate swaps. Because in the MooViE scene variables
	   * can only be swapped, a drag-and-drop event has to be
	   * translated into a swapping all variables between the
	   * drag and the drop position.
	   */
	  if (m_before_pos < i)
	    {
	      int pos = m_before_pos;

	      m_swaps.emplace_back (m_before_pos, ++pos);
	      while (pos < i)
		{
		  m_swaps.emplace_back (pos, pos + 1);
		  ++pos;
		}
	      m_dirty = true;
	    }
	  else if (m_before_pos > i)
	    {
	      int pos = m_before_pos;

	      m_swaps.emplace_back (m_before_pos, --pos);
	      while (pos > i)
		{
		  m_swaps.emplace_back (pos, pos - 1);
		  --pos;
		}
	      m_dirty = true;
	    }

	  return;
	}
    }
}
