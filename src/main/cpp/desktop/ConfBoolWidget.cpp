#include "ConfBoolWidget.h"
#include <ui_ConfBoolWidget.h>

ConfBoolWidget::ConfBoolWidget (const QString& tag, bool init_val, QWidget *parent) :
    QWidget (parent), m_ui (new Ui::ConfBoolWidget)
{
  m_ui->setupUi (this);

  m_ui->conf_tag->setText (tag);

  m_value = m_ui->conf_value;
  set_value (init_val);
}

ConfBoolWidget::~ConfBoolWidget ()
{
  delete m_ui;
}
