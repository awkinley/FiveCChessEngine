#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <algorithm>

#include "types.h"

#include "bitboard.h"
#include "debugutils.h"
#include "pieces.h"

 
template <BoardDimension width, BoardDimension height>
class Board
{
public:
    Board();
    Board(Universe, Time, Color);

    void setPieces(Piece[width * height]);
    Piece pieceOn(Square) const;
    std::string print();

    Square getSquare(File, Rank);

    BoardDimension getDistance(Square s1, Square s2);
    bool onBoard(Square s);

    void setColor(Color);
    Color getColor();
    Time boardTime;
    Universe boardUniverse;

    Piece pieces[width * height];
    Bitboard bb_byPiece[NUM_PIECE_TYPES];
    Bitboard bb_byColor[NUM_COLORS];
    Bitboard bb_onBoard;

    uint8_t distance[SQUARE_NB][SQUARE_NB];

    Color playerToMove;

private:
    void init();
    void calculateDistances();
    void calculatePieceBitboards();
    void calculateColorBitboards();
};

template <BoardDimension width, BoardDimension height>
Board<width, height>::Board()
{
    this->init();
}

template <BoardDimension width, BoardDimension height>
void Board<width, height>::init()
{
    for (size_t i = 0; i < NUM_PIECE_TYPES; i++)
    {
        bb_byPiece[i] = Bitboard(0);
    }
    for (size_t i = 0; i < NUM_COLORS; i++)
    {
        bb_byColor[i] = Bitboard(0);
    }

    bb_onBoard = Bitboard(0);
    for (Square s = SQ_A1; s < SQUARE_NB; ++s)
    {
        if(this->onBoard(s))
        {
            bb_onBoard |= (uint64_t) 0x1 << (uint64_t)s;
        }
    }
    
    calculateDistances();
}

template <BoardDimension width, BoardDimension height>
void Board<width, height>::calculateDistances()
{
    for (Square s1 = SQ_A1; s1 < SQUARE_NB; ++s1)
    {
        for (Square s2 = SQ_A1; s2 < SQUARE_NB; ++s2)
        {
            if (onBoard(s1) && onBoard(s2))
            {
                uint8_t row1 = (int)s1 / 8;
                uint8_t row2 = (int)s2 / 8;
                uint8_t col1 = (int)s1 % 7;
                uint8_t col2 = (int)s2 % 7;

                distance[s1][s2] = std::max(std::abs(row1-row2), std::abs(col1 - col2));
            }
            else
            {
                distance[s1][s2] =0xFF;
            }
            
        }
    }
}

template <BoardDimension width, BoardDimension height>
bool Board<width, height>::onBoard(Square s)
{
    return (s % 8 < width && s / 8 < height);
}

template <BoardDimension width, BoardDimension height>
Board<width, height>::Board(Universe u, Time t, Color plyr)
{
    this->boardUniverse = u;
    this->boardTime = t;
    this->playerToMove = plyr;

    this->init();
}

template <BoardDimension width, BoardDimension height>
void Board<width, height>::setPieces(Piece pieces[width * height])
{
    for (Square s = SQ_A1; s < width * height; ++s)
    {
        this->pieces[s] = pieces[s];
    }

    this->calculateColorBitboards();
    this->calculatePieceBitboards();
}

template <BoardDimension width, BoardDimension height>
Piece Board<width, height>::pieceOn(Square s) const
{
    return this->pieces[s];
}

template <BoardDimension width, BoardDimension height>
Square Board<width, height>::getSquare(File f, Rank r)
{
    return (Square)(r * (int)width + f);
}

template <BoardDimension width, BoardDimension height>
void Board<width, height>::calculatePieceBitboards()
{
    Rank startingRank = BD_TO_R(height);
    File endingFile = BD_TO_F(width);
    for (Rank r = startingRank; r >= RANK_1; --r)
    {
        for (File f = FILE_A; f <= endingFile; ++f)
        {
            Piece p = this->pieceOn(this->getSquare(f, r));

            if (p != NO_PIECE)
            {
                PieceType pT = pieceToPieceType(p);
                bb_byPiece[pT] |= (uint64_t)0x1 << make_square(f, r);
            }
        }
    }
    // std::cout<<"pieces bitboards:" << std::endl;
    // for (size_t i = 0; i < NUM_PIECE_TYPES; i++)
    // {
    //     std::cout << Bitboards::pretty(bb_byPiece[i]) << std::endl << std::endl;
    // }
}

template <BoardDimension width, BoardDimension height>
void Board<width, height>::calculateColorBitboards()
{
    Rank startingRank = BD_TO_R(height);
    File endingFile = BD_TO_F(width);
    for (Rank r = startingRank; r >= RANK_1; --r)
    {
        for (File f = FILE_A; f <= endingFile; ++f)
        {
            Piece p = this->pieceOn(this->getSquare(f, r));

            if (p != NO_PIECE)
            {
                Color c = pieceToColor(p);
                bb_byColor[c] |= (uint64_t)0x1 << make_square(f, r);
            }
        }
    }

    // std::cout<<"color bitboards:" << std::endl;
    // for (size_t i = 0; i < NUM_COLORS; i++)
    // {
    //     std::cout << Bitboards::pretty(this->bb_byColor[i]);
    // }
}

template <BoardDimension width, BoardDimension height>
void Board<width, height>::setColor(Color c) 
{
    this->playerToMove = c;
}
template <BoardDimension width, BoardDimension height>
Color Board<width, height>::getColor() 
{
    return this->playerToMove;
}

template <BoardDimension width, BoardDimension height>
std::string Board<width, height>::print()
{
    std::string s = rankSeperator(width); // "\n +---+---+---+---+---+---+---+---+\n";
    Rank startingRank = BD_TO_R(height);
    File endingFile = BD_TO_F(width);
    for (Rank r = startingRank; r >= RANK_1; --r)
    {
        for (File f = FILE_A; f <= endingFile; ++f)
        {
            s += " | ";
            s += PieceToChar[this->pieceOn(this->getSquare(f, r))];
        }

        s += " | " + std::to_string(1 + r) + rankSeperator(width); //"\n +---+---+---+---+---+---+---+---+\n";
    }
    s += fileLetters(width); //n  "   a   b   c   d   e   f   g   h\n";

    return s;
}

#endif // BOARD_H