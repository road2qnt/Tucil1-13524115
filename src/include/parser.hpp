#ifndef PARSER_HPP
#define PARSER_HPP

#include "global.hpp" 

class Parser {
public:
    static vector<string> readInput(const string& filename);
    static bool validateInput(const vector<string>& map);
    static void saveSolution(const string& filename, const string& content);
};

#endif 