#include "WebPlayer.h"

WebPlayer::WebPlayer(const std::string& name) : playerName(name) {}

void WebPlayer::setCallbacks(MoveFn selectMoveFn,
                             MoveFn retryMoveFn,
                             VoidFn winFn,
                             VoidFn loseFn,
                             VoidFn tieFn,
                             VoidFn forfeitFn) {
    onSelectMove = selectMoveFn;
    onRetryMove = retryMoveFn;
    onWin = winFn;
    onLose = loseFn;
    onTie = tieFn;
    onForfeit = forfeitFn;
}

int WebPlayer::selectMove(Board& board) {
    return onSelectMove ? onSelectMove(board) : -1;
}

int WebPlayer::retrySelectMove(Board& board) {
    return onRetryMove ? onRetryMove(board) : -1;
}

void WebPlayer::gameWon(Board& board) {
    if (onWin) onWin(board);
}

void WebPlayer::gameLost(Board& board) {
    if (onLose) onLose(board);
}

void WebPlayer::gameTie(Board& board) {
    if (onTie) onTie(board);
}

void WebPlayer::opponentForfeit(Board& board) {
    if (onForfeit) onForfeit(board);
}

std::string WebPlayer::getName() {
    return playerName;
}
