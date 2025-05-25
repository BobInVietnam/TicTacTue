#include "tictactuecore.h"

TicTacTueCore::TicTacTueCore() {
    setMsg("Core launched. Ready to go!");
}

bool TicTacTueCore::boxPressed(int index)
{
    setMsg("Block number " + std::to_string(index) + " pressed");
    if (currentGame.move(index / 3, index % 3)) {
        setXTurn();
        if (currentGame.getGs() != GameState::STARTED) {
            switch (currentGame.getGs()) {
            case XWON:
                emit gameWon("X");
                break;
            case OWON:
                emit gameWon("O");
                break;
            case DRAW:
                emit gameWon("NO ONE");
                break;
            default:
                break;
            }
        }
        return true;
    }
    return false;
}

void TicTacTueCore::reset()
{
    currentGame.reset();
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
