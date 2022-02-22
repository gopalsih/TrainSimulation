#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include "trafficObject.h"
#include "trainManager.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

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

class grid {
public:
    gridSquare gridArray[GRID_SIZE][GRID_SIZE]; // Grid of gridSquare structs
    int mNumTrains;                             // Number of trains in the grid
    void readTrackFile(void);                   // Function to read file containing train definition
    void readTrainFile(void);                   // Function to read file containing signal definition
    void readSinalFile(void);                   // Function to read file containing signal definition
    void computePaths(void);                    // Function to compute paths for all trains
    bool checkCollision(void);                  // Function to check for collisions based on train paths for all trains
    void drawGrid(int step);                    // Function to draw grid
    void simulate(void);                        // Function to simulate the paths
    void run(void);                             // Function to run all required functions and run the simulation
    grid(){}                                    // Constructor
private:
    std::vector<trainObject>trainArray;
    std::vector<int> string2Int(std::string input);
    void computePath(trainObject *train);
    int findNearestSignal(trainObject *train, int pos);

};




#endif // GRID_H_INCLUDED
