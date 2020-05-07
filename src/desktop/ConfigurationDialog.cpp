#include <ConfigurationDialog.h>
#include <ui_ConfigurationDialog.h>

#include <QLayout>
#include <QGroupBox>

ConfigurationDialog::ConfigurationDialog (QWidget *parent) :
    QDialog (parent), m_ui (new Ui::ConfigurationDialog)
{
  m_ui->setupUi (this);

  init_dialog ();

  // Connect call to a dialog button
  connect (m_ui->options_box, SIGNAL(clicked(QAbstractButton*)), this,
	   SLOT(on_options_box_clicked(QAbstractButton*)),
	   Qt::UniqueConnection);

  // Set desktop properties
  setWindowTitle ("Edit Configuration");
  setWindowIcon (QIcon ("./moovie.png"));
}

ConfigurationDialog::~ConfigurationDialog ()
{
  delete m_ui;
}

void
ConfigurationDialog::init_dialog ()
{
  Configuration& conf = Configuration::get_instance ();

  // Dimensions
  m_width = new ConfIntWidget ("Image width", conf.get_width (), 1);
  m_height = new ConfIntWidget ("Image height", conf.get_height (), 1);
  QLayout* dim = m_ui->dim_grp->layout ();
  dim->addWidget (m_width);
  dim->addWidget (m_height);

  // Line and fill
  m_prop_thick_strength = new ConfDoubleWidget (
      "Thick line strength", conf.get_prop_thick ().line_width, 0);
  m_prop_thin_strength = new ConfDoubleWidget ("Thin line strength",
					       conf.get_prop_thin ().line_width,
					       0);
  QLayout* linefill = m_ui->linefill_grp->layout ();
  linefill->addWidget (m_prop_thick_strength);
  linefill->addWidget (m_prop_thin_strength);

  // Font and font size
  m_scale_font = new ConfStringWidget (
      "Font of scale description",
      QString::fromStdString (conf.get_prop_scale_label ().font_name));
  m_axis_font = new ConfStringWidget (
      "Font of axis description",
      QString::fromStdString (conf.get_prop_axis_label ().font_name));
  m_scale_fsize = new ConfDoubleWidget ("Font size of scale description",
					conf.get_prop_scale_label ().font_size);
  m_axis_fsize = new ConfDoubleWidget ("Font size of axis description",
				       conf.get_prop_axis_label ().font_size);
  QLayout* font = m_ui->font_grp->layout ();
  font->addWidget (m_scale_font);
  font->addWidget (m_axis_fsize);
  font->addWidget (m_axis_font);
  font->addWidget (m_scale_fsize);

  // Output
  m_output_angle_span = new ConfDoubleWidget (
      "Span of the output angle (degrees)", conf.get_output_angle_span (), 0,
      360);
  m_output_inner_radius = new ConfDoubleWidget (
      "Start radius of the output grid", conf.get_output_inner_radius (), 0);
  m_output_thickness = new ConfDoubleWidget ("Thickness of the coloring axis",
					     conf.get_output_thickness (), 0);
  m_grid_size = new ConfDoubleWidget ("Height of the output grid",
				      conf.get_grid_size (), 0);
  m_num_major_sections_grid = new ConfIntWidget (
      "Number of big output subdivisions", conf.get_num_major_sections_grid (),
      1);
  m_num_minor_sections_grid = new ConfIntWidget (
      "Number of small output subdivisions",
      conf.get_num_minor_sections_grid (), 1);
  QLayout* output = m_ui->output_grp->layout ();
  output->addWidget (m_output_angle_span);
  output->addWidget (m_output_inner_radius);
  output->addWidget (m_output_thickness);
  output->addWidget (m_grid_size);
  output->addWidget (m_num_major_sections_grid);
  output->addWidget (m_num_minor_sections_grid);

  // Input
  m_input_inner_radius = new ConfDoubleWidget (
      "Start radius of the inputs axis", conf.get_input_inner_radius (), 0);
  m_input_thickness = new ConfDoubleWidget ("Thickness of an input axis",
					    conf.get_input_thickness (), 0);
  m_input_separation_angle = new ConfDoubleWidget (
      "Angle between input axis (degrees)", conf.get_input_separation_angle (),
      0);
  m_num_major_sections_axis = new ConfIntWidget (
      "Number of big input subdivisions", conf.get_num_major_sections_axis (),
      1);
  m_num_minor_sections_axis = new ConfIntWidget (
      "Number of small input subdivisions", conf.get_num_minor_sections_axis (),
      1);
  QLayout* input = m_ui->input_grp->layout ();
  input->addWidget (m_input_inner_radius);
  input->addWidget (m_input_thickness);
  input->addWidget (m_input_separation_angle);
  input->addWidget (m_num_major_sections_axis);
  input->addWidget (m_num_minor_sections_axis);

  // Histogram
  m_num_histogram_classes = new ConfIntWidget (
      "Classes of the histograms", conf.get_num_histogram_classes (), 1);
  m_histogram_height = new ConfDoubleWidget ("Height of a histogram",
					     conf.get_histogram_height (), 0);
  QLayout* histogram = m_ui->histogram_grp->layout ();
  histogram->addWidget (m_num_histogram_classes);
  histogram->addWidget (m_histogram_height);

  // Input/output vectors
  m_relevant_places = new ConfIntWidget ("Number of places to round",
					 conf.get_relevant_places (), 0, 15);
  QLayout* data = m_ui->data_grp->layout ();
  data->addWidget (m_relevant_places);
}

