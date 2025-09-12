
#include "connect-x/NPCPlayer.h"

#include <climits>
#include <cstdint>

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
    return miniMax(board, true, 0, INT_MIN, INT_MAX).col;

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

Move NPCPlayer::miniMax(Board &board, bool maximizing, int depth, int alpha, int beta) {
    // Initialize to maximize
    int curToken = token;
    int scoreInit = INT_MIN;

    if (!maximizing) { // Initialize to minimize
        curToken = opToken;
        scoreInit = INT_MAX;
    }

    Move nextMove = Move(scoreInit, -1);

    for (int i = 0; i < board.getWidth(); i++) {
        // Check all moves
        int moveRow = board.move(i, curToken);

        if (moveRow != -1) { // Move is valid
            Move move = Move(scoreInit, i);

            if (board.gameWon(moveRow, curToken)) { // Game won
                move.score *= -1;
            } else if (board.gameTie()) { // Game tie
                move.score = 0;
            } else if (depth < maxDepth) { // Continue search
                move.score = miniMax(board, !maximizing, depth + 1, alpha, beta).score;
            } else { // Max depth reached, evaluate board
                move.score = evaluator->getScore(board.getBoard(), token, opToken);
            }

            board.undoMove(i);

            if (maximizing) {
                if (move > nextMove) { // Update NPC best move
                    nextMove = move;
                }
                alpha = std::max(alpha, move.score); // Update alpha
            } else {
                if (move < nextMove) { // Update opponent best move
                    nextMove = move;
                }
                beta = std::min(beta, move.score); // Update beta
            }

            // Prune game tree
            if (beta <= alpha) {
                break;
            }
        }
    }

    return nextMove;
}


