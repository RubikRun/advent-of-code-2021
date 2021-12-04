#include <iostream>
#include <fstream>
#include <stdexcept>
#include <stack>

const int NUM_LEN = 12;
const int NUM_CNT = 1000;

int binToDec(const char *digits, int len) {
    int res = digits[0] - '0';
    for (int i = 1; i < len; i++) {
        res = res * 2 + digits[i] - '0';
    }
    return res;
}

void clearStack(std::stack<const char*> *stPtr) {
    while(!stPtr->empty()) {
        stPtr->pop();
    }
}

void swapStacks(std::stack<const char*>* &aStPtr, std::stack<const char*>* &bStPtr) {
    std::stack<const char*> *t = aStPtr;
    aStPtr = bStPtr;
    bStPtr = t;
}

const char* findRating(const char *inp, bool oxygen) {
    std::stack<const char*> stacks[3];
    std::stack<const char*> *stZero = &stacks[0];
    std::stack<const char*> *stOne = &stacks[1];
    std::stack<const char*> *stAll = &stacks[2];

    for (int i = 0; i < NUM_CNT; i++) {
        stAll->push(inp + i * NUM_LEN);
    }

    for (int pos = 0; pos < NUM_LEN; pos++) {
        while (!stAll->empty()) {
            const char* top = stAll->top();
            stAll->pop();

            if (top[pos] == '0') {
                stZero->push(top);
            }
            else {
                stOne->push(top);
            }
        }


        if (oxygen ? stZero->size() <= stOne->size() : stZero->size() > stOne->size()) {
            clearStack(stZero);
            swapStacks(stOne, stAll);
        }
        else {
            clearStack(stOne);
            swapStacks(stZero, stAll);
        }

        if (stAll->size() < 1) {
            throw std::logic_error("No numbers left.");
        }
        else if (stAll->size() == 1) {
            return stAll->top();
        }
    }
    throw std::logic_error("More than 1 number left after filtering.");
}

int main()
{
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open input file.");
    }

    char inp[NUM_CNT * NUM_LEN + 1];
    for (char *currInp = inp; file >> currInp; currInp += NUM_LEN);

    const char *oxygenPtr = findRating(inp, true);
    const char *carbonPtr = findRating(inp, false);

    std::cout << binToDec(oxygenPtr, NUM_LEN) * binToDec(carbonPtr, NUM_LEN) << std::endl;

    file.close();
    if (file.is_open()) {
        throw std::runtime_error("Cannot close input file.");
    }

    return 0;
}