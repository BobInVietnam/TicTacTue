#ifndef GAME_H
#define GAME_H

#include "board.h"
#include <countdowntimer.h>
#include <QObject>
#include <QTimer>

enum GameState {
    BEGIN,
    STARTED,
    XWON,
    OWON,
    DRAW,
};

class Game : public QObject {
    Q_OBJECT
    Q_PROPERTY(GameState gs READ gs WRITE setGs NOTIFY gsChanged FINAL)
    Q_PROPERTY(bool isX READ isX WRITE setIsX NOTIFY isXChanged FINAL)
public:
    Game();
    ~Game();
    virtual void reset();
    virtual bool move(int x, int y);

    bool getXTurn() const;
    QString getxTimerString() const;
    QString getoTimerString() const;

    GameState gs() const;
    void setGs(GameState newGs);

    QString getBoardSeq() const;
    void setBoardSeq(QString seq);

    CountdownTimer *getXTimer() const;
    CountdownTimer *getOTimer() const;

    bool isX() const;
    void setIsX(bool newIsX);

private slots:
    void xTimerTimesup();
    void oTimerTimesup();
signals:
    void gsChanged();
    void boardChanged();
    void msgReceived(QString);
    void isXChanged();
    void receivedChat(const QString&);
    void gameStarted();
    void opponentLeft();

protected:
    Board board;
    bool xTurn;
    GameState m_gs;
    CountdownTimer * xTimer;
    CountdownTimer * oTimer;

    void switchPlayer();
    void checkWin();
private:
    bool m_isX;
};

#endif // GAME_H
