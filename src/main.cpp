#include <iostream>
#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string.h>

int main(){
    grid mGrid;
    memset(mGrid.gridArray, 0, sizeof(mGrid.gridArray));
    mGrid.run();
    return 0;
}


