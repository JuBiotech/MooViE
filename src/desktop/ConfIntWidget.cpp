#include <ConfIntWidget.h>
#include <ui_ConfIntWidget.h>

ConfIntWidget::ConfIntWidget(const QString& tag, int init_val, int lower_restr, int upper_restr, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ConfIntWidget)
{
  ui->setupUi(this);

  ui->conf_tag->setText(tag);

  value = ui->conf_value;
  value->setMinimum(lower_restr);
  value->setMaximum(upper_restr);
  value->setValue(init_val);
}

ConfIntWidget::~ConfIntWidget()
{
  delete ui;
}
