#include <iostream>
#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
/*
using namespace std;
class gridObject {;
public:
    trainObject *trainObj;
    trackObject *trackObj;
};

class grid {
public:
    gridObject gridArray[5][5];
};

void printGrid (gridObject a[][5]){
    for(int i = 0; i<5;i++){
        for (int j=0; j<5;j++){
            if (a[i][j].trackObj != NULL && a[i][j].trainObj == NULL) {
                printf("  -");
            }
            if(a[i][j].trainObj != NULL){
                printf("  +");
            } else if(a[i][j].trackObj == NULL) {
                printf("  O");
            }
        }
       printf("\n");
    }
}
grid mgrid;
trackObject mTrackObject(10,straight);
trackObject mTrackObject2(10,straight);
trackObject mTrackObject3(10,fork);
trackObject mTrackObject4(10,straight);
trainObject mTrainObject(1);
trainObject mTrainObject2(2);

int main()
{
    mgrid.gridArray[5][5] = {0};
    mgrid.gridArray[0][0].trackObj = &mTrackObject;
    mgrid.gridArray[0][1].trackObj = &mTrackObject2;
    mgrid.gridArray[1][1].trackObj = &mTrackObject3;
    mgrid.gridArray[1][2].trackObj = &mTrackObject4;
    int i = 0;
    int j =0;
    while (mgrid.gridArray[i][j].trackObj != NULL){
        mgrid.gridArray[i][j].trainObj = &mTrainObject;
        cout <<j<< endl;
        j++;
    }
    printGrid(mgrid.gridArray);
    //cout << "Hello world!" << endl;
    return 0;
};*/

int main(){
    grid mGrid;
    mGrid.readTrackFile();
    mGrid.readTrainFile();
    mGrid.readSinalFile();
    mGrid.computePaths();
    mGrid.checkCollision();

    return 0;
}


