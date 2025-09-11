
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

int NPCPlayer::retrySelectMove(Board &board) {
    return selectMove(board);
}

void NPCPlayer::gameWon(Board &) { }

void NPCPlayer::gameLost(Board &) { }

void NPCPlayer::gameTie(Board &) { }

void NPCPlayer::opponentForfeit(Board &) { /* no-op */ }

std::string NPCPlayer::getName() {
    return "NPC";
}

Move NPCPlayer::miniMax(Board &board, bool maximizing, int depth) {
    // Initialize to maximize
    int curToken = token;
    int scoreInit = INT_MIN;

    if (!maximizing) { // Initialize to minimize
        curToken = opToken;
        scoreInit = INT_MAX;
    }

    Move nextMove = Move(scoreInit, -1);

    for (int i = 0; i < board.getWidth(); i++) {
        int moveRow = board.move(i, curToken);

        if (moveRow != 0) {
            Move move = Move(scoreInit, i);

            if (board.gameWon(moveRow, curToken)) { // Game won
                move.score *= -1;
            } else if (board.gameTie()) { // Game tie
                move.score = 0;
            } else if (depth < maxDepth) { // Continue search
                move.score = miniMax(board, !maximizing, depth + 1).col;
            } else { // Max depth reached, evaluate board
                move.score = evaluator->getScore(board.getBoard(), token, opToken);
            }

            // Update min/max score
            if ((maximizing && move >= nextMove) || (!maximizing && move <= nextMove))
                nextMove = move;
        }

        board.undoMove(i);
    }

    return nextMove;
}


