#include "ClassWizard.h"
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QRegularExpression>
#include <QString>
#include <QVBoxLayout>
#include <QVariant>
#include <QDebug>

ClassWizard::ClassWizard(QWizard *parent) : QWizard(parent)
{
    addPage(new IntroPage);
    addPage(new ClassInfoPage);
    addPage(new CodeStylePage);
    addPage(new OutputFilesPage);
    addPage(new ConclusionPage);

    setPixmap(QWizard::BannerPixmap,QPixmap{"://../res/meh-blank.png"});
    setPixmap(QWizard::BackgroundPixmap,QPixmap{"://../res/bg.jpeg"});

    setWindowTitle(tr("Class Wizard"));
}

void ClassWizard::accept()
{
    QByteArray className = field(QString("className")).toByteArray();
    QByteArray baseClass = field("baseClass").toByteArray();
    QByteArray macroName = field("macroName").toByteArray();
    QByteArray baseInclude = field("baseInclude").toByteArray();

    QString outputDir = field("outputDir").toString();
    QString header = field("header").toString();
    QString implementation = field("implementation").toString();

    QByteArray block;
    /*
        A.h
    */
    if(field("comment").toBool()){
        block += "/*\n";
        block +="    "+header.toLatin1()+'\n';
        block += "*/\n";
        block += '\n';
    }
    /*
    #ifdef
    #define
    */
    if(field("protect").toBool()){
        block +="#ifndef "+macroName + '\n';
        block +="#define " + macroName +'\n';
        block+='\n';
    }
    /*
    #include "A.h"
    */
    if(field("includeBase").toBool()){
        block += "#include "+baseInclude +'\n';
        block += '\n';
    }

    /*
    class A:public QWidget
    {
        Q_OBJECT
    */
    block += "class " + className;
    if(!baseClass.isEmpty())
        block += " : public "+baseClass;
    block +='\n';
    block +="{\n";
    //qmake ignore Q_OBJECT
    if(field("qobjectMacro").toBool()){
        block+= "   Q_OBJECT\n";
        block+= '\n';
    }

    /*
    public:
        A(QWidget *parent = nullptr);
    */
    block += "public:\n";
    if(field("qobjectCtor").toBool()){
        block+="    "+className+"(QObject *parent = nullptr);\n";
    }else if (field("qwidgetCtor").toBool()) {
        block +="    "+className+"(QWidget *parent = nullptr);\n";
    }else {
        /*
            A();
            A(const A &other);
            A &operator=(const A &other);
        */
        block +="    "+className+"();\n";
        if(field("copyCtor").toBool()){
            block += "    "+className+"(const "+className+" &other);\n";
            block+='\n';
            block+="    "+className+" &operator=" + "(const "+className+" &other);\n";
        }
    }
    //}; //class over
    block += "};\n";
    /*
    #endif //#ifdef over
    */
    if(field("protect").toBool()){
        block += '\n';
        block += "#endif\n";
    }
    QFile headerFile(outputDir+'/'+header);
    if(!headerFile.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,QObject::tr("Simple Wizard"),QObject::tr("Cannot write file %1:\n%2")
                             .arg(headerFile.fileName(),headerFile.errorString()));
        return;
    }
    headerFile.write(block);//write header file
    block.clear();
    /*
    A.cpp
    */
    if(field("comment").toBool()){
        block += "/*\n";
        block +="    "+implementation.toLatin1()+'\n';
        block +="*/\n";
        block += '\n';
    }
    //#include "A.h"
    block += "#include \"" + header.toLatin1() + "\"\n";
    block += '\n';

    if(field("qobjectCtor").toBool()){
        block += className +"::"+className+"(QObject *parent)\n";
        block +="    :"+ baseClass + "(parent)\n";
        block+="{\n";
        block += "}\n";
    }else if(field("qwidgetCtor").toBool()){
        block += className +"::"+className+"(QWidget *parent)\n";
        block +="    :"+ baseClass + "(parent)\n";
        block+="{\n";
        block += "}\n";
    }else if(field("defaultCtor").toBool()){
        block += className + "::" + className + "(){}\n";
        if(field("copyCtor").toBool())
        {
            block += "\n";
            block += className + "::" + className + "(const "+className+" *other)\n";
            block +="{\n";
            block +="    *this = other;\n";
            block +="}\n";
            block +='\n';
            block +=className +" &"+className+"::operator=(const "
                    + className +" &other)\n";
            block +="{\n";
            if(!baseClass.isEmpty())
                block += "    " +baseClass + "::operator=(other);\n";
            block +="    // missing code\n";
            block +="    return *this;";
            block +="}\n";
        }
    }

    QFile implementationFile(outputDir +'/'+implementation);
    if(!implementationFile.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,tr("Simple Wizard"),
                             QObject::tr("Cannot write file %1:\n%2")
                             .arg(implementationFile.fileName(),implementationFile.errorString()));
        return;
    }
    implementationFile.write(block);

    QDialog::accept();
}

