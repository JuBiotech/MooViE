#include <IOListWidget.h>
#include <ui_IOListWidget.h>

IOListWidget::IOListWidget(const DefVariable& var, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IOListWidget)
{
    ui->setupUi(this);

    ui->io_name_lbl->setText(QString::fromStdString(var.name));
    ui->toggle_rbtn->setChecked(true);
    ui->lower_dbox->setDecimals(5);
    ui->upper_dbox->setDecimals(5);
    ui->lower_dbox->setValue(var.min);
    ui->upper_dbox->setValue(var.max);

    toggle_dirty = false;
    bounds_dirty = false;
}

IOListWidget::~IOListWidget()
{
    delete ui;
}

QString IOListWidget::get_name() const
{
    return ui->io_name_lbl->text();
}

void IOListWidget::set_name(const std::string& name)
{
    ui->io_name_lbl->setText(QString::fromStdString(name));
}

bool IOListWidget::get_toggle() const
{
    return ui->toggle_rbtn->isChecked();
}

void IOListWidget::set_toggle(bool toggle)
{
    ui->toggle_rbtn->setChecked(toggle);
}

double IOListWidget::get_min() const
{
    return ui->lower_dbox->value();
}

void IOListWidget::set_min(double min)
{
    ui->lower_dbox->setValue(min);
}

double IOListWidget::get_max() const
{
    return ui->upper_dbox->value();
}

void IOListWidget::set_max(double max)
{
    ui->upper_dbox->setValue(max);
}

bool IOListWidget::is_toggle_dirty() const
{
    return toggle_dirty;
}

bool IOListWidget::are_bounds_dirty() const
{
    return bounds_dirty;
}

void IOListWidget::set_toggle_not_dirty()
{
    toggle_dirty = false;
}

void IOListWidget::set_bounds_not_dirty()
{
    bounds_dirty = false;
}

void IOListWidget::on_toggle_rbtn_clicked()
{
    toggle_dirty = true;
}

void IOListWidget::on_lower_dbox_valueChanged(double arg1)
{
    bounds_dirty = true;
}

void IOListWidget::on_upper_dbox_valueChanged(double arg1)
{
    bounds_dirty = true;
}
