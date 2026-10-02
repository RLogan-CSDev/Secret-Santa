#ifndef SANTABAG_H
#define SANTABAG_H

#include <vector>
#include "Player.h"

class SantaBag {
private:
    std::vector<Player> players;
    std::vector<Player> selectionPool;
    int playerCount = 0;
    const int MAX_REROLLS = 100;
    QString assignedName, assignedGift;

    void initPool();
    void removeAt(int pos);
    int genRandIndex(int size);

public:
    SantaBag();

    bool add(QString n);
    bool add(QString n, QString g);
    bool add(QString n, QString partner, bool hasPartner);

    void draw();
    QString getAssignedName(QString n);
    QString getAssignedGift(QString n);

    int getBagSize();
    QString getPlayerNameAt(int index);
    int getPlayerCount();
    void printHelp();

};


#endif // SANTABAG_H
