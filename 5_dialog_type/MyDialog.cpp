#include "MyDialog.h"
#include "ui_MyDialog.h"

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
}

MyDialog::~MyDialog()
{
    delete ui;
}

void MyDialog::on_quitButton_clicked()
{
    accept();
    //对于使用exec函数实现的模态对话框
    //执行了这个槽就会隐藏这个模态地画框
    //并返回QDialog::Accepted
}

void MyDialog::on_enterButton_clicked()
{

}
