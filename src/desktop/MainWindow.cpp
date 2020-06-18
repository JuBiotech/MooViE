#include <MainWindow.h>
#include <ui_MainWindow.h>

MainWindow::MainWindow (QWidget *parent) :
    QMainWindow (parent), m_ui (new Ui::MainWindow), m_view (
	new MooViEView (this)), m_scene (nullptr)
{
  m_ui->setupUi (this);

  // Set up view and add to the UI layer
  m_view->setMinimumSize (800, 800);
  m_ui->top_lay->insertWidget (0, m_view);

  m_ui->interactive_lay->setMaximumWidth (500);

  // Set up input/output variable lists
  m_input_list = new IOList;
  m_input_list->setDragDropMode (QAbstractItemView::DragDrop);
  m_input_list->setDefaultDropAction (Qt::MoveAction);
  m_output_list = new IOList;
  m_output_list->setDragDropMode (QAbstractItemView::DragDrop);
  m_output_list->setDefaultDropAction (Qt::MoveAction);

  // Add input/output variable lists into a scroll area
  m_ui->inputs_scr->setWidget (m_input_list);
  m_ui->outputs_scr->setWidget (m_output_list);

  // Dummy setup of the global MooViE configuration
  Configuration::initialize ("");

  // Set desktop properties
  setWindowIcon (QIcon ("./moovie.png"));
  setWindowTitle ("MooViE - Desktop");
}

MainWindow::~MainWindow ()
{
  delete m_ui;
}

void
MainWindow::on_input_file_btn_clicked ()
{
  // Let the user choose the path to the input file
  QString fpath = QFileDialog::getOpenFileName (this, "Choose input file",
						m_ui->input_file_txt->text (),
						"CSV (*.csv)");

  /* Set the chosen file path if valid and
   generate a default output path if empty */
  if (not fpath.isEmpty ())
    {
      m_ui->input_file_txt->setText (fpath);

      if (m_ui->output_file_txt->text ().isEmpty ())
	{
	  QStringList split_list = fpath.split (QRegExp ("csv$"));
	  m_ui->output_file_txt->setText (split_list[0] + "svg");
	}
    }
}

void
MainWindow::on_output_file_btn_clicked ()
{
  // Let the user choose the path to the output file
  QString fpath = QFileDialog::getSaveFileName (this, "Choose output file",
						m_ui->output_file_txt->text (),
						"SVG (*.svg)");

  // Set chosen path if valid
  if (!fpath.isEmpty ())
    {
      m_ui->output_file_txt->setText (fpath);
    }
}

