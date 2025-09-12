//
// Created by Patty Crowder on 9/11/25.
//

#ifndef CONNECT_X_PARTICIPANTS_H
#define CONNECT_X_PARTICIPANTS_H

#include "connect-x/Player.h"


struct Participant {
    const int token;
    const Player* player;

    Participant(int t, const Player& p) : token(t), player(p) {}
};

#endif //CONNECT_X_PARTICIPANTS_H