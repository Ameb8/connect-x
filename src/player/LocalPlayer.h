#ifndef CONNECT_X_LOCALPLAYER_H
#define CONNECT_X_LOCALPLAYER_H

#include "connect-x/Player.h"
#include <string>

class LocalPlayer : public Player {
public:
    explicit LocalPlayer(const std::string playerName);

    int selectMove(Board &board) override;
    int retrySelectMove(Board &board) override;
    void gameWon(Board &board) override;
    void gameLost(Board &board) override;
    void gameTie(Board &board) override;
    void opponentForfeit(Board &board) override;
    std::string getName() override;
private:
    std::string playerName;
    std::vector<Participants>;
};


#endif //CONNECT_X_LOCALPLAYER_H


