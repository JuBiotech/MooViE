/*
 * Label.h
 *
 *  Created on: Apr 27, 2018
 *      Author: stratmann
 */

#ifndef LABEL_H_
#define LABEL_H_

#include <string>
#include "TextProperties.h"

/** A Label is a formatted text that is stored as a text string
 * and a TextProperties object.
 * @brief The Label class
 */
class Label
{
public:
    /**
     * @brief Label
     * @param text
     * @param prop
     */
    Label(const std::string& text, const TextProperties& prop)
    : _text(text), _prop(prop)
    {
    }

    /** Access function for this Label's text.
     * @brief text
     * @return a reference to text
     */
    const std::string& get_text() const
    {
        return _text;
    }

    /** Access function for this Label's TextProperties.
     * @brief prop
     * @return a reference to prop
     */
    const TextProperties& get_properties() const
    {
        return _prop;
    }
private:
    /** The text of this Label */
    std::string _text;
    /** The TextProperties of this Label */
    TextProperties _prop;
};


#endif /* LABEL_H_ */
