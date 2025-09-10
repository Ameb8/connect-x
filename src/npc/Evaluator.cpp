
#include <cmath>

#include "Evaluator.h"


Evaluator::Evaluator(std::vector<int> evalLength, std::function<int(int)> evalFromCenter, std::function<int(int)> evalMaxLen, int winLen)
    : evalLength(evalLength),
      evalFromCenter(evalFromCenter),
      evalMaxLen(evalMaxLen),
        winLen(winLen)
{}


int Evaluator::getScore(const std::vector<std::vector<int>> &board, int token, int opToken) {
    getAllSegs(board, token, opToken);

    return score;
}

void Evaluator::getAllSegs(const std::vector<std::vector<int>> &board, int token, int opToken) {
    getRows(board, token);
    getCols(board, token);
    getDiagUp(board, token);
    getDiagDown(board, token);

    getRows(board, opToken);
    getCols(board, opToken);
    getDiagUp(board, opToken);
    getDiagDown(board, opToken);
}


int Evaluator::distFromMid(int segMidRow, int segMidCol) {
    return abs(segMidRow - midRow) + abs(segMidCol - midCol);
}

void Evaluator::updateSegment(int segMidRow, int segMidCol, int maxLen, int numTokens, int token) {
    std::cout << "\n\nSegment:\tmaxLen: " << maxLen << ", numTokens: " << numTokens << ", dist middle: " << distFromMid(segMidRow, segMidCol);
    if (numTokens == 0 || maxLen < winLen)
        return; // No points

    int segScore = evalLength[numTokens];
    segScore *= evalFromCenter(distFromMid(segMidRow, segMidCol));
    segScore *= evalMaxLen(maxLen);

    std::cout << "\nTEST:\t" << evalLength[numTokens] << ", " << evalFromCenter(distFromMid(segMidRow, segMidCol)) << ", " << evalMaxLen(maxLen);

    if (token != playerToken)
        score *= -1;

    score += segScore;
    std::cout << "\tScore: " << segScore;
}



void Evaluator::getRow(const std::vector<int> &row, int col, int token) {
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
                updateSegment((start + i) / 2, col, i - start, numTokens, token);
            }
        } else { // Empty cell
            if (!inSegment) {
                inSegment = true;
                start = i;
            }
        }
    }

    if (!inSegment) { // Add final segment
        updateSegment((start + row.size() - 1) / 2, col, row.size() - start - 1, numTokens, token);
    }
}

void Evaluator::getRows(const std::vector<std::vector<int>> &board, int token) {
    for (int i = 0; i < board.size(); i++) {
        getRow(board[i], i, token);
    }
}

void Evaluator::getCols(const std::vector<std::vector<int>> &board, int token) {
    /*
    for (int i = 0; i < board[0].size(); i++) {

    }
    */
    int x = 0;
}


void Evaluator::getDiagDown(const std::vector<std::vector<int>> &board, int token) {
    int rows = board.size();
    if (rows == 0)
        return;
    int cols = board[0].size();

    // Iterate over all possible main diagonals defined by (row - col)
    for (int diff = -(cols - 1); diff <= rows - 1; ++diff) {
        int start = 0;
        int numTokens = 0;
        bool inSegment = false;

        for (int row = 0; row < rows; ++row) {
            int col = row - diff; // because diff = row - col → col = row - diff

            if (col < 0 || col >= cols)
                continue;

            int val = board[row][col];

            if (val == token) {
                numTokens++;
                if (!inSegment) {
                    inSegment = true;
                    start = row;
                }
            } else if (val != 0) {
                if (inSegment) {
                    int midRow = (start + row) / 2;
                    int midCol = midRow - diff;
                    updateSegment(midRow, midCol, row - start, numTokens, token);
                    inSegment = false;
                    numTokens = 0;
                }
            } else {
                if (!inSegment) {
                    inSegment = true;
                    start = row;
                }
            }
        }

        // Handle trailing segment at end of diagonals
        if (inSegment) {
            int end = rows;
            for (int row = rows - 1; row >= 0; --row) {
                int col = row - diff;
                if (col >= 0 && col < cols) {
                    end = row + 1;
                    break;
                }
            }

            int midIdx = (start + end - 1) / 2;
            int midRow = midIdx;
            int midCol = midRow - diff;
            updateSegment(midRow, midCol, end - start, numTokens, token);
        }
    }
}


void Evaluator::getDiagUp(const std::vector<std::vector<int>> &board, int token) {
    int rows = board.size();

    if (rows == 0)
        return;
    int cols = board[0].size();

    // Iterate over all possible anti-diagonals defined by (row + col)
    for (int sum = 0; sum <= rows + cols - 2; ++sum) {
        int start = 0;
        int numTokens = 0;
        bool inSegment = false;

        for (int row = 0; row < rows; ++row) {
            int col = sum - row;

            if (col < 0 || col >= cols)
                continue;

            int val = board[row][col];

            if (val == token) { // Player token
                numTokens++;

                if (!inSegment) {
                    inSegment = true;
                    start = row; // row used as position in diagonal
                }
            } else if (val != 0) { // Opponent token
                if (inSegment) {
                    int midRow = (start + row) / 2;
                    int midCol = sum - midRow;
                    updateSegment(midRow, midCol, row - start, numTokens, token);
                    inSegment = false;
                    numTokens = 0;
                }
            } else { // Empty cell
                if (!inSegment) {
                    inSegment = true;
                    start = row;
                }
            }

        }

        // Handle trailing segment at end of diagonals
        if (inSegment) {
            int end = rows;
            for (int row = rows - 1; row >= 0; --row) {
                int col = sum - row;
                if (col >= 0 && col < cols) {
                    end = row + 1;
                    break;
                }
            }

            int midIdx = (start + end - 1) / 2;
            int midRow = midIdx;
            int midCol = sum - midRow;
            updateSegment(midRow, midCol, end - start, numTokens, token);
        }

    }
}


