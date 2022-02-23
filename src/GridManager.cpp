#include "GridManager.h"

void GridManager::drawGrid(int step){
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
                memset(&charGrid[i][j],'T',sizeof(char));
            } else if((gridArray[i][j].trackObj.next.size()>0) && gridArray[i][j].signalObj.present==true){
                memset(&charGrid[i][j],'s',sizeof(char));
            }else if((gridArray[i][j].trackObj.next.size()>0) && gridArray[i][j].signalObj.present==false){
                memset(&charGrid[i][j],'x',sizeof(char));
            }else {
                memset(&charGrid[i][j],'.',sizeof(char));
            }
            printf("%c",charGrid[i][j]);
        }
        printf("\n");
    }
}




