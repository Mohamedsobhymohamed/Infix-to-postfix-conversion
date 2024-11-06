# Infix Expression Evaluator
This project is a C program that converts and evaluates mathematical expressions written in infix notation by transforming them into postfix notation (Reverse Polish Notation) and calculating the result. It supports standard arithmetic operations and handles parentheses, decimals, and negative numbers.

# Features
Infix to Postfix Conversion: Converts infix expressions into postfix notation, respecting operator precedence and associativity.
Postfix Evaluation: Evaluates the resulting postfix expression to produce the final result.
Operator Support: Supports basic operators (+, -, *, /) and exponentiation (^).
Negative Numbers: Correctly interprets negative values in expressions.
Decimal Support: Handles floating-point numbers with decimal points.
Error Handling: Checks for invalid expressions and stack underflows.

# Prerequisites
To compile and run this program, you need:
A C compiler (like gcc).
Compilation
To compile the program, run:
gcc infix_evaluator.c -o infix_evaluator -lm
Usage
Run the executable:
./infix_evaluator
Enter an infix expression (e.g., (3 + 4) * 5 - 2).

The program will output the corresponding postfix expression and its evaluated result.

Example input and output:
Enter infix expression: (3 + 4) * 5 - 2
Postfix expression: 3 4 + 5 * 2 -
Value: 33.00
# Code Structure
infixToPostfix: Converts an infix expression to postfix notation.
evaluatePostfix: Evaluates a postfix expression and returns the final result.
Stack Implementation: Uses a linked list stack to handle operators and operands during conversion and evaluation.
Error Handling
The program provides feedback for:
Invalid characters in the expression.
Mismatched parentheses.
Invalid postfix expressions (stack underflow).
Example Expressions
3 + 4 * 2 / (1 - 5) ^ 2 ^ 3
-3 + (4.5 * 2) - 7 / (1 + 2)
