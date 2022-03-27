#ifndef CLASSWIZARD_H
#define CLASSWIZARD_H

#include <QWizard>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QRadioButton>
#include <QGroupBox>

class IntroPage;
class ClassInfoPage;
class CodeStylePage;
class OutputFilesPage;
class ConclusionPage;

class ClassWizard : public QWizard
{
    Q_OBJECT
public:
    explicit ClassWizard(QWizard *parent = nullptr);
    void accept() override;
signals:

public slots:
};

class IntroPage:public QWizardPage
{
    Q_OBJECT
public:
    IntroPage(QWidget* parent = nullptr);
private:
    QLabel *label;
};

class ClassInfoPage:public QWizardPage
{
    Q_OBJECT
public:
    ClassInfoPage(QWidget* parent = nullptr);
private:
    QLabel *classNameLabel;
    QLabel *baseClassLabel;
    QLineEdit *classNameLineEdit;
    QLineEdit *baseClassLineEdit;
    QCheckBox *qobjectMacroCheckBox;
    QGroupBox *groupBox;
    QRadioButton *qobject_RadioButton;
    QRadioButton *qwidget_RadioButton;
    QRadioButton *default_RadioButton;
    QCheckBox *copyCtorCheckBox;
};

class CodeStylePage: public QWizardPage
{
    Q_OBJECT
public:
    CodeStylePage(QWidget* parent = nullptr);
private:
    void initializePage() override;

private:
    QCheckBox* commentCheckBox;
    QCheckBox* protectCheckBox;
    QCheckBox* includeBaseCheckBox;
    QLabel* macroNameLabel;
    QLabel* baseIncludeLabel;
    QLineEdit* macroNameLineEdit;
    QLineEdit* baseIncludeLineEdit;
};

class OutputFilesPage:public QWizardPage
{
    Q_OBJECT
public:
    OutputFilesPage(QWidget *parent =nullptr);
protected:
    void initializePage() override;

private:
    void setExistingDirectory();
    QPushButton *outputDirButton;
    QLabel *outputDirLabel;
    QLabel *headerLabel;
    QLabel *implementationLabel;
    QLineEdit *outputDirLineEdit;
    QLineEdit *headerLineEdit;
    QLineEdit *implementationLineEdit;
};

class ConclusionPage:public QWizardPage{
    Q_OBJECT
public:
    ConclusionPage(QWidget *parent = nullptr);
protected:
    void initializePage() override;
private:
    QLabel *label;

};

#endif


