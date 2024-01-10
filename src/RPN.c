#include "RPN.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parsing.h"
#include "stack.h"

int is_digit(char c) { return c >= '0' && c <= '9'; }

int is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '~' || c == 's' || c == 'c' || c == 't' ||
           c == 'g' || c == 'l' || c == 'r';
}

int get_precedence(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '~':
        case 's':
        case 'c':
        case 't':
        case 'g':
        case 'l':
        case 'r':
            return 3;
        default:
            return 0;
    }
}

void reversed_polish_notation(char* expression, char* rpn, int* flag) {
    stack stack;
    init(&stack);
    int len = strlen(expression);
    int rpnIndex = 0;
    for (int i = 0; i < len; i++) {
        if (is_digit(expression[i])) {
            while (is_digit(expression[i]) || expression[i] == '.') {
                rpn[rpnIndex++] = expression[i++];
            }
            rpn[rpnIndex++] = ' ';
            i--;
        } else if (is_operator(expression[i])) {
            push(&stack, expression[i]);

            while (!is_empty(&stack) && get_precedence(peek(&stack, flag)) > get_precedence(expression[i])) {
                rpn[rpnIndex++] = pop(&stack, flag);
                rpn[rpnIndex++] = ' ';
            }

        } else if (expression[i] == '(') {
            push(&stack, expression[i]);
        } else if (expression[i] == ')') {
            while (peek(&stack, flag) != '(') {
                rpn[rpnIndex++] = pop(&stack, flag);
                rpn[rpnIndex++] = ' ';
            }
            pop(&stack, flag);

        } else if (expression[i] == 'x') {
            rpn[rpnIndex++] = 'x';
            rpn[rpnIndex++] = ' ';
        } else {
            printf("Invalid input");
        }
    }
    while (!is_empty(&stack)) {
        rpn[rpnIndex++] = pop(&stack, flag);
        rpn[rpnIndex++] = ' ';
    }
    rpn[rpnIndex] = '\0';
    clear(&stack);
}

float substitute(char* rpn, float x, int* flag) {
    stack stack;
    init(&stack);
    int len = strlen(rpn);
    for (int i = 0; i < len; i++) {
        if (is_digit(rpn[i])) {
            float num = atof(&rpn[i]);  // str to float
            while (is_digit(rpn[i]) || rpn[i] == '.') {
                i++;
            }
            push(&stack, num);
            i--;
        } else if (is_operator(rpn[i])) {
            float result = 0.0;
            float operand2 = pop(&stack, flag);
            switch (rpn[i]) {
                case '+':
                    result = pop(&stack, flag) + operand2;
                    break;
                case '-':
                    result = pop(&stack, flag) - operand2;
                    break;
                case '*':
                    result = pop(&stack, flag) * operand2;
                    break;
                case '/':
                    if (operand2 != 0.0) {
                        result = pop(&stack, flag) / operand2;
                    } else {
                        result = 2;
                    }
                    break;
                case '~':
                    result = -operand2;
                    break;
                case 's':
                    result = sin(operand2);
                    break;
                case 'c':
                    result = cos(operand2);
                    break;
                case 't':
                    result = tan(operand2);
                    break;
                case 'g':
                    result = 1 / tan(operand2);
                    break;
                case 'l':
                    result = log(operand2);
                    break;
                case 'r':
                    result = sqrt(operand2);
                    break;
            }
            push(&stack, result);
        } else if (rpn[i] == 'x') {
            push(&stack, x);
        }
    }
    float result = pop(&stack, flag);
    clear(&stack);
    return result;
}