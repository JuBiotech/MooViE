#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QDialog>
#include <Configuration.h>
#include <ConfDoubleWidget.h>
#include <ConfIntWidget.h>
#include <ConfStringWidget.h>

namespace Ui {
  class ConfigurationDialog;
}

class ConfigurationDialog : public QDialog
{
  Q_OBJECT

public:
  explicit ConfigurationDialog(QWidget *parent = nullptr);
  ~ConfigurationDialog();

private slots:
  void on_buttonBox_accepted();

private:
  Ui::ConfigurationDialog *ui;

  // Line and fill
  ConfDoubleWidget* prop_thick_strength, * prop_thin_strength;

  // Font and font size
  ConfStringWidget* scale_font, * axis_font;
  ConfDoubleWidget* scale_fsize, * axis_fsize;

  // Dimensions
  ConfIntWidget* width, * height;

  // Output
  ConfDoubleWidget* output_angle_span, * output_inner_radius,
                  * output_thickness, * grid_size;
  ConfIntWidget* num_major_sections_grid, * num_minor_sections_grid;

  // Input
  ConfDoubleWidget* input_inner_radius, * input_thickness,
                  * input_separation_angle;
  ConfIntWidget* num_major_sections_axis, * num_minor_sections_axis;

  // Histogram
  ConfIntWidget* num_histogram_classes;
  ConfDoubleWidget* histogram_height;

  // Data rows
  ConfDoubleWidget* connect_arc_ratio;
  ConfIntWidget* epsilon_places;
};

#endif // CONFIGURATIONDIALOG_H
