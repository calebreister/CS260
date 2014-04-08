/**@file KnightTour.cc
 * @author Caleb Reister <calebreister@gmail.com>
 *
 * Finds a solution for the Knight's Tour on a given chess board via brute force.
 * Recursion practice.
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

struct Board {
        Board();
        int size = 7;
        int a[7][7];
};

int solveKnightTour(Board board, int row, int col, int currentMove = 1);

int main() {
    Board board;
    int startPos[2];
    cout << "KNIGHT'S TOUR SOLVER" << endl << endl;

    cout << "Board Size (3-7): ";
    cin >> board.size;
    if (board.size > 7)
        board.size = 7;
    else if (board.size < 3)
        board.size = 3;

    cout << "Starting Position (x y): ";
    cin >> startPos[0] >> startPos[1];
    for (int i; i < startPos; i++)
        if (startPos[i] > board.size)
            startPos[i] = board.size;

    cout << endl << "Working";
}

Board::Board() {
    for (int y = 0; y < 7; y++)
        for (int x = 0; x < 7; x++)
            a[x][y] = -1;
}

/**@fn int solveKnightTour(Board board, int row, int col, int currentMoveNum = 1)
 @brief Recursively solves the knights tour using brute force. Prints any solutions it finds.
 @param board[io] The board we’re working with (board with previous moves and size)
 @param row[in] The row we’re going to attempt to place the knight on this move.
 @param col[in] The column we’re going to attempt place the knight on this move.
 @param currentMove[in] The move we’re making (1 = first placement, 16 = last placement on 4x4 board)
 @return The number of solutions the given board and move leads to

 Note: row and col may be invalid (<0 or >=boardsize) or already taken (<currentMoveNum)

 Possible positions to move (5x5 example, * is start)...
 + =  =  =  =  =
 |    6     7
 | 5           8
 |       *
 | 4           1
 |    3     2
 */
int solveKnightTour(Board board, int row, int col, int currentMove = 1) {
    cout << ".";
    board.a[row][col] = currentMove;
    currentMove++;
    if (currentMove == pow(board.size, 2))  //BASE CONDITION
        return currentMove;

    //GENERAL CONDITIONS
    else if (row + 2 <= board.size && col + 1 <= board.size
             && board.a[row + 2][col + 1] == -1)  //1
        return solveKnightTour(board, row + 2, col + 1, currentMove);
    else if (row + 1 <= board.size && col + 2 <= board.size
             && board.a[row + 1][col + 2] == -1)  //2
        return solveKnightTour(board, row + 1, col + 2, currentMove);

    else if (row - 1 >= 0 && col - 1 <= board.size
             && board.a[row - 1][col + 2] == -1)  //3
        return solveKnightTour(board, row - 1, col + 2, currentMove);
    else if (row - 2 >= 0 && col - 1 <= board.size
             && board.a[row - 2][col + 1] == -1)  //4
        return solveKnightTour(board, row - 2, col + 1, currentMove);

    else if (row - 2 >= 0 && col - 1 >= 0 && board.a[row - 2][col - 1] == -1)  //5
        return solveKnightTour(board, row - 2, col - 1, currentMove);
    else if (row - 1 >= 0 && col - 2 >= 0 && board.a[row - 1][col - 2] == -1)  //6
        return solveKnightTour(board, row - 1, col - 2, currentMove);

    else if (row + 1 <= board.size && col + 2 >= 0
             && board.a[row + 1][col - 2] == -1)  //7
        return solveKnightTour(board, row + 1, col + 2, currentMove);
    else if (row + 2 <= board.size && col + 1 >= 0
             && board.a[row + 2][col + 1] == -1)  //8
        return solveKnightTour(board, row + 2, col + 1, currentMove);

    else
    {
        cout << "NO SOLUTION" << endl;
        return -1;
    }
}
