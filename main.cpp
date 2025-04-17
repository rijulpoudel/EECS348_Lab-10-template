#include "calculator.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./calculator <filename>" << std::endl;
        return 1;
    }

    std::vector<std::string> numbers = readNumbersFromFile(argv[1]);
    std::string constant = "-123.456"; // Only handles addition for now (positive numbers only)

    for (const auto& num : numbers) {
        std::cout << "Checking: " << num << std::endl;
        if (isValidDouble(num)) {
            std::cout << "Valid double!" << std::endl;
            std::string result = addDoublesAsStrings(num, "123.456");
            std::cout << "Sum: " << result << std::endl;
        } else {
            std::cout << "Invalid double!" << std::endl;
        }
    }

    return 0;
}
