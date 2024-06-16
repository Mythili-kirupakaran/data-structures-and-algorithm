#include <stdio.h>

#define N 9

int grid[N][N];

void printGrid() {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            printf("%2d", grid[row][col]);
        printf("\n");
    }
}

int isSafe(int row, int col, int num) {
    // Check if 'num' is not in the current row
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num)
            return 0;

    // Check if 'num' is not in the current column
    for (int x = 0; x < N; x++)
        if (grid[x][col] == num)
            return 0;

    // Check if 'num' is not in the current 3x3 box
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return 0;

    return 1;
}

int solveSudoku() {
    int row, col, num;
    int isEmpty = 0;
    
    // Find an empty cell
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                isEmpty = 1;
                break;
            }
        }
        if (isEmpty)
            break;
    }
    
    // No empty cell means the Sudoku is solved
    if (!isEmpty)
        return 1;

    // Try numbers 1 through 9
    for (num = 1; num <= 9; num++) {
        if (isSafe(row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku())
                return 1;
            grid[row][col] = 0;
        }
    }
    return 0;
}

int main() {
    printf("Enter the Sudoku grid (use 0 for empty cells):\n");
    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++)
            scanf("%d", &grid[row][col]);

    if (solveSudoku() == 1)
        printGrid();
    else
        printf("No solution exists");

    return 0;
}
