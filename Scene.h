/*
 * Scene.h
 *
 *  Created on: 28.08.2017
 *      Author: beyss
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "CoordGrid.h"
#include "Drawer.h"
#include "VarAxis.h"
#include "DataLink.h"
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
    Scene(const std::string & fname, size_t width, size_t height, const DefDataSet & set);

    /** Draws the Scene with CoordGrid, VarAxis' and DataLinks.
     * @brief draw_scene
     */
    void draw_scene(void);

    virtual ~Scene() {}
private:
    /** Output data section of the diagram */
    CoordGrid _grid;
    /** Variable axis */
    std::vector<VarAxis> _axis;
    /** Data links */
    std::vector<DataLink> _links;

    /** Data set */
    const DefDataSet & _set;

    /** Draws data to file */
	Drawer _drawer;
	/** Drawer properties for link drawing */
	DrawerProperties<> _prop;
	/** Drawer properties for SplitAxis drawing */
	DrawerProperties<std::array<Color, 10>> _split_prop;
};

#endif /* SCENE_H_ */
