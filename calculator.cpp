#include "calculator.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

std::vector<std::string> readNumbersFromFile(const std::string& filename) {
    std::vector<std::string> numbers;
    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line)) {
        if (!line.empty()) {
            numbers.push_back(line);
        }
    }
    return numbers;
}

bool isValidDouble(const std::string& s) {
    if (s.empty()) return false;

    int i = 0;
    if (s[i] == '+' || s[i] == '-') i++;
    bool hasDigitsBefore = false, hasDigitsAfter = false, hasDot = false;

    while (i < s.size() && isdigit(s[i])) {
        hasDigitsBefore = true;
        i++;
    }

    if (i < s.size() && s[i] == '.') {
        hasDot = true;
        i++;
        while (i < s.size() && isdigit(s[i])) {
            hasDigitsAfter = true;
            i++;
        }
    }

    return (hasDigitsBefore || (hasDot && hasDigitsAfter)) && i == s.size();
}

std::string addStrings(const std::string& num1, const std::string& num2) {
    std::string result;
    int carry = 0;
    int i = num1.size() - 1, j = num2.size() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int a = i >= 0 ? num1[i--] - '0' : 0;
        int b = j >= 0 ? num2[j--] - '0' : 0;
        int sum = a + b + carry;
        carry = sum / 10;
        result.insert(result.begin(), (sum % 10) + '0');
    }
    return result;
}

std::string addDoublesAsStrings(const std::string& a, const std::string& b) {
    // Only handles positive values for now for simplicity
    std::string aInt = a, aFrac = "0";
    std::string bInt = b, bFrac = "0";

    size_t aDot = a.find('.');
    if (aDot != std::string::npos) {
        aInt = a.substr(0, aDot);
        aFrac = a.substr(aDot + 1);
    }

    size_t bDot = b.find('.');
    if (bDot != std::string::npos) {
        bInt = b.substr(0, bDot);
        bFrac = b.substr(bDot + 1);
    }

    // Pad fractional parts to same length
    while (aFrac.length() < bFrac.length()) aFrac += "0";
    while (bFrac.length() < aFrac.length()) bFrac += "0";

    // Add fractional part
    std::string fracSum = addStrings(aFrac, bFrac);
    bool carry = false;
    if (fracSum.length() > aFrac.length()) {
        carry = true;
        fracSum = fracSum.substr(1); // remove carry digit
    }

    // Add integer part
    std::string intSum = addStrings(aInt, bInt);
    if (carry) intSum = addStrings(intSum, "1");

    return intSum + "." + fracSum;
}

double parse_number(const std::string& s) {
    if (!isValidDouble(s)) {
        throw std::invalid_argument("Invalid double format");
    }

    // Parse manually
    bool negative = false;
    size_t i = 0;
    if (s[i] == '+' || s[i] == '-') {
        negative = (s[i] == '-');
        i++;
    }

    double result = 0.0;
    while (i < s.length() && isdigit(s[i])) {
        result = result * 10 + (s[i] - '0');
        i++;
    }

    if (i < s.length() && s[i] == '.') {
        i++;
        double frac = 0.0, divisor = 10.0;
        while (i < s.length() && isdigit(s[i])) {
            frac += (s[i] - '0') / divisor;
            divisor *= 10;
            i++;
        }
        result += frac;
    }

    return negative ? -result : result;
}

