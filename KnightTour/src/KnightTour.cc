/**@file KnightTour.cc
 @author Caleb Reister <calebreister@gmail.com>
 @brief Finds a solution for the Knight's Tour on a given chess board via brute force.
 */

#include <iostream>
#include <fstream>
#include <sstream>
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

int solveKnightTour(Board board, int row, int col, int currentMove, ostream& output);
void printBoard(const Board& board, ostream& output);

int main() {
    Board board;
    ofstream outFile;
    int startPos[2];

    cout << "KNIGHT'S TOUR SOLVER" << endl
         << "--------------------" << endl << endl;

    cout << "Board Size (3-10): ";
    cin >> board.size;
    if (board.size > 10)
        board.size = 10;
    else if (board.size < 3)
        board.size = 3;
    if (board.size >= 7)
    {
        char prompt;
        cout << "The size you have chosen will take a very long time."
             << "Are you sure you want to continue? [y/n] ";
        cin >> prompt;
        if (prompt != 'y')
            return 0;
    }

    cout << "Starting Position (x y): ";
    cin >> startPos[0] >> startPos[1];
    if (startPos[0] > board.size)
        startPos[0] = board.size;
    if (startPos[1] > board.size)
        startPos[1] = board.size;

    //check to see if user wants output to go to file
    char fileIOPrompt;
    cout << "Do you want the data generated to be written to a file? [y/n] ";
    cin.ignore();
    cin >> fileIOPrompt;
    if (fileIOPrompt == 'y')
    {
        ostringstream* boardData;  //allows data to be stored in RAM and then output
        //to a file at the end, it is a pointer in order to prevent a stack overflow
        boardData = new ostringstream;
        string fileName;
        cout << "File Name (default KnightTour.txt): ";
        cin.ignore();
        getline(cin, fileName);
        cout << endl;
        if (fileName == "")
            fileName = "KnightTour.txt";

        cout << endl << "Working..." << endl << endl << endl;
        //do the Knight's Tour
        int solutions = solveKnightTour(board, startPos[0] - 1, startPos[1] - 1, 1, *boardData);
        cout << "SOLUTIONS: " << solutions << endl;  //output total solutions to console

        //output to file
        outFile.open(fileName.c_str(), ios::trunc);
        outFile << "BOARD:" << board.size << "x" << board.size << endl;
        outFile << "STARTING POSITION: (" << startPos[0] << ", " << startPos[1] << ")" << endl;
        outFile << "SOLUTIONS: " << solutions << endl << endl << endl;
        outFile << boardData->str();
        delete boardData;
        boardData = NULL;
        outFile.close();
    }
    else
    {
        int solutions = solveKnightTour(board, startPos[0] - 1, startPos[1] - 1, 1, cout);
        if (solutions == 0)
            cout << "NO SOLUTION";
    }

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

    if (row >= board.size || row < 0 ||
             col >= board.size || col < 0)  //BOUND CHECK
        return 0;
    else if (board.a[row][col] == -1)  //SPACE OPEN?
    {
        board.a[row][col] = currentMove;
        currentMove++;
        for (int i = 0; i < 8; i++)
            solveKnightTour(board, row + MOVE[i][0], col + MOVE[i][1],
                            currentMove, output);
    }
    else if (currentMove == pow(board.size, 2) + 1)  //SOLUTION FOUND
        {
            solutions++;
            //output every 1000 solutions found
            if (solutions % 1000 == 0)
                cout << "SOLUTIONS FOUND: " << solutions << endl;
            output << "Solution #" << solutions << endl;  //header of every solution
            printBoard(board, output);
            return solutions;
        }
    return solutions;
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
    output << endl;
}
