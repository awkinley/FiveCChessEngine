#ifndef BITBOARD_H
#define BITBOARD_H

#include <string>

#include "types.h"

namespace Bitboards
{
    const std::string pretty(Bitboard b);
    const std::string print(Bitboard b);
    bool pieceAt(Bitboard, File f, Rank r);
}

constexpr Bitboard AllSquares = ~Bitboard(0);
constexpr Bitboard DarkSquares = 0xAA55AA55AA55AA55ULL;

constexpr Bitboard FileABB = 0x0101010101010101ULL;
constexpr Bitboard FileBBB = FileABB << 1;
constexpr Bitboard FileCBB = FileABB << 2;
constexpr Bitboard FileDBB = FileABB << 3;
constexpr Bitboard FileEBB = FileABB << 4;
constexpr Bitboard FileFBB = FileABB << 5;
constexpr Bitboard FileGBB = FileABB << 6;
constexpr Bitboard FileHBB = FileABB << 7;

constexpr Bitboard Rank1BB = 0xFF;
constexpr Bitboard Rank2BB = Rank1BB << (8 * 1);
constexpr Bitboard Rank3BB = Rank1BB << (8 * 2);
constexpr Bitboard Rank4BB = Rank1BB << (8 * 3);
constexpr Bitboard Rank5BB = Rank1BB << (8 * 4);
constexpr Bitboard Rank6BB = Rank1BB << (8 * 5);
constexpr Bitboard Rank7BB = Rank1BB << (8 * 6);
constexpr Bitboard Rank8BB = Rank1BB << (8 * 7);



#if _WIN64
// msvc defitions
#include <immintrin.h>

inline Square lsb(Bitboard b)
{
    unsigned long idx;
    _BitScanForward64(&idx, b);
    return (Square)idx;
}

inline Square msb(Bitboard b)
{
    unsigned long idx;
    _BitScanReverse64(&idx, b);
    return (Square)idx;
}

#endif

#if __GNUG__
// gcc c++ definitions

#endif

Square pop(Bitboard*);

#endif // #ifndef BITBOARD_H