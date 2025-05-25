#include "../../test-site/tic-tac-toe/TicTacToeCore/player.h"

Player::Player(std::string n, char s) : name(n), symbol(s) {}

char Player::getSymbol() { return symbol; }

std::string Player::getName() { return name; }


