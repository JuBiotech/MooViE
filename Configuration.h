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
	Configuration(const std::string & fname, std::size_t inputs);
	Configuration(const std::string & fname, std::size_t inputs, const std::string & fpath);

	inline const std::string & get_input_file() const {
		return _input_file;
	}

	inline const std::string & get_output_file() const {
		return _output_file;
	}

	inline void set_output_file(const std::string & output_file)
	{
		_output_file = output_file;
	}

	inline std::size_t get_inputs() const {
		return _inputs;
	}

	inline int get_width() const {
		return _width;
	}

	inline int get_height() const {
		return _height;
	}

	inline double get_input_inner_radius() const {
		return _input_inner_radius;
	}

	inline void set_input_inner_radius(double input_inner_radius) {
		_input_inner_radius = input_inner_radius;
	}

	inline double get_input_separation_angle() const {
		return _input_separation_angle;
	}

	inline void set_input_separation_angle(double input_separation_angle) {
		_input_separation_angle = input_separation_angle;
	}

	inline double get_input_thickness() const {
		return _input_thickness;
	}

	inline void set_input_thickness(double input_thickness) {
		_input_thickness = input_thickness;
	}

	inline double get_output_inner_radius() const {
		return _output_inner_radius;
	}

	inline void set_output_inner_radius(double output_inner_radius) {
		_output_inner_radius = output_inner_radius;
	}

	inline double get_output_thickness() const {
		return _output_thickness;
	}

	inline void set_output_thickness(double output_thickness) {
		_output_thickness = output_thickness;
	}

	inline double get_grid_size() const {
		return _grid_size;
	}

	inline void set_grid_size(double grid_size) {
		_grid_size = grid_size;
	}

	inline const DrawerProperties<> & get_prop_thick() const {
		return _prop_thick;
	}

	inline void set_propthick(const DrawerProperties<> & prop_thick) {
		_prop_thick = prop_thick;
	}

	inline const DrawerProperties<> & get_prop_thin() const {
		return _prop_thin;
	}

	inline void set_prop_thin(const DrawerProperties<> & prop_thin) {
		_prop_thin = prop_thin;
	}

	inline const TextProperties & get_tick_label() const {
		return _tick_label;
	}

	inline void set_ticklabel(const TextProperties & tick_label) {
		_tick_label = tick_label;
	}

	inline const TextProperties & get_var_label() const {
		return _var_label;
	}

	inline void set_var_label(const TextProperties& var_label) {
		_var_label = var_label;
	}

private:
	std::string 		_input_file;
	std::string			_output_file = "image.svg";

	std::size_t			_inputs;

	int 				_width = 500;
	int 				_height = 500;

	double 				_input_inner_radius = 150;
	double 				_input_thickness = 10;
	double 				_input_separation_angle = 5;

	double 				_output_inner_radius = 160;
	double 				_output_thickness = 10;
	double 				_grid_size = 150;

	DrawerProperties<> 	_prop_thick = {1, Color::BLACK, Color::BLACK};
	DrawerProperties<> 	_prop_thin = {0.5, Color::BLACK, Color::BLACK};

	TextProperties 		_tick_label = {"Liberation Serif", 8};
	TextProperties 		_var_label = {"Liberation Serif", 20};

	const std::regex 	mooviec_int;
	const std::regex 	mooviec_dbl;
	const std::regex 	mooviec_name;
};

#endif /* CONFIGURATION_H_ */
