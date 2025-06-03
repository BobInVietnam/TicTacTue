#include "gameclient.h"

GameClient * GameClient::instance = nullptr;

GameClient::GameClient()
{
    isOn = false;
    connected = false;
    connect(&socket, &QAbstractSocket::connected, this, &GameClient::connectedToServer);
    connect(&socket, &QAbstractSocket::disconnected, this, &GameClient::disconnected);
    connect(&socket, &QAbstractSocket::stateChanged, this, &GameClient::stateChanged);
    connect(&socket, &QAbstractSocket::errorOccurred, this, &GameClient::errorOccurred);

    connect(&socket, &QTcpSocket::readyRead, this, &GameClient::receiveMessage);
}

GameClient *GameClient::getInstance()
{
    if (instance == nullptr) {
        instance = new GameClient();
    }
    return instance;
}


void GameClient::connectToServer()
{
    if (!connected) {
        socket.connectToHost(QHostAddress::Any, 12345);
        connected = true;
    }
}

void GameClient::sendMessage(QString msg)
{
    qDebug() << "Message sent status: " << socket.write(msg.toUtf8());
}

void GameClient::disconnect()
{
    socket.disconnectFromHost();
    connected = false;
}


void GameClient::pingServer() {
    // something something ping ping
}

int GameClient::ping() {
    return m_ping;
}

void GameClient::setping(int newPing)
{
    if (m_ping == newPing)
        return;
    m_ping = newPing;
    emit pingChanged();
}

void GameClient::connectedToServer()
{
    qDebug() << "GC: connected to server";
}

void GameClient::disconnected()
{
    qDebug() << "GC: disconnected from server";
}

void GameClient::stateChanged(QAbstractSocket::SocketState s)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    qDebug() << "GC: state changed to " << metaEnum.valueToKey(s);
}
void GameClient::errorOccurred(QAbstractSocket::SocketError e)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    qDebug() << "GC: ERROR OCCURED: " << metaEnum.valueToKey(e);
}

void GameClient::receiveMessage()
{
    QByteArray data = socket.readAll();
    emit messageReceived(data);
}
