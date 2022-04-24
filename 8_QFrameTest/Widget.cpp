#include "Widget.h"

#include <QComboBox>
#include <QDateTimeEdit>
#include <QDebug>
#include <QFont>
#include <QLabel>
#include <QLineEdit>
#include <QMovie>
#include <QStackedWidget>
#include <QString>
#include <QStringList>
#include <QTextCodec>
#include <QToolBox>
#include <QVBoxLayout>
#include <QCoreApplication>

namespace {
    void createTextLabel(QString text, QVBoxLayout* layout) {
        QFont font;
        font.setFamily("微软雅黑");
        font.setPointSize(15);
        font.setBold(true);
        font.setItalic(true);
        // qDebug()<<font;
        // pointer<QLabel> const label = new QLabel; const pointer to int,即指针是常量,值是可变的
        auto* const textLabel = new QLabel;  //表示指针是常量
        // const auto* textLabel;
        textLabel->setFont(font);
        QString sampleText = textLabel->fontMetrics().elidedText(text, Qt::ElideMiddle, 200);
        textLabel->setText(sampleText);
        layout->addWidget(textLabel);
    }

    void createIconLabel(QVBoxLayout* layout) {
        auto* const iconLabel = new QLabel;
        QPixmap pixmap(QStringLiteral(":/1.png"));
        pixmap.scaled(iconLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        iconLabel->setScaledContents(true);
        iconLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        iconLabel->setPixmap(pixmap);

        layout->addWidget(iconLabel);
    }
    void createGifLabel(QVBoxLayout* layout) {
        auto* const movie = new QMovie(QString(":/失望.gif"));
        auto* const gifLabel = new QLabel;
        gifLabel->setScaledContents(true);
        gifLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        movie->setScaledSize(gifLabel->size() / 2);
        gifLabel->setMovie(movie);
        movie->start();
        layout->addWidget(gifLabel);
    }
    QWidget* createEmptyWidgetWithVBoxLayout(QWidget* parent) {
        auto* const widget = new QWidget;
        widget->setStyleSheet("background:white;");
        auto* const vlayout = new QVBoxLayout(parent);
        vlayout->setContentsMargins(1, 0, 1, 5);
        widget->setLayout(vlayout);
        return widget;
    }
    QStackedWidget* createStackedWidget(QVBoxLayout* layout, QWidget* parent) {
        QWidget* const w1 = createEmptyWidgetWithVBoxLayout(parent);
        w1->setWindowTitle("page one");
        auto* const w1Layout = static_cast<QVBoxLayout*>(w1->layout());
        createTextLabel(parent->tr("标题太长,需要省略,过时的技巧和用法!"), w1Layout);

        auto* const w2 = createEmptyWidgetWithVBoxLayout(parent);
        w2->setWindowTitle("page two");
        auto* const w2Layout = static_cast<QVBoxLayout*>(w2->layout());
        createIconLabel(w2Layout);

        auto* const w3 = createEmptyWidgetWithVBoxLayout(parent);
        w3->setWindowTitle("page three");
        auto* const w3Layout = static_cast<QVBoxLayout*>(w3->layout());
        createGifLabel(w3Layout);

        auto* const sw = new QStackedWidget;
        sw->addWidget(w1);
        sw->addWidget(w2);
        sw->addWidget(w3);
        sw->setCurrentIndex(0);

        QComboBox* comboBox = new QComboBox;
        comboBox->addItem("page 1");
        comboBox->addItem("page 2");
        comboBox->addItem("page 3");
        parent->connect(comboBox, SIGNAL(activated(int)), sw, SLOT(setCurrentIndex(int)));

        auto* const swLayout = new QVBoxLayout;
        swLayout->addWidget(comboBox);
        swLayout->addWidget(sw);
        layout->addLayout(swLayout);

        return sw;
    }

    QToolBox* createToolBox(QWidget* parent) {
        auto* const tb = new QToolBox(parent);
        auto* const lineEdit = new QLineEdit(parent);
        QString inputMast(">AA!-999-9999-9999_aa\#_HH;*");
        parent->connect(lineEdit, &QLineEdit::returnPressed, parent, [lineEdit]() {
            lineEdit->setFocus();
            qDebug() << lineEdit->text();
            qDebug() << lineEdit->displayText();
        });
        lineEdit->setInputMask(inputMast);
        tb->addItem(lineEdit, QStringLiteral("Mask:") + inputMast);

        auto* const timeEdit = new QDateTimeEdit(parent);
        timeEdit->setDateTime(QDateTime::currentDateTime());
        timeEdit->setDisplayFormat(QStringLiteral("yyyy-MM-dd_ddd_HH:mm:ss"));
        tb->addItem(timeEdit, QCoreApplication::tr("QDateTimeEdit"));

        QString text("title");
        QString elideText = parent->fontMetrics().elidedText(text, Qt::ElideRight, 150);
        tb->addItem(new QLabel(text, parent), elideText);

        return tb;
    }
}  // namespace

Widget::Widget(QWidget* parent) : QWidget(parent) {
    auto* const verticalLayout = new QVBoxLayout;
    createStackedWidget(verticalLayout, this);

    verticalLayout->addWidget(createToolBox(this));
    setLayout(verticalLayout);
}

Widget::~Widget() {}
