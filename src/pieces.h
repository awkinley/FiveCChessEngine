#ifndef PIECES_H
#define PIECES_H

#pragma once

#include <vector>

#include "types.h"
#include "move.h"
#include "vec4.h"

enum PieceType : int
{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    UNICORN,
    DRAGON,
    BRAWN,
    PRINCESS,
    ROYAL_QUEEN,
    COMMON_KING
};


enum Piece : int
{
    NO_PIECE,
    W_PAWN,
    W_KNIGHT,
    W_BISHOP,
    W_ROOK,
    W_QUEEN,
    W_KING,
    W_UNICORN,
    W_DRAGON,
    W_BRAWN,
    W_PRINCESS,
    W_ROYAL_QUEEN,
    W_COMMON_KING,
    B_PAWN,
    B_KNIGHT,
    B_BISHOP,
    B_ROOK,
    B_QUEEN,
    B_KING,
    B_UNICORN,
    B_DRAGON,
    B_BRAWN,
    B_PRINCESS,
    B_ROYAL_QUEEN,
    B_COMMON_KING,
};

namespace Pieces {
    
    Bitboard getPhysicalMoveBitboard(PieceType, Square, Bitboard, Bitboard);
}
PieceType pieceToPieceType(Piece p);
Color pieceToColor(Piece p);

#endif // PIECES_H