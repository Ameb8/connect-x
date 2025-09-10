
#include "connect-x/Game.h"

Game::Game(Player &player1, Player &player2, int width, int height, int winLen):
    player1(player1),
    player2(player2),
    board(Board(width, height, winLen))
{}

void Game::swapTurn(Player*& curPlayer, Player*& otherPlayer, int& curToken, int& otherToken) {
    std::swap(curPlayer, otherPlayer);
    std::swap(curToken, otherToken);
}

void Game::playGame(bool player1Move, int player1Token, int player2Token) {
    Player *curPlayer = &player1;
    Player *otherPlayer = &player2;
    int curToken = player1Token;
    int otherToken = player2Token;

    if (!player1Move) {
        curPlayer = &player2;
        curToken = player2Token;
        otherPlayer = &player1;
        otherToken = player1Token;
    }

    while (!board.gameTie()) {
        // Get move from player
        int moveCol = curPlayer->selectMove(board);
        int pos = board.move(moveCol, curToken);

        while (pos == -1) { // Invalid move selection
            moveCol = curPlayer->retrySelectMove(board);
            pos = board.move(moveCol, curToken);
        }

        if (pos == INT_MIN) // Player forfeit
            otherPlayer->opponentForfeit(board);

        int win = board.gameWon(pos, moveCol);

        if (win == curToken) {
            curPlayer->gameWon(board);
            otherPlayer->gameLost(board);
            return;
        }

        swapTurn(curPlayer, otherPlayer, curToken, otherToken);
    }

    // Game tie
    curPlayer->gameTie(board);
    otherPlayer->gameTie(board);
    }
}




