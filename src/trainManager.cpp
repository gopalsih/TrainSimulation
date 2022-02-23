
#include "trainManager.h"
#include <queue>
TrainManager::TrainManager(){}

void TrainManager::computePath(trainObject *train) {
    struct queueData {
       Position currentPosition;
       std::vector<Position> path;
    };
    std::queue<queueData> queueArray;

    queueData qd;
    qd.currentPosition = train->startPos;

    queueArray.push(qd);

    bool visited[GRID_SIZE][GRID_SIZE] = {0};

    while(1) {
        if (queueArray.empty() == false){
        qd = queueArray.front();
        queueArray.pop();
        }
        visited[qd.currentPosition.row][qd.currentPosition.col] = true;
        qd.path.push_back(qd.currentPosition);
        if ((qd.currentPosition.row == train->endPos.row) && (qd.currentPosition.col == train->endPos.col)) {
            printf("Path for tain\n");
            for(int i =0; i<qd.path.size(); i++){
                train->path.push_back(qd.path[i]);
                printf("%d,%d->", train->path[i].row,train->path[i].col);
            }

            break;
        }
        queueData new_qd = qd;
        for(int i=0; i<gridArray[qd.currentPosition.row][qd.currentPosition.col].trackObj.next.size(); i++) {
            Position next = gridArray[qd.currentPosition.row][qd.currentPosition.col].trackObj.next[i];
            if (visited[next.row][next.col]){continue;}

            new_qd.currentPosition = next;
            queueArray.push(new_qd);
        }
    }
}

void TrainManager::updatePaths() {
    for (int i=0; i<trainArray.size(); i++){
        computePath(&trainArray[i]);
    }
}

int TrainManager::findNearestSignal(trainObject *train, int pos){
    for (int i=0; i<pos; i++){
        if (gridArray[train->path[i].row][train->path[i].col].signalObj.present == true){
            return i;
        }
    }
    return pos;
}

bool TrainManager::checkCollision(void){
    int minPathSize = INT_MAX;
    int minPathTrainIndex = 0;
    bool retStatus = true;
    Position collisionPos;

        for (int i=0; i<trainArray.size(); i++){
            for(int j=i+1 ; j<trainArray.size(); j++){
                int tempPathSize =(trainArray[i].path.size());
                int tempPathSize2 =(trainArray[j].path.size());
                minPathSize = tempPathSize;
                if (tempPathSize2 < tempPathSize){
                    minPathSize = tempPathSize2;
                }
                for (int k = 0; k<minPathSize; k++){
                    if ((trainArray[i].path[k].col == trainArray[j].path[k].col)&&(trainArray[i].path[k].row == trainArray[j].path[k].row)){
                        retStatus = false;
                        collisionPos = trainArray[i].path[k];
                        int ret = findNearestSignal(&trainArray[i],k);
                        int ret2 =  findNearestSignal(&trainArray[j],k);
                        if (ret!=k){
                            Position posWait = {trainArray[i].path[ret].row,trainArray[i].path[ret].col};
                            trainArray[i].path.insert(trainArray[i].path.begin()+ ret,posWait);
                        }else if(ret2 != k){
                            Position posWait = {trainArray[i].path[ret2].row,trainArray[i].path[ret2].col};
                            trainArray[i].path.insert(trainArray[i].path.begin()+ ret2,posWait);
                        }else{
                            printf("No solution!!!\n");
                            return false;
                        }
                    }
                }
            }
        }
        if(retStatus){printf("No Collision!!\n");}
        return retStatus;
}
