/*
 * TextProperties.h
 *
 *  Created on: Mar 23, 2018
 *      Author: stratmann
 */

#ifndef TEXTPROPERTIES_H_
#define TEXTPROPERTIES_H_

#include <string>
#include "Color.h"

/** TextProperties can be used to control font, size, color and style of
 * a drawn text.
 * @brief The TextProperties class
 * @author beyss
 * @date 05.07.2017
 */
struct TextProperties
{
	/** The font name */
	std::string font_name;
	/** The font size */
	double font_size;
	/** The text color */
	Color color;
	/** The boldness of the text */
	double bold;
	/** The skewness of the text */
	double italic;

	/**
     * @brief TextProperties
     * @param font_name
     * @param font_size
     * @param color
     * @param bold
     * @param italic
    */
	TextProperties(const std::string& font_name, double font_size, const Color& color = Color::BLACK,
                   bool bold = false, bool italic = false)
    : font_name(font_name), font_size(font_size), color(color), bold(bold), italic(italic)
    {}
};


#endif /* TEXTPROPERTIES_H_ */
