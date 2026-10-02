#include "Player.h"

void Player::setName(const QString& name) {
    this->name = name;
}

void Player::setGift(const QString& gift) {
    this->gift = gift;
}

void Player::setPartner(const QString& partner) {
    this->partner = partner;
}

void Player::setAssignment(const QString& name, const QString& gift) {
    assignedName = name;
    assignedGift = gift;
}

QString Player::getName() { return name; }

QString Player::getGift() { return gift; }

QString Player::getPartner() { return partner; }

QString Player::getAssignedName() { return assignedName; }

QString Player::getAssignedGift() { return assignedGift; }