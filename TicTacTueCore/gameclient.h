#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QObject>
#include <QQmlEngine>
#include <QTcpSocket>
#include <game.h>

class GameClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int ping READ ping WRITE setping NOTIFY pingChanged FINAL)
    QML_ELEMENT
public:
    static GameClient * getInstance();
    void connectToServer();
    void sendMessage(QString);
    void disconnect();
    void pingServer();

    const QString IP_ADD = "localhost";
    int ping();
    void setping(int newPing);

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
    void messageReceived(QString);
    void pingChanged();
private:
    static GameClient * instance;
    QTcpSocket socket;
    int m_ping;
    bool isOn;
    bool connected;

    GameClient();
};

#endif // GAMECLIENT_H
