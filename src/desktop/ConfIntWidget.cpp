#include <ConfIntWidget.h>
#include <ui_ConfIntWidget.h>

ConfIntWidget::ConfIntWidget (const QString& tag, int init_val, int lower_restr,
			      int upper_restr, QWidget *parent) :
    QWidget (parent), m_ui (new Ui::ConfIntWidget)
{
  m_ui->setupUi (this);

  m_ui->conf_tag->setText (tag);

  m_value = m_ui->conf_value;
  m_value->setMinimum (lower_restr);
  m_value->setMaximum (upper_restr);
  m_value->setValue (init_val);
}

ConfIntWidget::~ConfIntWidget ()
{
  delete m_ui;
}
