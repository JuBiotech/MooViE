#ifndef IOLIST_H
#define IOLIST_H

#include <QListWidget>
#include <QDropEvent>
#include <QMouseEvent>
#include <vector>
#include "IOListWidget.h"

/** A list widget containing elements that display
 * the properties of MooViE variables. The element
 * order can be exchanged using drag-and-drop. The
 * result is translated internally into a format that
 * can be applied onto a MooViE scene.
 *
 * @brief a list of MooViE variable properties
 *
 * @date
 * @author stratmann
 */
class IOList : public QListWidget
{
  Q_OBJECT
public:
  /** Stores a position exchange of the variable
   * property widgets. This information is used to
   * reconstruct drag-and-drop events in a MooViE
   * scene.
   */
  struct Swap
  {
    /** Position of the first element */
    int before_pos;

    /** Position of the second element */
    int after_pos;

    /** Creates a Swap by the previous positions of
     * the two swapped elements.
     *
     * @param before_pos_ first elems previous position
     * @param after_pos_ second elems previous position
     */
    Swap (int before_pos_, int after_pos_) :
	before_pos (before_pos_), after_pos (after_pos_)
    {
    }
  };

private:
  /** List element exchanges */
  std::vector<Swap> m_swaps;

  /**  Intermediate storage for mouse clicks on elements */
  int m_before_pos;

  /** Indicates changes in the element order */
  bool m_dirty;

public:
  /** Creates an IOList.
   *
   * @param parent parent widget
   */
  explicit
  IOList (QWidget *parent = 0);

  /** Returns the list element exchanges that have
   * been applied to this list. Empty if list has
   * not been changed.
   *
   * @return list element exchanges
   */
  inline const std::vector<Swap>&
  get_swaps () const
  {
    return m_swaps;
  }

  /** Checks if the order of this lists element
   * have been changed.
   *
   * @return if order is changed
   */
  inline bool
  is_dirty () const
  {
    return m_dirty;
  }

  /** Sets the dirty status of this list to false
   * and removes all saved swaps.
   */
  inline void
  set_not_dirty ()
  {
    m_swaps.clear ();
    m_dirty = false;
  }

private slots:
  /** Is called if the user clicks on this list.
   *
   * @param event position information
   */
  virtual void
  mousePressEvent (QMouseEvent* event);

  /** Is called if the user drops an item in this
   * list.
   *
   * @param event drop information
   */
  virtual void
  dropEvent (QDropEvent* event);
};

#endif // IOLIST_H
