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

int SantaBag::genRandIndex(int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0, size - 1);
    return distrib(gen);
}

// Public functions
SantaBag::SantaBag() {

}

bool SantaBag::add(QString n) {
    Player tmp;
    tmp.setName(n);
    players.push_back(tmp);
    playerCount++;
    return true;
}

bool SantaBag::add(QString n, QString g) {
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

void SantaBag::draw() {
    bool isValid = false;
    int rerolls = 0;

    while(!isValid) {
        isValid = true;
        initPool();
        for (int i = 0; i < players.size(); i++) {
            int rd = genRandIndex(selectionPool.size());
            while((selectionPool[rd].getName() == players[i].getName() || selectionPool[rd].getName() == players[i].getPartner()) && rerolls < MAX_REROLLS) {
                rd = genRandIndex(selectionPool.size());
                rerolls++;
            }
            players[i].setAssignment(selectionPool[rd].getName(), selectionPool[rd].getGift());
            removeAt(rd);

            if (rerolls >= MAX_REROLLS) {
                isValid = false;
            }
        }
    }
}

QString SantaBag::getAssignedName(QString n) {
    for (auto& p : players) {
        if (p.getName() == n) {
            assignedName = p.getAssignedName();
        }
    }
    return assignedName;
}

QString SantaBag::getAssignedGift(QString n) {
    for (auto& p : players) {
        if (p.getName() == n) {
            assignedGift = p.getAssignedGift();
        }
    }
    return assignedGift;
}

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