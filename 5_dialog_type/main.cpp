#include "MyWidget.h"
#include <QApplication>
/**
 * 此程序内容:
 * 1. 模态和非模态窗口的创建和转换
 * 2. 信号和槽的关联方法,自动关联机制
 * 3. 自定义对话框,添加2个按钮"进入主界面""退出程序"
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget w;
    w.show();

    return a.exec();
}
