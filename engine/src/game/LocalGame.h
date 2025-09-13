//
// Created by Patty Crowder on 9/12/25.
//

#ifndef CONNECT_X_LOCALGAME_H
#define CONNECT_X_LOCALGAME_H

#include "connect-x/board.h"

enum class Difficulty {
    Easy,
    Medium,
    Hard
}

struct GameConfig {
    Difficulty diff;

}

class LocalGame {
public:
    LocalGame(GameConfig config, bool playerFirst);

private:
    Difficulty difficulty;
    Color playerTokColor;

    bool makeMove(int col)
};


#endif //CONNECT_X_LOCALGAME_H