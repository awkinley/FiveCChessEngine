// #include <vector>
#include "gtest/gtest.h"

#include "position.h"
#include "movegenerator.h"
// #include "Board.h"


Piece testKnightSimple[5 * 5] = {NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, 
                             NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, 
                            NO_PIECE, NO_PIECE, W_KNIGHT, NO_PIECE, NO_PIECE, 
                            NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, 
                            NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE};

Piece testBishopSimple[5 * 5] = {NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, 
                             NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, 
                            NO_PIECE, NO_PIECE, W_BISHOP, NO_PIECE, NO_PIECE, 
                            NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, 
                            NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE};

Piece testRookSimple[5 * 5] = {NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, 
                             NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, 
                            NO_PIECE, NO_PIECE, W_ROOK, NO_PIECE, NO_PIECE, 
                            NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, 
                            NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE};

Piece testKingSimple[5 * 5] = {NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, 
                             NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, 
                            NO_PIECE, NO_PIECE, W_KING, NO_PIECE, NO_PIECE, 
                            NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, 
                            NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE};
TEST(MoveGenTest, knightSimple)
{
    Board<FIVE, FIVE>* b = new Board<FIVE, FIVE>(0, 1, WHITE);
    b->setPieces(testKnightSimple);
    std::vector<Move>* moves = generateAll<WHITE, FIVE, FIVE>(b);

    EXPECT_EQ(moves->size(), 8);
}

// TEST(MoveGenTest, bishopSimple)
// {
//     Board<FIVE, FIVE>* b = new Board<FIVE, FIVE>(0, 1, WHITE);
//     b->setPieces(testBishopSimple);
//     std::vector<Move>* moves = generateAll<WHITE, FIVE, FIVE>(b);

//     EXPECT_EQ(moves->size(), 8);
// }

// TEST(MoveGenTest, rookSimple)
// {
//     Board<FIVE, FIVE>* b = new Board<FIVE, FIVE>(0, 1, WHITE);
//     b->setPieces(testRookSimple);
//     std::vector<Move>* moves = generateAll<WHITE, FIVE, FIVE>(b);

//     EXPECT_EQ(moves->size(), 8);
// }

// TEST(MoveGenTest, kingSimple)
// {
//     Board<FIVE, FIVE>* b = new Board<FIVE, FIVE>(0, 1, WHITE);
//     b->setPieces(testKingSimple);
//     std::vector<Move>* moves = generateAll<WHITE, FIVE, FIVE>(b);

//     EXPECT_EQ(moves->size(), 8);
// }