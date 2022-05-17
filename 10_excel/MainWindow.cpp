#include "MainWindow.h"

#include <ActiveQt/QAxObject>
#include <QtWidgets>

#include "ui_MainWindow.h"
enum Alignment {
    xlCenter = -4108,
    xlRight = -4152,
    xlTop = -4160,
    xlBottom = -4107,
    xlLeft = -4131,
};
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    _filePath = QDir::toNativeSeparators(QFileInfo(QStringLiteral("./1.xlsx")).absoluteFilePath());
    qDebug() << "init:" << QDir::toNativeSeparators(_filePath);
}

MainWindow::~MainWindow() {
    delete ui;
    _execl->dynamicCall("Quit()");  //退出
    _execl->deleteLater();
    _execl = Q_NULLPTR;
}

void MainWindow::createExcel() {
    QList<int> timecosts;
    QTime timer;
    unsigned int cost = 0;
    timer.start();

    if (!_execl) {
        qDebug() << "create excel";
        _execl = new QAxObject("Excel.Application", this);
        timecosts.append(timer.elapsed() - cost);
        cost = timer.elapsed();
        //_execl->dynamicCall("SetVisible(bool Visible)", false);  //是否可视化excel
        _execl->dynamicCall("SetUserControl(bool UserControl)", false);  //是否用户可操作
        _execl->setProperty("DisplayAlerts", false);  //是否弹出警告窗口
        timecosts.append(timer.elapsed() - cost);
        cost = timer.elapsed();

        workbooks = _execl->querySubObject("WorkBooks");  //获取工作簿集合
    }
    QAxObject* workbook;
    if (QFileInfo::exists(_filePath)) {
        workbook = workbooks->querySubObject("Open(const QString&)", _filePath);
    } else {
        workbook = workbooks->querySubObject("Add()");  //新建一个工作簿
    }
    // QAxObject* workbook = _excel->querySubObject("ActiveWorkBook");  //获取当前工作簿
    timecosts.append(timer.elapsed() - cost);
    cost = timer.elapsed();

    QAxObject* sheets = workbook->querySubObject("Sheets");  //获取工作表格集合
    timecosts.append(timer.elapsed() - cost);
    cost = timer.elapsed();

    int sheetCount = sheets->dynamicCall("Count()").toInt();
    qDebug() << "sheet count:" << sheetCount;
    for (size_t i = 1; i <= 3; ++i) {
        QAxObject* sheet = Q_NULLPTR;
        if (sheetCount >= i)
            sheet = sheets->querySubObject("Item(int)", i);  //获取当前工作表格1,sheet1
        else {
            int last = sheets->dynamicCall("Count()").toInt();
            QAxObject* pLastSheet = sheets->querySubObject("Item(int)", last);
            if (pLastSheet)
                sheet = sheets->querySubObject("Add(QVariant)", pLastSheet->asVariant());
            else
                sheet = sheets->querySubObject("Add()");
            sheet->setProperty("Name", QString("p%1").arg(i));  //修改sheet名称
        }
        timecosts.append(timer.elapsed() - cost);
        cost = timer.elapsed();
        //创建表头
        static unsigned int charnum = 65;
        QChar a = charnum;
        QChar b = ++charnum;
        ++charnum;
        const QVariant var = QString("%011:%022").arg(a).arg(b);
        double num = 23.123456789 + charnum;

        const QString value_num = QString::number(num, 'f', 12);
        qDebug() << value_num;
        QAxObject* range = sheet->querySubObject("Range(const QString&)", var);
        range->setProperty("MergeCells", true);
        range->setProperty("NumberFormatLocal", "@");
        range->setProperty("Value", value_num);
        range->setProperty("HorizontalAlignment", xlCenter);
        timecosts.append(timer.elapsed() - cost);
        cost = timer.elapsed();
        QAxObject* font = range->querySubObject("Font");  //获取单元格字体
        font->setProperty("Name", QStringLiteral("微软雅黑"));  //设置单元格字体
        font->setProperty("Bold", true);  //设置单元格字体加粗
        font->setProperty("Size", 12);  //设置单元格字体大小
        font->setProperty("Italic", false);  //设置单元格字体斜体
        font->setProperty("Underline", false);  //设置单元格下划线
        font->setProperty("Color", QColor(0, 0, 0));  //设置单元格字体颜色（红色）
        timecosts.append(timer.elapsed() - cost);
        cost = timer.elapsed();
    }

    workbook->dynamicCall("SaveAs(const QString&)", _filePath);
    timecosts.append(timer.elapsed() - cost);

    // cost = timer.elapsed();
    workbook->dynamicCall("Close()");  //关闭工作簿

    //_execl->dynamicCall("Quit()");  //退出
    // timecosts.append(timer.elapsed() - cost);

    foreach (const auto& time, timecosts) {
        qDebug() << "hs:" << time << "(ms)";
    }
    qDebug() << "--";
}

void MainWindow::on_pushButton_clicked() { createExcel_test(); }

void MainWindow::createExcel_test() {
    if (!_execl) {
        qDebug() << "create excel";
        _execl = new QAxObject("Excel.Application", this);
        _execl->dynamicCall("SetVisible(bool Visible)", false);  //是否可视化excel
        _execl->dynamicCall("SetUserControl(bool UserControl)", false);  //是否用户可操作
        _execl->setProperty("DisplayAlerts", false);  //是否弹出警告窗口

        workbooks = _execl->querySubObject("WorkBooks");  //获取工作簿集合
    }

    QAxObject* workbook;
    if (QFileInfo::exists(_filePath)) {
        workbook = workbooks->querySubObject("Open(const QString&)", _filePath);
    } else {
        workbook = workbooks->querySubObject("Add()");  //新建一个工作簿
    }

    QAxObject* sheets = workbook->querySubObject("Sheets");  //获取工作表格集合
    QAxObject* sheet = sheets->querySubObject("Item(int)", 1);  //获取当前工作表格1,sheet1

    QStringList value_num{"111.150000", "222.330000", "333.666600"};
    static int clickCount = 1;
    const QVariant var = QString("A%1:C%2").arg(clickCount).arg(clickCount);
    ++clickCount;
    QAxObject* range = sheet->querySubObject("Range(const QString&)", var);
    range->setProperty("NumberFormatLocal", "@");
    range->setProperty("HorizontalAlignment", xlCenter);
    range->setProperty("Value", value_num);

    workbook->dynamicCall("SaveAs(const QString&)", _filePath);
    workbook->dynamicCall("Close()");  //关闭工作簿
    workbook = Q_NULLPTR;
    delete range;
    delete sheet;
    delete sheets;
    //    _execl->dynamicCall("Quit()");  //退出
    //    _execl->deleteLater();
    //    _execl = Q_NULLPTR;
    qDebug() << "--end--";
}
