#include "windows/MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QCoreApplication::setOrganizationName("Spell");
	QCoreApplication::setOrganizationDomain("lolwtf.nl");
	QCoreApplication::setApplicationName("SpellTracker");
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}
