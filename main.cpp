#include "MainWindow.h"

#include <iostream>

#include <QApplication>
#include <QFile>
#include <QXmlStreamReader>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
