#include "MyWidget.h"

#include<QColorDialog>
#include<QDebug>
#include<QToolBox>
#include<QInputDialog>
#include<QFileDialog>
#include<QFontDialog>


MyWidget::MyWidget(QWidget *parent)
    :QWidget(parent)
{
    this->setMinimumSize(800,600);//窗口初始大小
    QVBoxLayout *verticalLayout;//垂直布局
    if (this->isMinimized() || this->isFullScreen()) {
        QHBoxLayout *horizontalLayout = new QHBoxLayout(this);
        QGroupBox *groupBox = new QGroupBox(this->windowTitle(), this);
        horizontalLayout->addWidget(groupBox);
        verticalLayout = new QVBoxLayout(groupBox);
    } else {
        verticalLayout = new QVBoxLayout(this);
    }

    QToolBox* toolbox = new QToolBox;
    verticalLayout->addWidget(toolbox);
    errorMessageDialog = new QErrorMessage(this);

    // dialog属性
    const QString doNotUserNativeDialog = tr("Do not user native dialog");
    int frameStyle = QFrame::Sunken | QFrame::Panel;

    // QInputDialog
    itemLabel = new QLabel;
    itemLabel->setFrameStyle(frameStyle);
    QPushButton *itemButton = new QPushButton(tr("QInputDialog::getIte&m()"));
    connect(itemButton, &QAbstractButton::clicked, this, &MyWidget::setItem);

    doubleLabel = new QLabel;
    doubleLabel->setFrameStyle(frameStyle);
    QPushButton *doubleButton =
          new QPushButton(tr("QInputDialog::get&Double()"));
    connect(doubleButton, &QAbstractButton::clicked, this, &MyWidget::setDouble);

    multiLineTextLabel = new QLabel;
    multiLineTextLabel->setFrameStyle(frameStyle);
    QPushButton *multiLineTextButton =
            new QPushButton(tr("QInputDialog::get&MultiLineText()"));
    connect(multiLineTextButton, &QAbstractButton::clicked, this, &MyWidget::setMultiLineText);

    page = new QWidget;
    m_layout = new QGridLayout(page);
    m_layout->setColumnStretch(1, 1);
    m_layout->setColumnMinimumWidth(1, 250);
    m_layout->addWidget(multiLineTextButton,0, 0);
    m_layout->addWidget(multiLineTextLabel, 0, 1);

    m_layout->addWidget(doubleButton,1, 0);
    m_layout->addWidget(doubleLabel,1, 1);

    m_layout->addWidget(itemButton, 2, 0);
    m_layout->addWidget(itemLabel, 2, 1);

    m_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 5, 0);
    toolbox->addItem(page, tr("Input Dialogs"));

    //QColorDialog
    colorLabel = new QLabel;
    colorLabel->setFrameStyle(frameStyle);
    colorButton = new QPushButton(tr("QColorDialog::get&Color()"));
    connect(colorButton, &QAbstractButton::clicked, this, &MyWidget::on_colorButton_clicked);

    page = new QWidget;
    m_layout = new QGridLayout(page);
    m_layout->setColumnStretch(1,1);
    m_layout->addWidget(this->colorButton,0,0);
    m_layout->addWidget(this->colorLabel,3,1);
    colorDialogOptionWidget = new DialogOptionWidget;
    colorDialogOptionWidget->addCheckBox(doNotUserNativeDialog,QColorDialog::DontUseNativeDialog);
    colorDialogOptionWidget->addCheckBox(tr("show alpha channel"),QColorDialog::ShowAlphaChannel);
    colorDialogOptionWidget->addCheckBox(tr("no buttons"),QColorDialog::NoButtons);
    m_layout->addWidget(colorDialogOptionWidget,4,0,1,2);
    m_layout->addItem(new QSpacerItem(0,0,QSizePolicy::Ignored,QSizePolicy::MinimumExpanding),5,0);

    toolbox->addItem(page,tr("Color Dialog"));

    //QFileDialog
    directoryLabel = new QLabel;
    directoryLabel->setFrameStyle(frameStyle);
    QPushButton *directoryButton =
                  new QPushButton(tr("QFileDialog::getE&xistingDirectory()"));

    openFileNameLabel = new QLabel;
    openFileNameLabel->setFrameStyle(frameStyle);
    QPushButton *openFileNameButton =
                  new QPushButton(tr("QFileDialog::get&OpenFileName()"));

    openFileNamesLabel = new QLabel;
    openFileNamesLabel->setFrameStyle(frameStyle);
    QPushButton *openFileNamesButton =
                  new QPushButton(tr("QFileDialog::&getOpenFileNames()"));

    saveFileNameLabel = new QLabel;
    saveFileNameLabel->setFrameStyle(frameStyle);
    QPushButton *saveFileNameButton =
                  new QPushButton(tr("QFileDialog::get&SaveFileName()"));
    connect(directoryButton, &QAbstractButton::clicked,
          this, &MyWidget::setExistingDirectory);
    connect(openFileNameButton, &QAbstractButton::clicked,
          this, &MyWidget::setOpenFileName);
    connect(openFileNamesButton, &QAbstractButton::clicked,
          this, &MyWidget::setOpenFileNames);
    connect(saveFileNameButton, &QAbstractButton::clicked,
          this, &MyWidget::setSaveFileName);

    page = new QWidget;
    m_layout = new QGridLayout(page);
    m_layout->setColumnStretch(1,1);
    m_layout->addWidget(directoryButton,0,0);
    m_layout->addWidget(directoryLabel,0,1);
    m_layout->addWidget(openFileNameButton,1,0);
    m_layout->addWidget(openFileNameLabel,1,1);
    m_layout->addWidget(openFileNamesButton,2,0);
    m_layout->addWidget(openFileNamesLabel,2,1);
    m_layout->addWidget(saveFileNameButton,3,0);
    m_layout->addWidget(saveFileNameLabel,3,1);
    fileDialogOptionWidget = new DialogOptionWidget;
    fileDialogOptionWidget->addCheckBox(doNotUserNativeDialog,QFileDialog::DontUseNativeDialog);
    fileDialogOptionWidget->addCheckBox(tr("Show directories only"), QFileDialog::ShowDirsOnly);
    fileDialogOptionWidget->addCheckBox(tr("Do not resolve symlinks"), QFileDialog::DontResolveSymlinks);
    fileDialogOptionWidget->addCheckBox(tr("Do not confirm overwrite"), QFileDialog::DontConfirmOverwrite);
    fileDialogOptionWidget->addCheckBox(tr("Do not use sheet"), QFileDialog::DontUseSheet);
    fileDialogOptionWidget->addCheckBox(tr("Readonly"), QFileDialog::ReadOnly);
    fileDialogOptionWidget->addCheckBox(tr("Hide name filter details"), QFileDialog::HideNameFilterDetails);
    fileDialogOptionWidget->addCheckBox(tr("Do not use custom directory icons (Windows)"),
                                         QFileDialog::DontUseCustomDirectoryIcons);
    m_layout->addWidget(fileDialogOptionWidget, 4, 0, 1 ,2);
    m_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 5, 0);

    toolbox->addItem(page, tr("File Dialogs"));

    //QFontDialog
    fontLabel = new QLabel;
    fontLabel->setFrameStyle(frameStyle);
    QPushButton *fontButton = new QPushButton(tr("QFontDialog::getFont()"));
    connect(fontButton,&QAbstractButton::clicked,this,&MyWidget::setFont);

    page = new QWidget;
    m_layout = new QGridLayout(page);
    m_layout->setColumnStretch(1,1);
    m_layout->addWidget(fontLabel,0,1);
    m_layout->addWidget(fontButton,0,0);
    fontDialogOptionWidget = new DialogOptionWidget;
    fontDialogOptionWidget->addCheckBox(doNotUserNativeDialog, QFontDialog::DontUseNativeDialog);
    fontDialogOptionWidget->addCheckBox(tr("Show scalable fonts"), QFontDialog::ScalableFonts);
    fontDialogOptionWidget->addCheckBox(tr("Show non scalable fonts"), QFontDialog::NonScalableFonts);
    fontDialogOptionWidget->addCheckBox(tr("Show monospaced fonts"), QFontDialog::MonospacedFonts);
    fontDialogOptionWidget->addCheckBox(tr("Show proportional fonts"), QFontDialog::ProportionalFonts);
    fontDialogOptionWidget->addCheckBox(tr("No buttons") , QFontDialog::NoButtons);
    m_layout->addWidget(fontDialogOptionWidget,2,0,1,2);
    m_layout->addItem(new QSpacerItem(0,0,QSizePolicy::Ignored,QSizePolicy::MinimumExpanding),3,0);
    toolbox->addItem(page,tr("Font Dialig"));

    //QMessageBox
    criticalLabel = new QLabel;
    criticalLabel->setFrameStyle(frameStyle);
    QPushButton *criticalButton = new QPushButton(tr("QMessageBox::critical()"));
    connect(criticalButton, &QAbstractButton::clicked, this, &MyWidget::criticalMessage);

    informationLabel = new QLabel;
    informationLabel->setFrameStyle(frameStyle);
    QPushButton *informationButton = new QPushButton(tr("QMessageBox::information()"));
    connect(informationButton, &QAbstractButton::clicked,
          this, &MyWidget::informationMessage);

    questionLabel = new QLabel;
    questionLabel->setFrameStyle(frameStyle);
    QPushButton *questionButton = new QPushButton(tr("QMessageBox::question()"));
    connect(questionButton, &QAbstractButton::clicked, this, &MyWidget::questionMessage);

    warningLabel = new QLabel;
    warningLabel->setFrameStyle(frameStyle);
    QPushButton *warningButton = new QPushButton(tr("QMessageBox::warning()"));
    connect(warningButton, &QAbstractButton::clicked, this, &MyWidget::warningMessage);

    errorLabel = new QLabel;
    errorLabel->setFrameStyle(frameStyle);
    QPushButton *errorButton = new QPushButton(tr("QMessageBox::showMessage()"));
    connect(errorButton, &QAbstractButton::clicked, this, &MyWidget::errorMessage);

    page = new QWidget;
    m_layout = new QGridLayout(page);
    m_layout->setColumnStretch(1,1);
    m_layout->addWidget(criticalButton,0,0);
    m_layout->addWidget(criticalLabel,0,1);
    m_layout->addWidget(informationButton,1,0);
    m_layout->addWidget(informationLabel,1,1);
    m_layout->addWidget(warningButton,2,0);
    m_layout->addWidget(warningLabel,2,1);
    m_layout->addWidget(errorButton,3,0);
    m_layout->addWidget(errorLabel,3,1);
    m_layout->addWidget(questionButton,4,0);
    m_layout->addWidget(questionLabel,4,1);
    m_layout->addItem(new QSpacerItem(0,0,QSizePolicy::Ignored,QSizePolicy::MinimumExpanding),5,0);
    toolbox->addItem(page,tr("QMessage Boxs"));
}

