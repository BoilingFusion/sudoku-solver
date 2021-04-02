#include "sudoku.h"
#include <bitset>

#ifndef SUDOKUIO
#define SUDOKUIO

template <int N>
void print_sudoku(Sudoku<N> sudoku);

template <int S>
void nice_print_square(std::bitset<S> square);

template <int N>
void nice_print_sudoku(Sudoku<N> sudoku);

template <int S>
std::bitset<S> decimal_to_bitset(int decimal);

#include "sudokuio.cpp"
#endif