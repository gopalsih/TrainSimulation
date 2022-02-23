#ifndef INPUTMANAGER_H_INCLUDED
#define INPUTMANAGER_H_INCLUDED

#include "RoutingManager.h"
#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <windows.h>
#include <sstream>
#include <fstream>
#include <iostream>

class InputManager : public RoutingManager {
public:
    void readTrackFile(void);                   // Function to read file containing train definition
    void readTrainFile(void);                   // Function to read file containing signal definition
    void readSinalFile(void);                   // Function to read file containing signal definition
private:
    std::vector<int> string2Int(std::string input);
};

#endif // INPUTMANAGER_H_INCLUDED
