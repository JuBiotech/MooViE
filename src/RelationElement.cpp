/*
 * DataLink.cpp
 *
 *  Created on: 12.12.2017
 *      Author: IBT\stratmann
 */

#include <RelationElement.h>
#include "CairoDrawer.h"

RelationElementFactory::RelationElementFactory(
		std::size_t _num_data_rows,
		const CodomainGrid& _grid,
		const std::vector<DomainAxis>& _axis)
: grid(_grid), axis(_axis)
{
	line_width = 0.1 * (1 + std::exp(-(_num_data_rows * 0.0006)));
	line_alpha = 0.3 * (1 + 3 * std::exp(-(_num_data_rows * 0.04)));
	fill_alpha = 0.25 * (1 + 3 * std::exp(-(_num_data_rows * 0.04)));

	std::pair<double, double> out = std::make_pair(
						grid.get_start().value(),
						grid.get_start() > grid.get_end() ?
								grid.get_end().value() + 2 * M_PIl : grid.get_end().value()
					);

	const MultiScale& scale = grid.get_scale();
	for (size_t i = 0; i < scale.get_scale_number(); ++i)
	{
		output_mapper.emplace_back(
				scale.get_extremes(i),
				out
		);
	}

	for (const DomainAxis& elem: axis)
	{
		input_mapper.emplace_back(
				elem.get_scale().get_extremes(),
				std::make_pair(elem.get_start().value(), elem.get_end().value())
		);
	}
}

RelationElement RelationElementFactory::create(const DefDataRow & row) const
{
	RelationElement elem;
	std::size_t num_inputs = axis.size(),
			num_cols = row.size();

	for (std::size_t i = 0; i < num_inputs; ++i)
	{
		elem.emplace_back(
				Polar(axis[i].get_radius(), input_mapper[i].map(row[i].value)),
				DrawerProperties<>(
						line_width,
						Color(axis[i].get_prop().fill_color, line_alpha),
						Color(axis[i].get_prop().fill_color, fill_alpha)
				)
		);
	}

	Color line(get_color(row[num_inputs].value), line_alpha);
	Color fill(line.r(), line.g(), line.b(), fill_alpha);
	DrawerProperties<> prop(line_width, line, fill);
	elem.emplace_back(
			Polar(
				grid.get_radius() - CairoDrawer::CONNECTOR_DELTA,
				output_mapper[0].map(row[num_inputs].value)
			),
			prop
	);

	double height_factor = grid.get_height() / (grid.get_num_outputs() - 0.5);
	for (std::size_t i = 0; i < num_cols - num_inputs; ++i)
	{
		elem.emplace_back(
				Polar(
					grid.get_radius()
						+ Configuration::get_instance().get_output_thickness()
						+ i * height_factor,
					output_mapper[i].map(row[i + num_inputs].value)
				),
				prop
		);
	}

	return elem;
}

const Color& RelationElementFactory::get_color(double val) const
{
	double range = angle_helper::rad_dist(
				grid.get_start().value(),
				grid.get_end().value()
			);
	double angle = output_mapper[0].map(val);

	std::size_t i = std::ceil(10 * (angle - grid.get_start().value()) / range);

	return Configuration::GLOW_10[i - 1];
}
