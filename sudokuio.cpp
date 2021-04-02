#include <iostream>
#include "sudoku.h"
#include "sudokuio.h"
#include <bitset>

template <int N>
void print_sudoku(Sudoku<N> sudoku)
{
    for (int y = 0; y != N * N; y++)
    {
        for (int x = 0; x != N * N; x++)
        {
            std::cout << sudoku[y * N * N + x] << "|";
        }
        std::cout << std::endl;
    }
    for (int i = 0; i != N * N * N * N + N * N; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;
}

template <int S>
void nice_print_square(std::bitset<S> square);

template <>
void nice_print_square<9>(std::bitset<9> square)
{
    if (square == std::bitset<9>(1))
        std::cout << "1";
    else if (square == std::bitset<9>(2))
        std::cout << "2";
    else if (square == std::bitset<9>(4))
        std::cout << "3";
    else if (square == std::bitset<9>(8))
        std::cout << "4";
    else if (square == std::bitset<9>(16))
        std::cout << "5";
    else if (square == std::bitset<9>(32))
        std::cout << "6";
    else if (square == std::bitset<9>(64))
        std::cout << "7";
    else if (square == std::bitset<9>(128))
        std::cout << "8";
    else if (square == std::bitset<9>(256))
        std::cout << "9";
    else
        std::cout << " ";
}

template <>
void nice_print_square<16>(std::bitset<16> square)
{
    if (square == std::bitset<16>(1))
        std::cout << " 1";
    else if (square == std::bitset<16>(2))
        std::cout << " 2";
    else if (square == std::bitset<16>(4))
        std::cout << " 3";
    else if (square == std::bitset<16>(8))
        std::cout << " 4";
    else if (square == std::bitset<16>(16))
        std::cout << " 5";
    else if (square == std::bitset<16>(32))
        std::cout << " 6";
    else if (square == std::bitset<16>(64))
        std::cout << " 7";
    else if (square == std::bitset<16>(128))
        std::cout << " 8";
    else if (square == std::bitset<16>(256))
        std::cout << " 9";
    else if (square == std::bitset<16>(512))
        std::cout << "10";
    else if (square == std::bitset<16>(1024))
        std::cout << "11";
    else if (square == std::bitset<16>(2048))
        std::cout << "12";
    else if (square == std::bitset<16>(4096))
        std::cout << "13";
    else if (square == std::bitset<16>(8192))
        std::cout << "14";
    else if (square == std::bitset<16>(16384))
        std::cout << "15";
    else if (square == std::bitset<16>(32768))
        std::cout << "16";
    else
        std::cout << "  ";
}

template <>
void nice_print_square<25>(std::bitset<25> square)
{
    if (square == std::bitset<25>(1))
        std::cout << " 1";
    else if (square == std::bitset<25>(2))
        std::cout << " 2";
    else if (square == std::bitset<25>(4))
        std::cout << " 3";
    else if (square == std::bitset<25>(8))
        std::cout << " 4";
    else if (square == std::bitset<25>(16))
        std::cout << " 5";
    else if (square == std::bitset<25>(32))
        std::cout << " 6";
    else if (square == std::bitset<25>(64))
        std::cout << " 7";
    else if (square == std::bitset<25>(128))
        std::cout << " 8";
    else if (square == std::bitset<25>(256))
        std::cout << " 9";
    else if (square == std::bitset<25>(512))
        std::cout << "10";
    else if (square == std::bitset<25>(1024))
        std::cout << "11";
    else if (square == std::bitset<25>(2048))
        std::cout << "12";
    else if (square == std::bitset<25>(4096))
        std::cout << "13";
    else if (square == std::bitset<25>(8192))
        std::cout << "14";
    else if (square == std::bitset<25>(16384))
        std::cout << "15";
    else if (square == std::bitset<25>(32768))
        std::cout << "16";
    else if (square == std::bitset<25>(65536))
        std::cout << "17";
    else if (square == std::bitset<25>(131072))
        std::cout << "18";
    else if (square == std::bitset<25>(262144))
        std::cout << "19";
    else if (square == std::bitset<25>(524288))
        std::cout << "20";
    else if (square == std::bitset<25>(1048576))
        std::cout << "21";
    else if (square == std::bitset<25>(2097152))
        std::cout << "22";
    else if (square == std::bitset<25>(4194304))
        std::cout << "23";
    else if (square == std::bitset<25>(8388608))
        std::cout << "24";
    else if (square == std::bitset<25>(16777216))
        std::cout << "25";
    else
        std::cout << "  ";
}

template <int N>
void nice_print_sudoku(Sudoku<N> sudoku)
{
    for (int y = 0; y != N * N; y++)
    {
        std::cout << "|";
        for (int x = 0; x != N * N; x++)
        {
            nice_print_square<N * N>(sudoku[y * N * N + x]);
            std::cout << "|";
        }
        std::cout << std::endl;
    }
    int end_size = 2;
    if (N == 1 || N == 2 | N == 3)
        end_size = N * N * 2 + 1;
    if (N == 4 || N == 5)
        end_size = N * N * 3 + 1;

    for (int i = 0; i != end_size; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;
}

template <int S>
std::bitset<S> decimal_to_bitset(int decimal)
{
    int binairy = 1;
    binairy <<= decimal - 1;
    return std::bitset<S>(binairy);
}