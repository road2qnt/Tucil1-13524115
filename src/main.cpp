#include <iostream>
#include <string>
#include <limits>
#include <filesystem>
#include <iomanip>
#include <vector>

#include "include/board.hpp"
#include "include/solver.hpp"
#include "include/parser.hpp"

using namespace std;
namespace fs = std::filesystem;

void pressAnyKeyToContinue() {
    cout << "\nTekan ENTER untuk lanjut...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main() {
    string inputFilename;
    const string TEST_DIR = "test/";

    while (true) {
        clearScreen();
        cout << BOLD << CYAN << "============================================" << RESET << endl;
        cout << BOLD << CYAN << "      LINKEDIN QUEENS SOLVER (CLI MODE)     " << RESET << endl;
        cout << "      Folder Target: " << TEST_DIR << endl;
        cout << BOLD << CYAN << "============================================" << RESET << endl;

        cout << "File tersedia:" << endl;
        bool filesFound = false;
        if (fs::exists(TEST_DIR)) {
            for (const auto& entry : fs::directory_iterator(TEST_DIR)) {
                if (entry.path().extension() == ".txt") {
                    cout << " - " << entry.path().filename().string() << endl;
                    filesFound = true;
                }
            }
        }
        if (!filesFound) cout << " (Tidak ada file .txt di folder test/)" << endl;
        cout << "--------------------------------------------" << endl;

        cout << "\n[INPUT] Masukkan nama file (ketik 'exit' untuk keluar): ";
        cin >> inputFilename;

        if (inputFilename == "exit" || inputFilename == "keluar") break;

        string fullPath = TEST_DIR + inputFilename;
        if (inputFilename.find(".txt") == string::npos) fullPath += ".txt";

        try {
            vector<string> map = Parser::readInput(fullPath);
            if (!Parser::validateInput(map)) {
                pressAnyKeyToContinue();
                continue;
            }

            int N = map.size();
            Board board(N, map);
            Solver solver(board);

            int updateRate;
            cout << "[CONFIG] Update visual tiap berapa iterasi? (1 = Realtime, 10000 = Cepat): ";
            if (!(cin >> updateRate)) {
                updateRate = 50000;
                cin.clear(); cin.ignore();
            }
            solver.setVisualUpdateRate(updateRate);

            cout << YELLOW << "\n[RUNNING] Memulai Brute Force..." << RESET << endl;
            
            bool success = solver.solve();

            clearScreen();
            cout << BOLD << CYAN << "============================================" << RESET << endl;
            cout << BOLD << CYAN << "               HASIL EKSEKUSI               " << RESET << endl;
            cout << BOLD << CYAN << "============================================" << RESET << endl;

            if (success) {
                cout << GREEN << BOLD << "[SUCCESS] Solusi Ditemukan!" << RESET << endl;
                board.printBoard(false); 
            } else {
                cout << RED << BOLD << "[FAILED] Tidak ada solusi yang mungkin." << RESET << endl;
            }

            cout << "--------------------------------------------" << endl;
            cout << "Waktu Eksekusi : " << BOLD << fixed << setprecision(4) << solver.getTime() << " ms" << RESET << endl;
            
            cout << "Total Iterasi  : " << BOLD << solver.getIterations() << RESET << endl;
            cout << "--------------------------------------------" << endl;

            char saveChoice;
            cout << "[OUTPUT] Simpan solusi ke file? (y/n): ";
            cin >> saveChoice;
            if (saveChoice == 'y' || saveChoice == 'Y') {
                string outFile;
                cout << "Nama file output (contoh: solusi.txt): ";
                cin >> outFile;
                Parser::saveSolution(outFile, board.getSolutionString());
            }

        } catch (const exception& e) {
            cerr << RED << "[ERROR] " << e.what() << RESET << endl;
        }

        pressAnyKeyToContinue();
    }

    return 0;
}