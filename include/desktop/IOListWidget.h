#ifndef IOLISTWIDGET_H
#define IOLISTWIDGET_H

#include <QWidget>
#include <Scene.h>

namespace Ui {
class IOListWidget;
}

class IOListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IOListWidget(const DefVariable& var, QWidget *parent = 0);
    ~IOListWidget();

    QString get_name() const;

    void set_name(const std::string& name);

    bool get_toggle() const;

    void set_toggle(bool toggle);

    double get_min() const;

    void set_min(double min);

    double get_max() const;

    void set_max(double max);

    bool is_toggle_dirty() const;

    bool are_bounds_dirty() const;

    void set_toggle_not_dirty();

    void set_bounds_not_dirty();
private slots:
    void on_toggle_rbtn_clicked();

    void on_lower_dbox_valueChanged(double arg1);

    void on_upper_dbox_valueChanged(double arg1);

private:
    Ui::IOListWidget *ui;
    bool toggle_dirty;
    bool bounds_dirty;
};

#endif // IOLISTWIDGET_H
