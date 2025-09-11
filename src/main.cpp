#include <iostream>

#include "connect-x/board.h"
#include "connect-x/Game.h"
#include "connect-x/NPCPlayer.h"
#include "../src/player/LocalPlayer.h"
#include "../src/npc/Difficulty.h"
#include "../src/npc/Evaluator.h"
/*
Evaluator* getEvaluator(Board &board) {
    std::vector<int> evalLen = {0, 1, 10, 100, 10000};
    std::function<int(int)> evalFromCenter = [](int dist) {
        return 1;
    };

    std::function<int(int)> evalMaxLen = [](int len) {
        return len * len;
    };

    return new Evaluator(evalLen, evalFromCenter, evalMaxLen, board.getConnectNum());

}
*/

void playLocalGame() {
    LocalPlayer local("Alex");
    NPCPlayer npc(6, 2, 1, 4, HardDifficulty);
    Game game(local, npc, 7, 6, 4);
    game.playGame(true, 1, 2);
}

int main() {
    playLocalGame();

    return 0;
}
