#include "pieces.h"
#include "bitboard.h"

#include <cassert>
#include <iostream>
#include <tuple>

namespace MovementVectors
{
    Vec4 knightVec{2, 1, 0, 0};
    std::vector<Vec4> *const allKnightMoves = Vector4::getAllPermutations(knightVec);
    Vec4 rookVec{1, 0, 0, 0};
    std::vector<Vec4> *allRookVecs = Vector4::getAllPermutations(rookVec);
    Vec4 bishopVec{1, 1, 0, 0};
    std::vector<Vec4> *allBishopVecs = Vector4::getAllPermutations(bishopVec);
    Vec4 unicornVec{1, 1, 1, 0};
    std::vector<Vec4> *allUnicornVecs = Vector4::getAllPermutations(unicornVec);
    Vec4 dragonVec{1, 1, 1, 0};
    std::vector<Vec4> *allDragonVecs = Vector4::getAllPermutations(dragonVec);
} // namespace MovementVectors


std::vector<Vec4> *getPhysicalVectors(std::vector<Vec4> *vecs)
{
    std::vector<Vec4> *physicalVecs = new std::vector<Vec4>();

    for (auto v : *vecs)
    {
        if (v.t == 0 && v.u == 0)
        {
            physicalVecs->push_back(v);
        }
    }

    return physicalVecs;
}

std::vector<Vec4> *getSuperPhysicalVectors(std::vector<Vec4> *vecs)
{
    std::vector<Vec4> *superPhysicalVecs = new std::vector<Vec4>();

    for (auto v : *vecs)
    {
        if (v.t != 0 || v.u != 0)
        {
            superPhysicalVecs->push_back(v);
        }
    }

    return superPhysicalVecs;
}
bool onBitboard(Rank r, File f)
{
    return (r >= RANK_1 && r <= RANK_8 && f >= FILE_A && f <= FILE_H);
}

Bitboard getPhysicalKnightMoves(Square s, Bitboard usPieces)
{
    Rank r = square_to_rank(s);
    File f = square_to_file(s);

    auto physicalMoves = getPhysicalVectors(MovementVectors::allKnightMoves);

    Bitboard b = Bitboard(0);

    for (auto v : *physicalMoves)
    {
        Rank newRank = (Rank)((int)r + v.x);
        File newFile = (File)((int)f + v.y);
        if (onBitboard(newRank, newFile) && !Bitboards::pieceAt(usPieces, newFile, newRank))
        {
            b |= (uint64_t)0x1 << (uint64_t)make_square(newFile, newRank);
        }
    }

    return b;
}

Bitboard getPhysicalBishopMoves(Square s, Bitboard usPieces, Bitboard themPieces)
{
    Rank r = square_to_rank(s);
    File f = square_to_file(s);

    Bitboard b = Bitboard(0);

    auto physicalMoves = getPhysicalVectors(MovementVectors::allBishopVecs);

    for (auto v : *physicalMoves)
    {
        Rank newRank = (Rank)((int)r + v.x);
        File newFile = (File)((int)f + v.y);
        while (onBitboard(newRank, newFile) && !Bitboards::pieceAt(usPieces, newFile, newRank))
        {
            b |= (uint64_t)0x1 << (uint64_t)make_square(newFile, newRank);
            if (Bitboards::pieceAt(themPieces, newFile, newRank))
            {
                break;
            }
            newRank = (Rank)((int)newRank + v.x);
            newFile = (File)((int)newFile + v.y);
        }
    }

    return b;
}

Bitboard getPhysicalRookMoves(Square s, Bitboard usPieces, Bitboard themPieces)
{
    Rank r = square_to_rank(s);
    File f = square_to_file(s);

    Bitboard b = Bitboard(0);

    auto physicalMoves = getPhysicalVectors(MovementVectors::allRookVecs);

    for (auto v : *physicalMoves)
    {
        Rank newRank = (Rank)((int)r + v.x);
        File newFile = (File)((int)f + v.y);
        while (onBitboard(newRank, newFile) && !Bitboards::pieceAt(usPieces, newFile, newRank))
        {
            b |= (uint64_t)0x1 << (uint64_t)make_square(newFile, newRank);
            if (Bitboards::pieceAt(themPieces, newFile, newRank))
            {
                break;
            }
            newRank = (Rank)((int)newRank + v.x);
            newFile = (File)((int)newFile + v.y);
        }
    }

    return b;
}