MyWidget::~MyWidget()
{

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

void MyWidget::setMultiLineText()
{
    bool ok;
    QString text = QInputDialog::getMultiLineText(this,
                                 tr("QInputDialog::getMultilineText()"),
                                 tr("Address:"),"jingon dd\nLONGYUE STREET",&ok);
    if(ok&&!text.isEmpty())
        multiLineTextLabel->setText(text);
}

void MyWidget::setDouble()
{
    bool ok;
    double d = QInputDialog::getDouble(this,tr("QInputdialog::getDouble()"),
                                       tr("Amount:"),3.141592,-10000,20000,2,&ok);
    if(ok)
        doubleLabel->setText(QStringLiteral("%1").arg(d));
}

void MyWidget::setItem()
{
    QStringList items;
    items<<tr("Spring")<<tr("Summer")<<tr("Fall")<<tr("Winter");
    bool ok;
    QString item = QInputDialog::getItem(this,tr("QInputDialog::getItem()"),
                                         tr("Season:"),items,0,false,&ok);
    if(ok&&!item.isEmpty())
        itemLabel->setText(item);
}

void MyWidget::setExistingDirectory()
{
    QFileDialog::Options options = QFlag(fileDialogOptionWidget->value());
    options |= QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(this,
                                      tr("QFileDialog::getExistingDirectory()"),
                                      directoryLabel->text(),
                                      options);
    if (!directory.isEmpty())
              directoryLabel->setText(directory);
}

void MyWidget::setOpenFileName()
{
    const QFileDialog::Options options = QFlag(fileDialogOptionWidget->value());
    QString selectedFilter;
    QString fileName = QFileDialog::getOpenFileName(this,
                                      tr("QFileDialog::getOpenFileName()"),
                                      openFileNameLabel->text(),
                                      tr("All Files (*);;Text Files (*.txt)"),
                                      &selectedFilter,
                                      options);
    if (!fileName.isEmpty())
        openFileNameLabel->setText(fileName);
}

void MyWidget::setOpenFileNames()
{
    const QFileDialog::Options options = QFlag(fileDialogOptionWidget->value());
          QString selectedFilter;
          QString openFilesPath;
          QStringList files = QFileDialog::getOpenFileNames(
                                      this, tr("QFileDialog::getOpenFileNames()"),
                                      openFilesPath,
                                      tr("All Files (*);;Text Files (*.txt)"),
                                      &selectedFilter,
                                      options);
    if (files.count()) {
        openFilesPath = files[0];
        openFileNamesLabel->setText(QStringLiteral("[%1]").arg(files.join(",\n")));
    }
}

void MyWidget::setSaveFileName()
{
    const QFileDialog::Options options = QFlag(fileDialogOptionWidget->value());
    QString selectedFilter;
    QString filename = QFileDialog::getSaveFileName(this,
                                              tr("QFileDialog::getSaveFileName"),
                                              saveFileNameLabel->text(),
                                              tr("All Files(*);;Text Files(*.txt)"),
                                              &selectedFilter,
                                              options);
    if(!filename.isEmpty())
        saveFileNameLabel->setText(filename);
}

void MyWidget::setFont()
{
    const QFontDialog::FontDialogOptions options = QFlag(fontDialogOptionWidget->value());
    bool ok;
    QFont font = QFontDialog::getFont(&ok,QFont(fontLabel->text()),this,"Select font",options);
    if(ok)
    {
        fontLabel->setText(font.key());
        fontLabel->setFont(font);
    }
}

#include<QMessageBox>
#define MESSAGE \
    MyWidget::tr("<p>Message Boxs have caption, a text," \
    "and any number of buttons, each with standard or custon texts."\
    "<p>Click a button to close the messagebox. pressing the Esc button "\
    "will activate the detected escape button (if any).")

#define MESSAGE_DETAILS \
    MyWidget::tr("If a message box has detailed text, the user can reveal it "\
    "by pressing the Show Details... button.")

void MyWidget::criticalMessage()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::critical(this,tr("QMessageBox::critical()"),
                                  MESSAGE,
                                  QMessageBox::Abort|QMessageBox::Retry|QMessageBox::Ignore);
    if(reply == QMessageBox::Abort)
        criticalLabel->setText(tr("Abort"));
    else if (reply == QMessageBox::Retry)
        criticalLabel->setText(tr("Retry"));
    else
        criticalLabel->setText(tr("Ignore"));
}

