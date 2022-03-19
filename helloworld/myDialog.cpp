#include "myDialog.h"
#include "ui_helloDialog.h"

myDialog::myDialog(QWidget *parent):
  QDialog (parent)
{
    ui = new Ui::helloDialog(); //构造ui类
    ui->setupUi(this);                //设置ui致当前类
}

myDialog::~myDialog()
{
    delete ui;
}
