
#include <vector>
#include <string>

#include "connect-x/board.h"
#include "connect-x/Player.h"

#include "../src/npc/Evaluator.h"
#include "../src/npc/Difficulty.h"

#ifndef CONNECT_X_NPCPLAYER_H
#define CONNECT_X_NPCPLAYER_H

struct Move;

class NPCPlayer : public Player {
public:
    NPCPlayer(int maxDepth, int token, int opToken, int winLen, Difficulty dif);
    int selectMove(Board &board) override;
    int retrySelectMove(Board &board) override;
    void gameWon(Board &board) override;
    void gameLost(Board &board) override;
    void gameTie(Board &board) override;
    void opponentForfeit(Board &board) override;
    std::string getName() override;

private:
    int maxDepth;
    int token;
    int opToken;
    std::unique_ptr<Evaluator> evaluator;

    Move miniMax(Board &board, bool maximizing, int depth);
};


#endif //CONNECT_X_NPCPLAYER_H

