/*
 * MooViEArgs.h
 *
 *  Created on: 28.11.2017
 *      Author: IBT\stratmann
 */

#ifndef ARGS_H_
#define ARGS_H_

#include <string>
#include <cstring>
#include <exception>
#include <regex>

/** Argument storage for MooViE.
 *
 */
class Args {
public:
	static const std::string HELP_STRING;
private:
	static const std::string SOPT_WIDTH;
	static const std::string LOPT_WIDTH;
	static const std::string SOPT_HEIGHT;
	static const std::string LOPT_HEIGHT;
	static const std::string SOPT_OUTPUT;
	static const std::string LOPT_OUTPUT;
	static const std::string SOPT_CONFIG;
	static const std::string LOPT_CONFIG;
	static const std::string SOPT_FILE_T;
	static const std::string LOPT_FILE_T;
	static const std::string SOPT_HELP;
	static const std::string LOPT_HELP;
	static const std::regex OPT_REGEX;
public:
	enum File_t {
		CSV, NOT_SUPPORTED
	};
	class ParseException : public std::exception
	{
	public:
		ParseException(const std::string & msg) : _msg(msg) {}
		virtual char const * what() { return _msg.c_str(); }
	private:
		const std::string _msg;
	};

public:
	static Args parse_from_commandline(int argc, char const * argv[]);

	inline int width() const { return _width; }
	inline int height() const { return _height; }
	inline const std::string & output_file() const { return _output_file; }
	inline const std::string & input_file() const { return _input_file; }
	inline File_t file_type() const { return _file_type; }
	inline bool help() const { return _help; }

	inline bool has_width() const { return _has_width; };
	inline bool has_height() const { return _has_height; };
	inline bool has_output_file() const { return _has_output_file; };
	inline bool has_config_file() const { return _has_config_file; };
	inline bool has_file_type() const { return _has_file_type; };

private:
	Args(int width, int height, const std::string & output_file,
			const std::string & input_file, const std::string & config_file,
			File_t file_type, bool help,
			bool has_width, bool has_height, bool has_output_file,
			bool has_config_file, bool has_file_type)
	: _width(width), _height(height), _output_file(output_file),
	  _input_file(input_file), _config_file(config_file),
	  _file_type(file_type), _help(help),
	  _has_width(has_width), _has_height(has_height),
	  _has_output_file(has_output_file), _has_config_file(has_config_file),
	  _has_file_type(has_file_type)
	{}

	const int 			_width, _height;
	const std::string 	_output_file, _input_file, _config_file;
	const File_t		_file_type;
	bool				_help;

	bool				_has_width, _has_height, _has_output_file,
							_has_config_file, _has_file_type;
};

#endif /* ARGS_H_ */
