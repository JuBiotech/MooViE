/*
 * Scene.cc
 *
 *  Created on: 28.08.2017
 *      Author: beyss
 */

#include "Scene.h"
#include "Config.h"

Scene::Scene(Drawer& drawer,
		const std::vector<Var>& inputs,
		const std::vector<Var>& outputs)
: _drawer(drawer)
{
	size_t num_inputs = inputs.size();
	size_t num_outputs = outputs.size();

	DrawerProperties<std::array<Color, 10>> properteis(1, Color::BLACK, Color::GLOW_10);

	_drawer.drawSplitAxis(200, 20, Angle(angle_helper::deg_to_rad(config::OUTPUT_BEGIN_ANGLE)),
			Angle(angle_helper::deg_to_rad(config::OUTPUT_END_ANGLE)), properteis,
			Drawer::Direction::DECREASING);

	_input_mapper.reserve(num_inputs);
	_output_mapper.reserve(num_outputs);

	double input_width = 180.0/(num_inputs) - config::INPUT_SEPERATION_ANGLE;

	for (size_t i = 0; i < num_inputs; ++i)
	{
		double start_angle_val = 90.0 + 0.5 * config::INPUT_SEPERATION_ANGLE +
				i * (input_width + config::INPUT_SEPERATION_ANGLE);
		double end_angle_val = start_angle_val + input_width;

		Angle start_angle(angle_helper::deg_to_rad(start_angle_val));
		Angle end_angle(angle_helper::deg_to_rad(end_angle_val));

		const Var& var = inputs.at(i);

		std::pair<double,double> extreme_vals = create_axis(var.min, var.max);

		//Angles will screw up the mapping :-(
		_input_mapper.push_back(Mapper(extreme_vals, std::make_pair(start_angle.get(), end_angle.get())));

		Ticks tick(10,10, extreme_vals, config::TICK_LABEL);
		Label label(var.name, config::VAR_LABEL);
		DrawerProperties<> prop(config::STROKE_WIDTH, Color::BLACK, Color::SET3.at(num_inputs, i));

		_drawer.drawAxis(config::INPUT_INNER_RADIUS, config::INPUT_THICKNESS,
				start_angle, end_angle, prop, Drawer::Direction::INCREASING, tick, label);

	}

	DrawerProperties<std::array<Color, 10>> properties(config::STROKE_WIDTH, Color::BLACK, Color::GLOW_10);
	_drawer.drawSplitAxis(config::OUTPUT_INNER_RADIUS, config::OUTPUT_THICKNESS,
			Angle(angle_helper::deg_to_rad(config::OUTPUT_BEGIN_ANGLE)),
			Angle(angle_helper::deg_to_rad(config::OUTPUT_END_ANGLE)),
			properties, Drawer::Direction::DECREASING);
}

void Scene::drawDataVector(std::vector<double> data)
{
}
