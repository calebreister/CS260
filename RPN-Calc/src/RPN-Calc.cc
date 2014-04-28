/**@file Stack.cc
 * @author Caleb Reister <calebreister@gmail.com>
 */

#include <cassert>
#include <stack>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <exception>
#include <stdexcept>
#include <utility>
using namespace std;

const string NUMBERS = "1234567890.";
const string OPERATORS = "+-*/";
const string LEGAL = NUMBERS + OPERATORS + "()Q";

string userInput();
void validateInfix(string& infix) throw (std::invalid_argument);
string postfixify(string infixEqn);
long double evaluatePostfix(string postfixEqn);
int getPrecedence(char op);

////////////////////////////////////////////////////////////////////////////////////
int main() {
    cout << "LEGAL CHARACTERS: \"1234567890+-*/()Q.,\"\n"
         << "Entering \"Q\" quits the program.\n"
         << "Please enter an equation to be evaluated...\n";
    string eqn;
    do
    {
        eqn = userInput();
        if (eqn != "Q")
        {
            //not necessarily the best application for exceptions, but
            //I figured it would be a good time to learn.
            try
            {
                validateInfix(eqn);
            }
            catch (std::invalid_argument&)
            {
                cout << "\"" << eqn << "\" is invalid. Please make "
                     << "sure you only use legal characters.\n";
            }
            cout << postfixify(eqn) << endl;
        }
    } while (eqn != "Q");
}

////////////////////////////////////////////////////////////////////////////////////////
///@brief Accepts and returns an infix expression from the user.
string userInput() {
    string input;
    cout << "-> ";
    getline(cin, input);
    return input;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/**@brief Removes whitespace and searches for invalid characters in an infix equation
 * @param infix The infix equation to format and validate
 * @throws std::invalid_argument
 *
 * Note that this function relies on the following statements:
 * const string NUMBERS = "1234567890.";
 * const string OPERATORS = "+-*()/";
 * const string LEGAL = NUMBERS + OPERATORS + "Q";
 */
void validateInfix(string& infix) throw (std::invalid_argument) {
    infix.erase(remove_if(infix.begin(), infix.end(),  //beginning and end iterators for std::remove
                [](char x) {return std::isspace(x);}),  //find all whitespace, lambda expression
                infix.end());  //end iterator for infix.erase()
    /* Lambda expression syntax
     * [ capture ] ( params ) { body }
     *
     * Capture pulls in variables from the current scope
     [a,&b] where a is captured by value and b is captured by reference.
     [this] captures the this pointer by value
     [&] captures all automatic variables mentioned in the body of the lambda by reference
     [=] captures all automatic variables mentioned in the body of the lambda by value
     [] captures nothing
     */
    cout << infix << endl;
    for (unsigned int i = 0; i < infix.length(); i++)
        if (LEGAL.find(infix[i]) == string::npos)  //search for invalid characters
            throw std::invalid_argument(infix);

    cout << "\nInfix: " << infix << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/**@brief Converts postfix to infix, expects a valid expression
 * @param infixEqn the infix equation to convert
 * @return the postfix expression
 */
string postfixify(string infixEqn) {
    string postfix = "";
    std::stack<char> operations;

    //iterate thru the input
    for (unsigned int i = 0; i < infixEqn.length(); i++)
    {
        if (NUMBERS.find(infixEqn[i]) != string::npos)  //if it is a number
        {
            //keep going until an operator is found
            //while the character at i is a number
            //while (NUMBERS.find(infixEqn[i]) != string::npos)
            //{
                postfix += infixEqn[i];  //append the number
                //i++;  //advance i
            //}
            //postfix += ",";  //comma-delimits numbers
            //i--;
        }

        else if (infixEqn[i] == '(')
            operations.push(infixEqn[i]);

        else if (OPERATORS.find(infixEqn[i]) != string::npos)
        {
                while (!operations.empty() &&
                       getPrecedence(operations.top()) >= getPrecedence(infixEqn[i]))
                {
                        postfix += operations.top();
                        operations.pop();
                }
            operations.push(infixEqn[i]);
        }

        else if (infixEqn[i] == ')')
        {
            while (!operations.empty() && operations.top() != '(')
            {
                postfix += operations.top();
                operations.pop();
            }
        }

        if (!operations.empty() && operations.top() == '(')
            operations.pop();
    }

    while (!operations.empty())
    {
        postfix += operations.top();
        operations.pop();
    }

    return postfix;
}

///////////////////////////////////////////////////////////////////////////////////////////
long double evaluatePostfix(string postfixEqn) {

}

//////////////////////////////////////////////////////////////////////////////////////////
int getPrecedence(char op) {
    switch (op)
    {
        case '+':
        case '-':
        return 1;
        break;

        case '*':
        case '/':
        return 2;
        break;

        case '(':
        return 3;
        break;
    }
}
