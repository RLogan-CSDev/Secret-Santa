#include "Player.h"

Player::Player(const QString &n, const QString &g) {
    // Default partner is player's name.
    this->name = n;
    this->gift = g;
    this->partner = n;
}

void Player::setName(const QString& name) {
    this->name = name;
}

void Player::setGift(const QString& gift) {
    this->gift = gift;
}

void Player::setPartner(const QString& partner) {
    this->partner = partner;
}

QString Player::getName() const { return name; }

QString Player::getGift() const { return gift; }

QString Player::getPartner() const { return partner; }
