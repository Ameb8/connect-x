
#ifndef CONNECT_X_EVALUATOR_H
#define CONNECT_X_EVALUATOR_H

#include <vector>
#include <functional>
#include <iostream>

#include <../src/npc/Difficulty.h>


class Evaluator {
    public:
        Evaluator(Difficulty dif, int winLen);
        int getScore(const std::vector<std::vector<int>> &board, int token, int opToken);

    private:
        Difficulty dif;
        int score;
        int midRow;
        int midCol;
        int winLen;
        int playerToken;

        void updateSegment(int mid_row, int mid_col, int max_len, int num_tokens, int token);
        void getAllSegs(const std::vector<std::vector<int>> &board, int token, int opToken);
        int distFromMid(int segMidRow, int segMidCol);
        int getMiddle(int height, int width);

        void getRow(const std::vector<int> &row, int col, int token);
        void getRows(const std::vector<std::vector<int>> &board, int token);
        void getCols(const std::vector<std::vector<int>> &board, int token);
        void getDiagUp(const std::vector<std::vector<int>> &board, int token);
        void getDiagDown(const std::vector<std::vector<int>> &board, int token);

};


#endif //CONNECT_X_EVALUATOR_H