#include <iostream>

#include "connect-x/board.h"
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
int main() {
    auto board = Board::create(7, 6, 4);

    if(!board) {
        std::cout << "Failed to create board\n";
        return 1;
    }

    //Evaluator *eval = getEvaluator(*board);

    //board->move(1, 1);
    //board->move(1, 2);
    //board->move(1, 1);

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 3; j++) {
            if (i % 2 == 0)
                board->move(i, 1);
        }
    }

    std::cout << "Test complete\n";
    std::cout << *board;

    //int score = eval->getScore(board->getBoard(), 1, 2);
    //std::cout << "\n\n\n\n\nScore:\n\n" << score;

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 3; j++) {
            if (i % 2 == 1)
                board->move(i, 1);
        }
    }

    //score = eval->getScore(board->getBoard(), 1, 2);
    //std::cout << "\n\n\n\n\nScore:\n\n" << score;

    std::cout << "\n\n\n\n\n" << *board;

    return 0;
}
