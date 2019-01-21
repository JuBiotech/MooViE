#include <ConfStringWidget.h>
#include <ui_ConfStringWidget.h>

ConfStringWidget::ConfStringWidget(const QString& tag, const QString& init_text, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ConfStringWidget)
{
  ui->setupUi(this);

  ui->conf_tag->setText(tag);

  text = ui->conf_text;
  text->setText(init_text);
}

ConfStringWidget::~ConfStringWidget()
{
  delete ui;
}
