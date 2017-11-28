/*
 * MooViEArgs.cpp
 *
 *  Created on: 28.11.2017
 *      Author: IBT\stratmann
 */

#include "MooViEArgs.h"

const std::string MooViEArgs::SOPT_WIDTH = "-w";
const std::string MooViEArgs::LOPT_WIDTH = "--width";
const std::string MooViEArgs::SOPT_HEIGHT = "-h";
const std::string MooViEArgs::LOPT_HEIGHT = "--height";
const std::string MooViEArgs::SOPT_OUTPUT = "-o";
const std::string MooViEArgs::LOPT_OUTPUT = "--output";
const std::string MooViEArgs::SOPT_FILE_T = "-f";
const std::string MooViEArgs::LOPT_FILE_T = "--file-type";
const std::regex MooViEArgs::OPT_REGEX("-[-]?\\S+");

MooViEArgs MooViEArgs::parse_from_commandline(int argc, char const * argv[])
{
	int width, height;
	std::string output_file, input_file;
	File_t file_type;

	bool widthSet = false, heightSet = false, outputFSet = false, inputFSet = false, ftypeSet = false;

	for (std::size_t i = 1; i < argc; ++i) {
		if (argv[i] == SOPT_WIDTH or argv[i] == LOPT_WIDTH) {
			if (widthSet) {
				throw ParseException(
						"width parameter was tried to set multiple times.");
			} else if (i + 1 >= argc) {
				throw ParseException(
						"width option expected an positional parameter, but none was given.");
			} else if (std::regex_match(argv[i + 1], OPT_REGEX)) {
				throw ParseException(
						"width option expected an positional parameter, but found option.");
			} else {
				width = std::stoi(argv[++i]);
				widthSet = true;
			}
		} else if (argv[i] == SOPT_HEIGHT or argv[i] == LOPT_HEIGHT) {
			if (heightSet) {
				throw ParseException(
						"height parameter was tried to set multiple times.");
			} else if (i + 1 >= argc) {
				throw ParseException(
						"height option expected an positional parameter, but none was given.");
			} else if (std::regex_match(argv[i + 1], OPT_REGEX)) {
				throw ParseException(
						"height option expected an positional parameter, but found option.");
			} else {
				height = std::stoi(argv[++i]);
				heightSet = true;
			}
		} else if (argv[i] == SOPT_OUTPUT or argv[i] == LOPT_OUTPUT) {
			if (outputFSet) {
				throw ParseException(
						"output file parameter was tried to set multiple times.");
			} else if (i + 1 >= argc) {
				throw ParseException(
						"output option expected an positional parameter, but none was given.");
			} else if (std::regex_match(argv[i + 1], OPT_REGEX)) {
				throw ParseException(
						"output option expected an positional parameter, but found option.");
			} else {
				output_file = argv[++i];
				outputFSet = true;
			}
		} else if (argv[i] == SOPT_FILE_T or argv[i] == LOPT_FILE_T) {
			if (ftypeSet) {
				throw ParseException(
						"file type parameter was tried to set multiple times.");
			} else if (i + 1 >= argc) {
				throw ParseException(
						"file type option expected an positional parameter, but none was given.");
			} else if (std::regex_match(argv[i + 1], OPT_REGEX)) {
				throw ParseException(
						"file type option expected an positional parameter, but found option.");
			} else {
				size_t pos = ++i;
				if (argv[pos] == std::string("csv")) {
					file_type = MooViEArgs::File_t::CSV;
				} else {
					throw ParseException("Given file type is not supported.");
				}
				ftypeSet = true;
			}
		} else if (std::regex_match(argv[i], OPT_REGEX)) {
			throw ParseException("Unknown option");
		} else {
			if (inputFSet) {
				throw ParseException(
						"Expected only one non-positional parameter.");
			} else {
				input_file = argv[i];
				inputFSet = true;
			}
		}
	}

	return MooViEArgs(width, height, output_file, input_file, file_type);
}

