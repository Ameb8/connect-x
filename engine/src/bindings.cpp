#include <emscripten/bind.h>

#include "connect-x/Game.h"
#include "connect-x/board.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(game_bindings) {

    class_<Board>("Board")
        .function("getBoard", &Board::getBoard);

    class_<Game>("Game")
        .class_function("webGame", &Game::webGame);
}
