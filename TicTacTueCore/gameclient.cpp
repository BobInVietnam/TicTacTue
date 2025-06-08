#include "gameclient.h"

GameClient * GameClient::instance = nullptr;

GameClient::GameClient()
{
    setCId("ABC123");
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
    }
}

void GameClient::sendMessage(QByteArray jsonData)
{
    if (socket.state() != QAbstractSocket::ConnectedState) {
        qWarning() << "Attempted to send to disconnected or invalid socket.";
        return;
    }

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_8);

    // out << (quint32)0;
    out << jsonData;
    // out.device()->seek(0);
    // out << (quint32)(block.size() - sizeof(quint32));

    socket.write(block);
    socket.flush(); // Ensure data is sent immediately
    qDebug() << "Client sent: " << jsonData;
}

void GameClient::disconnect()
{
    socket.disconnectFromHost();
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
    connected = true;
    emit onconnected();
}

void GameClient::disconnected()
{
    qDebug() << "GC: disconnected from server";
    connected = false;
    emit ondisconnected();
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

    while (socket.bytesAvailable() > 0) {
        socketBuffer.append(socket.readAll());

        while (socketBuffer.size() > 0) {
            // Stage 1: Read block size
            if (blockSize == 0 && socketBuffer.size() >= (qint32)sizeof(quint32)) {
                QDataStream in(&socketBuffer, QIODevice::ReadOnly);
                in.setVersion(QDataStream::Qt_6_8); // MUST match client's QDataStream version

                in >> blockSize;
                socketBuffer = socketBuffer.mid(sizeof(quint32)); // Remove size prefix from buffer
            }

            // Stage 2: Read actual block data
            if (blockSize > 0 && socketBuffer.size() >= (qint32)blockSize) {
                QByteArray jsonData = socketBuffer.mid(0, blockSize);
                socketBuffer = socketBuffer.mid(blockSize); // Remove processed data

                QJsonParseError parseError;
                QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);

                if (doc.isNull() || !doc.isObject()) {
                    // sendFramedJsonMessage(socket, QJsonDocument(QJsonObject{{"type", "error"}, {"message", "Invalid JSON format: " + parseError.errorString()}}).toJson(QJsonDocument::Compact));
                    qWarning() << "Received invalid JSON from" << socket.peerAddress().toString() << ":" << parseError.errorString();
                } else {
                    qDebug() << "GM: Received JSON from server: " << doc;
                    QJsonObject json = doc.object();
                    if (json.value("CMD").toString() == "A_ID") {
                        setCId(json.value("CID").toString());
                        qDebug() << "New ID set: " << cId();
                    } else if (json.value("CID").toString() != cId()) {
                        qWarning() << "GM: message not for this user!";
                    } else emit messageReceived(json);
                }
                blockSize = 0; // Reset for next message
            } else {
                // Not enough data for the full message yet, break and wait for more
                break;
            }
        }
    }
}

QString GameClient::cId() const
{
    return m_cId;
}

void GameClient::setCId(const QString &newCId)
{
    if (m_cId == newCId)
        return;
    m_cId = newCId;
    emit cIdChanged();
}

QString GameClient::rId() const
{
    return m_rId;
}

void GameClient::setRId(const QString &newRId)
{
    if (m_rId == newRId)
        return;
    m_rId = newRId;
    emit rIdChanged();
}
