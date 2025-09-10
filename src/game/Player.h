//
// Created by Patty Crowder on 9/10/25.
//

#ifndef CONNECT_X_PLAYER_H
#define CONNECT_X_PLAYER_H

#include "connect-x/board.h"
#include <string>


class Player {
public:
    virtual int selectMove(Board &board) = 0;
    virtual int retrySelectMove(Board &board) = 0;
    virtual void gameWon(Board &board) = 0;
    virtual void gameLost(Board &board) = 0;
    virtual void gameTie(Board &board) = 0;
    virtual void opponentForfeit(Board &board) = 0;
    virtual std::string getName() = 0;
    virtual ~Player() = default;
};


#endif //CONNECT_X_PLAYER_H