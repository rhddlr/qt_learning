#include <QDialog>

#include "MyWidget.h"
#include "ui_MyWidget.h"

#include "MyDialog.h"
MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    /** 因为变量作用域原因dialog会在MyWidget构造函数执行后就释放
    QDialog dialog(this);
    dialog.show();
     */
    QDialog *dialog = new QDialog(this);
    //dialog->setModal(true);//模态对话框,不能跟同一个程序其他对话框交互,跟setWindowModality(Qt::ApplicationModal)一样
    //dialog->setWindowModality(Qt::WindowModal);//阻塞父窗口及其他父窗口的子窗口
    //dialog->exec();//使用这个函数后,这个对话框关闭后才会显示后面的对话框
    dialog->show();//这个就可以同时显示

    connect(ui->showChildButton,&QPushButton::clicked,this,&MyWidget::showChildDialog);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::showChildDialog()
{
    MyDialog *dialog = new MyDialog(this);//绑定父窗口
    dialog->setWindowTitle(QStringLiteral("手动关联信号和槽创建的窗口"));
    dialog->show();
}

void MyWidget::on_showChildButton_auto_clicked()
{
    MyDialog *dialog = new MyDialog(this);//绑定父窗口
    dialog->setWindowTitle(QStringLiteral("自动关联信号和槽所创建的窗口"));
    dialog->show();
}


void MyWidget::on_DialogReturnCheckButton_clicked()
{
    MyDialog *dialog = new MyDialog(this);//绑定父窗口
    if(dialog->exec() == QDialog::Accepted)//执行到这里会卡主,然后会判断界面返回的消息
    {
        this->close();//关闭父窗口
    }
}
