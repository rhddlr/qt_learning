#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QLocale>
#include "ClassWizard.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(classwizard);
    QApplication a(argc, argv);

#ifndef QT_NO_TRANSLATION
    QString translatorFileName = QLatin1String("qt_");
    translatorFileName += QLocale::system().name();
    QTranslator *translator = new QTranslator(&a);
    if(translator->load(translatorFileName,
                        QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        a.installTranslator(translator);
#endif
    ClassWizard wizard;
    wizard.show();
    return a.exec();
}
