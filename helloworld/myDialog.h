#ifndef HELLODIALOG_H
#define HELLODIALOG_H

#include <QDialog>

//前置声明这个类中需要用到的ui
namespace Ui {
    class helloDialog;
}

class myDialog:public QDialog
{
    Q_OBJECT
public:
    explicit myDialog(QWidget * parent = nullptr);
    ~myDialog();

private:
    Ui::helloDialog *ui;
};

#endif // HELLODIALOG_H
