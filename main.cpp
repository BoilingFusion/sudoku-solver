#include <iostream>
#include <bitset>
#include "sudoku.h"
#include "sudokuio.h"

int main()
{
    Sudoku<3> veronica = Sudoku<3>();
    veronica[0 * 9 + 1] = decimal_to_bitset<3 * 3>(4);
    veronica[0 * 9 + 8] = decimal_to_bitset<3 * 3>(9);
    veronica[1 * 9 + 1] = decimal_to_bitset<3 * 3>(6);
    veronica[1 * 9 + 2] = decimal_to_bitset<3 * 3>(2);
    veronica[1 * 9 + 3] = decimal_to_bitset<3 * 3>(9);
    veronica[1 * 9 + 8] = decimal_to_bitset<3 * 3>(8);
    veronica[2 * 9 + 1] = decimal_to_bitset<3 * 3>(9);
    veronica[2 * 9 + 2] = decimal_to_bitset<3 * 3>(7);
    veronica[2 * 9 + 4] = decimal_to_bitset<3 * 3>(3);
    veronica[2 * 9 + 6] = decimal_to_bitset<3 * 3>(6);
    veronica[3 * 9 + 3] = decimal_to_bitset<3 * 3>(3);
    veronica[4 * 9 + 6] = decimal_to_bitset<3 * 3>(3);
    veronica[4 * 9 + 7] = decimal_to_bitset<3 * 3>(1);
    veronica[4 * 9 + 8] = decimal_to_bitset<3 * 3>(6);
    veronica[5 * 9 + 4] = decimal_to_bitset<3 * 3>(4);
    veronica[5 * 9 + 5] = decimal_to_bitset<3 * 3>(8);
    veronica[6 * 9 + 0] = decimal_to_bitset<3 * 3>(1);
    veronica[6 * 9 + 3] = decimal_to_bitset<3 * 3>(5);
    veronica[6 * 9 + 7] = decimal_to_bitset<3 * 3>(6);
    veronica[7 * 9 + 3] = decimal_to_bitset<3 * 3>(6);
    veronica[7 * 9 + 5] = decimal_to_bitset<3 * 3>(4);
    veronica[7 * 9 + 7] = decimal_to_bitset<3 * 3>(9);
    veronica[7 * 9 + 8] = decimal_to_bitset<3 * 3>(1);
    veronica[8 * 9 + 3] = decimal_to_bitset<3 * 3>(1);
    veronica[8 * 9 + 6] = decimal_to_bitset<3 * 3>(2);
    veronica[8 * 9 + 8] = decimal_to_bitset<3 * 3>(7);

    std::cout << "Trying to solve veronica Sudoku:" << std::endl;
    nice_print_sudoku(veronica);

    if (solve_sudoku(veronica, &veronica))
    {
        std::cout << "Veronica Sudoku solved!" << std::endl;
        std::cout << "That was eazy =)" << std::endl;
        nice_print_sudoku(veronica);
        std::cout << "The awnser is:" << std::endl;
        std::cout << "[";
        nice_print_square<9>(veronica[3 * 9 + 7]);
        std::cout << ", ";
        nice_print_square<9>(veronica[7 * 9 + 2]);
        std::cout << "]" << std::endl;
    }
    else
    {
        std::cout << "Veronica Sudoku is not solvable!" << std::endl;
        std::cout << "What an amatures" << std::endl;
    }

    Sudoku<3> s = Sudoku<3>();
    s[9 * 2 + 3] = std::bitset<9>(1);
    std::cout << "Trying to solve:" << std::endl;
    nice_print_sudoku(s);
    if (solve_sudoku<3>(s, &s))
    {
        std::cout << "Sudoku is solved!" << std::endl;
        nice_print_sudoku(s);
    }
    else
    {
        std::cout << "Sudoku cannot be solved =(" << std::endl;
    }

    Sudoku<4> s2 = Sudoku<4>();
    s2[1] = std::bitset<4 * 4>(1);
    std::cout << "Trying to solve:" << std::endl;
    nice_print_sudoku(s2);
    if (solve_sudoku<4>(s2, &s2))
    {
        std::cout << "Sudoku is solved!" << std::endl;
        nice_print_sudoku(s2);
    }
    else
    {
        std::cout << "Sudoku cannot be solved =(" << std::endl;
    }

    Sudoku<5> s3 = Sudoku<5>();
    s3[1] = std::bitset<5 * 5>(1);
    std::cout << "Trying to solve:" << std::endl;
    nice_print_sudoku(s3);
    if (solve_sudoku<5>(s3, &s3))
    {
        std::cout << "Sudoku is solved!" << std::endl;
        nice_print_sudoku(s3);
    }
    else
    {
        std::cout << "Sudoku cannot be solved =(" << std::endl;
    }
    std::cout << "Done" << std::endl;
    return 0;
}