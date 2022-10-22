#include "Widget.h"
#include <QObject>
#include <QApplication>
#include "TimedMessageBox.h"
#include <QColorDialog>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    Widget aa;
    aa.show();
    //    QColorDialog dd;
    //    dd.setOption(QColorDialog::ShowAlphaChannel);
    //    dd.show();
    return QApplication::exec();
}
