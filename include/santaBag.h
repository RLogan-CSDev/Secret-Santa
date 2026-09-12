#ifndef SANTABAG_H
#define SANTABAG_H

#include <vector>
#include <string>

struct santaBagStruct {
    std::string playerName;
    std::string playerList;
    int relativeIndex;
    bool hasChosen = false;
    int partnerIndex = -1;
};

class SantaBag {
public:
    SantaBag();
    SantaBag(const SantaBag& copy);

    bool addToBag(const std::string& name, const std::string& list/*, const int partIndex*/);
    bool findItem(int searchIndex);
    bool removeTemp(int& searchIndex, int& partnerIndex);
    bool replaceTemp();
    bool removePerm(int& searchIndex);
    void randomizeBag(SantaBag& originalBag);
    SantaBag createCopy(const SantaBag& originalBag);
    void clearBag();
    void setHasChosen(int index);
    void setPartnerIndex(const int playerIndex, const int partnerIndex);


    const int getSize() const;
    const std::vector<santaBagStruct>& getVector() const;
    const bool isEmpty() const;
    bool getHasChosen(int index) const;

    void printBag() const;      // Helper function

private:
    std::vector<santaBagStruct> santaBagVector;
    std::vector<santaBagStruct> holdingVec;
};


#endif // SANTABAG_H
