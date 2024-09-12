// sudoku.h
// Spencer Lommel
// Sept. 11th, 2024

#ifndef SUDOKU_H
#define SUDOKU_H

typedef struct {
    int board[9][9];
} sudoku_board_t;

typedef enum {
    NO_ERROR = 0,
    NULL_PTR_ERROR
} sudoku_error_t;

typedef enum {
    EASY = 0,
    MEDIUM,
    HARD
} sudoku_difficulty_t;

sudoku_error_t sudoku_init(sudoku_board_t* sudoku_board);
sudoku_error_t sudoku_generate_filled(sudoku_board_t* sudoku_board);
sudoku_error_t sudoku_unfill(sudoku_board_t* sudoku_board, sudoku_difficulty_t difficulty);

#endif
