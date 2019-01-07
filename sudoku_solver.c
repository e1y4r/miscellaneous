#include <stdio.h>

bool canPut(char board[9][9], int i, int j, char v) {
    for(int k = 0; k < 9; k++) {
        if(board[i][k] == v 
           || board[k][j] == v 
           || board[i / 3 * 3 + k % 3][j / 3 * 3 + k / 3] == v) {
            return false;
        }
    }
    return true;
}
void printBoard(char board[9][9]) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

bool solveSudoku(char board[9][9]) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(board[i][j] == '.') {
                bool numberAvailable = false;
                for(char v = '1'; v <= '9'; v++) {
                    if(canPut(board, i, j, v)) {
                        numberAvailable = true;
                        board[i][j] = v;
                        if(solveSudoku(board)) {
                            return true;
                        } else  {
                            board[i][j] = '.';
                            numberAvailable = false;
                        }
                    }
                }
                if(!numberAvailable) {
                    return false;
                }
            } // if .
        } // for j
    } // for i
    return true;
}
int main() {
    char board[9][9] = {{'5','3','.','.','7','.','.','.','.'}
    ,{'6','.','.','1','9','5','.','.','.'},{'.','9','8','.','.','.','.','6','.'},{'8','.','.','.','6','.','.','.','3'},{'4','.','.','8','.','3','.','.','1'},{'7','.','.','.','2','.','.','.','6'},{'.','6','.','.','.','.','2','8','.'},{'.','.','.','4','1','9','.','.','5'},{'.','.','.','.','8','.','.','7','9'}};
    printBoard(board);
    printf("\n");
    solveSudoku(board);
    printBoard(board);
    getchar();
    return 0;

}
