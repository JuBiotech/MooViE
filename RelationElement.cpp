/*
 * DataLink.cpp
 *
 *  Created on: 12.12.2017
 *      Author: IBT\stratmann
 */

#include "RelationElement.h"
#include "CairoDrawer.h"

std::size_t RelationElement::num_inputs = 0;

RelationElementFactory::RelationElementFactory(
		std::size_t num_data_rows,
		const CodomainGrid & grid,
		const std::vector<DomainAxis> & axis)
: _grid(grid), _axis(axis)
{
	RelationElement::num_inputs = axis.size();

	_line_width = 0.1 * (1 + std::exp(-(num_data_rows * 0.0006)));
	_line_alpha = 0.3 * (1 + 3 * std::exp(-(num_data_rows * 0.04)));
	_fill_alpha = 0.25 * (1 + 3 * std::exp(-(num_data_rows * 0.04)));

	std::pair<double, double> out = std::make_pair(
						grid.get_start().value(),
						grid.get_start() > grid.get_end() ?
								grid.get_end().value() + 2 * M_PIl : grid.get_end().value()
					);

	const MultiScale& scale = grid.get_scale();
	for (size_t i = 0; i < scale.get_scale_number(); ++i)
	{
		_output_mapper.emplace_back(
				scale.get_extremes(i),
				out
		);
	}

	for (const DomainAxis & elem: axis)
	{
		_input_mapper.emplace_back(
				elem.get_ticks().get_extremes(),
				std::make_pair(elem.get_start().value(), elem.get_end().value())
		);
	}
}

RelationElement RelationElementFactory::create(const DefDataRow & row) const
{
	RelationElement link;
	std::size_t num_inputs = _axis.size(),
			num_cols = row.size();

	for (std::size_t i = 0; i < num_inputs; ++i)
	{
		link.emplace_back(
				Polar(_axis[i].get_radius(), _input_mapper[i].map(row[i].value)),
				DrawerProperties<>(
						_line_width,
						Color(_axis[i].get_prop().fill_color, _line_alpha),
						Color(_axis[i].get_prop().fill_color, _fill_alpha)
				)
		);
	}

	Color line(get_color(row[num_inputs].value), _line_alpha);
	Color fill(line.r(), line.g(), line.b(), _fill_alpha);
	DrawerProperties<> prop(_line_width, line, fill);
	link.emplace_back(
			Polar(
				_grid.get_radius() - CairoDrawer::CONNECTOR_DELTA,
				_output_mapper[0].map(row[num_inputs].value)
			),
			prop
	);

	double height_factor = _grid.get_height() / (_grid.get_num_outputs() - 0.5);
	for (std::size_t i = 0; i < num_cols - num_inputs; ++i)
	{
		link.emplace_back(
				Polar(
					_grid.get_radius()
						+ Configuration::get_instance().get_output_thickness()
						+ i * height_factor,
					_output_mapper[i].map(row[i + num_inputs].value)
				),
				prop
		);
	}

	return link;
}

const Color & RelationElementFactory::get_color(double val) const
{
	double range = angle_helper::rad_dist(
				_grid.get_start().value(),
				_grid.get_end().value()
			);
	double angle = _output_mapper[0].map(val);

	std::size_t i = std::ceil(10 * (angle - _grid.get_start().value()) / range);

	return Configuration::GLOW_10[i - 1];
}
