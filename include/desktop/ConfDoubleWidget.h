#ifndef CONFDOUBLEWIDGET_H
#define CONFDOUBLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QDoubleSpinBox>
#include <float.h>

namespace Ui {
  class ConfDoubleWidget;
}

class ConfDoubleWidget : public QWidget
{
  Q_OBJECT

public:
  explicit ConfDoubleWidget(const QString& tag, double init_val, double lower_restr = DBL_MIN, double upper_restr = DBL_MAX,
                            int decimals = 1, double step = 0.1, QWidget *parent = nullptr);
  ~ConfDoubleWidget();

  inline double get_value()
  {
    return value->value();
  }

private:
  Ui::ConfDoubleWidget* ui;
  QDoubleSpinBox* value;
};

#endif // CONFDOUBLEWIDGET_H
