#include <iostream>
#include "connect-x/Game.h"


#include "player/WebPlayer.h"
#include "connect-x/NPCPlayer.h"

Game::Game(Player &player1, Player &player2, int width, int height, int winLen):
    player1(player1),
    player2(player2),
    board(Board(width, height, winLen))
{}

void Game::swapTurn(Player*& curPlayer, Player*& otherPlayer, int& curToken, int& otherToken) {
    std::swap(curPlayer, otherPlayer);
    std::swap(curToken, otherToken);
}

/*
bool Game::outputInfo(bool moveFirst, int token1, int token2) {
    std::vector<Participant> participants;

    if (moveFirst) {
        participants = {
            Participant(token1, player1),
            Participant(token2, player2)
        };
    } else {
        participants = {
            Participant(token2, player2),
            Participant(token1, player1)
        };
    }

    if (!player1.gameInfo(participants, token1) ||
        !player2.gameInfo(participants, token2))
    {
        return false;
    }

    return true;
}
*/

void Game::playGame(bool player1Move, int player1Token, int player2Token) {
    Player *curPlayer = &player1;
    Player *otherPlayer = &player2;

    //if (!outputInfo(player1Move, player1Token, player2Token))
        //return;

    int curToken = player1Token;
    int otherToken = player2Token;

    if (!player1Move) { // Determine current move;
        curPlayer = &player2;
        curToken = player2Token;
        otherPlayer = &player1;
        otherToken = player1Token;
    }

    while (!board.gameTie()) {
        // Get move from player
        int moveCol = curPlayer->selectMove(board);
        int pos = board.move(moveCol, curToken);
        int numAttempts = 0;

        while (pos == -1) { // Invalid move selection
            if (numAttempts++ == 10) {
                otherPlayer->opponentForfeit(board);
                curPlayer->gameLost(board);
            }

            moveCol = curPlayer->retrySelectMove(board);
            pos = board.move(moveCol, curToken);
        }

        if (pos == INT_MIN) // Player forfeit
            otherPlayer->opponentForfeit(board);

        int win = board.gameWon(pos, moveCol);

        if (win == curToken) { // Game won
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



void Game::webGame(std::string name,
              MoveFn selectMoveFn,
              MoveFn retryMoveFn,
              VoidFn winFn,
              VoidFn loseFn,
              VoidFn tieFn,
              VoidFn forfeitFn)
{
    // Create web player
    WebPlayer webPlayer("Alex");
    webPlayer.setCallbacks(selectMoveFn, retryMoveFn, winFn, loseFn, tieFn, forfeitFn);

    // Create npc
    NPCPlayer npc(4, 2, 1, 4, HardDifficulty);

    // Create Game object
    Game game(webPlayer, npc, 7, 6, 4);

    // Initiate game loop
    game.playGame(true, 1, 2);

}



