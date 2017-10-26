/*
 * Scene.h
 *
 *  Created on: 28.08.2017
 *      Author: beyss
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "Drawer.h"
#include "Mapper.h"
#include <vector>

struct Var
{
	Var(double min_, double max_, const std::string& label_)
	: min(min_), max(max_), label(label_)
	{};
	double min;
	double max;
	std::string label;
};

class Scene
{
public:
	Scene(Drawer& drawer, const std::vector<Var>& inputs, const std::vector<Var>& outputs);
	void drawDatapoint(std::vector<double> data);
	virtual ~Scene() {};
private:
	Drawer& _drawer;
	std::vector<Mapper> _input_mapper;
	std::vector<Mapper> _output_mapper;
};

#endif /* SCENE_H_ */
