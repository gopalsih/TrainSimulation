
#include "InputManager.h"

// --------------------------------------------------------------------------------------------------------------------
// DEFINES
// --------------------------------------------------------------------------------------------------------------------
#define TRAIN_FILE_SIZE_POSITION 0
#define TRACK_FILE_SIZE_POSITION 0
#define SIGNAL_FILE_SIZE_POSITION 0

#define TRACK_FILE_POSITION_OFFSET 3
#define TRAIN_FILE_START_POSITION_ROW 0
#define TRAIN_FILE_START_POSITION_COL 1
#define TRAIN_FILE_END_POSITION_ROW 2
#define TRAIN_FILE_END_POSITION_COL 3

// --------------------------------------------------------------------------------------------------------------------
/**
* @brief This function takes a string input and convert it to an int vector
*
* @param void
* @return void
*/
// --------------------------------------------------------------------------------------------------------------------
std::vector<int> InputManager::string2Int(std::string input) {
    std::istringstream iss (input);
    std::vector<int>v;
    int n;
    while(iss >> n){
        v.push_back(n);
    }
    return v;
}

// --------------------------------------------------------------------------------------------------------------------
/**
* @brief This function reads all the track coordinates
*        size
*        numtracks row1 col1 row2 col2 .....  (row2 and col2 is connected to row1 and col1)
*
* @param void
* @return void
*/
// --------------------------------------------------------------------------------------------------------------------
void InputManager::readTrackFile(void){
    std::ifstream trackFile("input_tracks.txt");
    std::string stringLineOutput;
    getline(trackFile, stringLineOutput);
    std::vector<int> vect = string2Int(stringLineOutput);
    uint32_t numTracks = vect[TRACK_FILE_SIZE_POSITION];
    vect.clear();

    for (uint32_t i=0; i< numTracks-1; i++) {
        vect.clear();
        getline(trackFile, stringLineOutput);
        vect = string2Int(stringLineOutput);
        uint32_t numNextTracks = vect[TRACK_FILE_SIZE_POSITION];
        Position pos = {vect[1],vect[2]};
        trackObject *trkPtr = &gridArray[pos.row][pos.col].trackObj;
        int index = TRACK_FILE_POSITION_OFFSET; // the 3r item in a row will be where the coordinates start
        for (int i=0; i<numNextTracks; i++) {
            Position nexstringLineOutput = {vect[index],vect[index+1]};
            index+=2;
            trkPtr->next.push_back(nexstringLineOutput);
        }
    }
    trackFile.close(); //close the file object.
}

// --------------------------------------------------------------------------------------------------------------------
/**
* @brief This function reads the input signals coordinates.
*        size
*        start pos end pos
*
* @param void
* @return void
*/
// --------------------------------------------------------------------------------------------------------------------
void InputManager::readTrainFile(void) {
    std::ifstream trainFile("input_trains.txt");
    std::string stringLineOutput;
    getline(trainFile, stringLineOutput);
    std::vector<int> vect = string2Int(stringLineOutput);
    int numTrains = vect[TRAIN_FILE_SIZE_POSITION];
    vect.clear();
    int index = 0;
    for (int i=0; i<numTrains; i++){
        vect.clear();
        getline(trainFile, stringLineOutput);
        vect = string2Int(stringLineOutput);
        trainObject train;
        train.startPos = {vect[TRAIN_FILE_START_POSITION_ROW],vect[TRAIN_FILE_START_POSITION_COL]};
        train.endPos = {vect[TRAIN_FILE_END_POSITION_ROW],vect[TRAIN_FILE_END_POSITION_COL]};
       // printf("%d, %d\n",train.starstringLineOutputos.row, train.starstringLineOutputos.col);
        trainArray.push_back(train);
    }
}

// --------------------------------------------------------------------------------------------------------------------
/**
* @brief This function reads the input signals coordinates
*        size
*        row1 col1 (coordinates where to place signal)
* @param void
* @return void
*/
// --------------------------------------------------------------------------------------------------------------------
void InputManager::readSinalFile(void) {
    std::ifstream trackFile("input_signals.txt");
    std::string stringLineOutput;
    getline(trackFile, stringLineOutput);
    std::vector<int> vect = string2Int(stringLineOutput);
    int numSignals = vect[SIGNAL_FILE_SIZE_POSITION];
    vect.clear();
    for (int i=0; i<numSignals; i++){
        vect.clear();
        getline(trackFile, stringLineOutput);
        vect = string2Int(stringLineOutput);
        gridArray[vect[0]][vect[1]].signalObj.present = true;
        printf("%d, %d\n",vect[0], vect[1]);
    }
}
