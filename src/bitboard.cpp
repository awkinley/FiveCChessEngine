#include "bitboard.h"
#include "types.h"

Square pop(Bitboard *b)
{
    Square index = lsb(*b);
    *b ^= (uint64_t) 0x1 << (uint64_t) index;
    return index;
}

bool Bitboards::pieceAt(Bitboard b, File f, Rank r)
{
    return b & ((uint64_t) 0x1 << make_square(f, r));
}

const std::string Bitboards::pretty(Bitboard b)
{

    std::string s = "+---+---+---+---+---+---+---+---+\n";

    for (Rank r = RANK_8; r >= RANK_1; --r)
    {
        for (File f = FILE_A; f <= FILE_H; ++f)
            s += b & ((uint64_t) 0x1 << make_square(f, r)) ? "| X " : "|   ";

        s += "|\n+---+---+---+---+---+---+---+---+\n";
    }

    return s;
}

const std::string Bitboards::print(Bitboard b)
{
    std::string s = "";

    for (size_t i = 0; i < SQUARE_NB; i++)
    {
        if (b & ((uint64_t) 0x1 << (uint64_t) i))
        {
            s += "1";
        }
        else
        {
            s += "0";
        }
        if ((i + 1) % 8 == 0)
        {
            s += "\n";
        }
    }

    return s;
}