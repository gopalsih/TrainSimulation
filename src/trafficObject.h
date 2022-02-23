#ifndef TRAFFICOBJECT_H_INCLUDED
#define TRAFFICOBJECT_H_INCLUDED
#include <vector>
// --------------------------------------------------------------------------------------------------------------------
// STRUCTS
// --------------------------------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------------------------------
/**
* @brief The position structure is a struct holds 2 integers corresponding to a row and column index on the simulation
*        grid.
*
*/
// --------------------------------------------------------------------------------------------------------------------
struct Position {
    int row;
    int col;
};


// --------------------------------------------------------------------------------------------------------------------
/**
* @brief TrainObject is a struct that holds the starting position and ending position index based on the grid.
*        It also hold a vector of type position which will hold the computed path co-ordinates.
*
*/
// --------------------------------------------------------------------------------------------------------------------
struct trainObject {
    Position startPos;
    Position endPos;
    std::vector<Position> path;
};


// --------------------------------------------------------------------------------------------------------------------
/**
* @brief TrackObject is a struct that holds a vector of positions which maps the subsequent connected tracks.
*        This does include all tracks connected forward, backward or junction.
*        Because of this there is no need to differentiate between a straight or fork.
*/
// --------------------------------------------------------------------------------------------------------------------
struct trackObject{
    std::vector<Position>next;
};


// --------------------------------------------------------------------------------------------------------------------
/**
* @brief SignalObject is a struct that has a simple boolean and the grid manager will use this status flag to
*        find the neareast signal in case a collision is in course.
*
*/
// --------------------------------------------------------------------------------------------------------------------

struct signalObject {
    bool present;
};

#endif