Bitboard getPhysicalQueenMoves(Square s, Bitboard usPieces, Bitboard themPieces)
{
    // TODO: add unicorn and dragon
    return getPhysicalRookMoves(s, usPieces, themPieces) | getPhysicalBishopMoves(s, usPieces, themPieces);
}

Bitboard getPhysicalKingMoves(Square s, Bitboard usPieces, Bitboard themPieces)
{
    Rank r = square_to_rank(s);
    File f = square_to_file(s);

    Bitboard b = Bitboard(0);

    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }

            Rank newR = (Rank)((int)r + i);
            File newF = (File)((int)f + j);
            if (onBitboard(newR, newF) && !Bitboards::pieceAt(usPieces, newF, newR) && !Bitboards::pieceAt(themPieces, newF, newR))
            {
                b |= (uint64_t)0x1 << (uint64_t)make_square(newF, newR);
            }
        }
    }

    return b;
}

/**
 * Provides a general way to get the moves for a specific piece on a specific square
 * Just calls the appropriate specific method, with the appropriate parameters
 * usPieces and themPieces are used to eliminate moves that are blocked
 */
Bitboard Pieces::getPhysicalMoveBitboard(PieceType pT, Square s, Bitboard usPieces, Bitboard themPieces)
{
    switch (pT)
    {
    case KNIGHT:
        return getPhysicalKnightMoves(s, usPieces);
    case BISHOP:
        return getPhysicalBishopMoves(s, usPieces, themPieces);
    case ROOK:
        return getPhysicalRookMoves(s, usPieces, themPieces);
    case KING:
        return getPhysicalKingMoves(s, usPieces, themPieces);
    case QUEEN:
        return getPhysicalQueenMoves(s, usPieces, themPieces);
    default:
        std::cout << "trying to get move bitboard for invalid piecetype" << std::endl;
        return Bitboard(0);
    }
}

/**
 * A gross way to go from Piece to PieceType
 */
PieceType pieceToPieceType(Piece p)
{
    assert(p != NO_PIECE);
    switch (p)
    {
    case W_PAWN:
        return PAWN;
    case W_KNIGHT:
        return KNIGHT;
    case W_BISHOP:
        return BISHOP;
    case W_ROOK:
        return ROOK;
    case W_QUEEN:
        return QUEEN;
    case W_KING:
        return KING;
    case W_UNICORN:
        return UNICORN;
    case W_DRAGON:
        return DRAGON;
    case W_BRAWN:
        return BRAWN;
    case W_PRINCESS:
        return PRINCESS;
    case W_ROYAL_QUEEN:
        return ROYAL_QUEEN;
    case W_COMMON_KING:
        return COMMON_KING;
    case B_PAWN:
        return PAWN;
    case B_KNIGHT:
        return KNIGHT;
    case B_BISHOP:
        return BISHOP;
    case B_ROOK:
        return ROOK;
    case B_QUEEN:
        return QUEEN;
    case B_KING:
        return KING;
    case B_UNICORN:
        return UNICORN;
    case B_DRAGON:
        return DRAGON;
    case B_BRAWN:
        return BRAWN;
    case B_PRINCESS:
        return PRINCESS;
    case B_ROYAL_QUEEN:
        return ROYAL_QUEEN;
    case B_COMMON_KING:
        return COMMON_KING;
    default:
        return PAWN; // should never get here
    }
}

Color pieceToColor(Piece p)
{
    assert(p != NO_PIECE);
    if ((int)p < B_PAWN)
    {
        return WHITE;
    }

    return BLACK;
}