#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>

std::vector<std::string> readNumbersFromFile(const std::string& filename);
bool isValidDouble(const std::string& s);
std::string addDoublesAsStrings(const std::string& a, const std::string& b);
double parse_number(const std::string& s);

#endif

