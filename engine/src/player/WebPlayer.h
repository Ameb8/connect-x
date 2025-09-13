#ifndef CONNECT_X_WEBPLAYER_H
#define CONNECT_X_WEBPLAYER_H

#include "connect-x/Player.h"
#include <string>
#include <functional>

//#include <emscripten/bind.h>

class WebPlayer : public Player {
public:
    using MoveFn = std::function<int(const Board&)>;
    using VoidFn = std::function<void(const Board&)>;

    explicit WebPlayer(const std::string playerName);

    // Setter for JS callbacks
    void setCallbacks(MoveFn selectMoveFn,
                      MoveFn retryMoveFn,
                      VoidFn winFn,
                      VoidFn loseFn,
                      VoidFn tieFn,
                      VoidFn forfeitFn);

    int selectMove(Board &board) override;
    int retrySelectMove(Board &board) override;
    void gameWon(Board &board) override;
    void gameLost(Board &board) override;
    void gameTie(Board &board) override;
    void opponentForfeit(Board &board) override;
    std::string getName() override;
private:
    std::string playerName;

    MoveFn onSelectMove = nullptr;
    MoveFn onRetryMove = nullptr;
    VoidFn onWin = nullptr;
    VoidFn onLose = nullptr;
    VoidFn onTie = nullptr;
    VoidFn onForfeit = nullptr;

};


#endif //CONNECT_X_WEBPLAYER_H