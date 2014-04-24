/**@file Stack.cc
 * @author Caleb Reister <calebreister@gmail.com>
 */

#include <stack>
#include <string>
#include <iostream>
using namespace std;

const string NUMBERS = "1234567890.";
const string OPERATORS = "+-*/()";
const string LEGAL = NUMBERS + "+-*/()Q";

string userInput();
string postfixify(string infixEqn);
double evaluatePostfix(string postfixEqn);

int main() {
    cout << "LEGAL CHARACTERS: \"1234567890+-*/()Q.,\"\n"
         "Entering \"Q\" quits the program."
         "Please enter an equation to be evaluated...\n";
    string eqn;
    do
    {
        eqn = userInput();
        if (eqn == "\0")
            cout << "The equation entered is invalid. Please make"
                 "sure you only use legal characters.\n";
        else
        {

        }
    } while (eqn != "Q");
}

/**@brief Accepts and verifies an infix expression from the user.
 * @return The verified input string from the user, with whitespace removed.
 */
string userInput() {
    string input;
    cout << "-> ";
    getline(cin, input);

    for (int i = 0; i < input.length(); i++)
    {
        //automatically ignore whitespace
        switch (input[i])
        {
            case ' ':
            case '\t':
            input.erase(i);
            break;

            default:
            if (LEGAL.find(input[i]) == string::npos)
                return "\0";  //error condition, an invalid character was found
            break;
        }
    }

    cout << "\nInfix: " << input << endl;
    return input;
}

string postfixify(string infixEqn) {
    string postfix = "";

    //iterate thru the input
    for (int i = 0; i < infixEqn.length(); i++)
    {
        if (NUMBERS.find(infixEqn[i]))  //if it is a number
        {
            //keep going until an operator is found
            //while (NUMBERS.find(infixEqn[i]))
        }
    }

    return postfix;
}

double evaluatePostfix(string postfixEqn) {

}
