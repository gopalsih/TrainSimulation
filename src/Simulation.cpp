#include "Simulation.h"
void Simulation::simulate(){
    uint8_t numSteps = 10;
    for (int step=0; step<numSteps; step++){
        drawGrid(step);
        Sleep(1000);
    }
}

void Simulation::run(){
    memset(gridArray,0,sizeof(gridArray));
    readSinalFile();
    readTrackFile();
    readTrainFile();

    updatePaths();

    simulate();

}
