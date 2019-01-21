#ifndef CONFSTRINGWIDGET_H
#define CONFSTRINGWIDGET_H

#include <QWidget>
#include <QLineEdit>

namespace Ui {
  class ConfStringWidget;
}

class ConfStringWidget : public QWidget
{
  Q_OBJECT

public:
  explicit ConfStringWidget(const QString& tag, const QString& init_text, QWidget *parent = nullptr);
  ~ConfStringWidget();

  inline QString get_text()
  {
    return text->text();
  }

private:
  Ui::ConfStringWidget *ui;
  QLineEdit* text;
};

#endif // CONFSTRINGWIDGET_H
