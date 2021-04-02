#include <bitset>

#ifndef SUDOKU
#define SUDOKU

template <int N>
class Sudoku
{
private:
    std::bitset<N * N> values[N * N * N * N];

public:
    Sudoku(std::bitset<N * N> initial);

    Sudoku();

    std::bitset<N * N> &operator[](int index);

    std::bitset<N * N> operator[](int index) const;
};

template <int S>
bool determined(const std::bitset<S> &square);

template <int S>
bool consistend(const std::bitset<S> &square);

template <int N>
bool consistend(const Sudoku<N> &sudoku);

template <int N>
bool apply_horiziontal(Sudoku<N> &sudoku);

template <int N>
bool apply_vertical(Sudoku<N> &sudoku);

template <int N>
bool apply_cell(Sudoku<N> &sudoku);

template <int N>
bool apply_sudoku(Sudoku<N> &sudoku);

template <int N>
bool solve_sudoku(Sudoku<N> sudoku, Sudoku<N> *out_sudoku = std::nullptr_t());

#include "sudoku.cpp"
#endif