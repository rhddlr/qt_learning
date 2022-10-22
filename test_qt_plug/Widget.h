#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QTimer>
#include <QWidget>
#include "TimedMessageBox.h"

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

public slots:
    void popTimedMessageBox();

private:
    QTimer _timer;
    TimedMessageBox* timedMB;
    QPushButton* nameButton;
};
