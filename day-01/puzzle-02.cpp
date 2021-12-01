#include <iostream>
#include <fstream>
#include <stdexcept>

int main()
{
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open input file.");
    }

    int ups = 0, curr;
    int prev[3];
    file >> prev[0] >> prev[1] >> prev[2];
    while (file >> curr) {
        if (prev[0] < curr) {
            ups++;
        }
        prev[0] = prev[1];
        prev[1] = prev[2];
        prev[2] = curr;
    }

    std::cout << ups << std::endl;

    file.close();
    if (file.is_open()) {
        throw std::runtime_error("Cannot close input file.");
    }

    return 0;
}