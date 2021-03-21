#include <iostream>
#include <bitset>
#include <cmath>

template <int N>
class Sudoku
{
private:
    std::bitset<N * N> values[N * N * N * N];

public:
    Sudoku(std::bitset<N * N> initial)
    {
        for (int i = 0; i != N * N * N * N; i++)
        {
            values[i] = initial;
        }
    }

    Sudoku()
    {
        for (int i = 0; i != N * N * N * N; i++)
        {
            values[i].set();
        }
    }

    std::bitset<N * N> &operator[](int index)
    {
        return values[index];
    }

    std::bitset<N * N> operator[](int index) const
    {
        return values[index];
    }
};

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
bool solve_sudoku(Sudoku<N> sudoku, Sudoku<N> *out_sudoku = std::nullptr_t())
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