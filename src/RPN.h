#ifndef RPN_H
#define RPN_H

float substitute(char* expression, float x, int* flag);
void reversed_polish_notation(char* expression, char* rpn, int* flag);
int is_digit(char c);
int is_operator(char c);
int get_precedence(char operator);
float applyOperator(char operatorChar, float operand1, float operand2);

#endif /* RPN_H */
