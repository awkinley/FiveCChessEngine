#include <iostream>

#include "board.h"

#include "gtest/gtest.h"

class BoardTest : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    BoardTest()
    {
        // You can do set-up work for each test here.
        Board<ONE, ONE> *oneBoard = new Board<ONE, ONE>();
        Board<TWO, TWO> *twoBoard = new Board<TWO, TWO>();
        Board<THREE, THREE> *threeBoard = new Board<THREE, THREE>();
        Board<FOUR, FOUR> *fourBoard = new Board<FOUR, FOUR>();
        Board<FIVE, FIVE> *fiveBoard = new Board<FIVE, FIVE>();
        Board<SIX, SIX> *sixBoard = new Board<SIX, SIX>();
        Board<SEVEN, SEVEN> *sevenBoard = new Board<SEVEN, SEVEN>();
        Board<EIGHT, EIGHT> *eightBoard = new Board<EIGHT, EIGHT>();
    }

    virtual ~BoardTest()
    {
        // You can do clean-up work that doesn't throw exceptions here.
        // delete oneBoard;
        // delete twoBoard;
        // delete threeBoard;
        // delete fourBoard;
        // delete fiveBoard;
        // delete sixBoard;
        // delete sevenBoard;
        // delete eightBoard;
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    virtual void SetUp()
    {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown()
    {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Objects declared here can be used by all tests in the test case for Project1.
    Board<ONE, ONE> *oneBoard;
    Board<TWO, TWO> *twoBoard;
    Board<THREE, THREE> *threeBoard;
    Board<FOUR, FOUR> *fourBoard;
    Board<FIVE, FIVE> *fiveBoard;
    Board<SIX, SIX> *sixBoard;
    Board<SEVEN, SEVEN> *sevenBoard;
    Board<EIGHT, EIGHT> *eightBoard;
};

/**
 * Counts the total number of squares that are actually within the dimensions of the board
 */
template<BoardDimension w, BoardDimension h>
int sumOnBoard(Board<w, h> *b)
{
    int sum = 0;
    for (Square i = SQ_A1; i < SQUARE_NB; ++i)
    {
        if (b->onBoard(i))
        {
            // std::cout << "square is: " << i << std::endl;
            sum++;
        }
    }
    return sum;
}

TEST_F(BoardTest, onBoardTest)
{
    EXPECT_EQ(sumOnBoard(oneBoard), 1);
    EXPECT_EQ(sumOnBoard(twoBoard), 4);
    EXPECT_EQ(sumOnBoard(threeBoard), 9);
    EXPECT_EQ(sumOnBoard(fourBoard), 16);
    EXPECT_EQ(sumOnBoard(fiveBoard), 25);
    EXPECT_EQ(sumOnBoard(sixBoard), 36);
    EXPECT_EQ(sumOnBoard(sevenBoard), 49);
    EXPECT_EQ(sumOnBoard(eightBoard), 64);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
