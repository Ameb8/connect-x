#include "connect-x/board.h"

constexpr std::tuple<int, int> UP_RIGHT(-1, 1);
constexpr std::tuple<int, int> UP_LEFT(-1, -1);
constexpr std::tuple<int, int> DOWN_RIGHT(1, 1);
constexpr std::tuple<int, int> DOWN_LEFT(1, -1);
constexpr std::tuple<int, int> RIGHT(0, 1);
constexpr std::tuple<int, int> LEFT(0, -1);
constexpr std::tuple<int, int> UP(-1, 0);
constexpr std::tuple<int, int> DOWN(1, 0);

constexpr int EMPTY = 0;

Board::Board(int width, int height, int connect_num)
    : width(width), height(height), connect_num(connect_num), full_cols(0),
      piecesPlayed(0), board(height, std::vector<int>(width, EMPTY)) {}

bool Board::valid_dimensions(int width, int height, int connect_num) {
    if (width < MIN_WIDTH || width > MAX_WIDTH) return false;
    if (height < MIN_HEIGHT || height > MAX_HEIGHT) return false;
    if (connect_num < MIN_CONNECT_NUM || connect_num > MAX_CONNECT_NUM) return false;
    if (connect_num > width || connect_num > height) return false;
    return true;
}

std::unique_ptr<Board> Board::create(int width, int height, int connect_num) {
    if (!valid_dimensions(width, height, connect_num))
        return nullptr;
    return std::make_unique<Board>(width, height, connect_num);
}

int Board::getWidth() const { return width; }
int Board::getHeight() const { return height; }
int Board::getConnectNum() const { return connect_num; }

const std::vector<std::vector<int>> &Board::getBoard() const {
    return board;
}

int& Board::at(int row, int col) { return board.at(row).at(col); }
const int& Board::at(int row, int col) const { return board.at(row).at(col); }

int Board::gameWon(int row, int col) {
    if (
            count_from(row, col, LEFT) + count_from(row, col, RIGHT) + 1 >= connect_num ||
            count_from(row, col, UP) + count_from(row, col, DOWN) + 1 >= connect_num ||
            count_from(row, col, UP_RIGHT) + count_from(row, col, DOWN_LEFT) + 1 >= connect_num ||
            count_from(row, col, UP_LEFT) + count_from(row, col, DOWN_RIGHT) + 1 >= connect_num
        )
        return board[row][col];

    return EMPTY;
}

bool Board::gameTie() {
    return piecesPlayed == width * height;
}

int Board::move(int col, int player) {
    if (col < 0 || col >= width)
        return -1;

    for (int row = height - 1; row >= 0; --row) {
        if (board[row][col] == EMPTY) {
            board[row][col] = player;
            piecesPlayed++;

            // Update full_cols if column is now full
            if (row == 0)
                full_cols++;

            return row;
        }
    }

    // Column is full
    return -1;
}


bool Board::undoMove(int col) {
    if (col < 0 || col >= width)
        return false;

    for (int row = 0; row < height; ++row) {
        if (board[row][col] != EMPTY) {
            board[row][col] = EMPTY;
            piecesPlayed--;

            return true;
        }
    }

    return false;
}

bool Board::in_bounds(int row, int col) {
    return row >= 0 && row < height && col >= 0 && col < width;
}

void Board::iterate_pos(int* row, int* col, const std::tuple<int, int>& step) {
    *row += std::get<0>(step);
    *col += std::get<1>(step);
}

int Board::count_from(int row, int col, const std::tuple<int, int>& step) {
    int token = board[row][col];
    if (token == EMPTY) return 0;

    int len = 0;
    iterate_pos(&row, &col, step);

    while (in_bounds(row, col) && board[row][col] == token) {
        len++;
        iterate_pos(&row, &col, step);
    }

    return len;
}

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



void update_score(int len, bool both_sides, int dist_center, bool isMax);

int getRows(std::vector<std::vector<int>> board, int token);
int getCols(std::vector<std::vector<int>> board, int token);
int getDiagUp(std::vector<std::vector<int>> board, int token);
int getDiagDown(std::vector<std::vector<int>> board, int token);


std::pair<std::vector<int>, std::vector<int>> Board::get_groups(int token) {
    std::vector<int> player_groups;
    std::vector<int> other_groups;

    for (int i = 0; i < height; i++) {
        int last_token = EMPTY;
        int in_row = 0;

        for (int j = 0; j < width; j++) {
            if (board[i][j] != EMPTY && board[i][j] == last_token) { // Increment group length
                in_row++;
            } else {
                if (last_token == token)
                    player_groups.push_back(in_row);
                else if (last_token != EMPTY)
                    other_groups.push_back(in_row);

                in_row = 1;
                last_token = board[i][j];

            }
        }
    }


    return {player_groups, other_groups};
}
