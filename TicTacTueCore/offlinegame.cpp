#include "offlinegame.h"


void OfflineGame::xTimerTimesup()
{
    setGs(GameState::OWON);
}

void OfflineGame::oTimerTimesup()
{
    setGs(GameState::XWON);
}

OfflineGame::OfflineGame() {
    qDebug() << "OfflineGame created";
}

OfflineGame::~OfflineGame()
{
}

void OfflineGame::switchPlayer() {
    xTurn = !xTurn;
}

void OfflineGame::reset()
{
    setGs(GameState::BEGIN);
    board.clear();
    xTurn = true;
    xTimer->reset();
    oTimer->reset();
}

bool OfflineGame::move(int x, int y)
{
    if (gs() == GameState::BEGIN) {
        setGs(GameState::STARTED);
    } else if (gs() != GameState::STARTED) {
        return false;
    }
    if (!board.placeMark(x, y, xTurn)) {
        std::cout << "Invalid move! Try again.\n";
        return false;
    }
    if (!xTurn) {
        xTimer->start();
        oTimer->pause();
    } else {
        xTimer->pause();
        oTimer->start();
    }
    checkWin();
    switchPlayer();
    emit boardChanged();
    board.display();
    return true;
}

void OfflineGame::checkWin()
{
    char winner = board.checkWinner();
    if (winner != ' ') {
        std::cout << "🎉 " << winner << " wins!\n";
        setGs(xTurn ? GameState::XWON : GameState::OWON);
        xTimer->pause();
        oTimer->pause();
        return;
    } else if (board.isFull()) {
        setGs(GameState::DRAW);
        xTimer->pause();
        oTimer->pause();
    }
}
