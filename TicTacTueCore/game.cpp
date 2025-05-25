#include "game.h"

GameState Game::getGs() const
{
    return gs;
}

Game::Game() {
    xTurn = true;
    gs = GameState::BEGIN;
    xTimer.setSingleShot(true);
    oTimer.setSingleShot(true);
};

void Game::switchPlayer() {
    xTurn = !xTurn;
}

void Game::start() {
    gs = GameState::STARTED;
}

void Game::reset()
{
    gs = GameState::BEGIN;
    board.clear();
    xTurn = true;
}

bool Game::move(int x, int y)
{
    if (!board.placeMark(x, y, xTurn)) {
        std::cout << "Invalid move! Try again.\n";
        return false;
    }
    if (gs != GameState::STARTED) {
        start();
    }
    board.display();
    checkWin();
    switchPlayer();
    return true;
}

void Game::checkWin()
{
    char winner = board.checkWinner();
    if (winner != ' ') {
        std::cout << "🎉 " << winner << " wins!\n";
        gs = xTurn ? GameState::XWON : GameState::OWON;
        return;
    } else if (board.isFull()) {
        gs = GameState::DRAW;
    }
}

bool Game::getXTurn() const
{
    return xTurn;
}
