#include <vector>
#include <memory>
#include <tuple>
#include <iostream>

// Board dimension requirements
constexpr int MIN_WIDTH = 3;
constexpr int MAX_WIDTH = 100;
constexpr int MIN_HEIGHT = 3;
constexpr int MAX_HEIGHT = 100;
constexpr int MIN_CONNECT_NUM = 3;
constexpr int MAX_CONNECT_NUM = 10;

// Direction tuples
constexpr std::tuple<int, int> UP_RIGHT(-1, 1);
constexpr std::tuple<int, int> UP_LEFT(-1, -1);
constexpr std::tuple<int, int> DOWN_RIGHT(1, 1);
constexpr std::tuple<int, int> DOWN_LEFT(1, -1);
constexpr std::tuple<int, int> RIGHT(0, 1);
constexpr std::tuple<int, int> LEFT(0, -1);
constexpr std::tuple<int, int> UP(-1, 0);
constexpr std::tuple<int, int> DOWN(1, 0);

// Empty cell value
constexpr int EMPTY = 0;


class Board {
public:
    Board(int width, int height, int connect_num)
        : width(width), height(height), connect_num(connect_num), full_cols(0), board(height, std::vector<int>(width, 0))
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const Board& b);

    static bool valid_dimensions(int width, int height, int connect_num) {
        if (width < MIN_WIDTH || width > MAX_WIDTH)
            return false;

        if (height < MIN_HEIGHT || height > MAX_HEIGHT)
            return false;

        if (connect_num < MIN_CONNECT_NUM || connect_num > MAX_CONNECT_NUM)
            return false;

        if (connect_num > width || connect_num > height)
            return false;

        return true;
    }

    static std::unique_ptr<Board> create(int width, int height, int connect_num) {
        if (!valid_dimensions(width, height, connect_num))
            return nullptr;
            
        return std::make_unique<Board>(width, height, connect_num);
    }

    // Accessors
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getConnectNum() const { return connect_num; }

    int& at(int row, int col) {
        return board.at(row).at(col);
    }

    const int& at(int row, int col) const {
        return board.at(row).at(col);
    }

    bool game_won(int row, int col) {
        if(count_from(row, col, LEFT) + count_from(row, col, RIGHT) + 1 >= connect_num)
            return true;
        if(count_from(row, col, UP) + count_from(row, col, DOWN) + 1 >= connect_num)
            return true;
        if(count_from(row, col, UP_RIGHT) + count_from(row, col, DOWN_LEFT) + 1 >= connect_num)
            return true;
        if(count_from(row, col, UP_LEFT) + count_from(row, col, DOWN_RIGHT) + 1 >= connect_num)
            return true;
            
        return false;
    }

    bool game_tie() {
        return width == full_cols;
    }
    
    bool move(int col, int player) {
        if(col < 0 || col >= width)
            return false; // Invalid column

        int row = height - 1;

        // Find next open position in column
        while(row >= 0 and board[row][col] == EMPTY) {
            row--;
        }

        if(row == height - 1) // Column full
            return false;

        board[row + 1][col] = player; // Update board
        
        if(row == height - 2) // Track column being full
            full_cols++;

        return true;
    }



private:
    int width;
    int height;
    int connect_num;
    int full_cols;
    std::vector<std::vector<int>> board;

    Board(int width, int height, int connect_num)
        : width(width), height(height), connect_num(connect_num), board(height, std::vector<int>(width, 0))
    {
    }

    const bool in_bounds(int row, int col) {
        return row >= 0 && row < height && col >= 0 && col < width;
    }

    const void iterate_pos(int* row, int* col, const tuple<int, int>& step) {
        *row += std::get<0>(step);
        *col += std::get<1>(step);
    }

    const int count_from(int row, int col, const tuple<int, int>& step) {
        int token = board[row][col];

        if(token == EMPTY)
            return 0;

        int len = 0;
        iterate_pos(&row, &col, step);

        while(in_bounds(row, col) and board[row][col] == token) {
            len++;
            iterate_pos(&row, &col, step);
        }

        return len;
    }

};

std::ostream& operator<<(std::ostream& os, const Board& b) {
    for (const auto& row : b.board) {
        os << "|";
        for (const auto& val : row) {
            os << " " << val << " |";
        }
        os << "\n";
    }
    return os;
}