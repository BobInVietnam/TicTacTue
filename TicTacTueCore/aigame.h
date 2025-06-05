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
    AIGame(bool, TicTacTueAI::Difficulty);
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
    TicTacTueAI::Difficulty diff;

};

#endif // AIGAME_H
