#ifndef DIALOGOPTIONWIDGET_H
#define DIALOGOPTIONWIDGET_H
#include <QGroupBox>
#include <QString>
#include <QWidget>
#include <QCheckBox>
#include <QVBoxLayout>

class DialogOptionWidget : public QGroupBox
{
public:
    explicit DialogOptionWidget(QWidget *parent = nullptr);
    void addCheckBox(const QString& text,int value);
    void addSpacer();
    int value() const;

private:
    using CheckBoxEntry = QPair<QCheckBox*,int>;
    QVBoxLayout *m_layout;
    QList<CheckBoxEntry> checkBoxEntries;
};

#endif // DIALOGOPTIONWIDGET_H
