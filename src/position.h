#ifndef POSITION_H
#define POSITION_H

#include <vector>
#include <string>
#include <cassert>

#include "types.h"
#include "board.h"

template <BoardDimension width, BoardDimension height>
class Position
{
private:
    std::vector<std::vector<Board<width, height> *> *> *timelines;
    Universe numTimelines;
    Universe numNegativeTimelines;

public:
    Position();
    ~Position();

    void addBoardToTimeline(Board<width, height> *, Universe);
    void makeMove(Move);
    std::string print();
};

template <BoardDimension width, BoardDimension height>
Position<width, height>::Position()
{
    timelines = new std::vector<std::vector<Board<width, height> *> *>();
    numTimelines = 0;
    numNegativeTimelines = 0;
}

template <BoardDimension width, BoardDimension height>
Position<width, height>::~Position()
{
    while (!timelines->empty())
    {
        auto v = timelines->back();
        delete v;
        timelines->pop_back();
    }

    delete timelines;
}

template <BoardDimension width, BoardDimension height>
void Position<width, height>::addBoardToTimeline(Board<width, height> *board, Universe timeline)
{
    Universe adjustedTimeline = timeline + numNegativeTimelines;

    if (0 <= adjustedTimeline && adjustedTimeline < numTimelines)
    {
        // we have to append to an existing timeline
        auto timeline = timelines->at(adjustedTimeline);
        timeline->push_back(board);
    }
    else
    {
        // we have to make a new timeline
        if (adjustedTimeline == -1)
        {
            numNegativeTimelines++;
            numTimelines++;

            auto newTimeline = new std::vector<Board<width, height> *>();
            newTimeline->push_back(board);

            timelines->insert(timelines->begin(), newTimeline);
            return;
        }
        if (adjustedTimeline == numTimelines)
        {
            numTimelines++;

            auto newTimeline = new std::vector<Board<width, height> *>();
            newTimeline->push_back(board);

            timelines->push_back(newTimeline);
            return;
        }

        // shouldn't get here
        std::cout << "tried to add a board at an invalid timeline" << std::endl;
        std::cout << "numTimelines is " << numTimelines << ", numNegativeTimelines is " << numNegativeTimelines << std::endl;
        std::cout << "the given timeline is " << timeline << std::endl;
    }
}

template <BoardDimension width, BoardDimension height>
void Position<width, height>::makeMove(Move m)
{
    auto startPos = m.startPos;
    auto endPos = m.endPos;

    auto startingAdjustedTimeline = numNegativeTimelines + startPos.u;
    // the timeline the move starts on must be within the known timelines
    assert(startingAdjustedTimeline < numTimelines);

    auto startingTimelineVector = timelines->at(startingAdjustedTimeline);

    Board<width, height>* startingBoard = startingTimelineVector->back();

    // the time the move starts on must be the time of the last board in the timeline
    assert(startingBoard->boardTime == startPos.t);

    // physical move
    if (startPos.u == endPos.u && startPos.t == endPos.t)
    {
        Piece piecesArray[width*height];
        for (size_t i = 0; i < width*height; i++)
        {
            piecesArray[i] = startingBoard->pieces[i];
        }
        int moveStartIndex = (int) square_to_rank(startPos.s) * width + (int) square_to_file(startPos.s);
        int moveEndIndex = (int) square_to_rank(endPos.s) * width + (int) square_to_file(endPos.s);
        std::cout << "moveStartIndex: " << moveStartIndex << " moveEndIndex: " << moveEndIndex << std::endl;
        piecesArray[moveEndIndex] = piecesArray[moveStartIndex];
        piecesArray[moveStartIndex] = NO_PIECE;

        // TODO: actually correctly deal with the time 
        // so that if it's a black move that we advance the time
        Board<width, height>* newBoard = new Board<width, height>(endPos.u, endPos.t, WHITE);
        newBoard->setPieces(piecesArray);
        this->addBoardToTimeline(newBoard, endPos.u);
    }
    else 
    {
        // superphysical move

    }
}

template <BoardDimension width, BoardDimension height>
std::string Position<width, height>::print()
{
    int timelineNum = -1 * numNegativeTimelines;

    std::string s = "";

    for (auto timeline : *timelines)
    {
        s += "timeline #" + std::to_string(timelineNum) + "\n";

        for (auto b : *timeline)
        {
            Time time = b->boardTime;
            s += "time: ";
            s += std::to_string(time);

            s += b->print();
        }

        timelineNum++;
    }

    return s;
}

#endif // POSITION_H