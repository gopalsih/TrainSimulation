#ifndef TRAINMANAGER_H_INCLUDED
#define TRAINMANAGER_H_INCLUDED

#include "grid.h"

class TrainManager : public grid {
public:
    TrainManager(void);
    void computePath(trainObject *train);                   // Function to compute paths for all trains
    void updatePaths(void);                                 // Function to load paths on trainArray
    int findNearestSignal(trainObject *train, int pos);     //
    bool checkCollision(void);                              // Function to check for collisions based on train paths for all trains
};
//

#endif // TRAINMANAGER_H_INCLUDED
