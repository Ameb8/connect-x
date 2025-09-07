//
// Created by Patty Crowder on 9/7/25.
//

#ifndef CONNECT_X_BOARD_H
#define CONNECT_X_BOARD_H

#include <vector>
#include <memory>
#include <tuple>
#include <iostream>

// Constants (you can put these in a separate constants.hpp if needed)
constexpr int MIN_WIDTH = 3;
constexpr int MAX_WIDTH = 100;
constexpr int MIN_HEIGHT = 3;
constexpr int MAX_HEIGHT = 100;
constexpr int MIN_CONNECT_NUM = 3;
constexpr int MAX_CONNECT_NUM = 10;

constexpr std::tuple<int, int> UP_RIGHT(-1, 1);
constexpr std::tuple<int, int> UP_LEFT(-1, -1);
constexpr std::tuple<int, int> DOWN_RIGHT(1, 1);
constexpr std::tuple<int, int> DOWN_LEFT(1, -1);
constexpr std::tuple<int, int> RIGHT(0, 1);
constexpr std::tuple<int, int> LEFT(0, -1);
constexpr std::tuple<int, int> UP(-1, 0);
constexpr std::tuple<int, int> DOWN(1, 0);

constexpr int EMPTY = 0;

class Board {
public:
    Board(int width, int height, int connect_num);

    friend std::ostream& operator<<(std::ostream& os, const Board& b);

    static bool valid_dimensions(int width, int height, int connect_num);
    static std::unique_ptr<Board> create(int width, int height, int connect_num);

    int getWidth() const;
    int getHeight() const;
    int getConnectNum() const;

    int& at(int row, int col);
    const int& at(int row, int col) const;

    bool game_won(int row, int col);
    bool game_tie();
    bool move(int col, int player);

private:
    int width;
    int height;
    int connect_num;
    int full_cols;
    std::vector<std::vector<int>> board;

    bool in_bounds(int row, int col);
    void iterate_pos(int* row, int* col, const std::tuple<int, int>& step);
    int count_from(int row, int col, const std::tuple<int, int>& step);
};


#endif //CONNECT_X_BOARD_H