//
// Created by Patty Crowder on 9/7/25.
//

#include "connect-x/NPCPlayer.h"

NPCPlayer::NPCPlayer(int depth, int token) {

}
void NPCPlayer::make_move(Board* board);





NPCPlayer::NPCPlayer(int depth, int token)
    : depth(depth), token(token) {}

void NPCPlayer::make_move(Board *board) {
    Board* play_board = board->copy()
}

bool NPCPlayer::evaluate_board(std::vector<std::vector<int>> board, int token, int connect_num) {

    for (int i = 0; i < board.size(); i++) {
        int len = 0;
        int last_token = 0;
        for (int j = 0; j < board[i].size() - connect_num; j++) {

        }
    }
}

int NPCPlayer::minimax(Board *board, bool maximizing) {

}





