#ifndef OFFLINEGAME_H
#define OFFLINEGAME_H

#include "board.h"
#include <countdowntimer.h>
#include <QObject>
#include <QTimer>
#include <game.h>

class OfflineGame : public Game {
public:
    OfflineGame();
    ~OfflineGame();
    void reset() override;
    bool move(int x, int y) override;

private slots:
    void xTimerTimesup();
    void oTimerTimesup();

    void switchPlayer();
    void checkWin();
};

#endif // OFFLINEGAME_H
