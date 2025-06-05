#include "onlinegame.h"

OnlineGame::OnlineGame() {
    gameClient = GameClient::getInstance();
    connect(gameClient, &GameClient::messageReceived, this, &OnlineGame::receiveServerUpdate);
    gameClient->sendMessage("START");
    qDebug() << "OnlineGame created";
}

OnlineGame::~OnlineGame()
{

    qDebug() << "OnlineGame destroyed";
}

void OnlineGame::reset()
{
    setGs(GameState::BEGIN);
    board.clear();
    xTurn = true;
    xTimer->reset();
    oTimer->reset();
    gameClient->sendMessage("RESET");
}

bool OnlineGame::move(int x, int y)
{
    if (gs() == GameState::BEGIN) {
        setGs(GameState::STARTED);
    } else if (gs() != GameState::STARTED) {
        return false;
    }
    if (!board.placeMark(x, y, xTurn)) {
        std::cout << "Invalid move! Try again.\n";
        return false;
    }
    int pos = x * 3 + y;
    gameClient->sendMessage("MOVE:" + QString::fromStdString(std::to_string(pos)));
    return true;
}

void OnlineGame::receiveServerUpdate(QByteArray data)
{
    QString msg = QString::fromUtf8(data).trimmed();
    QStringList lines = msg.split('\n');
    for (QString line : lines) {
        if (line.startsWith("ASSIGN:")) {
            char symbol = line.at(7).toLatin1();
            switch (symbol) {
            case 'X':
                setIsX(true);
                break;
            case 'O':
                setIsX(false);
                break;
            default:
                throw new std::logic_error("Wrong assignment symbol.");
                break;
            }
        }
        if (line.startsWith("BOARD:")) {
            QString seq = line.last(10).first(9);
            setBoardSeq(seq);
            if (!xTurn) {
                xTimer->start();
                oTimer->pause();
            } else {
                xTimer->pause();
                oTimer->start();
            }
            xTurn = !xTurn;
        } else if (line.startsWith("WINNER:")) {
            char symbol = line.at(7).toLatin1();
            switch (symbol) {
            case 'X':
                setGs(GameState::XWON);
                break;
            case 'O':
                setGs(GameState::OWON);
                break;
            case 'N':
                setGs(GameState::DRAW);
                break;
            }
            xTimer->pause();
            oTimer->pause();
        }
    }
}


