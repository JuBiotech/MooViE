#include <ConfDoubleWidget.h>
#include <ui_ConfDoubleWidget.h>

ConfDoubleWidget::ConfDoubleWidget (const QString& tag, double init_val,
				    double lower_restr, double upper_restr,
				    int decimals, double step, QWidget *parent) :
    QWidget (parent), m_ui (new Ui::ConfDoubleWidget)
{
  m_ui->setupUi (this);

  m_ui->conf_tag->setText (tag);

  m_value = m_ui->conf_value;
  m_value->setMinimum (lower_restr);
  m_value->setMaximum (upper_restr);
  m_value->setDecimals (decimals);
  m_value->setSingleStep (step);
  m_value->setValue (init_val);
}

ConfDoubleWidget::~ConfDoubleWidget ()
{
  delete m_ui;
}
