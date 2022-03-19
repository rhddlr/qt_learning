#include <QApplication>
#include "CustomWidght.h"
#include "ui_helloDialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  CustomWidght *mywidght = new CustomWidght;
  mywidght->show();
  QDialog w;
  Ui::helloDialog ui;
  ui.setupUi(&w);
  w.show();
  return a.exec();
}
