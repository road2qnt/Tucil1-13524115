#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "board.hpp"
#include <chrono>

class Solver {
private:
    Board& board;                  
    ull iterations; 
    double executionTimeMs;        
    int visualUpdateRate;          

public:
    Solver(Board& b);
    bool solve();
    unsigned long long getIterations() const { return iterations; }
    double getTime() const { return executionTimeMs; }
    void setVisualUpdateRate(int rate) { visualUpdateRate = rate; }
};

#endif