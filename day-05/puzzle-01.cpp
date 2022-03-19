#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <functional>

struct Line {
    int row;
    int first, last;
};

int findFirstLineWith(const std::vector<Line> &lines, int aInd, int bInd, const std::function<bool(Line)> &pred) {
    if (aInd > bInd) {
        return -1;
    }

    int mInd = (aInd + bInd) / 2;
    if (pred(lines[mInd])) {
        if (mInd == 0 || !pred(lines[mInd - 1])) {
            return mInd;
        }
        return findFirstLineWith(lines, aInd, mInd - 1, pred);
    }
    else {
        return findFirstLineWith(lines, mInd + 1, bInd, pred);
    }
}

int countTwoDimOverlaps(const std::vector<Line> &hLines, const std::vector<Line> &vLines) {
    int overlaps = 0;

    for (const Line &hLine : hLines) {
        const auto firstRowPred = [&hLine](Line line) -> bool { return line.row >= hLine.first; };
        const auto lastPred = [&hLine](Line line) -> bool { return line.last >= hLine.row; };

        int firstOnRow = findFirstLineWith(
            vLines, 0, vLines.size() - 1,
            [&hLine](Line line) -> bool { return line.row >= hLine.first; }
        );
        while (firstOnRow != -1 && vLines[firstOnRow].row <= hLine.last) {
            const int firstOnNextRow = findFirstLineWith(
                vLines, 0, vLines.size() - 1,
                [&](Line line) -> bool { return line.row > vLines[firstOnRow].row; }
            );
            const int lastOnRow = (firstOnNextRow == -1) ? vLines.size() - 1 : firstOnNextRow - 1;
            const int firstBelowH = findFirstLineWith(
                vLines, firstOnRow, lastOnRow,
                [&hLine](Line line) -> bool { return line.last >= hLine.row; }
            );
            if (firstBelowH != -1 && vLines[firstBelowH].first <= hLine.row) {
                overlaps++;
            }
            firstOnRow = firstOnNextRow;
        }
    }

    return overlaps;
}

void solve(std::istream &input) {

}

int main()
{
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open input file.");
    }

    solve(file);

    file.close();
    if (file.is_open()) {
        throw std::runtime_error("Cannot close input file.");
    }

    return 0;
}