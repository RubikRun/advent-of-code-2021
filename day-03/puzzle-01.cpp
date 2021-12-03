#include <iostream>
#include <fstream>
#include <stdexcept>

const int NUM_LEN = 12;

int binToDec(int *digits, int len) {
    int res = digits[0];
    for (int i = 1; i < len; i++) {
        res = res * 2 + digits[i];
    }
    return res;
}

int main()
{
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open input file.");
    }

    int bitSum[NUM_LEN];
    for (int i = 0; i < NUM_LEN; i++) {
        bitSum[i] = 0;
    }

    char inp[NUM_LEN + 1];
    int numCnt = 0;
    while (file >> inp) {
        for (int i = 0; i < NUM_LEN; i++) {
            bitSum[i] += inp[i] - '0';
        }
        numCnt++;
    }

    int gamBits[NUM_LEN + 1];
    for (int i = 0; i < NUM_LEN; i++) {
        gamBits[i] = (bitSum[i] * 2 > numCnt);
    }

    int epsBits[NUM_LEN + 1];
    for (int i = 0; i < NUM_LEN; i++) {
        epsBits[i] = (gamBits[i] + 1) % 2;
    }

    std::cout << binToDec(gamBits, NUM_LEN) * binToDec(epsBits, NUM_LEN) << std::endl;

    file.close();
    if (file.is_open()) {
        throw std::runtime_error("Cannot close input file.");
    }

    return 0;
}