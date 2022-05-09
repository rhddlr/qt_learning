#include <QGridLayout>
#include <QFile>
#include <QDebug>

#include "LayoutTest.h"
#include "ui_LayoutTest.h"

LayoutTest::LayoutTest(QWidget* parent)
    : QWidget(parent), ui(new Ui::LayoutTest) {
    ui->setupUi(this);
    //    auto* const layout = new QGridLayout;
    //    setLayout(layout);
    //    layout->addWidget(ui->fontComboBox, 0, 0, 1, 2);
    //    layout->addWidget(ui->pushButton, 0, 2, 1, 1);
    //    layout->addWidget(ui->textEdit, 1, 0, 1, 3);
    setMinimumSize(sizeHint());  // ignore minimumsizehint
    qDebug() << sizeHint();
    auto* const hideBtn = new QPushButton(tr("hide"));
    hideBtn->setCheckable(true);
    connect(hideBtn, &QPushButton::toggled, this, [=](bool checked) {
        ui->fontComboBox->setVisible(checked);
        if (checked)
            hideBtn->setText(tr("hide"));
        else
            hideBtn->setText(tr("show"));
    });
    auto* const layout = qobject_cast<QHBoxLayout*>(ui->horizontalLayout);
    layout->addWidget(hideBtn, 1);
}

LayoutTest::~LayoutTest() { delete ui; }

void LayoutTest::on_pushButton_clicked() {
    QFile file("./2.csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qDebug() << file.errorString();

        return;
    }
    static int count = 0;
    const QString appendSomething = QString("appendstr_%1").arg(count);
    file.write(appendSomething.toUtf8(), appendSomething.length());
    file.close();
}

void LayoutTest::unlockFile() {
    m_openedFile.reset(nullptr);
}

void LayoutTest::relockFile(const std::wstring& fileName) {
    m_openedFile.reset(new std::wofstream());
    // _SH_DENYWR is WinAPI dependent deny write mode
    m_openedFile->open(fileName, std::ios_base::app, _SH_DENYWR);
    if (!m_openedFile->is_open())
        m_openedFile.reset(nullptr);
}

void LayoutTest::writeFile() {
    m_openedFile.reset(new std::wofstream());
    QString fileName("./2.csv");
    m_openedFile->open(fileName.toStdWString().c_str(), std::ios_base::out | std::ios_base::app, _SH_DENYWR);

    if (m_openedFile) {
        static int count = 0;
        const QString appendSomething = QString("appendstr_%1").arg(count);
        m_openedFile->write(appendSomething.toStdWString().c_str(), appendSomething.toStdWString().length());
        m_openedFile->close();
    }
}
