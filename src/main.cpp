#include "mainwindow.h"
#include "santaBag.h"
#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
    SantaBag bag;
    bag.addToBag("Robert", "Chess set, games";
    bag.addToBag("Nancy", "clothes, chocolate";
    bag.addToBag("Jack", "car, clothes, games";
    bag.addToBag("Matthew", "car, clothes, games";
    bag.addToBag("Shelby", "car, clothes, games";
    bag.addToBag("Mom", "car, clothes, games");
    bag.addToBag("Kyle", "tools, guns");

    SantaBag copyBag = bag.createCopy(bag);
    copyBag.randomizeBag(bag);
    std::cout << "Main bag\n";
    bag.printBag();
    std::cout << "Randomized bag\n";
    copyBag.printBag();
    */


    MainWindow w;
    w.show();
    return QCoreApplication::exec();
}
