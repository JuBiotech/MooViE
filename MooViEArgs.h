/*
 * MooViEArgs.h
 *
 *  Created on: 28.11.2017
 *      Author: IBT\stratmann
 */

#ifndef MOOVIEARGS_H_
#define MOOVIEARGS_H_

#include <string>
#include <cstring>
#include <exception>
#include <regex>

/** Argument storage for MooViE.
 *
 */
class MooViEArgs {
private:
	static const std::string SOPT_WIDTH;
	static const std::string LOPT_WIDTH;
	static const std::string SOPT_HEIGHT;
	static const std::string LOPT_HEIGHT;
	static const std::string SOPT_OUTPUT;
	static const std::string LOPT_OUTPUT;
	static const std::string SOPT_FILE_T;
	static const std::string LOPT_FILE_T;
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
	static MooViEArgs parse_from_commandline(int argc, char const * argv[]);
	inline int width() const { return _width; }
	inline int height() const { return _height; }
	inline const std::string & output_file() const { return _output_file; }
	inline const std::string & input_file() const { return _input_file; }
	inline File_t file_type() const { return _file_type; }

private:
	MooViEArgs(int width, int height, const std::string & output_file,
			const std::string & input_file, File_t file_type)
	: _width(width), _height(height), _output_file(output_file), _input_file(input_file), _file_type(file_type)
	{}
	const int 			_width, _height;
	const std::string 	_output_file, _input_file;
	const File_t		_file_type;
};

#endif /* MOOVIEARGS_H_ */
