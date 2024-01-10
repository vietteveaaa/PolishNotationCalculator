#include "drawing.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "RPN.h"

void print_graph(char *polska) {
    float step_x = 4 * M_PI / (WIDTH - 1);
    float step_y = 2.0 / 24.0;
    int flag = 1;
    for (float y = -1.0; y < 1.0 && flag; y += step_y) {
        for (float x = 0.0; x < 4 * M_PI && flag; x += step_x) {
            float value = substitute(polska, x, &flag);
            if (fabs(value) < 1.0 + EPS && fabs(value - y) < step_y / 2) {
                printf("*");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
    if (flag == -1) {
        system("clear");
        printf("Invalid input");
    }
}
