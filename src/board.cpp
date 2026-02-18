#include "include/board.hpp"
#include <cmath>    
#include <iostream>
#include <vector>

using namespace std;


Board::Board(int size, const vector<string>& map) 
    : N(size), regionMap(map) {
    queens.assign(N, -1);
}

void Board::placeQueen(int row, int col) {
    queens[row] = col;
}

void Board::removeQueen(int row, int ) {
    queens[row] = -1; 
}


bool Board::isValidSolution() const {
    vector<bool> colSeen(N, false);
    vector<bool> colorSeen(26, false); 

    for (int r = 0; r < N; r++) {
        int c = queens[r];

        if (c == -1) return false; 

        if (colSeen[c]) return false;
        colSeen[c] = true;

        char colorChar = regionMap[r][c];
        int colorIdx = colorChar - 'A'; 
        
        if (colorIdx < 0 || colorIdx >= 26) return false; 
        
        if (colorSeen[colorIdx]) return false;
        colorSeen[colorIdx] = true;

        if (r > 0) {
            int prevC = queens[r-1];
            
            if (abs(prevC - c) <= 1) {
                return false;
            }
        }
    }

    return true;
}

bool Board::isSafe(int row, int col) const {
    char myColor = regionMap[row][col];

    for (int r = 0; r < row; r++) {
        int c = queens[r];

        if (c == col) return false;

        if (regionMap[r][c] == myColor) return false;

        if (r == row - 1) {
            if (abs(c - col) <= 1) return false; 
        }
    }
    return true;
}


void Board::printBoard(bool cleanScreen) const {
    if (cleanScreen) {
        #ifdef _WIN32
            system("cls");
        #else
            std::cout << "\033[2J\033[1;1H";
        #endif
    }

    cout << "   ";
    for(int j=0; j<N; j++) printf(" %2d ", j);
    cout << "\n";

    for (int i = 0; i < N; i++) {
        printf("%2d ", i);

        for (int j = 0; j < N; j++) {
            char region = regionMap[i][j];
            
            if (queens[i] == j) {
                cout << BG_RED << BOLD << " ♛ " << RESET; 
            } 
            else {
                int colorCode = 31 + (region % 6); 
                cout << "\033[" << colorCode << "m" << " " << region << " " << RESET;
            }
            cout << "|"; 
        }
        cout << "\n";
        

    }
    cout << endl;
}

string Board::getSolutionString() const {
    string output = "";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (queens[i] == j) output += "#"; 
            else output += regionMap[i][j];                
        }
        output += "\n";
    }
    return output;
}