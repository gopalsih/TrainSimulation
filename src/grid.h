#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include "trafficObject.h"
#include <vector>
#include <string>
#include <queue>
#include <thread>
#include <windows.h>

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
    void simulate(void);                        // Function to simulate the paths
    void run(void);                             // Function to run all required functions and run the simulation
protected:
    std::vector<trainObject>trainArray;
    int findNearestSignal(trainObject *train, int pos);

};




#endif // GRID_H_INCLUDED
