#ifndef TEXTPROPERTIES_H_
#define TEXTPROPERTIES_H_

#include <string>
#include <Color.h>

/** TextProperties can be used to control font, size, color and style of
 * a drawn text.
 *
 * @brief Properties to modify a MooViE Drawers text style
 *
 * @authors beyss, stratmann
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
  bool bold;
  /** The skewness of the text */
  bool italic;

  /** Creates a TextProperties instance with the given style information.
   *
   * @param font_name_
   * @param font_size_
   * @param color_
   * @param bold_
   * @param italic_
   */
  TextProperties (const std::string& font_name_, double font_size_,
		  const Color& color_ = Color::BLACK, bool bold_ = false,
		  bool italic_ = false) :
      font_name (font_name_), font_size (font_size_), color (color_), bold (
	  bold_), italic (italic_)
  {
  }
};


#endif /* TEXTPROPERTIES_H_ */
