#include <string>
#include "simulation.h"
#include <iostream>
#include <cstring>

int main() {
    const char* top = "D:\\CSEalgrithm\\bigtask2\\testbench\\data";
    const char* readfiletail = "\\medicine.txt";
    const char* strategytail = "\\strategy.txt";
    const char* deletetail = "\\delete.txt";
    const char* outtail = "\\task1_simulation_result.txt";
    
    for (int i = 1; i < 11; i++) {
        // Convert the integer i to a string
        char number[3];
        sprintf(number, "%d", i);
        // Concatenate the strings
        char MedFilename[strlen(top) + strlen(number) + strlen(readfiletail) + 1];
        char StrFilename[strlen(top) + strlen(number) + strlen(strategytail) + 1];
        char DelFilename[strlen(top) + strlen(number) + strlen(deletetail) + 1];
        char OutFilename[strlen(top) + strlen(number) + strlen(outtail) + 1];

        sprintf(MedFilename, "%s%s%s", top, number, readfiletail);
        sprintf(StrFilename, "%s%s%s", top, number, strategytail);
        sprintf(DelFilename, "%s%s%s", top, number, deletetail);
        sprintf(OutFilename, "%s%s%s", top, number, outtail);
        // Use the filenames as needed
        Simulation sim(MedFilename);
        //printf("sim%d\n",i);
        sim.RunSimulation(StrFilename, DelFilename, OutFilename);
        
    }

    return 0;
}

