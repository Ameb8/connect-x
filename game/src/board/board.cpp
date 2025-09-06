#include <vector>
#include <memory>

constexpr int MIN_WIDTH = 3;
constexpr int MAX_WIDTH = 100;
constexpr int MIN_HEIGHT = 3;
constexpr int MAX_HEIGHT = 100;
constexpr int MIN_CONNECT_NUM = 3;
constexpr int MAX_CONNECT_NUM = 10;


class Board {
public:
    Board(int width, int height, int connect_num)
        : width(width), height(height), connect_num(connect_num), board(height, std::vector<int>(width, 0))
    {
    }

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

private:
    int width;
    int height;
    int connect_num;
    std::vector<std::vector<int>> board;

    Board(int width, int height, int connect_num)
        : width(width), height(height), connect_num(connect_num), board(height, std::vector<int>(width, 0))
    {
    }
};