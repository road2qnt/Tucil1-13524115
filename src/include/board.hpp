#ifndef BOARD_HPP
#define BOARD_HPP
#include "global.hpp" 
#include <vector>
#include <string>
#include <iostream>


class Board {
private:
    int N;
    vector<string> regionMap;   
    vector<int> queens;     
public:
    Board(int size, const vector<string>& map);
    void placeQueen(int row, int col);
    void removeQueen(int row, int col);
    bool isValidSolution() const;
    bool isSafe(int row, int col) const;
    int getSize() const { return N; }    
    void printBoard(bool cleanScreen = false) const;    
    string getSolutionString() const;    
    const vector<int>& getState() const { return queens; }
};

#endif