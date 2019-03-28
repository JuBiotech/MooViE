#include <IOListWidget.h>
#include <ui_IOListWidget.h>

IOListWidget::IOListWidget (const DefVariable& var, QWidget *parent) :
    QWidget (parent), m_ui (new Ui::IOListWidget)
{
  m_ui->setupUi (this);

  m_ui->io_name_lbl->setText (QString::fromStdString (var.name));

  m_ui->toggle_rbtn->setChecked (true);

  // Set spin box range to (-Inf,Inf)
  double max = std::numeric_limits<double>::max ();
  m_ui->lower_dbox->setRange (-max, max);
  m_ui->lower_dbox->setDecimals (5);
  m_ui->lower_dbox->setValue (var.min);
  m_ui->upper_dbox->setRange (-max, max);
  m_ui->upper_dbox->setDecimals (5);
  m_ui->upper_dbox->setValue (var.max);

  m_toggle_dirty = false;
  m_bounds_dirty = false;
}

IOListWidget::~IOListWidget ()
{
  delete m_ui;
}

QString
IOListWidget::get_name () const
{
  return m_ui->io_name_lbl->text ();
}

bool
IOListWidget::get_toggle () const
{
  return m_ui->toggle_rbtn->isChecked ();
}

double
IOListWidget::get_min () const
{
  return m_ui->lower_dbox->value ();
}

double
IOListWidget::get_max () const
{
  return m_ui->upper_dbox->value ();
}

bool
IOListWidget::is_toggle_dirty () const
{
  return m_toggle_dirty;
}

bool
IOListWidget::are_bounds_dirty () const
{
  return m_bounds_dirty;
}

void
IOListWidget::set_toggle_not_dirty ()
{
  m_toggle_dirty = false;
}

void
IOListWidget::set_bounds_not_dirty ()
{
  m_bounds_dirty = false;
}

void
IOListWidget::on_toggle_rbtn_clicked ()
{
  m_toggle_dirty = true;
}

void
IOListWidget::on_lower_dbox_valueChanged (double arg1)
{
  m_bounds_dirty = true;
}

void
IOListWidget::on_upper_dbox_valueChanged (double arg1)
{
  m_bounds_dirty = true;
}
