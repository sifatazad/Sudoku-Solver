#include<stdio.h>
#include<stdbool.h>

static void grid_print(int rank,int grid[rank][rank]) {
    printf("-------------------------\n");
    for (int i=0; i<rank; i++) {
        for (int j=0; j<rank; j++) {
            if (j==0) {
                printf("| %d ",grid[i][j]);
            }
            if ((j+1)%3==0)
                printf("%d | ",grid[i][j]);
            else if (j!=0)
                printf("%d ",grid[i][j]);
        }
        if ((i+1)%3==0)
            printf("\n-------------------------\n");
        else
            printf("\n");
    }
}

static bool is_ok(int rank,int row,int col,int grid[rank][rank],int x) {
    // Horizontal check
    for (int i=0; i<rank; i++) {
        if (grid[row][i]==x)
            return false;
    }

    // Vertical check
    for (int i=0; i<rank; i++) {
        if (grid[i][col]==x)
            return false;
    }

    // 3X3 block check
    int start_row=(row/3)*3;
    int start_col=(col/3)*3;

    for (int i=start_row; i<=start_row+2; i++) {
        for (int j=start_col; j<=start_col+2; j++) {
            if (grid[i][j]==x)
                return false;
        }
    }

    return true;
}

static bool solve_sudoku(int rank,int row,int col,int grid[rank][rank]) {
    if (row==rank-1 && col==rank) {
        return true;
    }

    if (col==rank) {
        col=0;
        row++;
    }

    if (grid[row][col]>0)
        return solve_sudoku(rank,row,col+1,grid);

    for (int i=1; i<=9; i++) {
        if (is_ok(rank,row,col,grid,i)) {
            grid[row][col]=i;

            if (solve_sudoku(rank,row,col+1,grid))
                return 1;
        }
        grid[row][col]=0;
    }
    return false;
}

int main() {
    int rank=9;
    int grid[9][9]={
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };

    if (solve_sudoku(rank,0,0,grid)) {
        grid_print(rank,grid);
    }
    else {
        printf("There's no solution\n");
    }
}