#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <iomanip>

using ll  = long long;
using ull = unsigned long long;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::pair;
using std::max;
using std::min;

struct Point {
    int r, c;
    bool operator==(const Point& other) const {
        return r == other.r && c == other.c;
    }
};

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

#define BG_RED     "\033[41m"
#define BG_GREEN   "\033[42m"
#define BG_YELLOW  "\033[43m"
#define BG_BLUE    "\033[44m"


inline void clearScreen() {
    #ifdef _WIN32

        system("cls");
    #else
        std::cout << "\033[2J\033[1;1H";
    #endif
}


inline void sleepMs(int milliseconds) {
    if (milliseconds > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
}

#ifdef DEBUG_MODE
    #define LOG(x) std::cerr << YELLOW << "[DEBUG] " << x << RESET << std::endl
#else
    #define LOG(x) 
#endif

#endif 