#include "myLib.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

std::vector<std::vector<double>> readMatrixFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    std::vector<std::vector<double>> matrix;
    std::string line;

    if (!inputFile.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    while (std::getline(inputFile, line)) {
        std::vector<double> row;
        std::istringstream iss(line);
        double val;
        while (iss >> val) {
            row.push_back(val);
        }
        matrix.push_back(row);
    }

    inputFile.close();
    return matrix;
}

std::vector<double> readVectorFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    std::vector<double> vector;
    double val;

    if (!inputFile.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    while (inputFile >> val) {
        vector.push_back(val);
    }

    inputFile.close();
    return vector;
}
