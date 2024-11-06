#include<iostream>
#include<vector>

using namespace std;

//Functions to check if placing a queen at (row,col) is a safe
bool isSafe(vector<vector<int>>& board, int row, int col, int n){

    //Check for other queens in the same column
    for(int i = 0; i < row;i++){
        if(board[i][col] == 1) return false;
    }

    //Check for other queens in the upper left diagonal
    for(int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--){
        if(board[i][j] == 1) return false;
    }

    //Check for other queens in the upper right diagonal
    for(int i = row - 1, j = col + 1; i >= 0 && j < n; i--,j++){
        if(board[i][j] == 1) return false;
    }

    return true;
}

//Function to slove the N-Queens problem using backtracking
bool solveNQueens(vector<vector<int>>& board, int row,int n){
    //Base case : if all queens are placed
    if(row >= n) return true;

    if(row == 0 ) return solveNQueens(board, row + 1, n);

    //Try placing  queen in all columns of the current row
    for(int col = 0; col < n; col++){
        if(isSafe(board,row,col,n)){
            board[row][col] = 1; // place queen

            //Recursive call to place the next queen
            if(solveNQueens(board,row + 1, n)) return true;

            board[row][col] = 0; //Backtrack if placing a queen here doesn't lead to a solution
        }
    }

    return false; //If no placement is possible is this row
}

//Function to print the board
void printBoard(const vector<vector<int>>& board, int n){
    for(int i = 0; i < n;i++){
        for(int j = 0; j < n;j++){
            cout<<(board[i][j] == 1 ? "Q" : ". ");
        }
        cout<<endl;
    }
}

int main(){
    int n, startRow, startCol;

    cout<<"Enter the size of the board (n): ";
    cin>>n;

    //Initialize the board
    vector<vector<int>> board(n,vector<int>(n,0));

    //Get the starting position for the first queen
    cout<<"Enter the row and column of the first queen (0-based index): ";
    cin>>startRow>>startCol;

    //Place the first queen
    board[startRow][startCol] = 1;

    //Try to place remaining queens
    if(solveNQueens(board, 1, n)){
        cout<<" Solution:\n";
        printBoard(board,n);
    }else{
        cout<<"No solution exists for the given placement.\n";
    }

    return 0;
}