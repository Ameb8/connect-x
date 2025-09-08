//
// Created by Patty Crowder on 9/7/25.
//

#include "Evaluator.h"


Evaluator(std::vector<int> eval_length, std::function<int(int)> eval_from_center, int eval_both_sides);
int getScore(std::vector<std::vector<int>> board, int token);






void update_score(int len, bool both_sides, int dist_center, bool isMax);

void Evaluator::updateSegment(int mid_row, int mid_col, int max_len, int num_tokens) {
}


void Evaluator::getRow(std::vector<int> row, int col, int token) {
    int start = 0;
    int numTokens = 0;
    bool inSegment = false;

    for (int i = 0; i < row.size(); i++) {
        if (row[i] == token) { // Player token
            numTokens++;

            if (!inSegment)
                start = i;
        } else if (row[i] != 0) { // Opponent token
            if (!inSegment) {
                inSegment = false;
                updateSegment((start + i) / 2, col, i - start, numTokens);
            }
        } else { // Empty cell
            if (!inSegment) {
                inSegment = true;
                start = i;
            }
        }
    }

    if (!inSegment) { // Add final segmenet
        updateSegment((start + row.size() - 1) / 2, col, row.size() - start - 1, numTokens);
    }
}

void getRows(std::vector<std::vector<int>> board, int token) {
    for (int i = 0; i < board.size(); i++) {
        getRow(board[i], i, token)
    }
}

int getCols(std::vector<std::vector<int>> board, int token);
int getDiagUp(std::vector<std::vector<int>> board, int token);
int getDiagDown(std::vector<std::vector<int>> board, int token);

std::vector<int> colVector(std::vector<std::vector<int>> board);
std::vector<int> diagUpVector(std::vector<std::vector<int>> board);


