#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Test program for sudoku generator
// Spencer Lommel
// Sept. 11th, 2024

int main() {
  srand(time(NULL));
  sudoku_board_t sudoku_board;

  sudoku_init(&sudoku_board);
  sudoku_generate_filled(&sudoku_board);

  for (int x = 0; x < 9; x++) {
    for (int y = 0; y < 9; y++) {
      printf("%d ", sudoku_board.board[x][y]);
    }
    printf("\n");
  }
}
