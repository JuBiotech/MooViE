#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QDropEvent>
#include <Scene.h>
#include <Configuration.h>
#include <stdexcept>
#include <memory>
#include <MooViEView.h>
#include <IOList.h>
#include <IOListWidget.h>
#include <ConfigurationDialog.h>

namespace Ui
{
  class MainWindow;
}

/** Main window of Qt application. The heart of the MooViE desktop application.
 *
 * @brief main window of moovie desktop
 *
 * @date
 * @author stratmann
 */
class MainWindow : public QMainWindow
{
Q_OBJECT

private:
  /** Qt generated user interface */
  Ui::MainWindow* m_ui;

  /** A view for displaying the rendered MooViE scene */
  MooViEView* m_view;

  /** List widgets for input/output variables */
  IOList* m_input_list, *m_output_list;

  /** The MooViE scene of the application */
  std::unique_ptr<Scene> m_scene;

public:
  /** Creates the main window.
   *
   * @param parent parent widget
   */
  explicit
  MainWindow (QWidget *parent = 0);

  /** Destruktor
   */
  ~MainWindow ();

private slots:
  /** Calls a file chooser dialog for
   * the input file.
   */
  void
  on_input_file_btn_clicked ();

  /** Calls a file chooser dialog for
   * the output file.
   */
  void
  on_output_file_btn_clicked ();

  /**
   */
  void
  on_execute_btn_clicked ();

  /** Calls a dialog to edit the MooViE
   * configuration.
   */
  void
  on_config_btn_clicked ();
};

#endif // MAINWINDOW_H
