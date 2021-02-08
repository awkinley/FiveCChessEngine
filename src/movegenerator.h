#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#pragma once

#include <vector>

#include "types.h"
#include "board.h"
#include "pieces.h"
#include "move.h"
#include "bitboard.h"

template <Color c, BoardDimension w, BoardDimension h>
std::vector<Move> *generateAll(Board<w, h> *board)
{
    std::vector<Move> *moves = new std::vector<Move>();
    generateAllPhysical<c, w, h>(board, moves);
    generateAllSuperPhysical<c, w, h>(board, moves);

    return moves;
}

template <Color c, BoardDimension w, BoardDimension h>
void generateAllPhysical(Board<w, h> *board, std::vector<Move> *moves)
{
    generatePhysical<c, w, h, PAWN>(board, moves);
    generatePhysical<c, w, h, KNIGHT>(board, moves);
    generatePhysical<c, w, h, BISHOP>(board, moves);
    generatePhysical<c, w, h, ROOK>(board, moves);
    generatePhysical<c, w, h, QUEEN>(board, moves);
    generatePhysical<c, w, h, KING>(board, moves);
    generatePhysical<c, w, h, UNICORN>(board, moves);
    generatePhysical<c, w, h, DRAGON>(board, moves);
    generatePhysical<c, w, h, BRAWN>(board, moves);
    generatePhysical<c, w, h, PRINCESS>(board, moves);
    generatePhysical<c, w, h, ROYAL_QUEEN>(board, moves);
    generatePhysical<c, w, h, COMMON_KING>(board, moves);
}

template <Color c, BoardDimension w, BoardDimension h>
void generateAllSuperPhysical(Board<w, h> *board, std::vector<Move> *)
{
}

template <Color c, BoardDimension w, BoardDimension h, PieceType pieceType>
void generatePhysical(Board<w, h> *board, std::vector<Move> *moves)
{

    // anding bitmasks has the effect of creating a bitmask where the one's
    // correspond to places where there was a one on both bitmasks
    // so ourPieces is a bitmask of all the places that have our piece, and are the correct type
    // std::cout<<"bb by color: \n" << Bitboards::pretty( board->bb_byColor[c]);
    // std::cout<<"bb by piece: \n" << Bitboards::pretty( board->bb_byPiece[pieceType]);
    Bitboard ourPieces = board->bb_byColor[c] & board->bb_byPiece[pieceType];
    Color them = WHITE;
    if (c == WHITE)
    {
        them = BLACK;
    }
    // if we have no pieces of this type on the board, exist immediately
    if (!ourPieces)
    {
        return;
    }

    if (pieceType == PAWN)
    {
        // handle pawn seperately
        // TODO
        return;
    }

    // std::cout << "pieceType = " << pieceType << std::endl;

    // we pop out the 1 of the bitboard and get theri square, so while there are still any 1's in the bitboard
    while (ourPieces)
    {
        Square s = pop(&ourPieces);
        // std::cout << "square: " << s << std::endl;
        Bitboard possibleMoves = Pieces::getPhysicalMoveBitboard(pieceType, s, board->bb_byColor[c], board->bb_byColor[them]);
        // std::cout << "possible moves: " << std::endl
        //           << Bitboards::pretty(possibleMoves) << std::endl;
        Bitboard onBoardMoves = possibleMoves & board->bb_onBoard;
        // std::cout << "onboard bitboard: " << std::endl << Bitboards::pretty(board->bb_onBoard);
        // std::cout << "on board moves: " << std::endl
        //           << Bitboards::pretty(onBoardMoves) << std::endl;

        SuperPos startPos{board->boardUniverse, board->boardTime, s};

        while (onBoardMoves)
        {
            Square target = pop(&onBoardMoves);
            SuperPos endPos{board->boardUniverse, board->boardTime, target};
            Move m;
            m.startPos = startPos;
            m.endPos = endPos;
            moves->push_back(m);
        }
        // break;
    }
}

template <Color c, BoardDimension w, BoardDimension h, PieceType p>
void generateSuperPhysical(Board<w, h> *, std::vector<Move> *)
{
}
#endif // MOVEGENERATOR