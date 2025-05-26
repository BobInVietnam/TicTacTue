#include "tictactuecore.h"

TicTacTueCore::TicTacTueCore() {
    QObject::connect(currentGame.getXTimer(), &CountdownTimer::currentTimeChanged, this, &TicTacTueCore::getxTimerSignal);
    QObject::connect(currentGame.getOTimer(), &CountdownTimer::currentTimeChanged, this, &TicTacTueCore::getoTimerSignal);
    QObject::connect(&currentGame, &Game::gsChanged, this, &TicTacTueCore::checkGameState);
    qDebug() << "Core generated. Ready to go.";
}

bool TicTacTueCore::getBoxPressed(int index)
{
    setMsg("Block number " + std::to_string(index) + " pressed");
    if (currentGame.move(index / 3, index % 3)) {
        setXTurn();
        return true;
    }
    return false;
}

void TicTacTueCore::checkGameState()
{
    switch (currentGame.gs()) {
    case XWON:
        emit gameWon("X");
        break;
    case OWON:
        emit gameWon("O");
        break;
    case DRAW:
        emit gameWon("NO ONE");
    default:
        break;
    }
}

void TicTacTueCore::reset()
{
    currentGame.reset();
}

void TicTacTueCore::getxTimerSignal()
{
    setXTimerString(currentGame.getxTimerString());
}

void TicTacTueCore::getoTimerSignal()
{
    setOTimerString(currentGame.getoTimerString());
}

std::string TicTacTueCore::msg() const
{
    return m_msg;
}

void TicTacTueCore::setMsg(const std::string &newMsg)
{
    if (m_msg == newMsg)
        return;
    m_msg = newMsg;
    emit msgChanged();
}

bool TicTacTueCore::xTurn() const
{
    return m_xTurn;
}

void TicTacTueCore::setXTurn()
{
    if (m_xTurn != currentGame.getXTurn()) {
        m_xTurn = currentGame.getXTurn();
        emit turnChanged();
    }
}

QString TicTacTueCore::xTimerString() const
{
    return m_xTimerString;
}

void TicTacTueCore::setXTimerString(const QString &newXTimerString)
{
    if (m_xTimerString == newXTimerString)
        return;
    m_xTimerString = newXTimerString;
    emit xTimerStringChanged();
}

QString TicTacTueCore::oTimerString() const
{
    return m_oTimerString;
}

void TicTacTueCore::setOTimerString(const QString &newOTimerString)
{
    if (m_oTimerString == newOTimerString)
        return;
    m_oTimerString = newOTimerString;
    emit oTimerStringChanged();
}
