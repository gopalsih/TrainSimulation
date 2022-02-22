#ifndef TRACKOBJECT_H_INCLUDED
#define TRACKOBJECT_H_INCLUDED
#include <vector>

#define GENERIC_TRACK_LEN 10

enum typeTrack{straight, origin, terminate, fork};

struct Position {
    int row;
    int col;
};

struct trackObject{
    std::vector<Position>next;
};

#endif // TRACKOBJECT_H_INCLUDED
