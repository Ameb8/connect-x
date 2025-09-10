#include <iostream>

#include "../src/player/LocalPlayer.h"


LocalPlayer::LocalPlayer(const std::string &playerName) : playerName(playerName) {}

int getMove(Board &board) {
    int moveCol = -1;

    while (true) {
        std::cout << "Select column to place token (or -1 to exit game): \n" << board << std::endl;
        if (std::cin >> moveCol) {
            if (moveCol == -1) // Player forfeit
                return INT_MIN;
            if (moveCol >= 0 && moveCol < board.getWidth()) // Move selected
                return moveCol;

            // Move out of board
            std::cout << "Invalid move, value must be in range [" << 0 <<", " << board.getWidth() << "]" << std::endl;
        }
    }
}

int LocalPlayer::selectMove(Board &board) {
    return getMove(board);
}

int LocalPlayer::retrySelectMove(Board &board) {
    std::cout << "Move invalid, please try again" << std::endl;
    return getMove(board);
}

void LocalPlayer::gameLost(Board &board) {
    std::cout << "Game Lost" << std::endl;
}

void LocalPlayer::gameTie(Board &board) {
    std::cout << "Game Tie" << std::endl;
}

void LocalPlayer::opponentForfeit(Board &board) {
    std::cout << "Opponent Won! Opponent forfeited" << std::endl;
}

void LocalPlayer::gameWon(Board &board) {
    std::cout << "Game Won" << std::endl;
}

std::string LocalPlayer::getName() {
    return playerName;
}




