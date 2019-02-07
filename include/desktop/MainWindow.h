#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebView>
#include <QListWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QDropEvent>
#include <Scene.h>
#include <Configuration.h>
#include <stdexcept>
#include <memory>
#include <IOList.h>
#include <IOListWidget.h>
#include <ConfigurationDialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_execute_btn_clicked();

    void on_input_file_btn_clicked();

    void on_output_file_btn_clicked();

    void on_actionConfiguration_triggered();

    void on_actionUser_Manual_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    QWebView* pic;
    IOList* input_list, * output_list;

    std::unique_ptr<Scene> scene;
};

#endif // MAINWINDOW_H
