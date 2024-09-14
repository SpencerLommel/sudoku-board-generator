// sudoku.c
// Spencer Lommel
// Sept. 11th, 2024

// Cells go from 1-9 not 0-8!!

#include "sudoku.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

// Necessary so people can index this with the error value
// from their program to know what the issue is.
const char *sudoku_error_strings[] = {"NO_ERROR", "NULL_PTR_ERROR"};

// Header (public) methods
sudoku_error_t sudoku_init(sudoku_board_t *sudoku_board) {
  if (sudoku_board == NULL) {
    return NULL_PTR_ERROR;
  }
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      sudoku_board->board[j][i] = 0;
    }
  }
  return NO_ERROR;
}

sudoku_error_t sudoku_generate_filled(sudoku_board_t *sudoku_board) {
  for (int y = 0; y < 9; y++) {
    for (int x = 0; x < 9; x++) {
      sudoku_board->board[x][y];
    }
  }
}

// Static methods
static int get_box_value_from_cell(int cell) {
  // This takes in a cell and returns the first value in the box
  // Example: cell 5 is the second box (3x3) which starts at cell 4
  // so returns 4
  if (cell > 10 || cell < 1) {
    return -1;
  }
  int new_value;
  return new_value = (ceil(0.333 * cell) * 3) - 2;
}

int gen_random_with_exclusion_arr(int excluded[9]) {
  // Takes int[9] input in the format {1,1,0,0,0,0,0,0,0}
  // With the example array above it can return any value between 3-9 but not
  // 1,2 because they are excluded (denoted by 1) I know.. goofy syntax but it
  // works :P
  int excluded_amt = 0;
  int allowed_ints[9];

  for (int i = 0; i < 9; i++) {
    if (excluded[i] == 0) {
      allowed_ints[excluded_amt] = i + 1;
      excluded_amt++;
    }
  }
  if (excluded_amt == 0) {
    return -1;
  }

  int num = rand() % excluded_amt;
  return allowed_ints[num];
}

static bool valueinarray(float val, float *arr, size_t n) {
  for (size_t i = 0; i < n; i++) {
    if (arr[i] == val)
      return true;
  }
  return false;
}
