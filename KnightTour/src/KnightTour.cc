/**@file KnightTour.cc
 @author Caleb Reister <calebreister@gmail.com>
 @brief Finds a solution for the Knight's Tour on a given chess board via brute force.
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

/**@struct Board

 This struct is a package for a simple 2d array (10x10). The size can be the actual index or
 anything smaller. I am using it for a recusive function for enerating the Knight's Tour.
 */
struct Board {
        Board();
        unsigned short size = 10;
        int a[10][10];
};

int solveKnightTour(Board board, ostream& output, int row, int col,
                    unsigned int& currentSolution, int currentMove = 1);
void printBoard(const Board& board, ostream& output);

int main() {
    Board board;
    int startPos[2];

    //cerr forces console output even when data is being output
    //to a file in the command line
    cerr << "KNIGHT'S TOUR SOLVER" << endl
         << "--------------------" << endl << endl;

    cerr << "Board Size (3-10): ";
    cin >> board.size;
    if (board.size > 10)
        board.size = 10;
    else if (board.size < 3)
        board.size = 3;
    if (board.size >= 7)
    {
        char prompt;
        cerr << "The size you have chosen will take a very long time."
             << "Are you sure you want to continue? [y/n] ";
        cin >> prompt;
        if (prompt != 'y')
            return 0;
    }

    cerr << "Starting Position (x y): ";
    cin >> startPos[0] >> startPos[1];
    if (startPos[0] > board.size)
        startPos[0] = board.size;
    if (startPos[1] > board.size)
        startPos[1] = board.size;
    cerr << "WORKING..." << endl << endl;

    cout << "Board Size: " << board.size << "x" << board.size << endl
         << "Starting Position: " << '(' << startPos[0] << ", " << startPos[1] << ')' << endl;

    unsigned int solutions = 0;
    solveKnightTour(board, cout, startPos[0] - 1, startPos[1] - 1, solutions);
    if (solutions == 0)
        cerr << "NO SOLUTION";

    return 0;
}

Board::Board() {
    for (int y = 0; y < 7; y++)
        for (int x = 0; x < 7; x++)
            a[x][y] = -1;
}

/**@int solveKnightTour(Board board, int row, int col, int currentMove, ostream& output)
 @brief Recursively solves the knights tour using brute force. Prints any solutions it finds.
 
 @param board[io] The board we’re working with (board with previous moves and size)
 @param output[out] The output stream to use (can by anything that inherits ostream)
 @param row[in] The row we’re going to attempt to place the knight on this move.
 @param col[in] The column we’re going to attempt place the knight on this move.
 @param currentSolution[io] The solution counter, uses an external variable
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
int solveKnightTour(Board board, ostream& output, int row, int col,
                    unsigned int& currentSolution, int currentMove) {
    //create an array of 8 arrays of 2 ints
    static const int MOVE[8][2] = {{2, -1}, {1, -2}, {-1, -2}, {-2, -1},
                                   {-2, 1}, {-1, 2}, {1, 2}, {2, 1}};

    board.a[row][col] = currentMove;

    for (int i = 0; i < 8; i++)
    {
        //base case
        if (currentMove == pow(board.size, 2))
        {
            currentSolution++;
            cout << endl << "Solution #" << currentSolution << endl;
            printBoard(board, output);
            return currentSolution;
        }

        //general case, only make new call if MOVE works
        if ((row + MOVE[i][0] < board.size) && (row + MOVE[i][0] >= 0) &&
            (col + MOVE[i][1] < board.size) && (col + MOVE[i][1] >= 0) &&
            (board.a[row + MOVE[i][0]][col + MOVE[i][1]] == -1))
            solveKnightTour(board, output, row + MOVE[i][0], col + MOVE[i][1],
                            currentSolution, currentMove + 1);
    }

    return currentSolution;
}

/**@fn void printBoard(const Board& board, ostream& output)
 @brief Prints a board to any output stream.
 @param board The board to print
 @param output The stream to use, can be cout, a file, a string stream, etc
 */
void printBoard(const Board& board, ostream& output) {
    for (int y = 0; y < board.size; y++)
    {
        for (int x = 0; x < board.size; x++)
            output << setw(2) << setfill('0') << board.a[x][y] << " ";
        output << endl;
    }
}
