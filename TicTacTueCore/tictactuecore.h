#ifndef TICTACTUECORE_H
#define TICTACTUECORE_H

#include <game.h>
#include <QObject>
#include <QQmlEngine>
#include <player.h>
#include <gameclient.h>
#include <offlinegame.h>

struct PlayerInfo {
    int won;
    int lost;
    QString name;
    int currentWin = 0;

    PlayerInfo(Player p) {
        name = p.getName();
        won = p.getWonScore();
        lost = p.getLostScore();
    }
};

class TicTacTueCore : public QObject
{
    Q_OBJECT;
    Q_PROPERTY(std::string msg READ msg WRITE setMsg NOTIFY msgChanged FINAL);
    Q_PROPERTY(bool xTurn READ xTurn NOTIFY turnChanged FINAL);
    Q_PROPERTY(QString xTimerString READ xTimerString WRITE setXTimerString NOTIFY xTimerStringChanged FINAL)
    Q_PROPERTY(QString oTimerString READ oTimerString WRITE setOTimerString NOTIFY oTimerStringChanged FINAL)
    Q_PROPERTY(PlayerInfo * xInfo READ xInfo WRITE setXInfo NOTIFY xInfoChanged FINAL)
    Q_PROPERTY(PlayerInfo * oInfo READ oInfo WRITE setOInfo NOTIFY oInfoChanged FINAL)
    Q_PROPERTY(int gamemode READ gamemode WRITE setGamemode NOTIFY gamemodeChanged)
    Q_PROPERTY(int ping READ ping WRITE setPing NOTIFY pingChanged FINAL)
    QML_ELEMENT;
public:

    TicTacTueCore();
    void initGame();
    Q_INVOKABLE void connectToServer();
    Q_INVOKABLE void disconnectFromServer();

    std::string msg() const;
    void setMsg(const std::string &newMsg);

    bool xTurn() const;
    void setXTurn();

    QString xTimerString() const;
    void setXTimerString(const QString &newXTimerString);

    QString oTimerString() const;
    void setOTimerString(const QString &newOTimerString);

    Q_INVOKABLE QString getBoardSeq();
    void setBoardSeq(QString seq);
    PlayerInfo *xInfo() const;
    void setXInfo(PlayerInfo *newXInfo);

    PlayerInfo *oInfo() const;
    void setOInfo(PlayerInfo *newOInfo);

    int gamemode() const;
    void setGamemode(int newGamemode);

    int ping() const;
    void setPing(int newPing);


public slots:
    bool getBoxPressed(int index);
    void checkGameState();
    void reset();
    void getxTimerSignal();
    void getoTimerSignal();
    void startGame();
    void changeBoard();

signals:
    void gameWon(const QString& side);
    void msgChanged();
    void turnChanged();
    void xTimerStringChanged();
    void oTimerStringChanged();
    void xInfoChanged();
    void oInfoChanged();
    void gamemodeChanged();
    void pingChanged();
    void boardChanged();

private:
    Game * currentGame;
    GameClient * gameClient;

    std::string m_msg;
    bool m_xTurn;
    QString m_xTimerString;
    QString m_oTimerString;

    PlayerInfo *m_xInfo = nullptr;
    PlayerInfo *m_oInfo = nullptr;
    int m_gamemode;
    int m_ping;
};

#endif // TICTACTUECORE_H
