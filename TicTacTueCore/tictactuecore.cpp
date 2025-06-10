#include "tictactuecore.h"

#include <aigame.h>
#include <onlinegame.h>

TicTacTueCore::TicTacTueCore() {
    setGamemode(-1);
    gameClient = GameClient::getInstance();
    currentGame = nullptr;
    setIsX(true);
    setXTurn(true);
    QObject::connect(this, &TicTacTueCore::gamemodeChanged, &TicTacTueCore::startGame);
    QObject::connect(gameClient, &GameClient::onconnected, this, &TicTacTueCore::connectToServerSuccess);
    QObject::connect(gameClient, &GameClient::ondisconnected, this, &TicTacTueCore::disconnectFromServerSuccess);
    QObject::connect(gameClient, &GameClient::messageReceived, this, &TicTacTueCore::receiveServerMessage);
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
        currentGame = new AIGame(isX(), aiDiff());
        setXTurn(true);
        break;
    case 1:
        delete currentGame;
        currentGame = new OfflineGame();
        setIsX(true);
        setXTurn(true);
        break;
    case 2:
        delete currentGame;
        currentGame = new OnlineGame();
        setXTurn(false);
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

void TicTacTueCore::setUsername(const QString &usrname)
{
    QJsonObject json;

    json["CID"] = gameClient->cId();
    json["INGAME"] = false;
    json["CMD"] = "USRNAME";
    json["USRNAME"] = usrname;
    gameClient->sendMessage(QJsonDocument(json).toJson(QJsonDocument::Compact));
}

void TicTacTueCore::createRoom(const QString &rid)
{
    QJsonObject json;

    json["CID"] = gameClient->cId();
    json["INGAME"] = false;
    json["CMD"] = "CR";
    json["RID"] = rid;
    gameClient->sendMessage(QJsonDocument(json).toJson(QJsonDocument::Compact));
}


void TicTacTueCore::joinRoom(const QString &rid)
{
    QJsonObject json;

    json["CID"] = gameClient->cId();
    json["INGAME"] = false;
    json["CMD"] = "JR";
    json["RID"] = rid;
    gameClient->sendMessage(QJsonDocument(json).toJson(QJsonDocument::Compact));
}

void TicTacTueCore::leaveRoom()
{
    QJsonObject json;

    json["CID"] = gameClient->cId();
    json["INGAME"] = false;
    json["CMD"] = "LR";
    json["RID"] = gameClient->rId();
    gameClient->sendMessage(QJsonDocument(json).toJson(QJsonDocument::Compact));
}

void TicTacTueCore::sendMessage(const QString & msg)
{
    QJsonObject json;

    json["CID"] = gameClient->cId();
    json["RID"] = gameClient->rId();
    json["INGAME"] = true;
    json["CMD"] = "CHAT";
    json["MSG"] = msg;
    gameClient->sendMessage(QJsonDocument(json).toJson(QJsonDocument::Compact));
}

void TicTacTueCore::getBoxPressed(int index)
{
    setMsg("Block number " + std::to_string(index) + " pressed");
    if (xTurn() == isX()) {
        currentGame->move(index / 3, index % 3);
        if (gamemode() == 1) setIsX(!isX());
    } else {
        qDebug() << "Not your turn";
    }
}

void TicTacTueCore::checkGameState()
{
    switch (currentGame->gs()) {
    case XWON:
        setXTurn(!isX());
        emit gameWon("X");
        break;
    case OWON:
        setXTurn(!isX());
        emit gameWon("O");
        break;
    case DRAW:
        setXTurn(!isX());
        emit gameWon("NO ONE");
    default:
        break;
    }
}

void TicTacTueCore::reset()
{
    currentGame->reset();
    setXTurn(true);
    if (gamemode() == 1) setIsX(true);
    if (gamemode() == 2) setXTurn(false);
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
        QObject::connect(currentGame, &Game::gsChanged, this, &TicTacTueCore::checkGameState);
        QObject::connect(currentGame, &Game::boardChanged, this, &TicTacTueCore::changeBoard);
        QObject::connect(currentGame, &Game::receivedChat, this, &TicTacTueCore::onChatReceived);
        QObject::connect(currentGame, &Game::gameStarted, this, &TicTacTueCore::onGameStarted);
        QObject::connect(currentGame, &Game::opponentLeft, this, &TicTacTueCore::onOpponentLeft);
        setXTimerString(currentGame->getxTimerString());
        setOTimerString(currentGame->getoTimerString());
    }
    qDebug() << "Current game mode: " << gamemode();
}

void TicTacTueCore::changeBoard()
{
    setXTurn(!xTurn());
    emit boardChanged();
}

void TicTacTueCore::connectToServerSuccess()
{
    emit serverConnected();
}

void TicTacTueCore::disconnectFromServerSuccess()
{
    emit serverDisconnected();
}

void TicTacTueCore::receiveServerMessage(const QJsonObject &json)
{
    if (json.value("CMD").toString() == "PONG") {
        qint64 clientReceiveTime = QDateTime::currentMSecsSinceEpoch();
        qint64 ping = clientReceiveTime - json.value("S_SENT").toInteger();
        gameClient->notifyPongTimer();
        setPing(ping);
        return;
    }
    if (!json.value("INGAME").toBool()) {
        QString cmd = json.value("CMD").toString("NULL");
        if (cmd == "CR_OK") {
            gameClient->setRId(json.value("RID").toString());
            emit roomCreated();
        } else if (cmd == "JR_OK") {
            gameClient->setRId(json.value("RID").toString());
            emit roomJoined();
        } else if (cmd == "US_OK") {
            emit usernameSet();
        } else if (cmd == "ERR") {
            emit roomErrorOccured(json.value("MSG").toString("Error"));
        } else {
            qWarning() << "GM: invalid message received??";
        }
    }
}

void TicTacTueCore::onGameStarted(bool isX)
{
    setIsX(isX);
    emit gameStarted();
}

void TicTacTueCore::onChatReceived(const QString& msg)
{
    emit chatReceived(msg);
}

void TicTacTueCore::onOpponentLeft()
{
    emit opponentLeft();
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

int TicTacTueCore::aiDiff() const
{
    return m_aiDiff;
}

void TicTacTueCore::setAiDiff(int newAiDiff)
{
    m_aiDiff = newAiDiff;
}

bool TicTacTueCore::xTurn() const
{
    return m_xTurn;
}

void TicTacTueCore::setXTurn(bool newXTurn)
{
    if (m_xTurn == newXTurn)
        return;
    m_xTurn = newXTurn;
    emit xTurnChanged();
}
