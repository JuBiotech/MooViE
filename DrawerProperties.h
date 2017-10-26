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

template<typename FillColor_t = Color>
class DrawerProperties
{
public:
	DrawerProperties(const double& lineWidth, const Color& lineColor,
			const FillColor_t& fillColor)
			: _lineWidth { lineWidth }, _lineColor { lineColor }, _fillColor {
					fillColor }
	{
	}

	const FillColor_t& fillColor() const
	{
		return _fillColor;
	}

	const Color& lineColor() const
	{
		return _lineColor;
	}

	double lineWidth() const
	{
		return _lineWidth;
	}

	DrawerProperties halfLineWidth() const
	{
		return DrawerProperties(lineWidth() * 0.5, lineColor(), fillColor());
	}

private:
	double _lineWidth;
	Color _lineColor;
	FillColor_t _fillColor;

};

class TextProperties
{
public:
	TextProperties(const std::string& font_name, double font_size,
			const Color& color = Color::BLACK, bool bold = false, bool italic =
					false)
			: _font_name(font_name), _font_size(font_size), _color(color), _bold(
					bold), _italic(italic)
	{

	}

	double bold() const
	{
		return _bold;
	}

	const Color& color() const
	{
		return _color;
	}

	const std::string& fontname() const
	{
		return _font_name;
	}

	double fontsize() const
	{
		return _font_size;
	}

	double italic() const
	{
		return _italic;
	}

private:
	std::string _font_name;
	double _font_size;
	Color _color;
	double _bold;
	double _italic;
};

#endif /* DRAWERPROPERTIES_H_ */
