#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

// Keeps asking until the user enters a valid integer in [lo, hi]
inline int readInt(const std::string& prompt, int lo, int hi) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) std::exit(0);  // input closed
        try {
            size_t pos;
            int v = std::stoi(line, &pos);
            if (pos != line.size()) throw std::invalid_argument("extra chars");
            if (v < lo || v > hi) throw std::out_of_range("range");
            return v;
        } catch (...) {
            std::cout << "Invalid input. Enter a whole number between "
                      << lo << " and " << hi << ".\n";
        }
    }
}

// Keeps asking until the user enters a valid number in [lo, hi]
inline double readDouble(const std::string& prompt, double lo, double hi) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) std::exit(0);
        try {
            size_t pos;
            double v = std::stod(line, &pos);
            if (pos != line.size()) throw std::invalid_argument("extra chars");
            if (v < lo || v > hi) throw std::out_of_range("range");
            return v;
        } catch (...) {
            std::cout << "Invalid input. Enter a number between "
                      << lo << " and " << hi << ".\n";
        }
    }
}

// Reads a line of text; re-asks if empty unless allowEmpty is true
inline std::string readLine(const std::string& prompt, bool allowEmpty = false) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) std::exit(0);
        if (!line.empty() || allowEmpty) return line;
        std::cout << "Input cannot be empty.\n";
    }
}