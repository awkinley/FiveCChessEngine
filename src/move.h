#ifndef MOVE_H
#define MOVE_H

#include "types.h"

struct SuperPos {
    Universe u;
    Time t;
    Square s;
};

struct SuperPos;
struct Move {
    SuperPos startPos;
    SuperPos endPos;
};

#endif // MOVE_H