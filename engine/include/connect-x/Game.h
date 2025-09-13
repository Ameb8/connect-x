

#ifndef CONNECT_X_GAME_H
#define CONNECT_X_GAME_H

#include <functional>

#include "connect-x/Player.h"
#include "connect-x/participants.h"
#include "connect-x/board.h"


// TEMP Addition while testing WASM
using MoveFn = std::function<int(const Board&)>;
using VoidFn = std::function<void(const Board&)>;
// *********



class Game {
public:
    Game(Player &player1, Player &player2, int width, int height, int winLen);
    void playGame(bool player1Move, int player1Token, int player2Token);
    static void webGame(std::string name,
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

};


#endif //CONNECT_X_GAME_H




