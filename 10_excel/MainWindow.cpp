#include <ActiveQt/QAxObject>
#include <QtWidgets>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    _filePath = QStringLiteral("./1.xlsx");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::createExcel() {
    QAxObject* excel = new QAxObject("Excel.Application");
    if (!excel)
        qDebug() << "fail to create excel";
    excel->dynamicCall("SetVisible(bool Visible)", false);  //是否可视化excel
    excel->dynamicCall("SetUserControl(bool UserControl)", false);  //是否用户可操作
    excel->setProperty("DisplayAlerts", false);  //是否弹出警告窗口

    QAxObject* workbooks = excel->querySubObject("WorkBooks");  //获取工作簿集合
    workbooks->dynamicCall("Add");  //新建一个工作簿
    QAxObject* workbook = excel->querySubObject("ActiveWorkBook");  //获取当前工作簿
    QAxObject* sheets = workbook->querySubObject("Sheets");  //获取工作表格集合
    QAxObject* sheet = sheets->querySubObject("Item(int)", 1);  //获取当前工作表格1,sheet1
    sheet->setProperty("Name", "p1");  //修改sheet名称

    //创建表头
    const QVariant var = QStringLiteral("A1:A3");
    const QVariant value = tr("port1");
    QAxObject* range = sheet->querySubObject("Range(const QString&)", var);
    range->setProperty("MergeCells", true);
    range->setProperty("Value", value);
    qDebug() << "absolute path:" << QDir::toNativeSeparators(QDir(_filePath).absolutePath());
    qDebug() << "separators:" << QDir::toNativeSeparators(_filePath);
    workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(QDir(_filePath).absolutePath()));
    // workbook->dynamicCall("Close()");  //关闭工作簿
    excel->dynamicCall("Quit()");  //退出
}

void MainWindow::on_pushButton_clicked() {
    createExcel();
}
