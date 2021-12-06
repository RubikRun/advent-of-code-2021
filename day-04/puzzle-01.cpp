#include <iostream>
#include <fstream>
#include <stdexcept>

const int DRAWS_CNT = 100;
const int BOARDS_CNT = 100;
const int BOARD_SIZE = 5;

const int VALUE_MISSING = -1;

struct Board
{
    void read(std::ifstream& file) {
        for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
            file >> values[i];
        }
    }

    void mark(int x) {
        int ind = find(x);
        if (ind != VALUE_MISSING) {
            rowMarkCnt[ind / BOARD_SIZE]++;
            colMarkCnt[ind % BOARD_SIZE]++;
            values[ind] = VALUE_MISSING;
        }
    }

    bool isWin() const {
        for (int rc = 0; rc < BOARD_SIZE; rc++) {
            if (rowMarkCnt[rc] == 5 || colMarkCnt[rc] == 5) {;
                return true;
            }
        }
        return false;
    }

    int getScore(int draw) const {
        int score = 0;
        for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
            if (values[i] != VALUE_MISSING) {
                score += values[i];
            }
        }
        score *= draw;
        return score;
    }

private:

    int find(int x) const {
        for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
            if (values[i] == x) {
                return i;
            }
        }
        return VALUE_MISSING;
    }

    int values[BOARD_SIZE * BOARD_SIZE];

    int rowMarkCnt[BOARD_SIZE] = {0};
    int colMarkCnt[BOARD_SIZE] = {0};
};

int getWinScore(Board boards[], int draws[]) {
    for (int drawInd = 0; drawInd < DRAWS_CNT; drawInd++) {
        int draw = draws[drawInd];

        for (int boardInd = 0; boardInd < BOARDS_CNT; boardInd++) {
            boards[boardInd].mark(draw);
            if (boards[boardInd].isWin()) {
                return boards[boardInd].getScore(draw);
            }
        }
    }
}

int main()
{
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open input file.");
    }

    int draws[DRAWS_CNT];
    for (int i = 0; i < DRAWS_CNT; i++) {
        file >> draws[i];
    }

    Board boards[BOARDS_CNT];
    for (int i = 0; i < BOARDS_CNT; i++) {
        boards[i].read(file);
    }

    std::cout << getWinScore(boards, draws) << std::endl;

    file.close();
    if (file.is_open()) {
        throw std::runtime_error("Cannot close input file.");
    }

    return 0;
}