#include "aigame.h"

void AIGame::xTimerTimesup()
{
    setGs(GameState::OWON);
}

void AIGame::oTimerTimesup()
{
    setGs(GameState::XWON);
}

bool AIGame::aiMove(QString newBoardState)
{
    if (gs() == GameState::BEGIN) {
        setGs(GameState::STARTED);
    } else if (gs() != GameState::STARTED) {
        return false;
    }
    setBoardSeq(newBoardState);
    if (!xTurn) {
        xTimer->start();
        oTimer->pause();
    } else {
        xTimer->pause();
        oTimer->start();
    }
    checkWin();
    switchPlayer();
    return true;
}

AIGame::AIGame(bool isX, int diff) {
    setIsX(isX);
    this->diff = diff;
    aiTimer.setSingleShot(true);
    QObject::connect(&ai, &TicTacTueAI::moveReady, this, &AIGame::aiMove);
    QObject::connect(&aiTimer, &QTimer::timeout, this, &AIGame::requestMove);
    qDebug() << "AIGame created";
    if (isX != xTurn) {
        aiTimer.singleShot(1000, this, &AIGame::requestMove);
    }
}

AIGame::~AIGame()
{
}

void AIGame::switchPlayer() {
    xTurn = !xTurn;
}

void AIGame::reset()
{
    aiTimer.stop();
    setGs(GameState::BEGIN);
    board.clear();
    xTurn = true;
    xTimer->reset();
    oTimer->reset();
    if (isX() != xTurn) {
        aiTimer.start(1000);
    }
}

bool AIGame::move(int x, int y)
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
    emit boardChanged();
    board.display();
    checkWin();
    switchPlayer();
    aiTimer.start(1000);
    return true;
}

void AIGame::checkWin()
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

void AIGame::requestMove()
{
    char symPlayer = isX()? 'x' : 'o';
    char symAi = isX()? 'o' : 'x';
    ai.requestMove(getBoardSeq(), symAi, symPlayer, diff);
}

