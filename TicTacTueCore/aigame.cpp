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

AIGame::AIGame(bool isX, TicTacTueAI::Difficulty diff) {
    setIsX(isX);
    this->diff = diff;
    QObject::connect(&ai, &TicTacTueAI::moveReady, this, &AIGame::aiMove);
    qDebug() << "AIGame created";
    if (isX != xTurn) {
        QTimer::singleShot(1000, this, &AIGame::requestMove);
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
    setGs(GameState::BEGIN);
    board.clear();
    xTurn = true;
    xTimer->reset();
    oTimer->reset();
    if (isX() != xTurn) {
        QTimer::singleShot(1000, this, &AIGame::requestMove);
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
    switchPlayer();
    emit boardChanged();
    board.display();
    checkWin();
    QTimer::singleShot(1000, this, &AIGame::requestMove);
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

// bool AIGame::getXTurn() const
// {
//     return xTurn;
// }

// QString AIGame::getxTimerString() const
// {
//     return xTimer->currentTimeText();
// }

// QString AIGame::getoTimerString() const
// {
//     return oTimer->currentTimeText();
// }

// GameState AIGame::gs() const
// {
//     return m_gs;
// }

// void AIGame::setGs(GameState newGs)
// {
//     if (m_gs == newGs)
//         return;
//     m_gs = newGs;
//     emit gsChanged();
// }

// QString AIGame::getBoardSeq() const
// {
//     return QString::fromStdString(board.getSequence());
// }

// void AIGame::setBoardSeq(QString seq)
// {
//     board.setSequence(seq);
// }
