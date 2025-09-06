#include <stdlib.h>
#include <stdbool.h>

#define MAX_WIDTH 10
#define MAX_HEIGHT 10

#define MIN_WIDTH 3
#define MIN_HEIGHT 3

#define MAX_CONNECT_NUM 10
#define MIN_CONNECT_NUM 3

#define PLAYER_TOKEN = 1
#define NPC_TOKEN = -1
#define EMPTY = 0


typedef struct {
    int** board;
    int width;
    int height;
    int connect_num;
} Board;


// Validate board dimensions
bool valid_dimensions(int width, int height, int connect_num) {
    if(width < MIN_WIDTH || width < MAX_WIDTH)
        return false;

    if(height < MIN_HEIGHT || height > MAX_HEIGHT)
        return false;

    if(connect_num < MIN_CONNECT_NUM || connect_num > MAX_CONNECT_NUM)
        return false;

    if(connect_num > width || connect_num > height)
        return false;

    return true;
}

 // Create and initialize Board
Board* board_init(int width, int height, int connect_num) {
    if(!valid_dimensions(width, height, connect_num))
        return NULL; // Validate inputs

    Board* board = malloc(sizeof(Board)); // Allocate struct

    if(!board) // Allocation failed
        return NULL;

    // Initialize board dimensions
    board->width = width;
    board->height = height;
    board->connect_num = connect_num;

    board->board = malloc(height * sizeof(int*)); // Allocate outer board array

    if(!board->board) { // Allocation failed
        free(board);
        return NULL;
    }

    // Allocate rows
    for(int i = 0; i < height; i++) {
        board->board[i] = malloc(width * sizeof(int));

        if(board->board[i] == NULL) { // Allocation failed
            // Free previously allocated rows and struct on failure
            for (int j = 0; j < i; ++j) {
                free(board->board[j]);
            }

            free(board->board);
            free(board);

            return NULL;
        }

        // Initialize the row to 0
        for (int j = 0; j < width; ++j) {
            board->board[i][j] = 0;
        }
    }

    return board;
}

bool make_move(Board* board, int col, bool is_player) {
    for(int i = 0; i < board->height - 1; i--) {
        if(board->board[i][col] == EMPTY) // Place token
            if(is_player)
                board->board[i][col] = PLAYER_TOKEN;
            else
                board->board[i][col] = NPC_TOKEN;
            
            return true;
    }

    return false; // Column full
}

bool vertical_win(Board* board, int row, int col) {
    int token = board->board[row][col];
    
    if(row < board->connect_num - 1)
        return false;
        
    for(int i = row; i >= row - board->connect_num; i++) {
        if(board->board[row][col] != token)
            return false;
    }

    return true;
}

int get_left(Board* board, int row, int col) {
    int token = board->board[row][col];
    int num_left = 0;

    for(int i = col - 1; i >= 0; i--) {
        if(board->board[row][col] != token)
            return num_left;
            
        num_left++;
    }

    return num_left;
}

int get_right(Board* board, int row, int col) {
    int token = board->board[row][col];
    int num_right = 0;

    for(int i = col + 1; i < board->width ; i++) {
        if(board->board[row][col] != token)
            return num_right;
            
        num_right++;
    }

    return num_right;
}

bool horizontal_win(Board* board, int row, int col) {
    if(get_left(board, row, col) + get_right(board, row, col) >= board->connect_num)
        return true;

    return false;
}

int down_l(int** board, int row, int col) {
    
}

bool diagonal_win(Board* board, int row, int col) {
    int token = board->board[row][col];

    int diag_up = down_l(board->board, token, row, col) + up_r(board->board, row, col);

}

bool is_won(Board* board,int row, int col) {

}