void
ConfigurationDialog::fill_configuration_values ()
{
  Configuration& conf = Configuration::get_instance ();

  // Dimensions
  m_width->set_value (conf.get_width ());
  m_height->set_value (conf.get_height ());

  // Line and fill
  m_prop_thick_strength->set_value (conf.get_prop_thick ().line_width);
  m_prop_thin_strength->set_value (conf.get_prop_thin ().line_width);

  // Font and font size
  m_scale_font->set_text (
      QString::fromStdString (conf.get_prop_scale_label ().font_name));
  m_axis_font->set_text (
      QString::fromStdString (conf.get_prop_axis_label ().font_name));
  m_scale_fsize->set_value (conf.get_prop_scale_label ().font_size);
  m_axis_fsize->set_value (conf.get_prop_axis_label ().font_size);

  // Output
  m_output_angle_span->set_value (conf.get_output_angle_span ());
  m_output_inner_radius->set_value (conf.get_output_inner_radius ());
  m_output_thickness->set_value (conf.get_output_thickness ());
  m_grid_size->set_value (conf.get_grid_size ());
  m_num_major_sections_grid->set_value (conf.get_num_major_sections_grid ());
  m_num_minor_sections_grid->set_value (conf.get_num_minor_sections_grid ());

  // Input
  m_input_inner_radius->set_value (conf.get_input_inner_radius ());
  m_input_thickness->set_value (conf.get_input_thickness ());
  m_input_separation_angle->set_value (conf.get_input_separation_angle ());
  m_num_major_sections_axis->set_value (conf.get_num_major_sections_grid ());
  m_num_minor_sections_axis->set_value (conf.get_num_minor_sections_grid ());

  // Histogram
  m_num_histogram_classes->set_value (conf.get_num_histogram_classes ());
  m_histogram_height->set_value (conf.get_histogram_height ());

  // Input/output vectors
  m_relevant_places->set_value (conf.get_relevant_places ());
}

