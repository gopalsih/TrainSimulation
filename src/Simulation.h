#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include <thread>
#include <windows.h>

#include "InputManager.h"


class Simulation : public InputManager {
public:
    void simulate(void);                        // Function to simulate the paths
    void run(void);                             // Function to run all required functions and run the simulation
};


#endif // SIMULATION_H_INCLUDED
