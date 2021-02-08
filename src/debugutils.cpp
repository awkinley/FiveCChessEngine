#include "debugutils.h"

std::string rankSeperator(BoardDimension width) {
    std::string s = "\n ";
    for (size_t i = 0; i < width; i++)
    {
        s += "+---";
    }
    s += "+\n";
    return s;
}


char fileLetterArray[]= {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
std::string fileLetters(BoardDimension width) {
    std::string threeSpace = "   ";
    std::string s = threeSpace;
    for (size_t i = 0; i < width; i++)
    {
        s += fileLetterArray[i];
        s += threeSpace;
    }
    s += "\n";
    return s;
}