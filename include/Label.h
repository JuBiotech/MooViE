/*
 * Label.h
 *
 *  Created on: Apr 27, 2018
 *      Author: stratmann
 */

#ifndef LABEL_H_
#define LABEL_H_

#include <string>
#include <TextProperties.h>

/** A Label is a formatted text that is stored as a text string
 * and a TextProperties object.
 *
 * @brief The Label class
 *
 * @author stratmann
 * @date 27.04.2018
 */
class Label
{
public:
    /** Creates a Label from given text and TextProperties.
     *
     * @brief constructor
     *
     * @param text the text to be displayed
     * @param prop the TextProperties to be used
     */
    Label(const std::string& _text, const TextProperties& _prop)
    : text(_text), prop(_prop)
    {
    }

    /** Returns a const reference to this Labels text.
     *
     * @brief gets text
     *
     * @return a reference to the text
     */
    const std::string& get_text() const
    {
        return text;
    }

    /** Returns a const reference to this Labels TextProperties.
     *
     * @brief gets TextProperties
     *
     * @return a reference to the TextProperties
     */
    const TextProperties& get_properties() const
    {
        return prop;
    }
private:
    /** The text of this Label */
    std::string text;
    /** The TextProperties of this Label */
    TextProperties prop;
};


#endif /* LABEL_H_ */
