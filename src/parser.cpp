#include "include/parser.hpp"
#include <fstream>
#include <algorithm>
#include <set>
using namespace std;


vector<string> Parser::readInput(const string& filename) {
    vector<string> map;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << RED << "[PARSER ERROR] File tidak ditemukan: " << filename << RESET << endl;
        return {};
    }

    while (file >> line) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        map.push_back(line);
    }
    
    file.close();
    return map;
}


bool Parser::validateInput(const vector<string>& map) {
    if (map.empty()) {
        cerr << RED << "[PARSER ERROR] File kosong." << RESET << endl;
        return false;
    }

    int N = map.size();
    set<char> uniqueColors; 

    for (const string& row : map) {
        if ((int)row.length() != N) {
            cerr << RED << "[PARSER ERROR] Dimensi tidak konsisten." << RESET << endl;
            return false;
        }

        for (char c : row) {
            if (c < 'A' || c > 'Z') {
                cerr << RED << "[PARSER ERROR] Karakter ilegal '" << c << "'." << RESET << endl;
                return false;
            }
            uniqueColors.insert(c); 
        }
    }

    if ((int)uniqueColors.size() != N) {
        cerr << RED << "[PARSER ERROR] Jumlah warna (" << uniqueColors.size() 
             << ") tidak sama dengan dimensi papan (" << N << ")." << RESET << endl;
        cerr << YELLOW << "[HINT] Spek mewajibkan jumlah zona warna sama dengan N." << RESET << endl;
        return false;
    }

    return true;
}


void Parser::saveSolution(const string& filename, const string& content) {
    ofstream file(filename);
    if (file.is_open()) {
        file << content;
        file.close();
        cout << GREEN << "[SYSTEM] Solusi tersimpan di: " << filename << RESET << endl;
    } else {
        cerr << RED << "[SYSTEM ERROR] Gagal menulis file output." << RESET << endl;
    }
}