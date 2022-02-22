#ifndef TRAINOBJECT_H_INCLUDED
#define TRAINOBJECT_H_INCLUDED
#include "trackObject.h"

enum trainState {moving,stopped};
struct trainObject {
    Position startPos;
    Position endPos;
    std::vector<Position> path;
};


#endif // TRAINOBJECT_H_INCLUDED
