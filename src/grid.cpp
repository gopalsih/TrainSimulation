#include <iostream>
#include <fstream>
#include <sstream>
#include "grid.h"
#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <windows.h>

std::vector<int> grid::string2Int(std::string input) {
    std::istringstream iss (input);
    std::vector<int>v;
    int n;
    while(iss >> n){
        v.push_back(n);
    }
    return v;
}

void grid::readTrackFile(void){
    std::ifstream MyReadFile("input_tracks.txt");
    std::string tp;
    getline(MyReadFile, tp);
    std::vector<int> vect = string2Int(tp);
    uint32_t numTracks = vect[0];
    vect.clear();

    for (int i=0; i< numTracks-1; i++) {
        vect.clear();
        getline(MyReadFile, tp);
        vect = string2Int(tp);
        uint32_t numNextTracks = vect[0];
        Position pos = {vect[1],vect[2]};
        trackObject *trkPtr = &gridArray[pos.row][pos.col].trackObj;
        int index = 3;
        for (int i=0; i<numNextTracks; i++) {
            Position nextPos = {vect[index],vect[index+1]};
            index+=2;
            //printf("%d, %d\n",nextPos.row, nextPos.col);
            trkPtr->next.push_back(nextPos);
        }
    }
    MyReadFile.close(); //close the file object.
}

void grid::readTrainFile(void) {
    std::ifstream MyReadFile("input_trains.txt");
    std::string tp;
    getline(MyReadFile, tp);
    std::vector<int> vect = string2Int(tp);
    mNumTrains = vect[0];
    vect.clear();
    int index = 0;
    for (int i=0; i<mNumTrains; i++){
        vect.clear();
        getline(MyReadFile, tp);
        vect = string2Int(tp);
        trainObject train;
        train.startPos = {vect[0],vect[1]};
        train.endPos = {vect[2],vect[3]};
       // printf("%d, %d\n",train.startPos.row, train.startPos.col);
        trainArray.push_back(train);
    }
}

void grid::readSinalFile(void) {
    std::ifstream MyReadFile("input_signals.txt");
    std::string tp;
    getline(MyReadFile, tp);
    std::vector<int> vect = string2Int(tp);
    int numSignals = vect[0];
    vect.clear();
    for (int i=0; i<numSignals; i++){
        vect.clear();
        getline(MyReadFile, tp);
        vect = string2Int(tp);
        gridArray[vect[0]][vect[1]].signalObj.present = true;
        printf("%d, %d\n",vect[0], vect[1]);
    }
}

void grid::computePath(trainObject *train) {
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

void grid::computePaths() {
    for (int i=0; i<trainArray.size(); i++){
        computePath(&trainArray[i]);
    }
}
int grid::findNearestSignal(trainObject *train, int pos){
    for (int i=0; i<pos; i++){
        if (gridArray[train->path[i].row][train->path[i].col].signalObj.present == true){
            return i;
        }
    }
    return pos;
}

bool grid::checkCollision(void){
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

void grid::drawGrid(int step){
    char charGrid[GRID_SIZE][GRID_SIZE] = {0};
    printf("%d\n",step);

    for (int i=0;i<trainArray.size();i++){
        Position currentPos;
        if (step < trainArray[i].path.size()){
            currentPos = trainArray[i].path[step];
        } else {
            currentPos = trainArray[i].path[trainArray[i].path.size()-1];
        }
        charGrid[currentPos.row][currentPos.col] = 'T';
    }

    for (int i=0; i<GRID_SIZE; i++){
        for(int j=0; j<GRID_SIZE; j++){
            if (charGrid[i][j] == 'T'){
                charGrid[i][j] == 'T';
            } else if((gridArray[i][j].trackObj.next.size()>0) && gridArray[i][j].signalObj.present==true){
                printf("s");
                charGrid[i][j] == 's';
            }else if((gridArray[i][j].trackObj.next.size()>0) && gridArray[i][j].signalObj.present==false){
                printf("x");
                charGrid[i][j] == 'x';
            }else {
                printf(".");
                charGrid[i][j] == '.';
            }
            printf("%c",charGrid[i][j]);
        }
        printf("\n");
    }
}


void grid::simulate(){
    uint8_t numSteps = 10;
    for (int step=0; step<numSteps; step++){
        drawGrid(step);
        Sleep(1000);
    }
}

void grid::run(void){
    readTrackFile();
    readSinalFile();
    readTrainFile();
    computePaths();
    while(checkCollision() == false);
    simulate();
}



