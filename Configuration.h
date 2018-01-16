/*
 * Configuration.h
 *
 *  Created on: 16.01.2018
 *      Author: stratmann
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <string>
#include <vector>
#include <regex>
#include "Utils.h"
#include "DrawerProperties.h"

class Configuration {
public:
	Configuration() {};
	Configuration(const std::string & fpath);
public:
	std::string fname = "";

	size_t width = 500;
	size_t height = 500;

	double input_inner_radius = 150;
	double input_thickness = 10;

	double output_inner_radius = 160;
	double output_thickness = 10;
	double grid_size = 150;

	TextProperties tick_label = {"Liberation Serif", 8};
	TextProperties var_label = {"Liberation Serif", 20};

	DrawerProperties<> prop_thick = {1, Color::BLACK, Color::BLACK};
	DrawerProperties<> prop_thin = {0.5, Color::BLACK, Color::BLACK};
private:
	const std::regex mooviec_int;
	const std::regex mooviec_dbl;
	const std::regex mooviec_name;
};

#endif /* CONFIGURATION_H_ */
