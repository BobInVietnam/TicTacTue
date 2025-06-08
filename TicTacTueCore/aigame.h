#ifndef AIGAME_H
#define AIGAME_H

#include "board.h"
#include <countdowntimer.h>
#include <QObject>
#include <QTimer>
#include <game.h>
#include <tictactueai.h>

class AIGame : public Game {
public:
    AIGame(bool, int);
    ~AIGame();
    void reset() override;
    bool move(int x, int y) override;

private slots:
    void xTimerTimesup();
    void oTimerTimesup();
    void requestMove();
    bool aiMove(QString);
    void switchPlayer();
    void checkWin();
private:
    TicTacTueAI ai;
    int diff;

    QTimer aiTimer;
};

#endif // AIGAME_H
