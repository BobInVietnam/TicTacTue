#include "onlinegame.h"

OnlineGame::OnlineGame() {
    gameClient = GameClient::getInstance();
    connect(gameClient, &GameClient::messageReceived, this, &OnlineGame::receiveServerUpdate);

    QJsonObject json;
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
    QJsonObject json;

    json["CID"] = gameClient->cId();
    json["RID"] = gameClient->rId();
    json["INGAME"] = true;
    json["CMD"] = "REMATCH";
    gameClient->sendMessage(QJsonDocument(json).toJson(QJsonDocument::Compact));
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
    QJsonObject json;
    json["CID"] = gameClient->cId();
    json["RID"] = gameClient->rId();
    json["INGAME"] = true;
    json["CMD"] = "MOVE";
    json["AT"] = pos;
    gameClient->sendMessage(QJsonDocument(json).toJson(QJsonDocument::Compact));
    return true;
}

void OnlineGame::receiveServerUpdate(const QJsonObject& json)
{
    if (json.value("INGAME").toBool()) {
        QString type = json.value("CMD").toString("NULL");
        if (type == "ASN") {
            bool isX = json.value("ISX").toBool();
            setIsX(isX);
            emit gameStarted();
        } else if (type == "UPD") {
            QString seq = json.value("SEQ").toString();
            setBoardSeq(seq);
            xTimer->setInitialTime(json.value("X_T").toInt());
            oTimer->setInitialTime(json.value("O_T").toInt());
            if (xTurn) {
                xTimer->start();
                oTimer->pause();
            } else {
                xTimer->pause();
                oTimer->start();
            }
            xTurn = !xTurn;
            char symbol = json.value("GS").toString().at(0).toLatin1();
            switch (symbol) {
            case 'X':
                setGs(GameState::XWON);
                xTimer->pause();
                oTimer->pause();
                break;
            case 'O':
                setGs(GameState::OWON);
                xTimer->pause();
                oTimer->pause();
                break;
            case 'D':
                setGs(GameState::DRAW);
                xTimer->pause();
                oTimer->pause();
                break;
            case 'B':
                setGs(GameState::BEGIN);
                xTimer->pause();
                oTimer->pause();
                break;
            case 'N':
                setGs(GameState::STARTED);
                break;
            }
        } else if (type == "OPP_LEFT") {
            xTimer->pause();
            oTimer->pause();
            emit opponentLeft();
        } else if (type == "CHAT") {
            emit receivedChat(json.value("MSG").toString());
        }
    }

}
