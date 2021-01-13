#include "ConfStringWidget.h"
#include <ui_ConfStringWidget.h>

ConfStringWidget::ConfStringWidget (const QString& tag,
				    const QString& init_text, QWidget *parent) :
    QWidget (parent), m_ui (new Ui::ConfStringWidget)
{
  m_ui->setupUi (this);

  m_ui->conf_tag->setText (tag);

  m_text = m_ui->conf_text;
  m_text->setText (init_text);
}

ConfStringWidget::~ConfStringWidget ()
{
  delete m_ui;
}
