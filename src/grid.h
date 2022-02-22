#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include "gridSquare.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#define GRID_SIZE 12

class grid {
public:
    gridSquare gridArray[GRID_SIZE][GRID_SIZE];
    int mNumTrains;
    void readTrackFile(void);
    void readTrainFile(void);
    void readSinalFile(void);
    void computePaths(void);
    bool checkCollision(void);
    void drawGrid(int step);
    void simulate(void);
    void run(void);
    grid(){}
private:
    std::vector<trainObject>trainArray;
    std::vector<int> string2Int(std::string input);
    void computePath(trainObject *train);
    int findNearestSignal(trainObject *train, int pos);

};




#endif // GRID_H_INCLUDED
