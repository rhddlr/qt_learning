#include "LayoutTest.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LayoutTest w;
    w.show();
    return a.exec();
}
