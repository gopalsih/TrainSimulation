#ifndef GRIDMANAGER_H_INCLUDED
#define GRIDMANAGER_H_INCLUDED

#include "trafficObject.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// --------------------------------------------------------------------------------------------------------------------
// DEFINES
// --------------------------------------------------------------------------------------------------------------------
/**
* @brief Defines Grid Size
*
*
*/
// --------------------------------------------------------------------------------------------------------------------
#define GRID_SIZE 12

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
struct gridSquare {;
    trackObject trackObj;
    signalObject signalObj;

};


// --------------------------------------------------------------------------------------------------------------------
// STRUCTS
// --------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------
/**
* @brief
*
*
*/
// --------------------------------------------------------------------------------------------------------------------

class GridManager {
public:
    gridSquare gridArray[GRID_SIZE][GRID_SIZE]; // Grid of gridSquare structs
    uint32_t mGridSize;
    void drawGrid(int step);                    // Function to draw grid
protected:
    std::vector<trainObject>trainArray;
    int findNearestSignal(trainObject *train, int pos);

};


#endif // GRIDMANAGER_H_INCLUDED