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
#include "DataSet.h"

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
    Scene(Drawer & drawer, const std::vector<DefVar> & inputs, const std::vector<DefVar> & outputs);

    /** Draws a data vector to the data diagram.
     * @brief drawDatapoint
     * @param data the data vector
     */
    void drawDataVector(DefDataRow data);

    virtual ~Scene() {}
private:
    /** Draws data to file */
    Drawer& _drawer;
    /** Maps the input extrem values to a circle segment */
    std::vector<Mapper> _input_mapper;
    /** Maps the output extreme value to a circle segment */
    std::vector<Mapper> _output_mapper;
};

#endif /* SCENE_H_ */
