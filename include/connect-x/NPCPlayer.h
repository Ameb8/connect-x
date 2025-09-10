
#include <vector>

#include "connect-x/board.h"
#include "../src/npc/Evaluator.h"

#ifndef CONNECT_X_NPCPLAYER_H
#define CONNECT_X_NPCPLAYER_H

struct Move;
struct Difficulty;

class NPCPlayer {
public:
    NPCPlayer(int maxDepth, int token, int opToken, Difficulty &dif);
    void selectMove(Board &board);
private:
    int maxDepth;
    int token;
    int opToken;
    Evaluator evaluator;

    bool evaluateBoard(Board &board);
    Move miniMax(Board &board, bool maximizing, int depth);
};


#endif //CONNECT_X_NPCPLAYER_H

