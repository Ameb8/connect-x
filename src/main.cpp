#include <iostream>
#include "connect-x/board.h"

int main() {
    auto board = Board::create(7, 6, 4);

    if(!board) {
        std::cout << "Failed to create board\n";
        return 1;
    }


    board->move(1, 1);
    board->move(1, 2);
    board->move(1, 1);

    std::cout << *board;

    return 0;
}
