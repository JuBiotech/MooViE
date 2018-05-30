/*
 * Scene.h
 *
 *  Created on: 28.08.2017
 *      Author: beyss
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <algorithm>
#include "CairoDrawer.h"
#include "RelationElement.h"
#include "DataSet.h"
#include "Configuration.h"

/** Scene constructs a diagram that displays data vectors
 * @brief The Scene class
 * @author beyss
 * @date 28.08.2017
 */
class Scene
{
public:
    /** Creates a new MooViE Scene.
     * @brief Scene
     */
    Scene();

    void update(void);

private:
    /** Draws the Scene components CoordGrid, VarAxis' and DataLinks.
     * @brief draw_components
     */
    void draw_components(void);

    /**
     *
     */
    void initialize(void);
private:
    /** Data set */
    std::unique_ptr<DefDataSet>					set;

    /** Draws data to file */
    std::unique_ptr<Drawer> 					drawer;

    /** Output data section of the diagram */
    CodomainGrid 								grid;
    /** Variable axis */
    std::vector<DomainAxis> 					axis;
    /** Data links */
    std::vector<RelationElement> 				links;
};

#endif /* SCENE_H_ */
