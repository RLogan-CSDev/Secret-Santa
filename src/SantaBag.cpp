#include "SantaBag.h"
#include <random>
#include <algorithm>
#include <QDebug>

// Public functions
// Core game logic
SantaBag::SantaBag() {
    playerCount = 0;
    giverPlayer = nullptr;
    assignedPlayer = nullptr;
}
bool SantaBag::addPlayer(const QString &n) {
    Player tmp(n, "");
    players.push_back(tmp);
    playerCount = players.size();
    hasDrawnFlags.push_back(false);
    assignmentIndices.push_back(-1);
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
bool SantaBag::generateAssignments() {
    for(int i = 0; i < playerCount; i++) {
        // Fill assignmentIndices parallel vector with default values.
        assignmentIndices[i] = i;
    }

    // Random generator
    std::random_device rd;
    std::mt19937 gen(rd());

    for(int i = 0; i < MAX_ATTEMPTS; i++) {
        // Try to create a valid set of assignments
        std::shuffle(assignmentIndices.begin(), assignmentIndices.end(), gen);
        bool isValid = true;
        for(int i = 0; i < playerCount; i++) {
            int giver = i;
            int recipient = assignmentIndices[i];
            bool selfDraw = giver == recipient;
            bool partnerDraw = (players[giver].getName() != players[giver].getPartner()) &&
                               (players[giver].getPartner() == players[recipient].getName());
            if(selfDraw || partnerDraw) {
                // Ensures both self and partner assignments are not possible
                isValid = false;
                break;
            }
        }
        if(isValid) {
            return true;
        }
    }
    return false;
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

    int giver = -1;
    for(int i = 0; i < playerCount; i++) {
        if(&players[i] == giverPlayer) {
            giver = i;
            break;
        }
    }

    if (giver == -1) {
        // Could not assign a giver.
        return false;
    }

    // Pulls assignment index
    int assignment = assignmentIndices[giver];
    // Pulls assigned player from parallel assignmentIndices vector
    assignedPlayer = &players[assignment];
    setAssignedName(assignedPlayer->getName());
    setAssignedGift(assignedPlayer->getGift());
    // Tracks assignments
    hasDrawnFlags[giver] = true;
    return true;
}

// Mutator functions
void SantaBag::setGiver(const QString &n) {
    for(auto& player : players) {
        if(player.getName() == n) {
            giverPlayer = &player;
        }
    }
}
void SantaBag::setAssignedName(const QString &n) {
    assignedName = n;
}
void SantaBag::setAssignedGift(const QString &g) {
    assignedGift = g;
}

// Print functions
void SantaBag::printHelp() {
    qDebug() << "[DEBUG] - Bag Contents\n";
    for (auto& p : players) {
        qDebug() << "Name: " << p.getName() << "\t Gift: " << p.getGift() << "\t Partner: " << p.getPartner() << "\n";
    }
}

// Status functions
bool SantaBag::drawnAlready() {
    for(int i = 0; i < players.size(); i++) {
        if(&players[i] == giverPlayer) {
            int giverIndex = i;
            if(hasDrawnFlags[giverIndex]) {
                return true;
            }
        }
    }
    return false;
}
bool SantaBag::isGiftFull() const {
    for(const auto& player : players) {
        if(player.getGift() == "") {
            return false;
        }
    }
    return true;
}

// Accessor functions
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
QString SantaBag::getAssignedName() const {
    return assignedName;
}
QString SantaBag::getAssignedGift() const {
    return assignedGift;
}