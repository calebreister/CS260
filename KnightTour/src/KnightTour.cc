/**@file KnightTour.cc
 * @author Caleb Reister <calebreister@gmail.com>
 *
 * Finds a solution for the Knight's Tour on a given chess board via brute force.
 * Recursion practice.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

struct Board {
        Board();
        int size = 7;
        int a[8][8];
};

int solveKnightTour(Board board, int row, int col, int currentMove = 1,
                    ostream& output = cout);
void printBoard(const Board& board, ostream& output);

int main() {
    Board board;
    ofstream outFile;
    outFile.open("Knight's Tour.txt", ios::trunc);
    /*int startPos[2];
     cout << "KNIGHT'S TOUR SOLVER" << endl << endl;

     cout << "Board Size (3-7): ";
     cin >> board.size;
     if (board.size > 7)
     board.size = 7;
     else if (board.size < 3)
     board.size = 3;

     cout << "Starting Position (x y): ";
     cin >> startPos[0] >> startPos[1];
     for (int i; i < 2; i++)
     if (startPos[i] > board.size)
     startPos[i] = board.size;

     cout << endl << "Working..." << endl << endl;*/

    board.size = 5;
    int solutions = solveKnightTour(board, 0, 0, 1, outFile);// startPos[0] - 1, startPos[1] - 1);
    cout << "Working..." << endl << endl << endl;
    outFile <<
    cout << "SOLUTIONS: " << solutions;
    outFile.close();
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
int solveKnightTour(Board board, int row, int col, int currentMove, ostream& output) {
    //create an array of 8 arrays of 2 ints
    static const int MOVE[8][2] = {{2, -1}, {1, -2}, {-1, -2}, {-2, -1},
                                   {-2, 1}, {-1, 2}, {1, 2}, {2, 1}};
    static int solutions = 0;

    if (currentMove == pow(board.size, 2) + 1)  //SOLUTION FOUND
    {
        solutions++;
        //output every 1000 solutions found
        if (solutions % 1000 == 0)
            cout << "SOLUTIONS FOUND: " << solutions << endl << endl << endl;
        output << "Solution #" << solutions << endl;
        printBoard(board, output);
        return solutions;
    }
    else if (row >= board.size || row < 0 ||
             col >= board.size || col < 0)  //BOUND CHECK
        return 0;

    if (board.a[row][col] == -1)  //SPACE OPEN?
    {
        board.a[row][col] = currentMove;
        currentMove++;
        for (int i = 0; i < 8; i++)
            solveKnightTour(board, row + MOVE[i][0],
                            col + MOVE[i][1], currentMove, output);
    }
    return solutions;
}

void printBoard(const Board& board, ostream& output) {
    for (int y = 0; y < board.size; y++)
    {
        for (int x = 0; x < board.size; x++)
            output << setw(2) << setfill('0') << board.a[x][y] << " ";
        output << endl;
    }
    output << endl;
}
