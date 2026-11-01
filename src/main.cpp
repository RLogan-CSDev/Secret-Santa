#include "mainwindow.h"
#include "SantaBag.h"
#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;
    w.show();
    return QCoreApplication::exec();
}
