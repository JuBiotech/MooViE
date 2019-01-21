#include <ConfigurationDialog.h>
#include <ui_ConfigurationDialog.h>

#include <QLayout>
#include <QGroupBox>

ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ConfigurationDialog)
{
  ui->setupUi(this);

  Configuration& conf = Configuration::get_instance();

  // Line and fill
  prop_thick_strength = new ConfDoubleWidget("Thick line strength", conf.get_prop_thick().line_width, 0);
  prop_thin_strength = new ConfDoubleWidget("Thin line strength", conf.get_prop_thin().line_width, 0);
  QLayout* linefill = ui->linefill_grp->layout();
  linefill->addWidget(prop_thick_strength);
  linefill->addWidget(prop_thin_strength);

  // Font and font size
  scale_font = new ConfStringWidget("Font of scale description", QString::fromStdString(conf.get_prop_scale_label().font_name));
  axis_font = new ConfStringWidget("Font of axis description", QString::fromStdString(conf.get_prop_axis_label().font_name));
  scale_fsize = new ConfDoubleWidget("Font size of scale description", conf.get_prop_scale_label().font_size);
  axis_fsize = new ConfDoubleWidget("Font size of axis description", conf.get_prop_axis_label().font_size);
  QLayout* font = ui->font_grp->layout();
  font->addWidget(scale_font);
  font->addWidget(axis_fsize);
  font->addWidget(axis_font);
  font->addWidget(scale_fsize);

  // Dimensions
  width = new ConfIntWidget("Image width", conf.get_width(), 1);
  height = new ConfIntWidget("Image height", conf.get_height(), 1);
  QLayout* dim = ui->dim_grp->layout();
  dim->addWidget(width);
  dim->addWidget(height);

  // Output
  output_angle_span = new ConfDoubleWidget("Span of the output angle (degrees)", conf.get_output_angle_span(), 0, 360);
  output_inner_radius = new ConfDoubleWidget("Start radius of the output grid", conf.get_output_inner_radius(), 0);
  output_thickness = new ConfDoubleWidget("Thickness of the coloring axis", conf.get_output_thickness(), 0);
  grid_size = new ConfDoubleWidget("Height of the output grid", conf.get_grid_size(), 0);
  num_major_sections_grid = new ConfIntWidget("Number of big output subdivisions", conf.get_num_major_sections_grid(), 1);
  num_minor_sections_grid = new ConfIntWidget("Number of small output subdivisions", conf.get_num_minor_sections_grid(), 1);
  QLayout* output = ui->output_grp->layout();
  output->addWidget(output_angle_span);
  output->addWidget(output_inner_radius);
  output->addWidget(output_thickness);
  output->addWidget(grid_size);
  output->addWidget(num_major_sections_grid);
  output->addWidget(num_minor_sections_grid);

  // Input
  input_inner_radius = new ConfDoubleWidget("Start radius of the inputs axis", conf.get_input_inner_radius(), 0);
  input_thickness = new ConfDoubleWidget("Thickness of an input axis", conf.get_input_thickness(), 0);
  input_separation_angle = new ConfDoubleWidget("Angle between input axis (degrees)", conf.get_input_separation_angle(), 0);
  num_major_sections_axis = new ConfIntWidget("Number of big input subdivisions", conf.get_num_major_sections_grid(), 1);
  num_minor_sections_axis = new ConfIntWidget("Number of small input subdivisions", conf.get_num_minor_sections_grid(), 1);
  QLayout* input = ui->input_grp->layout();
  input->addWidget(input_inner_radius);
  input->addWidget(input_thickness);
  input->addWidget(input_separation_angle);
  input->addWidget(num_major_sections_axis);
  input->addWidget(num_minor_sections_axis);

  // Histogram
  num_histogram_classes = new ConfIntWidget("Classes of the histograms", conf.get_num_histogram_classes(), 1);
  histogram_height = new ConfDoubleWidget("Height of a histogram", conf.get_histogram_height(), 0);
  QLayout* histogram = ui->histogram_grp->layout();
  histogram->addWidget(num_histogram_classes);
  histogram->addWidget(histogram_height);

  // Data rows
  connect_arc_ratio = new ConfDoubleWidget("Ratio of connectors that is curved", conf.get_connector_arc_ratio(), 0, 1);
  epsilon_places = new ConfIntWidget("Decimal places before zero", conf.get_epsilon_places(), 0, 15);
  QLayout* data = ui->data_grp->layout();
  data->addWidget(connect_arc_ratio);
  data->addWidget(epsilon_places);
}

ConfigurationDialog::~ConfigurationDialog()
{
  delete ui;
}

void ConfigurationDialog::on_buttonBox_accepted()
{
  Configuration& conf = Configuration::get_instance();

  // Font and font size
  conf.set_prop_thick(DrawerProperties<>(prop_thick_strength->get_value(), Color::BLACK, Color::BLACK));
  conf.set_prop_thin(DrawerProperties<>(prop_thin_strength->get_value(), Color::BLACK, Color::BLACK));

  // Line and fill
  conf.set_prop_scale_label(TextProperties(scale_font->get_text().toStdString(), scale_fsize->get_value()));
  conf.set_prop_axis_label(TextProperties(axis_font->get_text().toStdString(), axis_fsize->get_value()));

  // Dimension
  conf.set_width(width->get_value());
  conf.set_height(height->get_value());

  // Output
  conf.set_output_angle_span(output_angle_span->get_value());
  conf.set_output_inner_radius(output_inner_radius->get_value());
  conf.set_output_thickness(output_thickness->get_value());
  conf.set_grid_size(grid_size->get_value());
  conf.set_num_major_sections_grid(num_major_sections_grid->get_value());
  conf.set_num_minor_sections_grid(num_minor_sections_grid->get_value());

  // Input
  conf.set_input_inner_radius(input_inner_radius->get_value());
  conf.set_input_thickness(input_thickness->get_value());
  conf.set_input_separation_angle(input_separation_angle->get_value());
  conf.set_num_major_sections_axis(num_major_sections_axis->get_value());
  conf.set_num_minor_sections_axis(num_minor_sections_axis->get_value());

  // Histogram
  conf.set_num_histogram_classes(num_histogram_classes->get_value());
  conf.set_histogram_height(histogram_height->get_value());

  // Data rows
  conf.set_connector_arc_ratio(connect_arc_ratio->get_value());
  conf.set_epsilon_places(epsilon_places->get_value());
}
