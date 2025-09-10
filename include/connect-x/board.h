
#ifndef CONNECT_X_BOARD_H
#define CONNECT_X_BOARD_H

#include <vector>
#include <memory>
#include <tuple>
#include <iostream>
#include <utility>

constexpr int MIN_WIDTH = 3;
constexpr int MAX_WIDTH = 100;
constexpr int MIN_HEIGHT = 3;
constexpr int MAX_HEIGHT = 100;
constexpr int MIN_CONNECT_NUM = 3;
constexpr int MAX_CONNECT_NUM = 10;


class Board {
public:
    Board(int width, int height, int connect_num);

    friend std::ostream& operator<<(std::ostream& os, const Board& b);

    static bool valid_dimensions(int width, int height, int connect_num);
    static std::unique_ptr<Board> create(int width, int height, int connect_num);

    int getWidth() const;
    int getHeight() const;
    int getConnectNum() const;

    const std::vector<std::vector<int>> &getBoard() const;

    int& at(int row, int col);
    const int& at(int row, int col) const;

    int gameWon(int row, int col);
    bool gameTie();
    int move(int col, int player);
    bool undoMove(int col);

private:
    int width;
    int height;
    int connect_num;
    int full_cols;
    int piecesPlayed;
    std::vector<std::vector<int>> board;

    bool in_bounds(int row, int col);
    void iterate_pos(int* row, int* col, const std::tuple<int, int>& step);
    int count_from(int row, int col, const std::tuple<int, int>& step);
    std::pair<std::vector<int>, std::vector<int>> get_groups(int token);
};


#endif //CONNECT_X_BOARD_H

