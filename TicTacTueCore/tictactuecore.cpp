#include "tictactuecore.h"

#include <aigame.h>
#include <onlinegame.h>

TicTacTueCore::TicTacTueCore() {
    setGamemode(-1);
    gameClient = GameClient::getInstance();
    currentGame = nullptr;
    setIsX(true);
    QObject::connect(this, &TicTacTueCore::gamemodeChanged, &TicTacTueCore::startGame);
    qDebug() << "Core generated. Ready to go.";
}

void TicTacTueCore::initGame()
{
    switch (gamemode()) {
    case -1:
        delete currentGame;
        currentGame = nullptr;
        break;
    case 0:
        delete currentGame;
        currentGame = new AIGame(isX(), TicTacTueAI::Difficulty::Impossible);
        break;
    case 1:
        delete currentGame;
        currentGame = new OfflineGame();
        break;
    case 2:
        delete currentGame;
        currentGame = new OnlineGame();
        break;
    default:
        qDebug() << "WTF Gamemode?";
    }
}

void TicTacTueCore::connectToServer()
{
    gameClient->connectToServer();
}

void TicTacTueCore::disconnectFromServer()
{
    gameClient->disconnect();
}

void TicTacTueCore::getBoxPressed(int index)
{
    setMsg("Block number " + std::to_string(index) + " pressed");
    if (currentGame->move(index / 3, index % 3))
        setXTurn();
}

void TicTacTueCore::checkGameState()
{
    switch (currentGame->gs()) {
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
    currentGame->reset();
}

void TicTacTueCore::getxTimerSignal()
{
    setXTimerString(currentGame->getxTimerString());
}

void TicTacTueCore::getoTimerSignal()
{
    setOTimerString(currentGame->getoTimerString());
}

void TicTacTueCore::startGame()
{
    initGame();
    if (currentGame != nullptr) {
        QObject::connect(currentGame->getXTimer(), &CountdownTimer::currentTimeChanged, this, &TicTacTueCore::getxTimerSignal);
        QObject::connect(currentGame->getOTimer(), &CountdownTimer::currentTimeChanged, this, &TicTacTueCore::getoTimerSignal);
        QObject::connect(currentGame, &Game::isXChanged, this, &TicTacTueCore::changeIsX);
        QObject::connect(currentGame, &Game::gsChanged, this, &TicTacTueCore::checkGameState);
        QObject::connect(currentGame, &Game::boardChanged, this, &TicTacTueCore::changeBoard);
        setXTimerString(currentGame->getxTimerString());
        setOTimerString(currentGame->getoTimerString());
    }
    qDebug() << "Current game mode: " << gamemode();
}

void TicTacTueCore::changeBoard()
{
    emit boardChanged();
}

void TicTacTueCore::changeIsX()
{
    setIsX(currentGame->isX());
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
    if (m_xTurn != currentGame->getXTurn()) {
        m_xTurn = currentGame->getXTurn();
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

QString TicTacTueCore::getBoardSeq()
{
    return currentGame->getBoardSeq();
}

void TicTacTueCore::setBoardSeq(QString seq)
{
    currentGame->setBoardSeq(seq);
}

PlayerInfo *TicTacTueCore::xInfo() const
{
    return m_xInfo;
}

void TicTacTueCore::setXInfo(PlayerInfo *newXInfo)
{
    if (m_xInfo == newXInfo)
        return;
    m_xInfo = newXInfo;
    emit xInfoChanged();
}

PlayerInfo *TicTacTueCore::oInfo() const
{
    return m_oInfo;
}

void TicTacTueCore::setOInfo(PlayerInfo *newOInfo)
{
    if (m_oInfo == newOInfo)
        return;
    m_oInfo = newOInfo;
    emit oInfoChanged();
}

int TicTacTueCore::gamemode() const
{
    return m_gamemode;
}

void TicTacTueCore::setGamemode(int newGamemode)
{
    if (m_gamemode == newGamemode)
        return;
    m_gamemode = newGamemode;
    emit gamemodeChanged();
}

int TicTacTueCore::ping() const
{
    return m_ping;
}

void TicTacTueCore::setPing(int newPing)
{
    if (m_ping == newPing)
        return;
    m_ping = newPing;
    emit pingChanged();
}

bool TicTacTueCore::isX() const
{
    return m_isX;
}

void TicTacTueCore::setIsX(bool newIsX)
{
    if (m_isX == newIsX)
        return;
    m_isX = newIsX;
    emit isXChanged();
}
