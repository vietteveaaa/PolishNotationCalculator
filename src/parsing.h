#ifndef PARSING_H
#define PARSING_H

#define INIT_SIZE 10
#define NUM_FUNCTIONS 6

char* input();
void remove_whitespaces(char* str);
void shorten(char* input);
void crop(char* input, char* function, char symbol);
int calculate_max_len(char* input);
int is_valid_operator(char c);
int is_valid_functionCode(char c);
int is_valid_expression(char* expression);
int is_valid_expression(char* expression);
void check_division_by_zero(char* expression, int* isValid);
void check_square_root(char* expression, int* isValid);

#endif  // PARSING_H