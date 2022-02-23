
#include "InputManager.h"

std::vector<int> InputManager::string2Int(std::string input) {
    std::istringstream iss (input);
    std::vector<int>v;
    int n;
    while(iss >> n){
        v.push_back(n);
    }
    return v;
}

void InputManager::readTrackFile(void){
    std::ifstream MyReadFile("input_tracks.txt");
    std::string tp;
    getline(MyReadFile, tp);
    std::vector<int> vect = string2Int(tp);
    uint32_t numTracks = vect[0];
    vect.clear();

    for (uint32_t i=0; i< numTracks-1; i++) {
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

void InputManager::readTrainFile(void) {
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

void InputManager::readSinalFile(void) {
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
