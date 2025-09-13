/*
#include <emscripten/bind.h>
#include "connect-x/WebPlayer.h"
#include "connect-x/Board.h"
#include "connect-x/Player.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(game_bindings) {
    class_<Board>("Board")
        .function("getBoard", &Board::getBoard);

    class_<WebPlayer, base<Player>>("WebPlayer")
        .constructor<std::string>()
        .function("setCallbacks", &WebPlayer::setCallbacks)
        .function("getName", &WebPlayer::getName);

    class_<Game>("Game")
        .class_function("webGame", &Game::webGame);
}
*/