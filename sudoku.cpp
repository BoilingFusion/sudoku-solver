#include <iostream>
#include <bitset>
#include "sudoku.h"

template <int N>
Sudoku<N>::Sudoku(std::bitset<N * N> initial)
{
    for (int i = 0; i != N * N * N * N; i++)
    {
        values[i] = initial;
    }
}

template <int N>
Sudoku<N>::Sudoku()
{
    for (int i = 0; i != N * N * N * N; i++)
    {
        values[i].set();
    }
}

template <int N>
std::bitset<N * N> &Sudoku<N>::operator[](int index)
{
    return values[index];
}

template <int N>
std::bitset<N * N> Sudoku<N>::operator[](int index) const
{
    return values[index];
}

template <int S>
bool determined(const std::bitset<S> &square)
{
    return square.count() == 1;
}

template <int S>
bool consistend(const std::bitset<S> &square)
{
    return !square.none();
}

template <int N>
bool consistend(const Sudoku<N> &sudoku)
{
    for (int y = 0; y != N * N; y++)
    {
        for (int x = 0; x != N * N; x++)
        {
            if (!consistend<N>(sudoku[y * N * N + x]))
                return false;
        }
    }
    return true;
}

template <int N>
bool apply_horiziontal(Sudoku<N> &sudoku)
{
    bool applied = false;
    for (int y = 0; y != N * N; y++)
    {
        for (int x = 0; x != N * N; x++)
        {
            std::bitset<N *N> &square = sudoku[y * N * N + x];
            if (!determined<N * N>(square))
            {
                continue;
            }
            for (int i = 0; i != N * N; i++)
            {
                if (i == x)
                {
                    continue;
                }
                if (!applied && (sudoku[y * N * N + i] & square).any())
                    applied = true;
                sudoku[y * N * N + i] &= ~square;
            }
        }
    }
    return applied;
}

template <int N>
bool apply_vertical(Sudoku<N> &sudoku)
{
    bool applied = false;
    for (int y = 0; y != N * N; y++)
    {
        for (int x = 0; x != N * N; x++)
        {
            std::bitset<N *N> &square = sudoku[y * N * N + x];
            if (!determined<N * N>(square))
            {
                continue;
            }
            for (int i = 0; i != N * N; i++)
            {
                if (i == y)
                {
                    continue;
                }
                if (!applied && (sudoku[i * N * N + x] & square).any())
                    applied = true;
                sudoku[i * N * N + x] &= ~square;
            }
        }
    }
    return applied;
}

template <int N>
bool apply_cell(Sudoku<N> &sudoku)
{
    bool applied = false;
    for (int y = 0; y != N * N; y++)
    {
        for (int x = 0; x != N * N; x++)
        {
            std::bitset<N *N> &square = sudoku[y * N * N + x];
            int groupY = y / N;
            int groupX = x / N;
            if (!determined<N * N>(square))
            {
                continue;
            }

            for (int i = 0; i != N; i++)
            {
                for (int j = 0; j != N; j++)
                {
                    if ((groupY * N + i) == y && groupX * N + j == x)
                    {
                        continue;
                    }
                    if (!applied && (sudoku[(groupY * N + i) * N * N + groupX * N + j] & square).any())
                        applied = true;
                    sudoku[(groupY * N + i) * N * N + groupX * N + j] &= ~square;
                }
            }
        }
    }
    return applied;
}

template <int N>
bool apply_sudoku(Sudoku<N> &sudoku)
{
    bool applied = false;
    applied |= apply_cell(sudoku);
    applied |= apply_horiziontal(sudoku);
    applied |= apply_vertical(sudoku);
    return applied;
}

template <int N>
bool solve_sudoku(Sudoku<N> sudoku, Sudoku<N> *out_sudoku)
{
    bool solved = true;
    while (apply_sudoku<N>(sudoku))
    {
    }
    std::bitset<N *N> *candidate = std::nullptr_t();
    int candidate_index = -1;
    int candidate_count = N * N + 1;
    for (int y = 0; y != N * N; y++)
    {
        for (int x = 0; x != N * N; x++)
        {
            std::bitset<N *N> &square = sudoku[y * N * N + x];
            int square_count = square.count();
            if (square_count == 0)
            {
                return false;
            }
            if (square_count > 1 && square_count < candidate_count)
            {
                candidate = &square;
                candidate_count = square.count();
                candidate_index = y * N * N + x;
                solved = false;
            }
        }
    }

    if (solved)
    {
        if (out_sudoku != std::nullptr_t())
            *out_sudoku = sudoku;
        return true;
    }
    for (int i = 0; i != N * N; i++)
    {
        if (candidate[i] == false)
        {
            continue;
        }
        std::bitset<N *N> attempt = std::bitset<N * N>();
        attempt.set(i);
        sudoku[candidate_index] = attempt;
        if (solve_sudoku<N>(sudoku, out_sudoku))
        {
            return true;
        }
    }
    return false;
}