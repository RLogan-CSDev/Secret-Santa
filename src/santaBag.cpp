#include "santaBag.h"
#include <random>
#include <QDebug>

// Private functions
void SantaBag::initPool() {
    selectionPool = players;
}

void SantaBag::removeAt(int pos) {
    if(pos >= 0 && pos < selectionPool.size()) {
        selectionPool.erase(selectionPool.begin() + pos);
        playerCount--;      // need to adjust here
    }
}

int SantaBag::genRandIndex() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0, players.size() - 1);
    return distrib(gen);
}

// Public functions
SantaBag::SantaBag() {
    playerCount = 0;
    giverPlayer = nullptr;
    assignedPlayer = nullptr;
}

bool SantaBag::add(const QString &n) {
    Player tmp(n, n);
    tmp.setName(n);
    players.push_back(tmp);
    playerCount++;
    return true;
}

bool SantaBag::add(const QString &n, const QString &g) {
    Player tmp(n, g);
    players.push_back(tmp);

    for (auto& p : players) {
        if (p.getName() == n){
            p.setGift(g);
            return true;
        }
    }
    return false;
}

bool SantaBag::add(QString n, QString partner, bool hasPartner) {
    if (hasPartner) {
        for (auto& p : players) {
            if (p.getName() == n) {
                p.setPartner(partner);
                return true;
            }
        }
    }
    return false;
}

// void SantaBag::draw() {
//     bool isValid = false;
//     int redraw = 0;

//     while (redraw <= MAX_REDRAW && !isValid) {
//         int rd = genRandIndex();
//         for (int i = 0; i < players.size(); i++) {

//         }
//     }

//     while(!isValid) {
//         isValid = true;
//         initPool();
//         for (int i = 0; i < players.size(); i++) {
//             int rd = genRandIndex();
//             bool selfDraw = selectionPool[rd].getName() == players[i].getName();
//             bool partnerDraw = selectionPool[rd].getName() == players[i].getPartner();
//             while((selfDraw || partnerDraw) && redraw < MAX_REDRAW) {
//                 rd = genRandIndex();
//                 redraw++;
//             }
//             players[i].setAssignment(selectionPool[rd].getName(), selectionPool[rd].getGift());
//             removeAt(rd);

//             if (redraw >= MAX_REDRAW) {
//                 isValid = false;
//             }
//         }
//         redraw = 0;
//     }
// }

// QString SantaBag::getAssignedName(QString n) {
//     for (auto& p : players) {
//         if (p.getName() == n) {
//             assignedName = p.getAssignedName();
//         }
//     }
//     return assignedName;
// }

// QString SantaBag::getAssignedGift(QString n) {
//     for (auto& p : players) {
//         if (p.getName() == n) {
//             assignedGift = p.getAssignedGift();
//         }
//     }
//     return assignedGift;
// }

int SantaBag::getBagSize() {
    return players.size();
}

QString SantaBag::getPlayerNameAt(int index) {
    for (int i = 0; i < players.size(); i++) {
        if (i == index) {
            return players[i].getName();
        }
    }
    return "";
}

int SantaBag::getPlayerCount() {
    if(playerCount < 0) {
        playerCount = 0;
    }
    return playerCount;
}

void SantaBag::printHelp() {
    qDebug() << "[DEBUG] - Bag Contents\n";
    for (auto& p : players) {
        qDebug() << "Name: " << p.getName() << "\t Gift: " << p.getGift() << "\t Partner: " << p.getPartner() << "\n";
    }
}

bool SantaBag::drawPlayer() {
    if(giverPlayer == nullptr) {
        // No one was selected.
        return false;
    }

    int giverIndex = -1;
    for(int i = 0; i < players.size(); i++) {
        if(&players[i] == giverPlayer) {
            giverIndex = i;
            qDebug() << "Giver Index is: " << giverIndex;
        }
    }

    if(giverIndex != -1 && hasDrawnFlags[giverIndex]) {
        // Person already gave - prevents multiple clicks on the button.
        return false;
    }

    int redraw = 0;
    while(redraw <= MAX_REDRAW) {
        int rd = genRandIndex();
        if(rd < playerCount) {
            assignedPlayer = &players.at(rd);
            bool selfDraw = giverPlayer->getName() == assignedPlayer->getName();
            bool partnerDraw = giverPlayer->getPartner() == assignedPlayer->getName();

            if((!selfDraw && !partnerDraw) && !isAssignedFlags[rd]) {
                assignedName = assignedPlayer->getName();
                assignedGift = assignedPlayer->getGift();
                isAssignedFlags[rd] = true;
                return true;
            }
        }
        redraw++;
    }
    // All 100 redraws were used.
    return false;
}

bool SantaBag::addPlayer(const QString &n) {
    Player tmp(n, "");
    players.push_back(tmp);
    playerCount = players.size();
    isAssignedFlags.push_back(false);
    hasDrawnFlags.push_back(false);
    return true;
}

bool SantaBag::updatePlayer(const QString &n, const QString &g, const QString &p) {
    for(auto& player : players) {
        if(player.getName() == n) {
            player.setGift(g);
            player.setPartner(p);
            return true;
        }
    }
    return false;
}

void SantaBag::setGiver(const QString &n) {
    for(auto& player : players) {
        if(player.getName() == n) {
            giverPlayer = &player;
        }
    }
    giverPlayer = nullptr;
}

QString SantaBag::getAssignedName() const {
    return assignedName;
}

QString SantaBag::getAssignedGift() const {
    return assignedGift;
}