#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player {
private:
    QString name, gift, partner, assignedName, assignedGift;

public:
    void setName(const QString& name);
    void setGift(const QString& gift);
    void setPartner(const QString& partner);
    void setAssignment(const QString& name, const QString& gift);
    QString getName();
    QString getGift();
    QString getPartner();
    QString getAssignedName();
    QString getAssignedGift();

};

#endif // PLAYER_H
