#include "maindashboard.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (a.platformName() == "offscreen") {
        MainDashBoard mdb;
        mdb.Check();
        return 0;  // Завершаем приложение сразу после выполнения функции
    } else {
        QTranslator translator;
        const QStringList uiLanguages = QLocale::system().uiLanguages();
        for (const QString &locale : uiLanguages) {
            const QString baseName = "ONIT_" + QLocale(locale).name();
            if (translator.load(":/i18n/" + baseName)) {
                a.installTranslator(&translator);
                break;
            }
        }
        MainDashBoard w;
        w.show();
        return a.exec();  // Запускаем цикл событий только в нормальном режиме
    }
}