void
MainWindow::on_execute_btn_clicked ()
{
  // Get values from input/output file edit
  QString input_loc = m_ui->input_file_txt->text (), output_loc =
      m_ui->output_file_txt->text ();

  if (!input_loc.isEmpty () && !output_loc.isEmpty ())
    {
      // Set changes to global configuration object
      Configuration& conf = Configuration::get_instance ();
      if (conf.get_input_file () != input_loc.toStdString ())
	{
	  m_scene.reset ();

	  m_input_list->clear ();
	  m_output_list->clear ();

	  conf.set_input_file (input_loc.toStdString ());
	}
      conf.set_output_file (output_loc.toStdString ());

      // Try to paint the MooViE scene with the given parameters
      try
	{
	  // Initialize the scene if necessary
	  if (not m_scene)
	    {
	      // Automatically paints the scene
	      m_scene.reset (new Scene);

	      // Set up and display input and output variables of this Scene
	      std::vector<DefVariable> ivars = m_scene->get_input_variables (),
		  ovars = m_scene->get_output_variables ();
	      for (const DefVariable& var : ivars)
		{
		  QListWidgetItem* listWidgetItem = new QListWidgetItem (
		      m_input_list);
		  m_input_list->addItem (listWidgetItem);
		  IOListWidget* ioListWidget = new IOListWidget (var);
		  listWidgetItem->setSizeHint (ioListWidget->sizeHint ());
		  m_input_list->setItemWidget (listWidgetItem, ioListWidget);
		}
	      for (const DefVariable& var : ovars)
		{
		  QListWidgetItem* listWidgetItem = new QListWidgetItem;
		  m_output_list->addItem (listWidgetItem);
		  IOListWidget* ioListWidget = new IOListWidget (var);
		  listWidgetItem->setSizeHint (ioListWidget->sizeHint ());
		  m_output_list->setItemWidget (listWidgetItem, ioListWidget);
		}
	    }
	  else
	    {
	      // Check if the input variable values have been edited
	      if (m_input_list->is_dirty ())
		{
		  const std::vector<IOList::Swap>& swaps =
		      m_input_list->get_swaps ();

		  for (int i = 0; i < swaps.size (); ++i)
		    {
		      m_scene->swap_inputs (
			  static_cast<std::size_t> (swaps[i].before_pos),
			  static_cast<std::size_t> (swaps[i].after_pos));
		    }

		  m_input_list->set_not_dirty ();
		}

	      // Execute input variable changes on scene instance
	      for (int i = 0; i < m_input_list->count (); ++i)
		{
		  IOListWidget* item =
		      dynamic_cast<IOListWidget*> (m_input_list->itemWidget (
			  m_input_list->item (i)));
		  if (item->is_toggle_dirty ())
		    {
		      m_scene->toggle_input (static_cast<std::size_t> (i),
					     item->get_toggle ());
		      item->set_toggle_not_dirty ();
		    }
		  if (item->are_bounds_dirty () && item->get_toggle ())
		    {
		      m_scene->restrict_input (static_cast<std::size_t> (i),
					       item->get_min (),
					       item->get_max ());
		      item->set_bounds_not_dirty ();
		    }
		}

	      // Check if the output variable values have been edited
	      if (m_output_list->is_dirty ())
		{
		  const std::vector<IOList::Swap>& swaps =
		      m_output_list->get_swaps ();

		  for (int i = 0; i < swaps.size (); ++i)
		    {
		      m_scene->swap_outputs (
			  static_cast<std::size_t> (swaps[i].before_pos),
			  static_cast<std::size_t> (swaps[i].after_pos));
		    }

		  m_output_list->set_not_dirty ();
		}

	      // Execute output variable changes on scene instance
	      for (int i = 0; i < m_output_list->count (); ++i)
		{
		  IOListWidget* item =
		      dynamic_cast<IOListWidget*> (m_output_list->itemWidget (
			  m_output_list->item (i)));
		  if (item->is_toggle_dirty ())
		    {
		      m_scene->toggle_output (static_cast<std::size_t> (i),
					      item->get_toggle ());
		      item->set_toggle_not_dirty ();
		    }
		  if (item->are_bounds_dirty () && item->get_toggle ())
		    {
		      m_scene->restrict_output (static_cast<std::size_t> (i),
						item->get_min (),
						item->get_max ());
		      item->set_bounds_not_dirty ();
		    }
		}

	      // Repaint scene
	      m_scene->update ();
	    }

	  // Load SVG image and set the zoom using the image size
	  m_view->load (QUrl (QString("file://") + output_loc));
	  m_view->show ();
	  m_view->adjust_zoom_by_svg_size(conf.get_width(), conf.get_height());
	  setWindowTitle (QString("MooViE - Desktop: ") + input_loc);
	}
      catch (const std::exception& e)
	{
	  // Message user that an error accurred during MooViE execution
	  QMessageBox msg_box;
	  msg_box.setWindowTitle ("MooViE execution failed");
	  msg_box.setText (e.what ());
	  msg_box.setStandardButtons (QMessageBox::Ok);
	  msg_box.exec ();
	}
    }
  else
    {
      // Message user that input/output file edit is empty
      QMessageBox msg_box;
      msg_box.setWindowTitle ("Missing information");
      msg_box.setText ("Input or output file box are empty");
      msg_box.setStandardButtons (QMessageBox::Ok);
      msg_box.exec ();
    }
}

void
MainWindow::on_config_btn_clicked ()
{
  // Dialog to edit MooViE configuration
  ConfigurationDialog ().exec ();
}
