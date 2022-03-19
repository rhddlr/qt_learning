#ifndef HELLODIALOG_H
#define HELLODIALOG_H

#include <QDialog>

namespace Ui {
  class helloDialog;
}

class helloDialog : public QDialog
{
  Q_OBJECT

public:
  explicit helloDialog(QWidget *parent = nullptr);
  ~helloDialog();

private:
  Ui::helloDialog *ui;
};

#endif // HELLODIALOG_H
