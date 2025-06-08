#ifndef TICTACTUEAI_H
#define TICTACTUEAI_H

#include <QObject>
#include <QString>
#include <vector>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

class TicTacTueAI : public QObject
{
    Q_OBJECT
public:

    explicit TicTacTueAI(QObject *parent = nullptr);

    /**
     * @brief Requests the AI to make a move.
     * The result will be emitted via the moveReady signal.
     * @param currentBoardString A 9-character QString representing the board (e.g., "XO X O  ").
     * @param aiPlayer The character representing the AI (e.g., 'O').
     * @param humanPlayer The character representing the human opponent (e.g., 'X').
     * @param difficulty The difficulty level for the AI.
     */
    Q_INVOKABLE void requestMove(const QString& currentBoardString,
                                 char aiPlayer,
                                 char humanPlayer,
                                 int difficulty);

signals:
    /**
     * @brief Emitted when the AI has calculated its move.
     * @param newBoardState The 9-character QString representing the board after AI's move.
     */
    void moveReady(QString newBoardState);

private:
    // Internal board representation for easier manipulation
    using Board = std::vector<char>;

    // --- Move Calculation Strategies ---
    int findRandomMove(const Board& board) const;
    int findHardMove(const Board& board, char aiPlayer, char humanPlayer) const;
    int findImpossibleMove(Board board, char aiPlayer, char humanPlayer) const; // Board by value for minimax

    // --- Minimax with Alpha-Beta Pruning Helpers ---
    struct MoveScore {
        int move = -1;
        int score = 0;
    };
    MoveScore minimax(Board currentBoard, char player, char aiPlayer, char humanPlayer, int alpha, int beta, bool isMaximizingPlayer);

    // --- Game Logic Helpers ---
    char checkWinner(const Board& board) const;
    bool isBoardFull(const Board& board) const;
    std::vector<int> getAvailableMoves(const Board& board) const;
    bool canWin(const Board& board, char player, int& winningMove) const;

    // --- Utility Functions ---
    Board qstringToBoard(const QString& qstr) const;
    QString boardToQString(const Board& board) const;
};

#endif // TICTACTOEAI_H
