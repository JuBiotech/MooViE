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

/** Var represents an entity attribute and stores its name,
 * maximal and minimal value.
 * @brief The Var struct
 */
struct Var
{
    /** Creates a Variable with the given name, min and max value.
     * @brief Var
     * @param min the min value
     * @param max the max value
     * @param name the name
     */
    Var(double _min, double _max, const std::string& _name)
    : min(_min), max(_max), name(_name) {}

    /** Minimal value */
    double min;

    /** Maximal value */
    double max;

    /** Variable name */
    std::string name;
};

/** Scene constructs a diagram that displays data vectors
 * @brief The Scene class
 * @author beyss
 * @date 28.08.2017
 */
class Scene
{
public:
    /** Creates a new Scene from a given drawer, input and output variable.
     * @brief Scene
     * @param drawer the drawer
     * @param inputs the input variables
     * @param outputs the output variables
     */
    Scene(Drawer& drawer, const std::vector<Var>& inputs, const std::vector<Var>& outputs);

    /** Draws a data vector to the data diagram.
     * @brief drawDatapoint
     * @param data the data vector
     */
    void drawDataVector(std::vector<double> data);

    virtual ~Scene() {}
private:
    /** Draws data to file */
    Drawer& _drawer;
    /** Maps the input extrem values to a circle segment */
    std::vector<Mapper> _input_mapper;
    /** ??? */
    std::vector<Mapper> _output_mapper;
};

#endif /* SCENE_H_ */
