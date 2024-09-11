#ifndef MYLIB_H
#define MYLIB_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::vector<std::vector<double>> readMatrixFromFile(const std::string& filename);
std::vector<double> readVectorFromFile(const std::string& filename);

#endif 