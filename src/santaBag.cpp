#include "santaBag.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>    // Useful for std::shuffle(beginning index, ending index, random bit generator)

SantaBag::SantaBag() {

}

SantaBag::SantaBag(const SantaBag& copy) {
    this->santaBagVector = copy.santaBagVector;
    std::cout << "\n[DEBUG] Copy Constructor called.\n";
}

void SantaBag::addToBag(const std::string& name, const std::string& list, const int partIndex) {
    santaBagStruct s;
    s.playerName = name;
    s.playerList = list;
    s.relativeIndex = getSize();
    s.hasChosen = false;
    s.partnerIndex = partIndex;
    santaBagVector.push_back(s);
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

SantaBag SantaBag::createCopy(const SantaBag& originalBag) {
    SantaBag copyBag = originalBag;
    return copyBag;
}

void SantaBag::clearBag() {
    santaBagVector.clear();
}

void SantaBag::setHasChosen(int index) {
    santaBagVector[index].hasChosen = true;
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

void SantaBag::printBag() const {
    for(const auto& item : santaBagVector) {
        std::cout << "Player Index: " << item.relativeIndex;
        std::cout << " | Name: " << std::setw(10) << std::left << item.playerName;
        std::cout << " | List: " << std::setw(50) << item.playerList;
        std::cout << " | Chosen Value: " << std::setw(10) << item.hasChosen << "\n";
    }
}