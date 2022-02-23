#ifndef ROUTINGMANAGER_H_INCLUDED
#define ROUTINGMANAGER_H_INCLUDED

#include "GridManager.h"

class RoutingManager : public GridManager {
public:
    RoutingManager(void);
    void computePath(trainObject *train);                   // Function to compute paths for all trains
    void printPaths(void);                                  // Debug function to print paths
    bool checkCollision(void);                              // Function to check for collisions based on train paths for all trains
    void updatePaths(void);                                 // Function to load paths on trainArray
    int findLongestPath(void);

private:
    int findNearestSignal(trainObject *train, int pos);     // Finds nearest signal before collision point
};
//

#endif // ROUTINGMANAGER_H_INCLUDED
