#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player {
private:
    QString name, gift, partner;

public:
    Player(const QString &n, const QString &g);
    void setName(const QString& name);
    void setGift(const QString& gift);
    void setPartner(const QString& partner);
    QString getName() const;
    QString getGift() const;
    QString getPartner() const;

};

#endif // PLAYER_H
