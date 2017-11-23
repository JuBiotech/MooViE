/*
 * DrawerProperties.h
 *
 *  Created on: 05.07.2017
 *      Author: beyss
 */

#ifndef DRAWERPROPERTIES_H_
#define DRAWERPROPERTIES_H_

#include <algorithm>
#include "Color.h"

/** DrawerProperties can be used to control the line thinkness, stroke and
 * fill color of a Drawer.
 * @brief The DrawerProperties class
 * @author beyss
 * @date 05.07.2017
 */
template<typename FILL = Color>
class DrawerProperties
{
public:
    /** Creates a DrawerProperties instance storing the given line thinkness,
     * stroke and fill color of a Drawer.
     * @brief DrawerProperties
     * @param lineWidth the line width
     * @param lineColor the line color
     * @param fillColor the fill color
     */
    DrawerProperties(const double& lineWidth, const Color& lineColor, const FILL& fillColor)
    : _lineWidth { lineWidth }, _lineColor { lineColor }, _fillColor { fillColor }
    {
    }

    /** Getter function for the line width.
     * @brief lineWidth
     * @return the line width
     */
    double lineWidth() const
    {
            return _lineWidth;
    }

    /** Readonly access function for the line color.
     * @brief lineColor
     * @return a constant reference to the line color
     */
    const Color& lineColor() const
    {
        return _lineColor;
    }

    /** Readonly access function for the fill color.
     * @brief fillColor
     * @return a constant reference to the fill color
     */
    const FILL& fillColor() const
    {
        return _fillColor;
    }

    /** Creates a DrawerProperties instance with half the line width of this
     * DrawerProperties.
     * @brief halfLineWidth
     * @return the new DrawerProperties
     */
    DrawerProperties halfLineWidth() const
    {
        return DrawerProperties(lineWidth() * 0.5, lineColor(), fillColor());
    }

private:
    /** The line width */
    const double _lineWidth;
    /** Line color */
    const Color _lineColor;
    /** Fill color(s) */
    const FILL _fillColor;
};


/** TextProperties can be used to control font, size, color and style of
 * a drawn text.
 * @brief The TextProperties class
 * @author beyss
 * @date 05.07.2017
 */
class TextProperties
{
public:
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
    : _font_name(font_name), _font_size(font_size), _color(color), _bold(bold), _italic(italic)
    {
    }

    /** Readonly access function for the font name.
     * @brief fontname
     * @return a constant reference to the font name
     */
    const std::string& fontname() const
    {
        return _font_name;
    }

    /** Getter function for the font size.
     * @brief fontsize
     * @return the font size
     */
    double fontsize() const
    {
        return _font_size;
    }

    /** Readonly access function for the text color.
     * @brief color
     * @return a constant reference to the text color
     */
    const Color& color() const
    {
        return _color;
    }

    /** Getter function for the boldness.
     * @brief bold
     * @return the boldness
     */
    double bold() const
    {
        return _bold;
    }

    /** Getter function for the skewness.
     * @brief italic
     * @return the skewness
     */
    double italic() const
    {
        return _italic;
    }
private:
    /** The font name */
    std::string _font_name;
    /** The font size */
    double _font_size;
    /** The text color */
    Color _color;
    /** The boldness of the text */
    double _bold;
    /** The skewness of the text */
    double _italic;
};

#endif /* DRAWERPROPERTIES_H_ */
