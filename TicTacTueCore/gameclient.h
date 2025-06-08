#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QObject>
#include <QQmlEngine>
#include <QTcpSocket>
#include <game.h>
#include <QJsonDocument>
#include <QJsonObject>

class GameClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int ping READ ping WRITE setping NOTIFY pingChanged FINAL)
    Q_PROPERTY(QString cId READ cId WRITE setCId NOTIFY cIdChanged FINAL)
    Q_PROPERTY(QString rId READ rId WRITE setRId NOTIFY rIdChanged FINAL)
    QML_ELEMENT
public:
    static GameClient * getInstance();
    void connectToServer();
    void sendMessage(QByteArray);
    void disconnect();
    void pingServer();

    const QString IP_ADD = "localhost";
    int ping();
    void setping(int newPing);

    QString cId() const;
    void setCId(const QString &newCId);

    QString rId() const;
    void setRId(const QString &newRId);

private slots:
    void connectedToServer();
    void disconnected();
    void stateChanged(QAbstractSocket::SocketState);
    void errorOccurred(QAbstractSocket::SocketError);
    void receiveMessage();
signals:
    void onconnected();
    void ondisconnected();
    void onstateChanged(QAbstractSocket::SocketState);
    void onerrorOccurred(QAbstractSocket::SocketError);
    void messageReceived(const QJsonObject&);
    void pingChanged();
    void cIdChanged();

    void rIdChanged();

private:
    static GameClient * instance;
    QTcpSocket socket;
    int m_ping;
    bool isOn;
    bool connected;
    QByteArray socketBuffer = QByteArray();
    quint32 blockSize = 0;

    GameClient();
    QString m_cId;
    QString m_rId;
};

#endif // GAMECLIENT_H
