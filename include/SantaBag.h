#ifndef SANTABAG_H
#define SANTABAG_H

#include <vector>
#include "Player.h"

class SantaBag {
private:
    const int MAX_ATTEMPTS = 100;

    std::vector<Player> players;
    std::vector<bool> hasDrawnFlags;
    std::vector<int> assignmentIndices;

    Player* giverPlayer;
    Player* assignedPlayer;
    QString assignedName, assignedGift;

    int playerCount;

public:
    SantaBag();
    bool addPlayer(const QString &n);
    bool updatePlayer(const QString &n, const QString &g, const QString &p);
    bool generateAssignments();
    bool drawPlayer();

    void setGiver(const QString &n);
    void setAssignedName(const QString &n);
    void setAssignedGift(const QString &g);

    void printHelp();

    bool drawnAlready();
    bool isGiftFull() const;

    QString getPlayerNameAt(int index);
    int getPlayerCount();
    QString getAssignedName() const;
    QString getAssignedGift() const;

};


#endif // SANTABAG_H
