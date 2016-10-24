//
//  main.cpp
//  Queueing Mode
//  Starter code provided by A. Hornof and Y. Zhang - 2015-04-14
//  Modified by Jared Goddard - 4/21/15
//

#include "DES.h"

int main(int argc, const char * argv[]) {
    DES sim;
    const int num_trials = 1000;
    
    for (int i = 0; i < num_trials; i++) {
        sim.initialize();
        
        sim.run();
    }
    
    return 0;
}
