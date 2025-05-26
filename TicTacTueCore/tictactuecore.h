#ifndef TICTACTUECORE_H
#define TICTACTUECORE_H

#include <game.h>
#include <QObject>
#include <QQmlEngine>
#include <player.h>

class TicTacTueCore : public QObject
{
    Q_OBJECT;
    Q_PROPERTY(std::string msg READ msg WRITE setMsg NOTIFY msgChanged FINAL);
    Q_PROPERTY(bool xTurn READ xTurn NOTIFY turnChanged FINAL);
    Q_PROPERTY(QString xTimerString READ xTimerString WRITE setXTimerString NOTIFY xTimerStringChanged FINAL)
    Q_PROPERTY(QString oTimerString READ oTimerString WRITE setOTimerString NOTIFY oTimerStringChanged FINAL)
    QML_ELEMENT;
public:
    TicTacTueCore();
    std::string msg() const;
    void setMsg(const std::string &newMsg);

    bool xTurn() const;
    void setXTurn();

    QString xTimerString() const;
    void setXTimerString(const QString &newXTimerString);

    QString oTimerString() const;
    void setOTimerString(const QString &newOTimerString);

public slots:
    bool getBoxPressed(int index);
    void checkGameState();
    void reset();
    void getxTimerSignal();
    void getoTimerSignal();
signals:
    void gameWon(const QString& side);
    void msgChanged();
    void turnChanged();

    void xTimerStringChanged();
    void oTimerStringChanged();
private:
    Game currentGame;
    Player * playerX;
    Player * playerO;
    std::string m_msg;
    bool m_xTurn;
    QString m_xTimerString;
    QString m_oTimerString;
};

#endif // TICTACTUECORE_H
