#include "GridManager.h"

// --------------------------------------------------------------------------------------------------------------------
/**
* @brief This function takes a step integer and prints the grid with trains chars updated by the number of steps in the
*        path.
*
* @param void
* @return void
*/
// --------------------------------------------------------------------------------------------------------------------
void GridManager::drawGrid(int step){
    char charGrid[GRID_SIZE][GRID_SIZE] = {0};
    printf("STEP AT: %d\n",step);

    for (int i=0;i<trainArray.size();i++){
        Position currentPos;
        if (step < trainArray[i].path.size()){
            //if the train is not at the end the update the grid by step
            currentPos = trainArray[i].path[step];
        } else {
            // if the train is at the end then it says at that position
            currentPos = trainArray[i].path[trainArray[i].path.size()-1];
        }
        charGrid[currentPos.row][currentPos.col] = 'T';
    }

    for (int i=0; i<GRID_SIZE; i++){
        for(int j=0; j<GRID_SIZE; j++){
            char *gridPtr = &charGrid[i][j];
            if (*gridPtr == 'T'){
                memset(gridPtr,'T',sizeof(char));
            } else if((gridArray[i][j].trackObj.next.size()>0) && gridArray[i][j].signalObj.present==true){
                // if there is a signal and track at that position then print char 's'
                memset(gridPtr,'s',sizeof(char));
            }else if((gridArray[i][j].trackObj.next.size()>0) && gridArray[i][j].signalObj.present==false){
                // if there is a track but no signal at that position then print char 'x'
                memset(gridPtr,'x',sizeof(char));
            }else{
                // if there is neither signal nor track at that position then print char '.'
                memset(gridPtr,'.',sizeof(char));
            }
            printf("%c",*gridPtr);
        }
        printf("\n");
    }
}




