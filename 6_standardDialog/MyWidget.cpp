#include "MyWidget.h"
#include "ui_MyWidget.h"

#include<QColorDialog>
#include<QDebug>
#include<QToolBox>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    const QString doNotUserNativeDialog = tr("Do not user native dialog");

    int frameStyle = QFrame::Sunken | QFrame::Panel;

    colorLabel = new QLabel;
    colorLabel->setFrameStyle(frameStyle);

    QToolBox* toolbox = new QToolBox;
    ui->verticalLayout->addWidget(toolbox);
    page = new QWidget;
    m_layout = new QGridLayout(page);
    m_layout->setColumnStretch(1,1);
    m_layout->addWidget(ui->colorButton,0,0);
    m_layout->addWidget(colorLabel,0,1);
    colorDialogOptionWidget = new DialogOptionWidget;
    colorDialogOptionWidget->addCheckBox(doNotUserNativeDialog,QColorDialog::DontUseNativeDialog);
    colorDialogOptionWidget->addCheckBox(tr("show alpha channel"),QColorDialog::ShowAlphaChannel);
    colorDialogOptionWidget->addCheckBox(tr("no buttons"),QColorDialog::NoButtons);
    m_layout->addItem(new QSpacerItem(0,0,QSizePolicy::Ignored,QSizePolicy::MinimumExpanding),1,0);
    m_layout->addWidget(colorDialogOptionWidget,1,0,2,2);

    toolbox->addItem(page,tr("Color Dialog"));
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_colorButton_clicked()
{
    //1. 使用静态函数 QColorDialog::getColor 来创建,好处不用创建对象
//    QColor color = QColorDialog::getColor(Qt::red,this,tr("颜色对话框"),QColorDialog::ShowAlphaChannel);
//    qDebug()<<"color:"<<color;
    //2. 创建对象方式, 好处是可以灵活配置
    QColorDialog dialog(Qt::gray,this);//创建对象
    dialog.exec();//模态方式运行
    QColor color = dialog.currentColor();//获取颜色信息
    if(color.isValid()){
        colorLabel->setText(color.name());
        colorLabel->setPalette(QPalette(color));
        colorLabel->setAutoFillBackground(true);
        qDebug()<<"color:"<<color;
    }
}
