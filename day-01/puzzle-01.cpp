#include <iostream>
#include <fstream>
#include <stdexcept>

int main()
{
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open input file.");
    }

    int ups = 0;
    int prev, curr;
    file >> prev;
    while (file >> curr) {
        if (curr > prev) {
            ups++;
        }
        prev = curr;
    }

    std::cout << ups << std::endl;

    file.close();
    if (file.is_open()) {
        throw std::runtime_error("Cannot close input file.");
    }

    return 0;
}