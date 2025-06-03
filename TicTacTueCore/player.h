#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player {
private:
    QString name;
    char symbol;
    int wonScore;
    int lostScore;
public:
    Player(QString n, char s);

    QString getName();
    char getSymbol();
    int getWonScore() const;
    void setWonScore(int newWonScore);
    int getLostScore() const;
    void setLostScore(int newLostScore);
};

#endif // PLAYER_H
