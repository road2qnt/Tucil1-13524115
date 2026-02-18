#include "include/solver.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>

using namespace std;

Solver::Solver(Board& b) : board(b) {
    iterations = 0;
    executionTimeMs = 0.0;
    visualUpdateRate = 50000;
}

bool Solver::solve() {
    iterations = 0;
    auto start = chrono::high_resolution_clock::now();
    
    int N = board.getSize();

    for (int i = 0; i < N; i++) {
        board.placeQueen(i, 0);
    }

    while (true) {
        iterations++;

        if (iterations % visualUpdateRate == 0) {
            board.printBoard(true);
            cout << "[Running] Brute Force Odometer..." << endl;
            cout << "Iterasi: " << iterations << endl;
        }

        if (board.isValidSolution()) {
            auto end = chrono::high_resolution_clock::now();
            executionTimeMs = chrono::duration<double, milli>(end - start).count();
            return true;
        }

        int rowToMove = N - 1;
        bool carry = true;

        while (carry && rowToMove >= 0) {
            int currentQueenCol = board.getState()[rowToMove];

            if (currentQueenCol < N - 1) {
                board.placeQueen(rowToMove, currentQueenCol + 1);
                carry = false;
            } 
            else {
                board.placeQueen(rowToMove, 0);
                rowToMove--;
            }
        }

        if (rowToMove < 0) {
            break;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    executionTimeMs = chrono::duration<double, milli>(end - start).count();
    
    return false;
}