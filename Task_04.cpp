// Implement a Sudoku Solver :

#include <iostream>
#include <vector>

using namespace std;

#define N 9

bool isSafe(int grid[N][N], int row, int col, int num);
bool solveSudoku(int grid[N][N]);
bool findEmptyLocation(int grid[N][N], int &row, int &col);
void printGrid(int grid[N][N]);

int main() {
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid)) {
        cout << "Sudoku puzzle solved successfully:\n";
        printGrid(grid);
    } else {
        cout << "No solution exists for the given Sudoku puzzle.\n";
    }

    return 0;
}

bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if 'num' is not in current row
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num) {
            return false;
        }
    }

    // Check if 'num' is not in current column
    for (int x = 0; x < N; x++) {
        if (grid[x][col] == num) {
            return false;
        }
    }

    // Check if 'num' is not in current 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

bool findEmptyLocation(int grid[N][N], int &row, int &col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool solveSudoku(int grid[N][N]) {
    int row, col;

    // If there is no unassigned location, we are done
    if (!findEmptyLocation(grid, row, col)) {
        return true;
    }

    // Consider digits 1 to 9
    for (int num = 1; num <= 9; num++) {
        // Check if looks promising
        if (isSafe(grid, row, col, num)) {
            // Make tentative assignment
            grid[row][col] = num;

            // Return if success
            if (solveSudoku(grid)) {
                return true;
            }

            // Failure, unmake & try again
            grid[row][col] = 0;
        }
    }

    return false; // This triggers backtracking
}

void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}