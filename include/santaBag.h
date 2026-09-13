#ifndef SANTABAG_H
#define SANTABAG_H

#include <vector>
#include <string>
#include <QString>
#include <map>

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
    bool removeTemp(int& searchIndex, int partnerIndex = -1);
    bool replaceTemp();
    bool removePerm(int& searchIndex);
    int randomBag();
    void randomizeBag(SantaBag& originalBag);
    //SantaBag createCopy(const SantaBag& originalBag);
    void clearBag();
    void setHasChosen(int index);
    void setPartnerIndex(const int playerIndex, const int partnerIndex);

    const int getSize() const;
    const std::vector<santaBagStruct>& getVector() const;
    const bool isEmpty() const;
    bool getHasChosen(int index) const;
    const std::string getPlayerName(int index) const;
    const int getRelativeIndex(int index) const;
    const std::string getPlayerList(int index) const;

    void printBag() const;      // Helper function

    // CHANGES START HERE
    void addPlayerEntry(QString& name, QString& list);
    bool findPlayerEntry(QString name);
    std::map<QString, QString> removePlayerEntry(QString name);
    void printPlayerEntry() const;

private:
    std::vector<santaBagStruct> santaBagVector;
    std::vector<santaBagStruct> holdingVec;

    // CHANGES START HERE
    std::map<QString, QString> playerEntry;
    std::vector<std::map<QString, QString>> playerEntryList;

};


#endif // SANTABAG_H
