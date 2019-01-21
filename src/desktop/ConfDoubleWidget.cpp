#include <ConfDoubleWidget.h>
#include <ui_ConfDoubleWidget.h>

ConfDoubleWidget::ConfDoubleWidget(const QString& tag, double init_val, double lower_restr, double upper_restr,
                                   int decimals, double step, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ConfDoubleWidget)
{
  ui->setupUi(this);

  ui->conf_tag->setText(tag);

  value = ui->conf_value;
  value->setMinimum(lower_restr);
  value->setMaximum(upper_restr);
  value->setDecimals(decimals);
  value->setSingleStep(step);
  value->setValue(init_val);
}

ConfDoubleWidget::~ConfDoubleWidget()
{
  delete ui;
}
