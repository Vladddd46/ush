#include "ush.h"

/*
	reallocates memory for input buffer if it`s needed.
*/
void mx_reallocation(char **input, int *index, int *size) {
    char *free_input;

    if (*index + 1 == *size) {
        free_input = *input;
        *input = mx_str_realloc(*input, 100);
        *size += 100;
        free(free_input);
     }
}

