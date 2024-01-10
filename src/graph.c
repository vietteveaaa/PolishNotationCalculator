#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RPN.h"
#include "drawing.h"
#include "parsing.h"
#include "stack.h"

int main() {
    char *expr = input();
    if (is_valid_expression(expr)) {
        int flag = 0;
        shorten(expr);
        char *polska = (char *)malloc(calculate_max_len(expr) * strlen(expr) * sizeof(char));
        reversed_polish_notation(expr, polska, &flag);
        // char *output = polska; //log
        // while (*output != '\0') {printf("%c", *output);output++;}printf("\n"); // log
        if (flag == -1) {
            printf("Invalid input");
        } else {
            print_graph(polska);
        }
        free(polska);
    } else {
        printf("Invalid input");
    }
    free(expr);
    return 0;
}
