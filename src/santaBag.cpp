#include "santaBag.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>    // Useful for std::shuffle(beginning index, ending index, random bit generator)
#include <QDebug>

SantaBag::SantaBag() {

}

SantaBag::SantaBag(const SantaBag& copy) {
    this->santaBagVector = copy.santaBagVector;
    std::cout << "\n[DEBUG] Copy Constructor called.\n";
}

bool SantaBag::addToBag(const std::string& name, const std::string& list/*, const int partIndex*/) {
    santaBagStruct s;
    s.playerName = name;
    s.playerList = list;
    s.relativeIndex = getSize();
    //s.hasChosen = false;
    //s.partnerIndex = partIndex;
    santaBagVector.push_back(s);
    return true;
}

bool SantaBag::findItem(int searchIndex) {
    for(int i = 0; i < getSize(); i++) {
        if(santaBagVector[i].relativeIndex == searchIndex) {
            //searchIndex = item.relativeIndex;
            std::cout << "\n[DEBUG] Player " << santaBagVector[i].playerName << " was found.\n";
            return true;
        }
    }
    return false;
}

bool SantaBag::removeTemp(int& searchIndex, int partnerIndex) {
    for(int i = 0; i < getSize(); i++) {
        if(santaBagVector[i].relativeIndex == searchIndex || (santaBagVector[i].relativeIndex == partnerIndex && partnerIndex != -1)) {
            holdingVec.push_back(santaBagVector[i]);
            std::cout << "\n[DEBUG] holdingVec has player " << santaBagVector[i].playerName << "\n";
            santaBagVector[i] = santaBagVector.back();
            santaBagVector.pop_back();
        }
    }
    return true;
}

bool SantaBag::replaceTemp() {
    if(!holdingVec.empty()) {
        for(const auto& item : holdingVec){
            santaBagVector.push_back(item);
        }
        holdingVec.clear();
        std::cout << "\n[DEBUG] holdingVec is empty again.\n";
        return true;
    }
    return false;
}

bool SantaBag::removePerm(int& searchIndex) {
    for(int i = 0; i < getSize(); i++) {
        if(santaBagVector[i].relativeIndex == searchIndex) {
            std::cout << "\n[DEBUG] player " << santaBagVector[i].playerName << " has been removed permanently from the bag\n";
            santaBagVector[i] = santaBagVector.back();
            santaBagVector.pop_back();
            return true;
        }
    }
    return false;
}

int SantaBag::randomBag() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0, getSize());
    return distrib(gen);
}

void SantaBag::randomizeBag(SantaBag& originalBag) {
    std::vector<santaBagStruct> testVec = originalBag.getVector();
    bool hasBadMatch;
    int i;
    do {
        hasBadMatch = false;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(santaBagVector.begin(), santaBagVector.end(), gen);
        i = 0;
        while(!hasBadMatch && i < getSize()) {
            int drawIndex = santaBagVector[i].relativeIndex;
            if((drawIndex == testVec[i].relativeIndex) || (testVec[i].partnerIndex != -1 && drawIndex == testVec[i].partnerIndex)){
                hasBadMatch = true;
                std::cout << "\n[DEBUG] reshuffle was needed.\n";
            }
            i++;
        }
    } while(hasBadMatch);
}

/*SantaBag SantaBag::createCopy(const SantaBag& originalBag) {
    SantaBag copyBag = originalBag;
    return copyBag;
}*/

void SantaBag::clearBag() {
    santaBagVector.clear();
}

void SantaBag::setHasChosen(int index) {
    santaBagVector[index].hasChosen = true;
}

void SantaBag::setPartnerIndex(const int playerIndex, const int partnerIndex) {
    santaBagVector[playerIndex].partnerIndex = partnerIndex;
    santaBagVector[partnerIndex].partnerIndex = playerIndex;
}

const int SantaBag::getSize() const {
    return santaBagVector.size();
}

const std::vector<santaBagStruct>& SantaBag::getVector() const {
    return santaBagVector;
}

const bool SantaBag::isEmpty() const {
    return santaBagVector.empty();
}

bool SantaBag::getHasChosen(int index) const {
    return santaBagVector[index].hasChosen;
}

const std::string SantaBag::getPlayerName(int index) const {
    return santaBagVector[index].playerName;
}

const int SantaBag::getRelativeIndex(int index) const {
    std::cout << "\n[DEBUG] the relative index retrieved is " << santaBagVector[index].relativeIndex << "\n";
    return santaBagVector[index].relativeIndex;
}

const std::string SantaBag::getPlayerList(int index) const {
    return santaBagVector[index].playerList;
}

void SantaBag::printBag() const {
    std::cout << "---------- BAG ROSTER " << getSize() << " ----------\n";
    for(const auto& item : santaBagVector) {
        std::cout << "Player Index: " << item.relativeIndex;
        std::cout << " | Partner Index: " << item.partnerIndex;
        std::cout << " | Name: " << std::setw(10) << std::left << item.playerName << "\n";
        //std::cout << " | List: " << std::setw(50) << item.playerList;
        //std::cout << " | Chosen Value: " << std::setw(10) << item.hasChosen << "\n";
    }
}

// CHANGES START HERE
void SantaBag::addPlayerEntry(QString& name, QString& list) {
    // Adds a player's entry to the vector. Name is key value in map and list is the associated value (name, list).
    playerEntry.clear();
    playerEntry[name] = list;
    playerEntryList.push_back(playerEntry);
    qDebug().noquote().nospace() << "[DEBUG] Player " << name << " was added to the vector.";
}

bool SantaBag::findPlayerEntry(QString name) {
    // Finds a player in the vector by first looping through elements in vector, then key, value pairs in mapped entries.
    for(const auto& element : playerEntryList) {
        for(const auto& [key, value] : element) {
            if(key == name) {
                qDebug().noquote().nospace() << "[DEBUG] Player " << name << " has been found.";
                qDebug().noquote().nospace() << "[DEBUG] Associated list is " << value << ".";
                return true;
            }
        }
    }
    qDebug().noquote().nospace() << "[DEBUG] Player " << name << " was not found.";
    return false;
}

std::map<QString, QString> SantaBag::removePlayerEntry(QString name) {
    // Assigns a player entry to a temporary variable, removes the player entry, then returns the temporary variable.
    std::map<QString, QString> tempMap;
    for(int i = 0; i < playerEntryList.size(); i++) {
        for(const auto& [key, value] : playerEntryList[i]) {
            if(key == name) {
                tempMap[name] = value;
                qDebug().noquote().nospace() << "[DEBUG] Player name: " << name << " & List: " << value << " will be removed.";
                playerEntryList[i] = playerEntryList.back();
                playerEntryList.pop_back();
                return tempMap;
            }
        }
    }
    qDebug().noquote().nospace() << "[DEBUG] Empty map is returned. " << name << " was not found.";
    tempMap[""] = "";
    return tempMap;
}

void SantaBag::printPlayerEntry() const {
    // Prints roster for players
    qDebug() << "\n----------BAG ROSTER----------\n";
    for(const auto& element : playerEntryList) {
        for(const auto& [key, value] : element) {
            qDebug().noquote().nospace() << "Player name: " << key << " | Player List: " << value;
        }
    }
}