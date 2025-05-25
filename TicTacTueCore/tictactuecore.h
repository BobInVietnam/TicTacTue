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
    QML_ELEMENT;
public:
    TicTacTueCore();
    std::string msg() const;
    void setMsg(const std::string &newMsg);

    bool xTurn() const;
    void setXTurn();

public slots:
    bool boxPressed(int index);
    void reset();
signals:
    void gameWon(const QString& side);
    void msgChanged();
    void turnChanged();
private:
    Game currentGame;
    Player * playerX;
    Player * playerO;
    std::string m_msg;
    bool m_xTurn;
};

#endif // TICTACTUECORE_H