void
ConfigurationDialog::update_configuration ()
{
  Configuration& conf = Configuration::get_instance ();

  // Dimension
  conf.set_width (m_width->get_value ());
  conf.set_height (m_height->get_value ());

  // Font and font size
  conf.set_prop_thick (
      DrawerProperties<> (m_prop_thick_strength->get_value (), Color::BLACK,
			  Color::BLACK));
  conf.set_prop_thin (
      DrawerProperties<> (m_prop_thin_strength->get_value (), Color::BLACK,
			  Color::BLACK));

  // Line and fill
  conf.set_prop_scale_label (
      TextProperties (m_scale_font->get_text ().toStdString (),
		      m_scale_fsize->get_value ()));
  conf.set_prop_axis_label (
      TextProperties (m_axis_font->get_text ().toStdString (),
		      m_axis_fsize->get_value ()));

  // Output
  conf.set_output_angle_span (m_output_angle_span->get_value ());
  conf.set_output_inner_radius (m_output_inner_radius->get_value ());
  conf.set_output_thickness (m_output_thickness->get_value ());
  conf.set_grid_size (m_grid_size->get_value ());
  conf.set_num_major_sections_grid (m_num_major_sections_grid->get_value ());
  conf.set_num_minor_sections_grid (m_num_minor_sections_grid->get_value ());

  // Input
  conf.set_input_inner_radius (m_input_inner_radius->get_value ());
  conf.set_input_thickness (m_input_thickness->get_value ());
  conf.set_input_separation_angle (m_input_separation_angle->get_value ());
  conf.set_num_major_sections_axis (m_num_major_sections_axis->get_value ());
  conf.set_num_minor_sections_axis (m_num_minor_sections_axis->get_value ());

  // Histogram
  conf.set_num_histogram_classes (m_num_histogram_classes->get_value ());
  conf.set_histogram_height (m_histogram_height->get_value ());

  // Data rows
  conf.set_relevant_places (m_relevant_places->get_value ());
}

void
ConfigurationDialog::load_configuration ()
{
  // Let the user choose a configuration file path
  QString fpath = QFileDialog::getOpenFileName (this,
						"Select configuration to load",
						"", "Configuration (*.conf)");

  /* Set the chosen path if valid and try to initialize the configuration
   * from it. Use old input/output file paths.
   */
  if (not fpath.isEmpty ())
    {
      std::string input_loc = Configuration::get_instance ().get_input_file ();
      std::string output_loc =
	  Configuration::get_instance ().get_output_file ();

      try
	{
	  Configuration::initialize (input_loc, fpath.toStdString ());

	  Configuration& conf = Configuration::get_instance ();
	  conf.set_input_file (input_loc);
	  conf.set_output_file (output_loc);

	  fill_configuration_values ();
	}
      catch (const std::exception& e)
	{
	  QMessageBox msg_box;

	  msg_box.setWindowTitle ("Failed to load configuration");
	  msg_box.setText (e.what ());
	  msg_box.setStandardButtons (QMessageBox::Ok);
	  msg_box.exec ();

	  update_configuration ();
	}
    }
}

void
ConfigurationDialog::save_configuration ()
{
  // Let the user choose a file path to save the configuration values to
  QString fpath = QFileDialog::getSaveFileName (
      this, "Select path to safe configuration", "", "Configuration (*.conf)");

  // Set the cosen path if valid
  if (not fpath.isEmpty ())
    {
      try
	{
	  Configuration::save_to_file (fpath.toStdString ());
	}
      catch (const std::exception& e)
	{
	  QMessageBox msg_box;

	  msg_box.setWindowTitle ("Failed to save configuration");
	  msg_box.setText (e.what ());
	  msg_box.setStandardButtons (QMessageBox::Ok);
	  msg_box.exec ();
	}
    }
}

void
ConfigurationDialog::on_options_box_clicked (QAbstractButton* button)
{
  QDialogButtonBox::StandardButton type = m_ui->options_box->standardButton (
      button);

  switch (type)
    {
    case QDialogButtonBox::Ok:
      update_configuration ();
      accept ();
      break;
    case QDialogButtonBox::Open:
      load_configuration ();
      break;
    case QDialogButtonBox::Save:
      save_configuration ();
      break;
    default:
      break;
    }
}
