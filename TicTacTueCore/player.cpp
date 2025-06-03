#include "player.h"

Player::Player(QString n, char s) : name(n), symbol(s) {}

int Player::getWonScore() const
{
    return wonScore;
}

void Player::setWonScore(int newWonScore)
{
    wonScore = newWonScore;
}

int Player::getLostScore() const
{
    return lostScore;
}

void Player::setLostScore(int newLostScore)
{
    lostScore = newLostScore;
}

char Player::getSymbol() { return symbol; }

QString Player::getName() { return name; }


