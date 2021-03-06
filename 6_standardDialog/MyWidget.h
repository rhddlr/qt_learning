#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include<QLabel>
#include<QPushButton>
#include<QErrorMessage>
#include "DialogOptionWidget.h"

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

private slots:
    void on_colorButton_clicked();
    void setMultiLineText();
    void setDouble();
    void setItem();

    void setExistingDirectory();
    void setOpenFileName();
    void setOpenFileNames();
    void setSaveFileName();

    void setFont();

    void criticalMessage();
    void informationMessage();
    void questionMessage();
    void warningMessage();
    void errorMessage();
private:
    QWidget *page;
    QGridLayout *m_layout;

    QLabel *doubleLabel;
    QLabel *itemLabel;
    QLabel *multiLineTextLabel;

    QLabel *colorLabel;

    QLabel *fontLabel;

    QLabel *directoryLabel;
    QLabel *openFileNameLabel;
    QLabel *openFileNamesLabel;
    QLabel *saveFileNameLabel;

    QLabel *criticalLabel;
    QLabel *informationLabel;
    QLabel *questionLabel;
    QLabel *warningLabel;
    QLabel *errorLabel;

    QPushButton *colorButton;

    QErrorMessage *errorMessageDialog;

    DialogOptionWidget *fileDialogOptionWidget;
    DialogOptionWidget *colorDialogOptionWidget;
    DialogOptionWidget *fontDialogOptionWidget;
};

#endif // MYWIDGET_H
