#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string name;
    char symbol;
public:
    Player(std::string n, char s);

    std::string getName();
    char getSymbol();
};

#endif // PLAYER_H
