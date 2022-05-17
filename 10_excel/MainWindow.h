#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE
class QAxObject;
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void createExcel();
    void createExcel_test();
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow* ui;
    QString _filePath;
    QAxObject* _execl{};
    QAxObject* workbooks{};
};
#endif  // MAINWINDOW_H