IntroPage::IntroPage(QWidget *parent):QWizardPage(parent)
{
    setTitle(tr("Introduction"));
    setPixmap(QWizard::WatermarkPixmap,QPixmap(":/res/flushed.png"));

    label = new QLabel(tr("this wizard will generate a skeleton c++ class definition, including a few functions. you simply "
                          "options to produce a header file and an "
                          "implementation file for your new c++ class."));
    label->setWordWrap(true);//应该是自动换行功能
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

ClassInfoPage::ClassInfoPage(QWidget *parent):QWizardPage(parent)
{
    setTitle(tr("Class Information"));
    setSubTitle(tr("Specify basic information about the class for which you "
                   "want to generate skeleton source code files."));
    setPixmap(QWizard::LogoPixmap,QPixmap(":/res/frown.png"));

    classNameLabel = new QLabel(tr("&Class name:"));
    classNameLineEdit = new QLineEdit;
    classNameLabel->setBuddy(classNameLineEdit);

    baseClassLabel = new QLabel(tr("B&ase class:"));
    baseClassLineEdit = new QLineEdit;
    baseClassLabel->setBuddy(baseClassLineEdit);

    qobjectMacroCheckBox = new QCheckBox(tr("Generate Q_OBJECT &macro"));
    qobject_RadioButton = new QRadioButton(tr("Q&Object-style constructor"));
    qwidget_RadioButton = new QRadioButton(tr("Q&Widget-style constructor"));
    default_RadioButton = new QRadioButton(tr("&Default-style constructor"));
    copyCtorCheckBox = new QCheckBox(tr("&Generate copy constructor and operator="));

    default_RadioButton->setChecked(true);
    //当radio被选中时,让copy checkbox可用
    connect(default_RadioButton,&QAbstractButton::toggled,copyCtorCheckBox,&QWidget::setEnabled);
    connect(qobject_RadioButton,&QAbstractButton::toggled,this,[this](bool tuggled){
        tuggled? this->baseClassLineEdit->setText("QObject"):this->baseClassLineEdit->clear();
    });
    connect(qwidget_RadioButton,&QAbstractButton::toggled,this,[this](bool tuggled){
        tuggled? this->baseClassLineEdit->setText("QWidget"):this->baseClassLineEdit->clear();
    });

    registerField("className*",classNameLineEdit);
    registerField("baseClass",baseClassLineEdit);
    registerField("qobjectMacro",qobjectMacroCheckBox);
    registerField("qobjectCtor",qobject_RadioButton);
    registerField("qwidgetCtor",qwidget_RadioButton);
    registerField("defaultCtor",default_RadioButton);
    registerField("copyCtor",copyCtorCheckBox);

    groupBox = new QGroupBox(tr("C&onstructor"));
    QVBoxLayout *groupBoxLayout = new QVBoxLayout;
    groupBoxLayout->addWidget(qobject_RadioButton);
    groupBoxLayout->addWidget(qwidget_RadioButton);
    groupBoxLayout->addWidget(default_RadioButton);
    groupBoxLayout->addWidget(copyCtorCheckBox);
    groupBoxLayout->setSpacing(10);
    groupBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::MinimumExpanding);
    groupBox->setLayout(groupBoxLayout);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(classNameLabel,0,0);
    layout->addWidget(classNameLineEdit,0,1);
    layout->addWidget(baseClassLabel,1,0);
    layout->addWidget(baseClassLineEdit,1,1);
    layout->addWidget(qobjectMacroCheckBox,2,0,1,2);
    layout->addWidget(groupBox,3,0,1,2);
    setLayout(layout);
    //qDebug()<<this->layout(); // 0x0
}

