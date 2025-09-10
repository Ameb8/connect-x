
#include "connect-x/NPCPlayer.h"

#include <climits>

struct Move {
    int score;
    int col;

    Move(int score, int col) : score(score), col(col) {}

    bool operator == (const Move &other) const {
        return score == other.score;
    }
    bool operator < (const Move &other) const {
        return score < other.score;
    }
    bool operator > (const Move &other) const {
        return score > other.score;
    }
    bool operator <= (const Move &other) const {
        return score <= other.score;
    }
    bool operator >= (const Move &other) const {
        return score >= other.score;
    }
};

NPCPlayer::NPCPlayer(int maxDepth, int token, int opToken, int winLen, Difficulty dif):
    maxDepth(maxDepth),
    token(token),
    opToken(opToken),
    evaluator(std::make_unique<Evaluator>(dif, winLen))
{ }







int NPCPlayer::selectMove(Board &board) {
    return miniMax(board, true, 0).col;

}


Move NPCPlayer::miniMax(Board &board, bool maximizing, int depth) {
    int curToken = token;

    if (maximizing) {
        Move bestMove = Move(INT_MIN, -1);
        int maxScore = INT_MIN;
        int nextCol = -1;

        for (int i = 0; i < board.getWidth(); i++) {
            int moveRow = board.move(i, curToken);

            if (moveRow != 0) { // Valid move
                int isWin = board.gameWon(moveRow, i);
                int score = INT_MIN;
                Move move = Move(INT_MIN, i);

                if (isWin == token) // Game won
                    move.score = INT_MAX;
                else if (isWin == opToken) // Game lost
                    move.score = INT_MIN;
                else if (board.gameTie()) // Tied
                    move.score = 0;
                else if (depth < maxDepth) // Continue search
                    move.score = miniMax(board, false, depth + 1).score;
                else // Evaluate current board, max depth reached
                    move.score = evaluator->getScore(board.getBoard(), token, opToken);

                if (move >= bestMove) // Update max score
                    bestMove = move;
            }

            board.undoMove(i);
        }

        return bestMove;
    } else {
        Move bestMove = Move(INT_MAX, -1);
        int minScore = INT_MAX;
        int nextCol = -1;

        for (int i = 0; i < board.getWidth(); i++) {
            int moveRow = board.move(i, curToken);

            if (moveRow != 0) { // Valid move
                int isWin = board.gameWon(moveRow, i);
                int score = INT_MIN;
                Move move = Move(INT_MAX, i);

                if (isWin == token) // Game won
                    move.score = INT_MAX;
                else if (isWin == opToken) // Game lost
                    move.score = INT_MIN;
                else if (board.gameTie()) // Tied
                    move.score = 0;
                else if (depth < maxDepth) // Continue search
                    move.score = miniMax(board, true, depth + 1).score;
                else // Evaluate current board, max depth reached
                    move.score = evaluator->getScore(board.getBoard(), token, opToken);

                if (move >= bestMove)
                    bestMove = move;
            }

            board.undoMove(i);

        }

        return bestMove;
    }


}



