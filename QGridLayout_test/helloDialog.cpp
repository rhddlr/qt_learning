#include "helloDialog.h"
#include "ui_helloDialog.h"

helloDialog::helloDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::helloDialog)
{
  ui->setupUi(this);
}

helloDialog::~helloDialog()
{
  delete ui;
}
