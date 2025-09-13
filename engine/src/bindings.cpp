#include <emscripten/bind.h>
#include "WebPlayer.h"
#include "connect-x/Board.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(web_player_bindings) {
    class_<Board>("Board")
        .function("getBoard", &Board::getBoard);

    class_<WebPlayer, base<Player>>("WebPlayer")
        .constructor<std::string>()
        .function("setCallbacks", &WebPlayer::setCallbacks)
        .function("getName", &WebPlayer::getName)
        ;
}