void MyWidget::informationMessage()
{
    QMessageBox information(QMessageBox::Information,tr("QMessageBox::information()")
                            , MESSAGE,QMessageBox::StandardButton::Ok,this);
    information.addButton(tr("jump to step"),QMessageBox::ButtonRole::AcceptRole);
    int reply = information.exec();
    if (reply == QMessageBox::Ok)
        informationLabel->setText(tr("OK"));
    else if(reply == QMessageBox::AcceptRole)
        informationLabel->setText(tr("jump to step"));
    else
        informationLabel->setText(tr("Escape"));
}

void MyWidget::questionMessage()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("QMessageBox::question()"),
                                  MESSAGE,
                                  QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (reply == QMessageBox::Yes)
      questionLabel->setText(tr("Yes"));
    else if (reply == QMessageBox::No)
      questionLabel->setText(tr("No"));
    else
      questionLabel->setText(tr("Cancel"));
}

void MyWidget::warningMessage()
{
    QMessageBox msgBox(QMessageBox::Warning, tr("QMessageBox::warning()"),
                             MESSAGE, nullptr, this);

    msgBox.setDetailedText(MESSAGE_DETAILS);
    msgBox.addButton(tr("Save &Again"), QMessageBox::AcceptRole);
    msgBox.addButton(tr("&Continue"), QMessageBox::RejectRole);
    if (msgBox.exec() == QMessageBox::AcceptRole)
      warningLabel->setText(tr("Save Again"));
    else
      warningLabel->setText(tr("Continue"));
}

void MyWidget::errorMessage()
{
    errorMessageDialog->showMessage(
    tr("This dialog shows and remembers error messages. "
     "If the checkbox is checked (as it is by default), "
     "the shown message will be shown again, "
     "but if the user unchecks the box the message "
     "will not appear again if QErrorMessage::showMessage() "
     "is called with the same message."),tr("error"));
    errorLabel->setText(tr("If the box is unchecked, the message "
                 "won't appear again."));
}
