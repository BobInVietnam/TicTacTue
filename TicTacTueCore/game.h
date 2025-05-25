#ifndef GAME_H
#define GAME_H

#include "board.h"

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

private:
    Board board;
    bool xTurn;
    GameState gs;
    QTimer xTimer;
    QTimer oTimer;

public:
    Game();
    void start();
    void reset();
    bool move(int x, int y);
    void switchPlayer();
    void checkWin();

    bool getXTurn() const;
    GameState getGs() const;
signals:

};

#endif // GAME_H
