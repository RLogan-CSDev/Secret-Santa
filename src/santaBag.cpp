#include "santaBag.h"
#include <random>
#include <QDebug>


// Private functions
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

    if(drawnAlready()) {
        // Player has already drawn for their assignment.
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
                for(int i = 0; i < players.size(); i++) {
                    if(&players[i] == giverPlayer) {
                        hasDrawnFlags[i] = true;
                    }
                }
                return true;
            }
        }
        redraw++;
    }
    // All 100 redraws were used.
    return false;
}

bool SantaBag::drawnAlready() {
    for(int i = 0; i < players.size(); i++) {
        if(&players[i] == giverPlayer) {
            int giverIndex = i;
            qDebug() << "giverIndex is " << giverIndex << " and flagged as " << hasDrawnFlags[giverIndex];
            if(hasDrawnFlags[giverIndex]) {
                return true;
            }
        }
    }
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
}

QString SantaBag::getAssignedName() const {
    return assignedName;
}

QString SantaBag::getAssignedGift() const {
    return assignedGift;
}