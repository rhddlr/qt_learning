#include <QDialog>
#include "DialogOptionWidget.h"

DialogOptionWidget::DialogOptionWidget(QWidget *parent)
    :QGroupBox(parent)
    ,m_layout(new QVBoxLayout)
{
    this->setTitle(QDialog::tr("Option"));
    this->setLayout(this->m_layout);
}

void DialogOptionWidget::addCheckBox(const QString &text, int value)
{
    QCheckBox *checkBox = new QCheckBox(text);
    auto tmpQPair = CheckBoxEntry(checkBox,value);

    //查询是否已经存在,再插入链表
    if(value>=0 && !checkBoxEntries.count(tmpQPair))
    {
        m_layout->addWidget(checkBox);
        checkBoxEntries.append(tmpQPair);
    }
    else
    {
        delete checkBox;
    }
}

void DialogOptionWidget::addSpacer()
{
    m_layout->addItem(
                new QSpacerItem(0,0,
                        QSizePolicy::Ignored,
                        QSizePolicy::MinimumExpanding));
}

int DialogOptionWidget::value() const
{
    int ret = 0;
    foreach(const auto& checkboxEntry,checkBoxEntries)
        if(checkboxEntry.first->isChecked())
            ret |=checkboxEntry.second;
    //返回各种flag的或运算结果
    return ret;
}
