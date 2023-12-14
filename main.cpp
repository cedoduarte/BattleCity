#include "mainwindow.h"
#include "namekey.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    NameKey::initializeKeyMap();
    MainWindow w;
    w.showMaximized();
    return a.exec();
}
