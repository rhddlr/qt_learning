#ifndef LAYOUTTEST_H
#define LAYOUTTEST_H

#include <fstream>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class LayoutTest;
}
QT_END_NAMESPACE

class LayoutTest : public QWidget {
    Q_OBJECT

    public:
    LayoutTest(QWidget* parent = nullptr);
    ~LayoutTest();

    private slots:
    void on_pushButton_clicked();

    private:
    Ui::LayoutTest* ui;
    std::unique_ptr<std::wofstream> m_openedFile;
    void unlockFile();
    void relockFile(const std::wstring& fileName);
    void writeFile();
};
#endif  // LAYOUTTEST_H
