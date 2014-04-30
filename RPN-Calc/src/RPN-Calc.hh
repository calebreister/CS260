/**@file RPN-Calc.hh
 * @author Caleb Reister <calebreister@gmail.com>
 */

#ifndef RPN_CALC_HH
#define RPN_CALC_HH

#include <stack>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <exception>
#include <stdexcept>
#include <utility>
#include <cstdlib>
#include <cstring>

const std::string NUMBERS = "1234567890";
const std::string OPERATORS = "+-*/";
const std::string LEGAL = NUMBERS + OPERATORS + "()Q";

/////////////////////////////////////////////////////////////////
///@brief An exception class that is thrown when an illegal character is entered by the user
struct illegal_char : public std::exception
{
  const char * what() const throw ()
  {
    return "Invalid character";
  }
};

///@brief Thrown when the user enters mismatching parenthesis
struct open_paren : public std::exception
{
  const char * what() const throw ()
  {
    return "Parenthesis do not match.";
  }
};

///@brief Thrown when an operator is placed at the end of an infix expression
struct op_at_end : public std::exception
{
  const char * what() const throw ()
  {
    return "An operator was placed at the end of the infix expression.";
  }
};

/////////////////////////////////////////////////////////////////////////////////////
std::string userInput();
void validateInfix(std::string& infix) throw (illegal_char, open_paren, op_at_end);
std::string postfixify(const std::string& infixEqn);
float evaluatePostfix(std::string postfixEqn);
int getPrecedence(char op);
int countChar(const std::string& input, char ch);

//////////////////////////////////////////////////////////////////////////////////
//Curly brace formatting rule:
//Anything that is commonly nested needs a curly brace on its own line.
//This includes for and while loops, and if/else if/else statements
//Switches will easily get confusing if they are nested, so the top brace
//can be on the same line as the switch.
//Other statements that can have the brace on 1 line are:
//functions, classes/structs, initializer lists, lambda functions,
//try/catch statements, and enums

#endif
