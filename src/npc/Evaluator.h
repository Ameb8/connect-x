//
// Created by Patty Crowder on 9/7/25.
//

#ifndef CONNECT_X_EVALUATOR_H
#define CONNECT_X_EVALUATOR_H

#include <vector>
#include <functional>
#include <iostream>


class Evaluator {
    public:
        Evaluator(std::vector<int> eval_length, std::function<int(int)> eval_from_center, int eval_both_sides);
        int getScore(std::vector<std::vector<int>> board, int token);

    private:
        std::vector<int> eval_length; // Base score based on length of segment
        std::function<int(int)> eval_from_center; // Multiplier based on distance form center of board
        int eval_both_sides; // Score multiplier when win possible from 2 directions
        int score;

        void update_score(int len, bool both_sides, int dist_center, bool isMax);
        void update_segment(int mid_row, int mid_col, int max_len, int num_tokens);

        int getRows(std::vector<std::vector<int>> board, int token);
        int getCols(std::vector<std::vector<int>> board, int token);
        int getDiagUp(std::vector<std::vector<int>> board, int token);
        int getDiagDown(std::vector<std::vector<int>> board, int token);

};


#endif //CONNECT_X_EVALUATOR_H