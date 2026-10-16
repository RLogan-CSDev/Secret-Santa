#ifndef SANTABAG_H
#define SANTABAG_H

#include <vector>
#include "Player.h"

class SantaBag {
private:
    // old vars
    std::vector<Player> players;
    std::vector<Player> selectionPool;
    int playerCount;
    const int MAX_REDRAW = 100;
    QString assignedName, assignedGift;

    // new vars
    std::vector<bool> isAssignedFlags;
    std::vector<bool> hasDrawnFlags;
    int currentIndex = 0;
    Player* giverPlayer;
    Player* assignedPlayer;

    void initPool(); // untouched
    void removeAt(int pos); // untouched
    int genRandIndex();

public:
    SantaBag();

    bool add(const QString &n); // remove
    bool add(const QString &n, const QString &g); // remove
    bool add(QString n, QString partner, bool hasPartner); // remove

    void draw(); //remove
    QString getAssignedName(QString n);
    QString getAssignedGift(QString n);

    int getBagSize(); // remove
    QString getPlayerNameAt(int index); // untouched
    int getPlayerCount(); // untouched
    void printHelp(); // untouched

    bool drawPlayer();
    bool addPlayer(const QString &n);
    bool updatePlayer(const QString &n, const QString &g, const QString &p);
    void setGiver(const QString &n);
    QString getAssignedName() const;
    QString getAssignedGift() const;

};


#endif // SANTABAG_H