CodeStylePage::CodeStylePage(QWidget *parent):QWizardPage (parent)
{
    setTitle(tr("Code Style Options"));
    setSubTitle(tr("Choose the formatting of the generated code."));
    setPixmap(QWizard::LogoPixmap,QPixmap(":/../res/grimace.png"));
    commentCheckBox = new QCheckBox(tr("&Start generated files with a "
                                       "comment"));
    commentCheckBox->setChecked(true);

    protectCheckBox = new QCheckBox(tr("&Protect header file against multiple "
                                       "inclusions"));
    protectCheckBox->setChecked(true);

    macroNameLabel = new QLabel(tr("&Macro name:"));
    macroNameLineEdit = new QLineEdit;
    macroNameLabel->setBuddy(macroNameLineEdit);

    includeBaseCheckBox = new QCheckBox(tr("&Include base class definition"));
    baseIncludeLabel = new QLabel(tr("Base class include:"));
    baseIncludeLineEdit = new QLineEdit;
    baseIncludeLabel->setBuddy(baseIncludeLineEdit);

    connect(protectCheckBox,&QAbstractButton::toggled,
            macroNameLabel,&QWidget::setEnabled);
    connect(protectCheckBox,&QAbstractButton::toggled,
            macroNameLineEdit,&QWidget::setEnabled);
    connect(includeBaseCheckBox,&QAbstractButton::toggled,
            baseIncludeLabel,&QWidget::setEnabled);
    connect(includeBaseCheckBox,&QAbstractButton::toggled,
            baseIncludeLineEdit,&QWidget::setEnabled);

    registerField("comment",commentCheckBox);
    registerField("protect",protectCheckBox);
    registerField("macroName",macroNameLineEdit);
    registerField("includeBase",includeBaseCheckBox);
    registerField("baseInclude",baseIncludeLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->setColumnMinimumWidth(0,20);
    layout->addWidget(commentCheckBox,0,0,1,3);
    layout->addWidget(protectCheckBox,1,0,1,3);
    layout->addWidget(macroNameLabel,2,1);
    layout->addWidget(macroNameLineEdit,2,2);
    layout->addWidget(includeBaseCheckBox,3,0,1,3);
    layout->addWidget(baseIncludeLabel,4,1);
    layout->addWidget(baseIncludeLineEdit,4,2);

    setLayout(layout);
}

void CodeStylePage::initializePage()
{
    QString className = field("className").toString();
    macroNameLabel->setText(className.toUpper() + "_H");

    QString baseClass = field("baseClass").toString();

    includeBaseCheckBox->setChecked(!baseClass.isEmpty());
    includeBaseCheckBox->setEnabled(!baseClass.isEmpty());
    baseIncludeLabel->setEnabled(!baseClass.isEmpty());
    baseIncludeLineEdit->setEnabled(!baseClass.isEmpty());

    static QRegularExpression rx("Q[A-Z].*");
    if(baseClass.isEmpty())
    {
        baseIncludeLineEdit->clear();
    }else if(rx.match(baseClass).hasMatch()){
        baseIncludeLineEdit->setText('<'+baseClass+'>');
    }else {
        baseIncludeLineEdit->setText('"'+baseClass.toLower()+".h\"");
    }
}

OutputFilesPage::OutputFilesPage(QWidget *parent):QWizardPage (parent)
{
    setTitle(tr("Output Files"));
    setSubTitle(tr("Specify where you want the wizard to put the generated "
                   "skeleton code."));
    outputDirLabel = new QLabel(tr("&Output directory:"));
    outputDirLineEdit = new QLineEdit;
    outputDirLabel->setBuddy(outputDirLineEdit);
    outputDirButton = new QPushButton(tr("selectDir"));
    connect(outputDirButton,&QAbstractButton::clicked,this, &OutputFilesPage::setExistingDirectory);
    QHBoxLayout *outputDirLayout = new QHBoxLayout;
    outputDirLayout->addWidget(outputDirLineEdit);
    outputDirLayout->addWidget(outputDirButton);

    headerLabel = new QLabel(tr("&Header file name:"));
    headerLineEdit = new QLineEdit;
    headerLabel->setBuddy(headerLineEdit);

    implementationLabel = new QLabel(tr("&Implementation file name:"));
    implementationLineEdit = new QLineEdit;
    implementationLabel->setBuddy(implementationLineEdit);

    registerField("outputDir*",outputDirLineEdit);
    registerField("header*",headerLineEdit);
    registerField("implementation*",implementationLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(outputDirLabel,0,0);
    layout->addLayout(outputDirLayout,0,1);
    layout->addWidget(headerLabel,1,0);
    layout->addWidget(headerLineEdit,1,1);
    layout->addWidget(implementationLabel,2,0);
    layout->addWidget(implementationLineEdit,2,1);
    setLayout(layout);
}
void OutputFilesPage::setExistingDirectory()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(this,
                                      tr("QFileDialog::getExistingDirectory()"),
                                      outputDirLineEdit->text(),
                                      options);
    if (!directory.isEmpty())
              outputDirLineEdit->setText(directory);
}
void OutputFilesPage::initializePage()
{
    QString className = field("className").toString();
    headerLineEdit->setText(className.toLower()+".h");
    implementationLineEdit->setText(className.toLower()+".cpp");
    outputDirLineEdit->setText(QDir::toNativeSeparators(QDir::tempPath()));
}

ConclusionPage::ConclusionPage(QWidget *parent):QWizardPage (parent)
{
    setTitle(tr("Conclusion"));
    setPixmap(QWizard::WatermarkPixmap,QPixmap(":/../res/angry.png"));

    label = new QLabel;
    label->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

void ConclusionPage::initializePage()
{
    QString finishText = wizard()->buttonText(QWizard::FinishButton);
    finishText.remove('&');
    label->setText(tr("Click %1 generate the class skeleton.")
                   .arg(finishText));
}
