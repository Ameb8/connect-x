
#include <vector>

#include "connect-x/board.h"
#include "../src/npc/Evaluator.h"
#include "../src/npc/Difficulty.h"

#ifndef CONNECT_X_NPCPLAYER_H
#define CONNECT_X_NPCPLAYER_H

struct Move;
struct Difficulty;

class NPCPlayer {
public:
    NPCPlayer(int maxDepth, int token, int opToken, int winLen, Difficulty dif);
    int selectMove(Board &board);

private:
    int maxDepth;
    int token;
    int opToken;
    std::unique_ptr<Evaluator> evaluator;

    Move miniMax(Board &board, bool maximizing, int depth);
};


#endif //CONNECT_X_NPCPLAYER_H

