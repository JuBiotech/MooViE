#include <MainWindow.h>
#include <ui_MainWindow.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    pic(new QWebView(this)),
    scene(nullptr)
{
    ui->setupUi(this);

    pic->setMinimumSize(800,800);
    ui->top_lay->insertWidget(0, pic);

    ui->interactive_lay->setMaximumWidth(500);

    input_list = new IOList;
    input_list->setDragDropMode(QAbstractItemView::DragDrop);
    input_list->setDefaultDropAction(Qt::MoveAction);

    output_list = new IOList;
    output_list->setDragDropMode(QAbstractItemView::DragDrop);
    output_list->setDefaultDropAction(Qt::MoveAction);

    ui->inputs_scr->setWidget(input_list);
    ui->outputs_scr->setWidget(output_list);

    Configuration::initialize("");
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_input_file_btn_clicked()
{
    static const QString filter = tr("CSV (*.csv");
    QString fpath = QFileDialog::getOpenFileName(
                this,
                "Choose input file",
                ui->input_file_txt->text(),
                "CSV (*.csv)"
                );
    if (not fpath.isEmpty())
    {
        ui->input_file_txt->setText(fpath);

        QStringList split_list = fpath.split(QRegExp("csv$"));
        ui->output_file_txt->setText(split_list[0] + "svg");
    }
}

void MainWindow::on_output_file_btn_clicked()
{
    static const QString filter = tr("SVG (*.svg");
    QString fpath = QFileDialog::getSaveFileName(
                this,
                "Choose output file",
                ui->output_file_txt->text(),
				"SVG (*.svg)"
                );
    if (!fpath.isEmpty())
    {
        ui->output_file_txt->setText(fpath);
    }
}

void MainWindow::on_execute_btn_clicked()
{
    QString input_loc = ui->input_file_txt->text(),
            output_loc = ui->output_file_txt->text();
    if (!input_loc.isEmpty() && !output_loc.isEmpty())
    {
        Configuration& conf = Configuration::get_instance();
        if (conf.get_input_file() != input_loc.toStdString())
        {
        	scene.reset();

        	input_list->clear();
        	output_list->clear();

        	conf.set_input_file(input_loc.toStdString());
        }
        conf.set_output_file(output_loc.toStdString());

        try
        {
            if (scene == nullptr)
            {
                scene.reset(new Scene);

                std::vector<DefVariable> ivars = scene->get_input_variables(),
                        ovars = scene->get_output_variables();

                for (const DefVariable& var: ivars)
                {
                    QListWidgetItem* listWidgetItem = new QListWidgetItem(input_list);
                    input_list->addItem(listWidgetItem);
                    IOListWidget* ioListWidget = new IOListWidget(var);
                    listWidgetItem->setSizeHint(ioListWidget->sizeHint());
                    input_list->setItemWidget(listWidgetItem, ioListWidget);
                }

                for (const DefVariable& var: ovars)
                {
                    QListWidgetItem* listWidgetItem = new QListWidgetItem;
                    output_list->addItem(listWidgetItem);
                    IOListWidget* ioListWidget = new IOListWidget(var);
                    listWidgetItem->setSizeHint(ioListWidget->sizeHint());
                    output_list->setItemWidget(listWidgetItem, ioListWidget);
                }
            }
            else
            {
                if (input_list->is_dirty())
                {
                    const std::vector<IOList::Swap>& swaps = input_list->get_swaps();

                    for (int i = 0; i < swaps.size(); ++i)
                    {
                    	std::cout << "Swapped " << swaps[i].before_pos << " with " << swaps[i].after_pos << std::endl;
                        scene->swap_inputs(static_cast<std::size_t>(swaps[i].before_pos),
                                           static_cast<std::size_t>(swaps[i].after_pos));
                    }

                    input_list->not_dirty();
                }

                for (int i = 0; i < input_list->count(); ++i)
                {
                    IOListWidget* item = dynamic_cast<IOListWidget*>(input_list->itemWidget(input_list->item(i)));
                    if (item->is_toggle_dirty())
                    {
                          scene->toggle_input(static_cast<std::size_t>(i), item->get_toggle());
                          item->set_toggle_not_dirty();
                    }
                    if (item->are_bounds_dirty() && item->get_toggle())
                    {
                        scene->restrict_input(static_cast<std::size_t>(i), item->get_min(), item->get_max());
                        item->set_bounds_not_dirty();
                    }
                }

                if (output_list->is_dirty())
                {
                    const std::vector<IOList::Swap>& swaps = output_list->get_swaps();

                    for (int i = 0; i < swaps.size(); ++i)
                    {
                    	std::cout << "Swapped " << swaps[i].before_pos << " with " << swaps[i].after_pos << std::endl;
                        scene->swap_outputs(static_cast<std::size_t>(swaps[i].before_pos),
                                           static_cast<std::size_t>(swaps[i].after_pos));
                    }

                    output_list->not_dirty();
                }

                for (int i = 0; i < output_list->count(); ++i)
                {
                    IOListWidget* item = dynamic_cast<IOListWidget*>(output_list->itemWidget(output_list->item(i)));
                    if (item->is_toggle_dirty())
                    {
                          scene->toggle_output(static_cast<std::size_t>(i), item->get_toggle());
                          item->set_toggle_not_dirty();
                    }
                    if (item->are_bounds_dirty() && item->get_toggle())
                    {
                        scene->restrict_output(static_cast<std::size_t>(i), item->get_min(), item->get_max());
                        item->set_bounds_not_dirty();
                    }
                }

                scene->update();
            }

            pic->load(QUrl(output_loc));
            pic->show();
        }
        catch (const std::exception& e)
        {
            QMessageBox msg_box;

            msg_box.setWindowTitle("MooViE execution error");
            msg_box.setText(e.what());
            msg_box.setStandardButtons(QMessageBox::Ok);
            msg_box.exec();
        }
    }
    else
    {
        QMessageBox msg_box;

        msg_box.setWindowTitle("Missing information error");
        msg_box.setText("Input or output file box are empty");
        msg_box.setStandardButtons(QMessageBox::Ok);
        msg_box.exec();
    }
}

void MainWindow::on_config_btn_clicked()
{
  ConfigurationDialog dialog;
  dialog.setWindowTitle("Edit Configuration");
  dialog.exec();
}
