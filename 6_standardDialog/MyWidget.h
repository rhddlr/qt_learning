#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include<QLabel>

#include "DialogOptionWidget.h"

namespace Ui {
    class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

private slots:
    void on_colorButton_clicked();

private:
    Ui::MyWidget *ui;
    QWidget *page;
    QGridLayout *m_layout;

    QLabel* colorLabel;
    DialogOptionWidget* colorDialogOptionWidget;
};

#endif // MYWIDGET_H
