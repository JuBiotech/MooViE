#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QPushButton>
#include <QMessageBox>
#include <Configuration.h>
#include <ConfDoubleWidget.h>
#include <ConfIntWidget.h>
#include <ConfStringWidget.h>

namespace Ui
{
  class ConfigurationDialog;
}

/** This dialog enables the user to view and edit the values of
 * the MooViE configuration. Moreover, the user can store his current
 * changes to the configuration to a file and load a stored configuration
 * from a file.
 *
 * @brief a user dialog for editing the MooViE configuration
 */
class ConfigurationDialog : public QDialog
{
Q_OBJECT

private:
  /** Qt generated user interface */
  Ui::ConfigurationDialog* m_ui;

  /** General line and fill styles */
  ConfDoubleWidget* m_prop_thick_strength, *m_prop_thin_strength;

  /** General font and font size */
  ConfStringWidget* m_scale_font, *m_axis_font;
  ConfDoubleWidget* m_scale_fsize, *m_axis_fsize;

  /** Width and height of the output image */
  ConfIntWidget* m_width, *m_height;

  /** OutputGrid modification values */
  ConfDoubleWidget* m_output_angle_span, *m_output_inner_radius,
      *m_output_thickness, *m_grid_size;
  ConfIntWidget* m_num_major_sections_grid, *m_num_minor_sections_grid;

  /** InputAxis modification values */
  ConfDoubleWidget* m_input_inner_radius, *m_input_thickness,
      *m_input_separation_angle;
  ConfIntWidget* m_num_major_sections_axis, *m_num_minor_sections_axis;

  /** Histogram modification values */
  ConfIntWidget* m_num_histogram_classes;
  ConfDoubleWidget* m_histogram_height;

  /** IOVector modification values */
  ConfIntWidget* m_relevant_places;

public:
  /** Creates a ConfigurationDialog.
   *
   * @param parent parent widget
   */
  explicit
  ConfigurationDialog (QWidget *parent = 0);

  /** Destructor.
   */
  ~ConfigurationDialog ();

private:
  /** Sets up the dialog and initializes the widgets
   * with the MooViE configuration values.
   */
  void
  init_dialog ();

  /** Fills the widgets with the MooViE configuration
   * values.
   */
  void
  fill_configuration_values ();

  /** Writes user input
   */
  void
  update_configuration ();

  /** Load a MooViE configuration from a specified file and
   * fills the widgets its values.
   */
  void
  load_configuration ();

  /** Save the displayed configuration values to a specified
   * file.
   */
  void
  save_configuration ();

private slots:
  /** Is called when an button of this dialog is clicked.
   *
   * @param button button identifier
   */
  void
  on_options_box_clicked (QAbstractButton* button);
};

#endif // CONFIGURATIONDIALOG_H
