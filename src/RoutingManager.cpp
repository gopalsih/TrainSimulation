
#include "RoutingManager.h"
#include <queue>

// --------------------------------------------------------------------------------------------------------------------
/**
* @brief Constructor
*
* @param void
* @return void
*/
// --------------------------------------------------------------------------------------------------------------------
RoutingManager::RoutingManager(){}


// --------------------------------------------------------------------------------------------------------------------
/**
* @brief This function finds the optimum path for the train based on the start and end position.
*        In this case as all segments are the same length and there's no loops a BFS gives the shortest path
*
* @param train - train object whose path is to be computed
* @return void
*/
// --------------------------------------------------------------------------------------------------------------------
void RoutingManager::computePath(trainObject *train) {
    // struct type to hold current path and position as traversing
    struct queueData {
       Position currentPosition;
       std::vector<Position> path;
    };
    // inti queue to hold best path
    std::queue<queueData> queueArray;
    queueData qd;
    // set queue item to the current postion which is the start
    qd.currentPosition = train->startPos;
    queueArray.push(qd);
    // bool array to keep track of the visited nodes
    bool visited[GRID_SIZE][GRID_SIZE] = {0};

    while(1) {
        // if queue is is not empty then pop the first element of queueData
        if (queueArray.empty() == false){
            qd = queueArray.front();
            queueArray.pop();
        }
        // update visited array with the current position checked
        visited[qd.currentPosition.row][qd.currentPosition.col] = true;
        // update queue with the current position
        qd.path.push_back(qd.currentPosition);
        // if the position is the end position then push the path corrdinates to the train object path
        if ((qd.currentPosition.row == train->endPos.row) && (qd.currentPosition.col == train->endPos.col)) {
            printf("Path for tain\n");
            for(int i =0; i<qd.path.size(); i++){
                train->path.push_back(qd.path[i]);
            }

            break;
        }
        // while there is a track attached to the current position, if it has not been visited then push to queue to be checked
        queueData new_qd = qd;
        for(int i=0; i<gridArray[qd.currentPosition.row][qd.currentPosition.col].trackObj.next.size(); i++) {
            Position next = gridArray[qd.currentPosition.row][qd.currentPosition.col].trackObj.next[i];
            if (visited[next.row][next.col]){continue;}

            new_qd.currentPosition = next;
            queueArray.push(new_qd);
        }
    }
}

// --------------------------------------------------------------------------------------------------------------------
/**
* @brief This function conpute the paths of each train object found
*
* @param void
* @return void
*/
// --------------------------------------------------------------------------------------------------------------------
void RoutingManager::updatePaths() {
    for (int i=0; i<trainArray.size(); i++){
        computePath(&trainArray[i]);
    }
}

// --------------------------------------------------------------------------------------------------------------------
/**
* @brief This function finds the nearest signal in the trian object parsed in
*
* @param train - train object containing path vector
*        pos - poition index of the point before which to look for a signal
*
* @return int - position index of the nearest signal
*/
// --------------------------------------------------------------------------------------------------------------------
int RoutingManager::findNearestSignal(trainObject *train, int pos){
    for (int i=0; i<pos; i++){
        if (gridArray[train->path[i].row][train->path[i].col].signalObj.present == true){
            return i;
        }
    }
    return pos;
}

// --------------------------------------------------------------------------------------------------------------------
/**
* @brief This function checks for collisions and fixes the paths.
*
* @param void
* @return bool - return true if no collision is found
*/
// --------------------------------------------------------------------------------------------------------------------
bool RoutingManager::checkCollision(void){
    int minPathSize = 0xFFFFFFFF;
    int minPathTrainIndex = 0;
    bool retStatus = true;
    Position collisionPos;

   // printf("Before Correction\n");
   // printPaths();
   // printf("\n")
     // iterate over all trains
    for (int i=0; i<trainArray.size(); i++){
        //iterate over the other trains
        for(int j=i+1 ; j<trainArray.size(); j++){
            int trainPathSize1 =(trainArray[i].path.size());
            int trainPathSize2 =(trainArray[j].path.size());
            // find the minimum path train.
            minPathSize = trainPathSize1;
            if (trainPathSize2 < trainPathSize1){
                minPathSize = tempPathSize2;
            }
            // iterate over all the paths
            for (int k = 0; k<minPathSize; k++){
                Position *currentTrainPosition1 = trainArray[i].path[k]; // position ptr for train 1
                Position *currentTrainPosition2 = trainArray[j].path[k]; // position ptr for train 2
                // if there's a coordinate overlap then there's a collision, if the train is at the end already even if overlap it's not treated as a collision.
                if ((currentTrainPosition1->col == currentTrainPosition2->col)&&(currentTrainPosition1->row == currentTrainPosition2->row) && (k!=minPathSize-1)){
                    retStatus = false;
                    collisionPos = trainArray[i].path[k];
                    // finds the nearest signal in all the path coordinates before the collision point
                    int nearestSinalPath1 = findNearestSignal(&trainArray[i],k);
                    int nearestSinalPath2 =  findNearestSignal(&trainArray[j],k);
                    // if either path finds a signal repeat the coordinate to delay the train
                    if (nearestSinalPath1!=k){
                        Position posWait = {trainArray[i].path[ret].row,trainArray[i].path[ret].col};
                        trainArray[i].path.insert(trainArray[i].path.begin()+ ret,posWait);
                    }else if(nearestSinalPath2 != k){
                        Position posWait = {trainArray[i].path[ret2].row,trainArray[i].path[ret2].col};
                        trainArray[i].path.insert(trainArray[i].path.begin()+ ret2,posWait);
                    }else{
                        // if no signal wad found then crash the program
                        printf("No solution!!!\n");
                        return false;
                    }
                }
            }
        }
    }
   // printf("After Correction\n");
   // printPaths();
    if(retStatus){printf("No Collision!!\n");}
    return retStatus;
}

// --------------------------------------------------------------------------------------------------------------------
/**
* @brief This function prints all the paths stored in the trainObjects
*
* @param void
* @return int - longestPath
*/
// --------------------------------------------------------------------------------------------------------------------

void RoutingManager::printPaths(void) {
    for (int i=0; i<trainArray.size();i++){
        for (int j=0; j<trainArray[i].path.size(); j++){
            printf("%d,%d->",trainArray[i].path[j].row,trainArray[i].path[j].col);
        }
        printf("nextTrain\n");
    }
}

// --------------------------------------------------------------------------------------------------------------------
/**
* @brief This function checks for the longest path amonst all the trains
*
* @param void
* @return int - longestPath
*/
// --------------------------------------------------------------------------------------------------------------------
int RoutingManager::findLongestPath(void){
    int longestPath = 0;
    for (int i=0; i<trainArray.size();i++){
        int currentSize = trainArray[i].path.size();
        if (currentSize > longestPath){
            longestPath = currentSize;
        }
    }
    return longestPath;
}
