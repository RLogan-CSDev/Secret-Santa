#include "mainwindow.h"
#include "santaBag.h"
#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SantaBag bag;
    bag.addToBag("Robert", "Chess set, games", 1);
    bag.addToBag("Nancy", "clothes, chocolate", 0);
    bag.addToBag("Jack", "car, clothes, games", -1);
    bag.addToBag("Matthew", "car, clothes, games", -1);
    bag.addToBag("Shelby", "car, clothes, games", 6);
    bag.addToBag("Mom", "car, clothes, games", -1);
    bag.addToBag("Kyle", "tools, guns", 4);

    SantaBag copyBag = bag.createCopy(bag);
    copyBag.randomizeBag(bag);
    std::cout << "Main bag\n";
    bag.printBag();
    std::cout << "Randomized bag\n";
    copyBag.printBag();



    MainWindow w;
    w.show();
    return QCoreApplication::exec();
}
