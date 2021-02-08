#include <iostream>

#include "position.h"
#include "movegenerator.h"
#include "vec4.h"

Piece standardBoard[SQUARE_NB] = {W_ROOK, W_KNIGHT, W_BISHOP, W_QUEEN, W_KING, W_BISHOP, W_KNIGHT, W_ROOK, 
                                    W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN,
                                    NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, 
                                    NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, 
                                    NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, 
                                    NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, 
                                    B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN,
                                    B_ROOK, B_KNIGHT, B_BISHOP, B_QUEEN, B_KING, B_BISHOP, B_KNIGHT, B_ROOK};

Piece smallBoard[5 * 5] = {W_KING, W_QUEEN, W_BISHOP, W_KNIGHT, W_ROOK, 
                            W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN, 
                            NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, 
                            B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN,
                            B_KING, B_QUEEN, B_BISHOP, B_KNIGHT, B_ROOK};

Piece testSmallBoard[5 * 5] = {W_KING, W_QUEEN, NO_PIECE, W_KNIGHT, W_ROOK, 
                             NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, 
                            NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, 
                            B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN,
                            B_KING, B_QUEEN, B_BISHOP, B_KNIGHT, B_ROOK};
int main(int, char**) {
    
    // Board<EIGHT, EIGHT>* b = new Board<EIGHT, EIGHT>();
    // b->setPieces(standardBoard);
    Board<FIVE, FIVE>* b = new Board<FIVE, FIVE>(0, 1, WHITE);
    b->setPieces(testSmallBoard);

    std::cout << b->print() << std::endl;

    Position<FIVE, FIVE> p = Position<FIVE, FIVE>();
    p.addBoardToTimeline(b, 0);
    
    std::cout << "position before: " << std::endl;
    std::cout << p.print();

    std::vector<Move>* moves = generateAll<WHITE, FIVE, FIVE>(b);
    std::cout << "making move: "  <<  "from (" << moves->at(0).startPos.u << "T" << moves->at(0).startPos.t << ") square: " << moves->at(0).startPos.s << " to  (" << moves->at(0).endPos.u << "T" << moves->at(0).endPos.t << ") square: " << moves->at(0).endPos.s << std::endl;
    p.makeMove(moves->at(0));

    std::cout << "position after: " << std::endl;
    std::cout << p.print();
    // Vec4 knightVec{2, 1, 0, 0};
    // std::vector<Vec4>* perms = Vector4::getAllPermutations(knightVec);
    // std::cout << "got given " << perms->size() << " permutations" << std::endl;
    // for (size_t i = 0; i < perms->size(); i++)
    // {
    //     Vec4 v = perms->at(i);
    //     std::cout << "(" << v.x << ", " << v.y << ", " << v.u << ", " << v.t << ")" << std::endl;
    // }

    // std::vector<Move>* moves = generateAll<WHITE, FIVE, FIVE>(b);

    // for (auto  m : *moves) 
    // {
    //     std::cout<<"move from (" << m.startPos.u << "T" << m.startPos.t << ") square: " << m.startPos.s << " to  (" << m.endPos.u << "T" << m.endPos.t << ") square: " << m.endPos.s << std::endl;
    // }

    return 0;
}
