#include "Simulation.h"

// --------------------------------------------------------------------------------------------------------------------
/**
* @brief This function takes the longest path and calls the drawGrid function that many times.
*
* @param void
*/
// --------------------------------------------------------------------------------------------------------------------
void Simulation::simulate(){
    int numSteps = findLongestPath();
    for (int step=0; step<numSteps; step++){
        drawGrid(step);
        Sleep(100);
    }
}

// --------------------------------------------------------------------------------------------------------------------
/**
* @brief This reads the input files for the train, tracks and signals position.
*        calls update paths to compute all the paths for the trains
*        checks for collisions and fixes the paths until no more colllision is found.
* @param void
*/
// --------------------------------------------------------------------------------------------------------------------
void Simulation::run(){
    memset(gridArray,0,sizeof(gridArray));
    readSinalFile();
    readTrackFile();
    readTrainFile();

    updatePaths();
    while(checkCollision() == false);
    simulate();

}
