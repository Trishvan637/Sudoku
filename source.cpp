#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int GRID_SIZE = 9;

class SudokuGenerator {
public:
    vector<vector<int>> generate() {
        vector<vector<int>> grid(GRID_SIZE, vector<int>(GRID_SIZE, 0));
        generateSudoku(grid);
        return grid;
    }

private:
    bool isValid(vector<vector<int>>& grid, int row, int col, int num) {
        return !usedInRow(grid, row, num) && !usedInCol(grid, col, num) && !usedInBox(grid, row - row % 3, col - col % 3, num) && grid[row][col] == 0;
    }

    bool usedInRow(vector<vector<int>>& grid, int row, int num) {
        for (int col = 0; col < GRID_SIZE; ++col) {
            if (grid[row][col] == num) {
                return true;
            }
        }
        return false;
    }

    bool usedInCol(vector<vector<int>>& grid, int col, int num) {
        for (int row = 0; row < GRID_SIZE; ++row) {
            if (grid[row][col] == num) {
                return true;
            }
        }
        return false;
    }

    bool usedInBox(vector<vector<int>>& grid, int boxStartRow, int boxStartCol, int num) {
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if (grid[row + boxStartRow][col + boxStartCol] == num) {
                    return true;
                }
            }
        }
        return false;
    }

    bool findEmptyLocation(vector<vector<int>>& grid, int& row, int& col) {
        for (row = 0; row < GRID_SIZE; ++row) {
            for (col = 0; col < GRID_SIZE; ++col) {
                if (grid[row][col] == 0) {
                    return true;
                }
            }
        }
        return false;
    }

    bool generateSudoku(vector<vector<int>>& grid) {
        int row, col;
        if (!findEmptyLocation(grid, row, col)) {
            return true; // No empty location found, puzzle filled successfully
        }

        for (int num = 1; num <= 9; ++num) {
            if (isValid(grid, row, col, num)) {
                grid[row][col] = num;

                if (generateSudoku(grid)) {
                    return true;
                }

                grid[row][col] = 0; // Reset if solution not found
            }
        }
        return false; // Trigger backtracking
    }
};

void printGrid(vector<vector<int>>& grid) {
    system("cls");
    for (int i = 0; i < GRID_SIZE; ++i) {
        if (i % 3 == 0 && i != 0) {
            cout << "---------------------" << endl;
        }
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (j % 3 == 0 && j != 0) {
                cout << "| ";
            }
            if (grid[i][j] == 0) {
                cout << "_ ";
            } else {
                cout << grid[i][j] << " ";
            }
        }
        cout << endl;
    }
}

bool checkWin(vector<vector<int>>& grid) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid[i][j] == 0) {
                return false; // Puzzle not complete yet
            }
        }
    }
    return true; // Puzzle complete
}

vector<vector<int>> generateNewPuzzle() {
    SudokuGenerator generator;
    vector<vector<int>> solution = generator.generate();
    vector<vector<int>> puzzle = solution;

    int numToHide = 40; // Adjust the difficulty by changing this number
    while (numToHide > 0) {
        int row = rand() % GRID_SIZE;
        int col = rand() % GRID_SIZE;
        if (puzzle[row][col] != 0) {
            puzzle[row][col] = 0;
            numToHide--;
        }
    }

    return puzzle;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for randomization

    cout << "Welcome to Sudoku!" << endl;
    cout << "Fill in the missing numbers (use 0 for empty spaces):" << endl;

    vector<vector<int>> puzzle = generateNewPuzzle();

    while (!checkWin(puzzle)) {
        cout << "\nCurrent Sudoku Puzzle:" << endl;
        printGrid(puzzle);

        int row, col, num;
        cout << "\nEnter Row, Column, and Number (space-separated, 1-9): ";
        cin >> row >> col >> num;

        if (row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9) {
            cout << "Invalid input. Please enter valid values (1-9)!" << endl;
            continue;
        }

        if (puzzle[row - 1][col - 1] != 0) {
            cout << "This cell is already filled. Try again." << endl;
        } else {
            puzzle[row - 1][col - 1] = num;
        }
    }

    cout << "\nCongratulations! You solved the Sudoku puzzle:" << endl;
    printGrid(puzzle);

    return 0;
}
