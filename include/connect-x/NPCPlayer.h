#include <vector>

#include "connect-x/board.h"

#ifndef CONNECT_X_NPCPLAYER_H
#define CONNECT_X_NPCPLAYER_H


class NPCPlayer {
public:
    NPCPlayer(int depth, int token);
    void make_move(Board* board);
private:
    int depth;

    bool evaluate_board(std::vector<std::vector<int>>);
    int minimax(Board* board, bool maximizing);
};


#endif //CONNECT_X_NPCPLAYER_H