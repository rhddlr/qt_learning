#include "Widget.h"
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QVBoxLayout>
#include <QColor>
#include <QLabel>

Widget::Widget(QWidget* parent) : QWidget(parent)
{
    nameButton = new QPushButton;
    auto* layout = new QVBoxLayout;
    layout->addWidget(nameButton);
    nameButton->setText(tr("wishing子提"));
    nameButton->setFont(QFont(QStringLiteral("微软雅黑"), 50));
    setLayout(layout);

    _timer.setInterval(2000);
    _timer.start();
    connect(&_timer, &QTimer::timeout, this, [this]() {
        QPalette normalPalette; //正常的步骤
        QColor color(255, 255, 255);
        color.setAlphaF(0.65); //设置透明度为0.3
        normalPalette.setColor(QPalette::WindowText, color);
        nameButton->setPalette(normalPalette);
        qDebug() << "remaining time:" << _timer.remainingTime();
        _timer.stop();
    });

    connect(nameButton, &QPushButton::clicked, this, &Widget::popTimedMessageBox);
    QString hint = QStringLiteral("%1\n%2").arg("asda", "wewqe");
    qDebug() << hint;
}

Widget::~Widget() { delete nameButton; }

void Widget::popTimedMessageBox()
{
    TimedMessageBoxParam param;
    param.title = tr("Instance Segmentation (1)");
    const QString correctTextToShow =
        "[DL-E0301]\nError: Model File: "
        "\"D:/DLK2.2/example_projects/InstanceSegmentation(WoodenBlocks)\" cannot be "
        "found.\n\nSolution:  Please set \"Model->Model File\" correctly.";

    /// errorText contains Escape characters cause QLabel calculated incorrect text length
    const QString errorText =
        "[DL-E0301]\nError: Model File: "
        "\"D:\\DLK2.2\\example_projects\\InstanceSegmentation(WoodenBlocks)\" cannot be "
        "found.\n\nSolution:  Please set \"Model->Model File\" correctly.";
    const QString errorText2 =
        "[DL-E0301]\nError: Model File: "
        "\"D:\\DLK\\2.2\\Exa\\Mple_\\Projects\\Instance\\Segment\\Ition(WoodenBlocks)\" cannot be "
        "found.\n\nSolution:  Please set \"Model->Model File\" correctly.";
    const QString testText =
        "真汉字汉字汉字D:"
        "\\abcdefghijklnopqrstuvwxyZabcdefghijklnopqrstuvwxyZabcdefghijklnopqrstuvwxyZ汉字汉字";
    param.text = testText;

    //    param.solution =
    //        tr("解决方案: The camera is not detected yet.Please check the IP and the camera
    //        network"
    //           "The camera is not detected yet.Please check the IP and the camera network");
    param.timedButtonText = tr("confirm");
    param.timeInMs = 10000;
    //    const auto ret = QMessageBox::warning(this, param.title, testText, QMessageBox::Ok | QMessageBox::Cancel);
    //    if (ret == QMessageBox::Cancel)
    //        return;
    timedMB = new TimedMessageBox(QtCriticalMsg, param);
    timedMB->addButton(tr("other btn"), QMessageBox::AcceptRole);
    timedMB->show();
}
