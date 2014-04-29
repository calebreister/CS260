/**@file Stack.cc
 * @author Caleb Reister <calebreister@gmail.com>
 */

#include <cassert>
#include "RPN-Calc.hh"
using namespace std;

const string NUMBERS = "1234567890.";
const string OPERATORS = "+-*/";
const string LEGAL = NUMBERS + OPERATORS + "()Q";
//const char DELIM = '';  //Delimiter for postfix string

// Curly brace formatting rule:
//Anything that is commonly nested needs a curly brace on its own line.
//This includes for and while loops, and if/else if/else statements
//Switches will easily get confusing if they are nested, so the top brace
//can be on the same line as the switch.
//Other statements that can have the brace on 1 line are:
//functions, classes/structs, initializer lists, lambda functions,
//try/catch statements, and enums
////////////////////////////////////////////////////////////////////////////////////
int main() {
    cout << "LEGAL CHARACTERS: \"1234567890+-*/()Q.,\"\n"
         << "Entering \"Q\" quits the program.\n"
         << "Please enter an equation to be evaluated...\n";
    string eqn;
    do
    {
        eqn = userInput();  //infix equation
        string pfixEqn;  //postfix equation
        if (eqn != "Q")
        {
            //not necessarily the best application for exceptions, but
            //I figured it would be a good time to learn.
            try {
                validateInfix(eqn);
            }
            catch (open_paren&) {
                cout << "\"" << eqn << "\" is invalid. Please make "
                     << "sure you have matching parenthesis.\n";
            }
            catch (op_at_end&) {
                cout << "\"" << eqn << "\" is invalid. No operators"
                     << " at the end of an expression.\n";
            }
            catch (illegal_char&) {
                cout << "\"" << eqn << "\" is invalid. Please make "
                     << "sure you only use legal characters.\n";
            }
            cout << "\nInfix: " << eqn << endl;
            pfixEqn = postfixify(eqn);
            cout << "Postfix: " << pfixEqn << endl;
            cout << "Result: " << evaluatePostfix(pfixEqn) << endl;
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
void validateInfix(string& infix) throw (illegal_char, open_paren, op_at_end) {
    infix.erase(remove_if(infix.begin(), infix.end(),  //beginning and end iterators for std::remove
                [](char x) {return std::isspace(x);}),  //find all whitespace, lambda expression
                infix.end());  //end iterator for infix.erase()
    /* Lambda expression syntax (cppreference.com)
     * [ capture ] ( params ) { body }
     *
     * Capture pulls in variables from the current scope
     [a,&b] where a is captured by value and b is captured by reference.
     [this] captures the this pointer by value
     [&] captures all automatic variables mentioned in the body of the lambda by reference
     [=] captures all automatic variables mentioned in the body of the lambda by value
     [] captures nothing
     */

    if (countChar(infix, '(') != countChar(infix, ')'))
            throw open_paren();

    switch (infix[infix.length() - 1]) {
        case '+':
        case '-':
        case '*':
        case '/':
        throw op_at_end();
        break;
    }

    for (string::size_type i = 0; i < infix.length(); i++)
        if (LEGAL.find(infix[i]) == string::npos)  //search for invalid characters
            throw illegal_char();
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/**@brief Converts postfix to infix, expects a valid expression
 * @param infixEqn the infix equation to convert
 * @return the postfix expression
 *
   Based roughly on this algorithm....

   For each item in the infix expression
        If it is a number
            append it to postfix string.
        else If it is a left parenthesis
            push it onto the stack
        else If it is an operator (+,-,*,/)
            If the stack is not empty
                while the operator on the top of the stack is >= precedence
                    pop the operator and append it to postfix expression
            push operator onto the stack
        else If it is right parenthesis then
            while the stack is not empty and top not equal to left parenthesis
                Pop from stack and append to postfix expression
            pop out the left parenthesis and discard it
        While stack is not empty
            pop and append to the postfix string.
 */
string postfixify(const string& infixEqn) {
    string postfix = "";
    std::stack<char> operations;

    //iterate thru the input
    for (string::size_type i = 0; i < infixEqn.length(); i++)
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
            //i--;
            //postfix += DELIM;
        }

        else if (infixEqn[i] == '(')
            operations.push(infixEqn[i]);

        else if (OPERATORS.find(infixEqn[i]) != string::npos)
        {
            //if (!operations.empty())
                while (!operations.empty() && getPrecedence(operations.top()) >= getPrecedence(infixEqn[i]))
                {
                        postfix += operations.top();
                        //postfix += DELIM;
                        operations.pop();
                }
            operations.push(infixEqn[i]);
        }

        else if (infixEqn[i] == ')')
        {
            while (!operations.empty() && operations.top() != '(')
            {
                postfix += operations.top();
                //postfix += DELIM;
                operations.pop();
            }
            operations.pop();
        }
    }

    while (!operations.empty())
    {
        postfix += operations.top();
        //postfix += DELIM;
        operations.pop();
    }

    postfix += '\0';
    return postfix;
}

///////////////////////////////////////////////////////////////////////////////////////////
/**@brief Evaluates a postfix expression, assumes that const char DELIM is defined.
 * @param postfixEqn A string containing a valid postfix (RPN) expression delimited with DELIM
 * @return The result of the calculation
 *
   Conversion algorithm from Wikipedia, converted to be fully iterative and suit my format.

   1. Read one character input at a time and keep pushing it into the character stack until the new
      line character is reached
   2. Perform pop from the character stack. If the stack is empty, go to step (3)
      Number: Push in to the integer stack and then go to step (1)
      Operator: Assign the operator to pop
      1. Pop a number from  integer stack and assign it to op1
      2. Pop another number from integer stack and assign it to op2
      3. Calculate op1 op op2 and push the output into the integer stack. Go to step (2)
   3. Pop the result from the integer stack and display the result
 */
long double evaluatePostfix(string postfixEqn) {
    stack<char> chStack;  //character stack
    stack<long double> numStack;  //number stack

    for (string::size_type i = 0; postfixEqn[i] != '\0'; i++)
    {
        chStack.push(postfixEqn[i]);

        if (NUMBERS.find(chStack.top()) != string::npos)
        {
            char* num = new char[2];
            num[0] = chStack.top();
            num[1] = '\0';
            chStack.pop();
            numStack.push(strtold(num, &num));
        }
        else if (OPERATORS.find(postfixEqn[i]) != string::npos)
        {
            long double op[2];  //operands
            op[1] = numStack.top();
            numStack.pop();
            op[0] = numStack.top();
            numStack.pop();

            switch (postfixEqn[i]) {
                case '+':
                numStack.push(op[0] + op[1]);
                break;

                case '-':
                numStack.push(op[0] - op[1]);
                break;

                case '*':
                numStack.push(op[0] * op[1]);
                break;

                case '/':
                numStack.push(op[0] / op[1]);
            }
        }
    }

    return numStack.top();
}

//////////////////////////////////////////////////////////////////////////////////////////
int getPrecedence(char op) {
    switch (op) {
        case '+':
        case '-':
        return 1;
        break;

        case '*':
        case '/':
        return 2;
        break;
    }

    //deals with parenthesis
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////
int countChar(const string& input, char ch) {
    int result = 0;
    for (string::size_type i = 0; i < input.length(); i++)
        if (input[i] == ch)
            result++;
    return result;
}
