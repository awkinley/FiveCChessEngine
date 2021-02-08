// #ifndef TYPES_H
// #define TYPES_H
#pragma once

#include <cstdint>
#include <cassert>

typedef uint64_t Bitboard;
typedef int32_t Time;
typedef int32_t Universe;

enum BoardDimension : uint8_t
{ // since ONE will equal 0, we've got
    ONE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT
};




enum Color : int
{
    WHITE,
    BLACK
};



const int NUM_PIECE_TYPES = 12;
const int NUM_COLORS = 2;

const char PieceToChar[1 + 2 * NUM_PIECE_TYPES] = {' ', 'P', 'N', 'B', 'R', 'Q', 'K', 'U', 'D', 'B', 'C', 'Y', 'I',
                                                   'p', 'n', 'b', 'r', 'q', 'k', 'u', 'd', 'b', 'c', 'y', 'i'};

enum File : int
{
    FILE_A,
    FILE_B,
    FILE_C,
    FILE_D,
    FILE_E,
    FILE_F,
    FILE_G,
    FILE_H,
    FILE_NB
};

enum Rank : int
{
    RANK_1,
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_NB
};

#define BD_TO_R(bD) (Rank)((int)bD - 1)
#define BD_TO_F(bD) (File)((int)bD - 1)

enum Square : int
{
    SQ_A1,
    SQ_B1,
    SQ_C1,
    SQ_D1,
    SQ_E1,
    SQ_F1,
    SQ_G1,
    SQ_H1,
    SQ_A2,
    SQ_B2,
    SQ_C2,
    SQ_D2,
    SQ_E2,
    SQ_F2,
    SQ_G2,
    SQ_H2,
    SQ_A3,
    SQ_B3,
    SQ_C3,
    SQ_D3,
    SQ_E3,
    SQ_F3,
    SQ_G3,
    SQ_H3,
    SQ_A4,
    SQ_B4,
    SQ_C4,
    SQ_D4,
    SQ_E4,
    SQ_F4,
    SQ_G4,
    SQ_H4,
    SQ_A5,
    SQ_B5,
    SQ_C5,
    SQ_D5,
    SQ_E5,
    SQ_F5,
    SQ_G5,
    SQ_H5,
    SQ_A6,
    SQ_B6,
    SQ_C6,
    SQ_D6,
    SQ_E6,
    SQ_F6,
    SQ_G6,
    SQ_H6,
    SQ_A7,
    SQ_B7,
    SQ_C7,
    SQ_D7,
    SQ_E7,
    SQ_F7,
    SQ_G7,
    SQ_H7,
    SQ_A8,
    SQ_B8,
    SQ_C8,
    SQ_D8,
    SQ_E8,
    SQ_F8,
    SQ_G8,
    SQ_H8,
    SQ_NONE,

    SQUARE_ZERO = 0,
    SQUARE_NB = 64
};

constexpr Rank square_to_rank(Square s) {
    return (Rank) ((int)s >> 3);
}

constexpr File square_to_file(Square s) {
    return (File) ((int)s % 8);
}

inline Square &operator++(Square &d) { return d = Square(int(d) + 1); }
inline Square &operator--(Square &d) { return d = Square(int(d) - 1); }

constexpr Square make_square(File f, Rank r)
{
    return Square((r << 3) + f);
}

#define ENABLE_INCR_OPERATORS_ON(T)                          \
    inline T &operator++(T &d) { return d = T(int(d) + 1); } \
    inline T &operator--(T &d) { return d = T(int(d) - 1); }

ENABLE_INCR_OPERATORS_ON(File)
ENABLE_INCR_OPERATORS_ON(Rank)
// ENABLE_INCR_OPERATORS_ON(Square)

#undef ENABLE_INCR_OPERATORS_ON

// #endif // TYPES_H