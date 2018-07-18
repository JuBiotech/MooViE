#ifndef SCENE_H_
#define SCENE_H_

#include <algorithm>
#include <CairoDrawer.h>
#include <DataSet.h>
#include <Configuration.h>
#include <IOVector.h>

/** Scene class represents a MooViE scene. It is initially drawn and every alteration
 * will require an update to be persistent.
 *
 * @brief The Scene class
 *
 * @author beyss
 * @date 28.08.2017
 */
class Scene
{
public:
    /** Creates a new MooViE Scene and draws it immediately. It is required to first
     * initialize a Configuration.
     */
    Scene();

    /** Reinitializes all components and redraws the MooViE scene.
     */
    void update(void);

    /** Enables/disables the input with the given index. The scene needs to be updated
     * afterwards.
     *
     * @param index the input index
     * @param mode set enabled or disabled
     *
     * @throw out_of_bounds if index is incorrect
     */
    void toggle_input(std::size_t index, bool mode);

    /** Enables/disables the output with the given index. The scene needs to be
     * updated afterwards.
     *
     * @param index the output index
     * @param mode set enabled or disabled
     *
     * @throw out_of_bounds if index is incorrect
     */
    void toggle_output(std::size_t index, bool mode);

    /** Rearranges the order of inputs in this MooViE scene by swapping the inputs
     * with the given indices. The scene needs to be updated afterwards.
     *
     * @param from_index the first inputs index
     * @param to_index the second inputs index
     *
     * @throw out_of_bounds if indices are incorrect
     */
    void swap_inputs(std::size_t from_index, std::size_t to_index);

    /** Rearranges the order of outputs in this MooViE scene by swapping the outputs
     * with the given indices. The scene needs to be updated afterwards.
     *
     * @param from_index the first outputs index
     * @param to_index the second outputs index
     *
     * @throw out_of_bounds if indices are incorrect
     */
    void swap_outputs(std::size_t from_index, std::size_t to_index);

    /** Restricts the input with given index to a given interval. Every row
     * whose associated input value is not in the interval will be disabled.
     * The scene needs to be updated afterwards.
     *
     * @param index the input index
     * @param lower_restr the lower bound
     * @param upper_restr the upper bound
     */
    void restrict_input(std::size_t index, double lower_restr, double upper_restr);

    /** Restricts the output with given index to a given interval. Every row
     * whose associated output value is not in the interval will be disabled.
     * The scene needs to be updated afterwards.
     *
     * @param index the output index
     * @param lower_restr the lower bound
     * @param upper_restr the upper bound
     */
    void restrict_output(std::size_t index, double lower_restr, double upper_restr);

private:
    /** Draws the Scene components OutputGrid, InputAxis' and IOVectors.
     */
    void draw_components(void);

    /** Initializes InputAxis' and IOVectors.
     */
    void initialize(void);
private:
    /** Data set */
    std::unique_ptr<DefDataSet>					set;

    /** Draws data to file */
    std::unique_ptr<Drawer> 					drawer;

    /** Output data section of the diagram */
    OutputGrid 								grid;
    /** Input data sections of the diagram */
    std::vector<InputAxis> 					axis;
    /** Relation elements */
    std::vector<IOVector> 				links;
};

#endif /* SCENE_H_ */
