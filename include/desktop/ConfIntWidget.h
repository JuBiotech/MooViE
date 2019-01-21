#ifndef CONFINTWIDGET_H
#define CONFINTWIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <limits.h>

namespace Ui {
  class ConfIntWidget;
}

class ConfIntWidget : public QWidget
{
  Q_OBJECT

public:
  explicit ConfIntWidget(const QString& tag, int init_val, int lower_restr = INT_MIN, int upper_restr = INT_MAX,
                         QWidget *parent = nullptr);
  ~ConfIntWidget();

  inline int get_value()
  {
    return value->value();
  }

private:
  Ui::ConfIntWidget *ui;
  QSpinBox* value;
};

#endif // CONFINTWIDGET_H
