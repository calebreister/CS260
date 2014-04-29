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

struct illegal_char : public std::exception
{
  const char * what() const throw ()
  {
    return "Invalid character";
  }
};

struct open_paren : public std::exception
{
  const char * what() const throw ()
  {
    return "Parenthesis do not match.";
  }
};

struct op_at_end : public std::exception
{
  const char * what() const throw ()
  {
    return "An operator was placed at the end of the infix expression.";
  }
};

std::string userInput();
void validateInfix(std::string& infix) throw (illegal_char, open_paren, op_at_end);
std::string postfixify(const std::string& infixEqn);
long double evaluatePostfix(std::string postfixEqn);
int getPrecedence(char op);
int countChar(const std::string& input, char ch);

/*Stack Implementation Example
 * //STACKS
/* Stacks can be implemented with either an array or a Linked List.
 *
 * Stacks MUST use LIFO
 * Last
 * IN
 * First
 * OUT
 *
 * Stack operations:
 * push - add something to the top
 * pop - remove something from the top
 *//*

#include <iostream>
using namespace std;

const unsigned int SIZE = 10;

class StackArray {
    private:
    unsigned int top = 0;
    int data[SIZE];

    public:
    bool push(int x) {
        if (top < SIZE)
        {
            data[top] = x;
            top++;
            return true;
        }
        else
            return false;
    }
    bool pop(int& x) {
        if (empty())
            return false;

        x = data[--top];
        return true;
    }
    bool empty() {
        return top == 0 ? true : false;
    }
};*/

/*
 * A LinkedList may or may not take more memory.
 * If you have an array of 1000 ints, but only use 10, the array is
 * far less efficient.
 * If you a linked list instead, it will be more efficient
 * However, a linked list of 1000 ints will take around 2x the space
 * of an array with 1000 ints.
 */
/*class StackLL {
    private:
    struct Node {
        int data;
        Node* next = NULL;
    };
    Node* top = NULL;

    public:
    bool empty() {
        return top == NULL ? true : false;
    }
    void push(int data) {
        Node* n = new Node;
        n->data = data;
        n->next = top;
        top = n;
    }
    bool pop(int& dataOut) {
        if (empty())
            return false;
        dataOut = top->data;
        Node* n2d = top;  //Node to delete
        top = top->next;
        delete n2d;
        return true;
    }
};


int main() {
    TEST CODE
    StackLL s;
    s.push(4);
    s.push(10);
    s.push(-56);
    s.push(1);

    int x;
    while (s.pop(x))
        cout << x << endl;
}
 */

#endif
