#include "tictactueai.h"
#include <QDebug>
#include <random>       // For std::mt19937 and std::uniform_int_distribution
#include <algorithm>    // For std::max and std::min
#include <limits>       // For std::numeric_limits

TicTacTueAI::TicTacTueAI(QObject *parent) : QObject(parent)
{
    // Seed for random number generation
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

TicTacTueAI::Board TicTacTueAI::qstringToBoard(const QString& qstr) const {
    Board board(9);
    for (int i = 0; i < 9; ++i) {
        if (i < qstr.length()) {
            board[i] = qstr.at(i).toLatin1(); // Assuming 'X', 'O', or ' '
        } else {
            board[i] = ' '; // Should not happen if qstr is always length 9
        }
    }
    return board;
}

QString TicTacTueAI::boardToQString(const Board& board) const {
    QString qstr;
    qstr.reserve(9);
    for (char c : board) {
        qstr += c;
    }
    return qstr;
}

void TicTacTueAI::requestMove(const QString& currentBoardString,
                              char aiPlayer,
                              char humanPlayer,
                              int difficulty)
{
    // Capture necessary variables for the lambda
    // Note: Capturing `this` allows calling member functions and emitting signals.
    // Qt's signal/slot mechanism handles cross-thread emission correctly (queued).
    QtConcurrent::run([this, currentBoardString, aiPlayer, humanPlayer, difficulty]() {
        Board board = qstringToBoard(currentBoardString);
        int bestMove = -1;

        // Check if game is already over
        if (checkWinner(board) != ' ' || isBoardFull(board)) {
            // qWarning() << "AI requested move on a finished game.";
            emit moveReady(currentBoardString); // Return current board if game is over
            return;
        }

        switch (difficulty) {
        case 1:
            bestMove = findRandomMove(board);
            break;
        case 2:
            bestMove = findHardMove(board, aiPlayer, humanPlayer);
            break;
        case 3:
            bestMove = findImpossibleMove(board, aiPlayer, humanPlayer);
            break;
        default:
            bestMove = findRandomMove(board);
        }

        Board nextBoard = board;
        if (bestMove != -1 && bestMove >=0 && bestMove < 9 && nextBoard[bestMove] == ' ') {
            nextBoard[bestMove] = aiPlayer;
            emit moveReady(boardToQString(nextBoard));
        } else {
            qWarning() << "AI could not determine a valid move. Difficulty:" << static_cast<int>(difficulty)
            << "Calculated move:" << bestMove;
            // Fallback: if no valid move found (should not happen for valid boards),
            // emit current board or an error signal.
            // For robustness, find any random valid move if bestMove was invalid.
            int fallbackMove = findRandomMove(board);
            if(fallbackMove != -1) {
                nextBoard[fallbackMove] = aiPlayer;
                emit moveReady(boardToQString(nextBoard));
            } else {
                emit moveReady(currentBoardString); // Or handle error
            }
        }
    });
}

std::vector<int> TicTacTueAI::getAvailableMoves(const Board& board) const {
    std::vector<int> moves;
    for (int i = 0; i < 9; ++i) {
        if (board[i] == ' ') {
            moves.push_back(i);
        }
    }
    return moves;
}

int TicTacTueAI::findRandomMove(const Board& board) const {
    std::vector<int> availableMoves = getAvailableMoves(board);
    if (availableMoves.empty()) {
        return -1; // No moves possible
    }
    int randomIndex = std::rand() % availableMoves.size();
    return availableMoves[randomIndex];
}


bool TicTacTueAI::canWin(const Board& board, char player, int& winningMove) const {
    for (int move : getAvailableMoves(board)) {
        Board tempBoard = board;
        tempBoard[move] = player;
        if (checkWinner(tempBoard) == player) {
            winningMove = move;
            return true;
        }
    }
    return false;
}

int TicTacTueAI::findHardMove(const Board& board, char aiPlayer, char humanPlayer) const {
    int move;

    // 1. Check if AI can win in the next move
    if (canWin(board, aiPlayer, move)) {
        return move;
    }

    // 2. Check if human can win in the next move, and block it
    if (canWin(board, humanPlayer, move)) {
        return move;
    }

    // 3. Try to take the center if it's available
    if (board[4] == ' ') {
        return 4;
    }

    // 4. Otherwise, make a random available move (sides)
    return findRandomMove(board);
}


int TicTacTueAI::findImpossibleMove(Board board, char aiPlayer, char humanPlayer) const {
    // The Minimax function itself (or a wrapper around it) will determine the best move.
    // We call minimax for the AI's turn (maximizing player).
    MoveScore bestMoveScore = const_cast<TicTacTueAI*>(this)->minimax(board, aiPlayer, aiPlayer, humanPlayer,
                                                                       std::numeric_limits<int>::min(),
                                                                       std::numeric_limits<int>::max(), true);
    return bestMoveScore.move;
}

TicTacTueAI::MoveScore TicTacTueAI::minimax(Board currentBoard, char currentPlayer,
                                            char aiPlayer, char humanPlayer,
                                            int alpha, int beta, bool isMaximizingPlayer) {
    char winner = checkWinner(currentBoard);
    if (winner == aiPlayer) return {-1, 10};
    if (winner == humanPlayer) return {-1, -10};
    if (isBoardFull(currentBoard)) return {-1, 0};

    std::vector<int> availableMoves = getAvailableMoves(currentBoard);
    MoveScore bestMove;

    if (isMaximizingPlayer) { // AI's turn (Maximizer)
        bestMove.score = std::numeric_limits<int>::min();
        bestMove.move = availableMoves.empty() ? -1 : availableMoves[0]; // Default if all paths bad

        for (int move : availableMoves) {
            currentBoard[move] = aiPlayer;
            MoveScore currentScore = minimax(currentBoard, humanPlayer, aiPlayer, humanPlayer, alpha, beta, false);
            currentBoard[move] = ' '; // Backtrack

            if (currentScore.score > bestMove.score) {
                bestMove.score = currentScore.score;
                bestMove.move = move;
            }
            alpha = std::max(alpha, bestMove.score);
            if (beta <= alpha) {
                break; // Beta cut-off
            }
        }
    } else { // Human's turn (Minimizer)
        bestMove.score = std::numeric_limits<int>::max();
        bestMove.move = availableMoves.empty() ? -1 : availableMoves[0]; // Default

        for (int move : availableMoves) {
            currentBoard[move] = humanPlayer;
            MoveScore currentScore = minimax(currentBoard, aiPlayer, aiPlayer, humanPlayer, alpha, beta, true);
            currentBoard[move] = ' '; // Backtrack

            if (currentScore.score < bestMove.score) {
                bestMove.score = currentScore.score;
                bestMove.move = move;
            }
            beta = std::min(beta, bestMove.score);
            if (beta <= alpha) {
                break; // Alpha cut-off
            }
        }
    }
    return bestMove;
}


char TicTacTueAI::checkWinner(const Board& board) const {
    // Rows
    for (int i = 0; i < 3; ++i) {
        if (board[i * 3] != ' ' && board[i * 3] == board[i * 3 + 1] && board[i * 3 + 1] == board[i * 3 + 2]) {
            return board[i * 3];
        }
    }
    // Columns
    for (int i = 0; i < 3; ++i) {
        if (board[i] != ' ' && board[i] == board[i + 3] && board[i + 3] == board[i + 6]) {
            return board[i];
        }
    }
    // Diagonals
    if (board[0] != ' ' && board[0] == board[4] && board[4] == board[8]) {
        return board[0];
    }
    if (board[2] != ' ' && board[2] == board[4] && board[4] == board[6]) {
        return board[2];
    }
    return ' '; // No winner
}

bool TicTacTueAI::isBoardFull(const Board& board) const {
    for (char cell : board) {
        if (cell == ' ') {
            return false;
        }
    }
    return true;
}
