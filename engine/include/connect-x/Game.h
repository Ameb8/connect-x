

#ifndef CONNECT_X_GAME_H
#define CONNECT_X_GAME_H

#include "connect-x/Player.h"
#include "connect-x/participants.h"

class Game {
public:
    Game(Player &player1, Player &player2, int width, int height, int winLen);
    void playGame(bool player1Move, int player1Token, int player2Token);
    static void setCallbacks(std::string name,
                  MoveFn selectMoveFn,
                  MoveFn retryMoveFn,
                  VoidFn winFn,
                  VoidFn loseFn,
                  VoidFn tieFn,
                  VoidFn forfeitFn);
private:
    Player &player1;
    Player &player2;
    Board board;

    void swapTurn(Player*& curPlayer, Player*& otherPlayer, int& curToken, int& otherToken);
    bool outputInfo();
    bool passInfo(Player*& player, int token) {

    }
};


#endif //CONNECT_X_GAME_H




