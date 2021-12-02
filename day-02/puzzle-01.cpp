#include <iostream>
#include <fstream>
#include <stdexcept>

const int MAX_CMD_LEN = 7;

int main()
{
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open input file.");
    }

    int hor = 0, dep = 0;
    char cmd[MAX_CMD_LEN + 1];
    int arg;
    while (file >> cmd >> arg) {
        switch (cmd[0]) {
            case 'f': hor += arg; break;
            case 'd': dep += arg; break;
            case 'u': dep -= arg;
        }
    }

    std::cout << hor * dep << std::endl;

    file.close();
    if (file.is_open()) {
        throw std::runtime_error("Cannot close input file.");
    }

    return 0;
}