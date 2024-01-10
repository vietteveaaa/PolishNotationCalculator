#include "parsing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RPN.h"

char *input() {
    int size = INIT_SIZE;
    int flag = 1;
    char *result = malloc(size * sizeof(char));
    if (result == NULL) {
        flag = 0;
    }
    int count = 0;
    while (1) {
        char symbol;
        scanf("%c", &symbol);
        ++count;
        if (count > size) {
            size *= 2;
            char *tmp = realloc(result, size * sizeof(char));
            if (tmp == NULL) {
                flag = 0;
                free(result);
            } else {
                result = tmp;
            }
        }
        if (symbol == '\n') {
            *(result + count - 1) = '\0';
            break;
        } else {
            *(result + count - 1) = symbol;
        }
    }
    if (!flag) {
        free(result);
    }
    return result;
}

void remove_whitespaces(char *str) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}

void shorten(char *input) {
    remove_whitespaces(input);
    char *functions[] = {"sin", "cos", "ctg", "tan", "sqrt", "ln"};
    char symbols[] = {'s', 'c', 'g', 't', 'r', 'l'};
    for (int i = 0; i < NUM_FUNCTIONS; ++i) {
        crop(input, functions[i], symbols[i]);
    }
    remove_whitespaces(input);
    int len = strlen(input);
    if (input[0] == '-') {
        input[0] = '~';
    }
    for (int i = 1; i < len; ++i) {
        if (input[i] == '-' && (is_valid_operator(input[i - 1]) || input[i - 1] == '(')) {
            input[i] = '~';
        } else if (input[i] == ',') {
            input[i] = '.';
        }
    }
}

void crop(char *input, char *function, char symbol) {
    int f_len = strlen(function);
    while (strstr(input, function)) {
        char *ptr = strstr(input, function);
        for (int i = 0; i < f_len; ++i) {
            ptr[i] = ' ';
        }
        ptr[0] = symbol;
    }
}

int calculate_max_len(char *input) {
    int m = 0, n = 0;
    while (*input != '\0') {
        if (is_digit(*input)) {
            ++n;
        } else if (is_operator(*input)) {
            ++m;
        }
        ++input;
    }
    return 100 * (2 * n + m + 1);
}

int is_valid_operator(char c) { return (c == '+' || c == '-' || c == '*' || c == '/' || c == '~'); }

int is_next_skob(const char *expression, int x) {
    int result = 0;
    for (int i = x;; i++) {
        if (expression[i] == '(') {
            result = 1;
            break;
        } else if (expression[i] == ' ') {
            continue;
        } else {
            break;
        }
    }
    return result;
}

int is_valid_expression(char *expression) {
    int flag_num = 0;
    int flag_operator = 0;
    int result = 1;

    for (int i = 0; expression[i] != '\0'; i++) {
        char current = expression[i];
        // printf("%c\n", current);
        if (current == 's') {
            if (expression[i + 1] == 'i' && expression[i + 2] == 'n' && is_next_skob(expression, i + 3)) {
                i += 3;
            } else if (expression[i + 1] == 'q' && expression[i + 2] == 'r' && expression[i + 3] == 't' &&
                       is_next_skob(expression, i + 4)) {
                i += 4;
            } else {
                result = 0;
            }
        } else if (current == 'c') {
            if (expression[i + 1] == 'o' && expression[i + 2] == 's' && is_next_skob(expression, i + 3)) {
                i += 3;
            } else if (expression[i + 1] == 't' && expression[i + 2] == 'g' &&
                       is_next_skob(expression, i + 3)) {
                i += 3;
            } else {
                result = 0;
            }
        } else if (current == 't') {
            if (expression[i + 1] == 'a' && expression[i + 2] == 'n' && is_next_skob(expression, i + 3)) {
                i += 3;
            } else {
                result = 0;
            }
        } else if (is_digit(current) || current == 'x') {
            if (flag_num) {
                return 0;
            } else {
                while (is_digit(expression[++i]) || expression[i] == '.') {
                }
                flag_operator = 0;
                flag_num = 1;
                i--;
            }
        } else if (is_valid_operator(current)) {
            if (flag_operator == 1) {
                return 0;
            } else {
                flag_num = 0;
                flag_operator = 1;
                if (current == '-' && is_next_skob(expression, i + 1)) {
                    flag_operator = 0;
                }
            }
        }
    }
    if (flag_operator == 1 || flag_num == 0) {
        result = 0;
    }
    return result;
}
