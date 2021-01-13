#ifndef LABEL_H_
#define LABEL_H_

#include <string>
#include "TextProperties.h"

/** A Label is a formatted text that is stored as a text string
 * and a TextProperties object.
 *
 * @brief Text label MooViE component representation
 *
 * @author stratmann
 * @date 27.04.2018
 */
class Label
{
private:
  /** The text of this Label */
  std::string m_text;
  /** The TextProperties of this Label */
  TextProperties m_prop;
public:
  /** Creates a Label from given text and TextProperties.
   *
   * @param text the text to be displayed
   * @param prop the TextProperties to be used
   */
  Label (const std::string& text, const TextProperties& prop) :
      m_text (text), m_prop (prop)
  {
  }

  /** Returns a const reference to this Labels text.
   *
   * @return a reference to the text
   */
  const std::string&
  get_text () const
  {
    return m_text;
  }

  /** Returns a const reference to this Labels TextProperties.
   *
   * @return a reference to the TextProperties
   */
  const TextProperties&
  get_properties () const
  {
    return m_prop;
  }
};


#endif /* LABEL_H_ */
