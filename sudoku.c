// sudoku.c
// Spencer Lommel
// Sept. 11th, 2024

// Cells go from 1-9 not 0-8!!

#include "sudoku.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

static int gen_random_with_exclusion_arr(uint8_t excluded[9]);
static uint8_t get_box_value_from_cell(uint8_t cell);
static void combine_arr(uint8_t arr1[9], uint8_t arr2[9], uint8_t result[9],
                        int *result_size);
static void allowed_values(sudoku_board_t *sudoku_board, uint8_t x, uint8_t y,
                           uint8_t result[9], int *result_size);

// Necessary so people can index this with the error value
// from their program to know what the issue is.
const char *sudoku_error_strings[] = {"NO_ERROR", "NULL_PTR_ERROR"};

typedef enum { ROW = 0, COLUMN, BOX } sudoku_section_t;

// Header methods
sudoku_error_t sudoku_init(sudoku_board_t *sudoku_board) {
  if (sudoku_board == NULL) {
    return NULL_PTR_ERROR;
  }
  for (uint8_t i = 0; i < 9; i++) {
    for (uint8_t j = 0; j < 9; j++) {
      sudoku_board->board[j][i] = 0;
    }
  }
  return NO_ERROR;
}

sudoku_error_t sudoku_generate_filled(sudoku_board_t *sudoku_board) {
  uint8_t allowed[9] = {0}; // Array to hold allowed values for each cell
  int allowed_size = 0;

  for (uint8_t y = 0; y < 9; y++) {
    for (uint8_t x = 0; x < 9; x++) {
      allowed_values(sudoku_board, x, y, allowed, &allowed_size);

      if (allowed_size == 0) {
        return NO_ERROR;
      }

      uint8_t excl_arr[9] = {1};
      for (int i = 0; i < allowed_size; i++) {
        excl_arr[allowed[i] - 1] = 0; // Mark allowed values as not excluded
      }

      int random_value = gen_random_with_exclusion_arr(excl_arr);
      if (random_value == -1) {
        // Failed to generate a valid number, Sudoku generation failed
        return NO_ERROR; // replace later with better error value
      }

      sudoku_board->board[x][y] = random_value;
    }
  }

  return NO_ERROR;
}

// Static methods
static uint8_t get_box_value_from_cell(uint8_t cell) {
  // This takes in a cell and returns the first value in the box
  // Example: cell 5 is the second box (3x3) which starts at cell 4
  // so returns 4
  if (cell > 10 || cell < 1) {
    return -1;
  }
  int new_value;
  return new_value = (ceil(0.333 * cell) * 3) - 2;
}

int gen_random_with_exclusion_arr(uint8_t excluded[9]) {
  // Takes int[9] input in the format {1,1,0,0,0,0,0,0,0}
  // With the example array above it can return any value between 3-9 but not
  // 1,2 because they are excluded (denoted by 1) I know.. goofy syntax but it
  // works :P
  int excluded_amt = 0;
  int allowed_ints[9];

  for (uint8_t i = 0; i < 9; i++) {
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

static void get_int_arr_of_section(sudoku_board_t *sudoku_board,
                                   sudoku_section_t section, uint8_t x,
                                   uint8_t y, uint8_t section_values[9]) {
  // Must pass array of size 9 in section_values. This is okay because in
  // columns, rows, and boxes there can only be 9 nums at most
  if (section == ROW) {
    for (uint8_t i = 0; i < 9; i++) {
      section_values[i] = sudoku_board->board[i][y];
    }
  }
  if (section == COLUMN) {
    for (uint8_t i = 0; i < 9; i++) {
      section_values[i] = sudoku_board->board[x][i];
    }
  }
  if (section == BOX) {
    for (uint8_t i = get_box_value_from_cell(x); i < 3; i++) {
      for (uint8_t k = get_box_value_from_cell(y); k < 3; k++) {
        section_values[i + k] = sudoku_board->board[i][k];
      }
    }
  }
}

static void combine_arr(uint8_t arr1[9], uint8_t arr2[9], uint8_t result[9],
                        int *result_size) {
  bool seen[10] = {false};
  int index = 0;

  for (int i = 0; i < 9; i++) {
    if (arr1[i] >= 1 && arr1[i] <= 9 && !seen[arr1[i]]) {
      seen[arr1[i]] = true;
      result[index++] = arr1[i];
    }
    if (arr2[i] >= 1 && arr2[i] <= 9 && !seen[arr2[i]]) {
      seen[arr2[i]] = true;
      result[index++] = arr2[i];
    }
  }

  *result_size = index;
}

static void allowed_values(sudoku_board_t *sudoku_board, uint8_t x, uint8_t y,
                           uint8_t result[9], int *result_size) {
  uint8_t row_values[9] = {0};
  uint8_t col_values[9] = {0};
  uint8_t box_values[9] = {0};

  get_int_arr_of_section(sudoku_board, ROW, x, y, row_values);
  get_int_arr_of_section(sudoku_board, COLUMN, x, y, col_values);
  get_int_arr_of_section(sudoku_board, BOX, x, y, box_values);

  uint8_t combined_values[9] = {0};
  int combined_size = 0;
  combine_arr(row_values, col_values, combined_values, &combined_size);

  uint8_t temp_result[9] = {0};
  int temp_size = 0;
  combine_arr(combined_values, box_values, temp_result, &temp_size);

  bool seen[10] = {false};
  for (int i = 0; i < temp_size; i++) {
    if (temp_result[i] >= 1 && temp_result[i] <= 9) {
      seen[temp_result[i]] = true;
    }
  }

  // Fill result with allowed numbers
  int index = 0;
  for (uint8_t num = 1; num <= 9; num++) {
    if (!seen[num]) {
      result[index++] = num;
    }
  }

  *result_size = index;
}
