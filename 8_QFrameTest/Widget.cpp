#include "Widget.h"

#include <QFont>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QDebug>
#include <QMovie>
#include <QTextCodec>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QFont font;
    font.setFamily("微软雅黑");
    font.setPointSize(15);
    font.setBold(true);
    font.setItalic(true);
    //qDebug()<<font;
    //pointer<QLabel> const label = new QLabel; const pointer to int,即指针是常量,值是可变的
    auto* const textLabel = new QLabel;//表示指针是常量
    //const auto* textLabel;
    textLabel->setFont(font);
    QString sampleText = textLabel->fontMetrics().elidedText(
                tr("标题太长,需要省略,过时的技巧和用法!"),Qt::ElideMiddle,200);
    textLabel->setText(sampleText);

    auto* const iconLabel = new QLabel;
    QPixmap pixmap(QStringLiteral(":/1.png"));
    pixmap.scaled(iconLabel->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    iconLabel->setScaledContents(true);
    iconLabel->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    iconLabel->setPixmap(pixmap);

    auto* const movie = new QMovie(QString(":/失望.gif"));
    auto* const gifLabel = new QLabel;
    gifLabel->setScaledContents(true);
    movie->setScaledSize(gifLabel->size()/2);
    gifLabel->setMovie(movie);
    movie->start();

    auto* const verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(textLabel);
    verticalLayout->addWidget(iconLabel);
    verticalLayout->addWidget(gifLabel);
    setLayout(verticalLayout);
}

Widget::~Widget()
{
}

