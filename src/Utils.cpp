#include <Utils.h>

namespace Util
{

  std::string
  read_file (const std::string & fpath)
  {
    std::ifstream in (fpath);
    if (in)
      {
	std::ostringstream content;
	content << in.rdbuf ();
	return content.str ();
      }
    else
      {
	throw std::invalid_argument ("invalid file path: " + fpath);
      }
  }

  void
  write_file (const std::string & fpath, const std::string & content)
  {
    std::ofstream out (fpath);
    if (out)
      {
	out << content;
      }
    else
      {
	throw std::invalid_argument ("invalid file path: " + fpath);
      }
  }

  std::vector<std::string>
  split (const std::string & str, const std::string & delims, bool remove_empty,
	 bool quoted_names)
  {
    std::vector<std::string> res;
    std::size_t prev = 0;
    bool qouted = false;

    for (std::size_t i = 0; i < str.length (); ++i)
      {
	if (quoted_names and str[i] == '"')
	  {
	    qouted = not qouted;
	  }

	if (quoted_names and qouted)
	  {
	    continue;
	  }

	if (i + delims.length () <= str.length ()
	    && str.compare (i, delims.length (), delims) == 0)
	  {
	    const std::string & part = str.substr (prev, i - prev);
	    if (not (remove_empty and part.empty ()))
	      {
		res.push_back (part);
	      }
	    prev = i + delims.length ();
	  }
      }
    if (prev < str.length ())
      {
	const std::string & part = str.substr (prev, str.length () - prev);

	if (quoted_names and qouted and part.find ('"') != std::string::npos)
	  {
	    throw std::invalid_argument ("missing qouted name bracket");
	  }

	if (not (remove_empty and part.empty ()))
	  {
	    res.push_back (part);
	  }
      }

    return res;
  }

  std::string
  strip (const std::string & str)
  {
    if (str.empty ())
      {
	return str;
      }

    std::size_t leading = str.find_first_not_of (' '), trailing =
	str.find_last_not_of (' ');
    return str.substr (leading, trailing - leading + 1);
  }

}
