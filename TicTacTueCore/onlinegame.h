#ifndef ONLINEGAME_H
#define ONLINEGAME_H

#include "board.h"
#include <countdowntimer.h>
#include <QObject>
#include <QTimer>
#include <game.h>
#include <gameclient.h>

class OnlineGame : public Game {

public:
    OnlineGame();
    ~OnlineGame();
    void reset() override;
    bool move(int x, int y) override;

private slots:
    void receiveServerUpdate(QByteArray);
signals:

private:
    GameClient * gameClient;
};

#endif // ONLINEGAME_H
