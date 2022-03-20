#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

namespace Ui {
    class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();
public slots:
    void showChildDialog();

private slots:
    //自动关联的解析: on_发射信号的部件对象名称_信号名()
    void on_showChildButton_auto_clicked();
    void on_DialogReturnCheckButton_clicked();

private:
    Ui::MyWidget *ui;
};

#endif // MYWIDGET_H
