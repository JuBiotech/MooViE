/*
 * MooViEArgs.cpp
 *
 *  Created on: 28.11.2017
 *      Author: IBT\stratmann
 */

#include "Args.h"

const std::string Args::HELP_STRING =
		"MooViE is a tool to display multi-dimensional data (R^n -> R^m) in a "
		"clear circular chart.\n"
		"usage: moovie [OPTION] [OPTION <PARAMETER>] DATAFILE\n"
		"List of MooViE options:\n"
		"-w, --width <WIDTH>\t\tSet width for output image.\n"
		"-h, --height <HEIGHT>\t\tSet height for output image.\n"
		"-o, --output <PATH>\t\tStore the output image under this path.\n"
		"-f, --file-type <FTYPE>\t\tReads data from a file of the given format.\n"
		"--help\t\t\t\tPrints help string.";

const std::string Args::SOPT_WIDTH = "-w";
const std::string Args::LOPT_WIDTH = "--width";
const std::string Args::SOPT_HEIGHT = "-h";
const std::string Args::LOPT_HEIGHT = "--height";
const std::string Args::SOPT_OUTPUT = "-o";
const std::string Args::LOPT_OUTPUT = "--output-file";
const std::string Args::SOPT_CONFIG = "-c";
const std::string Args::LOPT_CONFIG = "--configuration-file";
const std::string Args::SOPT_FILE_T = "-f";
const std::string Args::LOPT_FILE_T = "--file-type";
const std::string Args::LOPT_HELP = "--help";
const std::regex Args::OPT_REGEX("-[-]?\\S+");

Args Args::parse_from_commandline(int argc, char const * argv[])
{
	int width, height;
	std::string output_file, input_file, config_file;
	File_t file_type;
	bool help = false;

	bool widthSet = false, heightSet = false, outputFSet = false,
			inputFSet = false, configFSet = false, ftypeSet = false, helpSet = false;

	for (int i = 1; i < argc; ++i) {
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
						"output file option expected an positional parameter, but none was given.");
			} else if (std::regex_match(argv[i + 1], OPT_REGEX)) {
				throw ParseException(
						"output file option expected an positional parameter, but found option.");
			} else {
				output_file = argv[++i];
				outputFSet = true;
			}
		} else if (argv[i] == SOPT_CONFIG or argv[i] == LOPT_CONFIG) {
			if (configFSet) {
				throw ParseException(
						"configuration file parameter was tried to set multiple times.");
			} else if (i + 1 >= argc) {
				throw ParseException(
						"configuration file option expected an positional parameter, but none was given.");
			} else if (std::regex_match(argv[i + 1], OPT_REGEX)) {
				throw ParseException(
						"configuration file option expected an positional parameter, but found option.");
			} else {
				config_file = argv[++i];
				configFSet = true;
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
					file_type = Args::File_t::CSV;
				} else {
					throw ParseException("Given file type is not supported.");
				}
				ftypeSet = true;
			}
		} else if (argv[i] == LOPT_HELP)
		{
			if (helpSet)
			{
				throw ParseException("help option was tried to set multiple times.");
			} else {
				help = true;
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

	if (!inputFSet) throw ParseException("Expected one non-positional parameter.");

	return Args(width, height, output_file, input_file, config_file, file_type, help,
			widthSet, heightSet, outputFSet, configFSet, ftypeSet);
}

