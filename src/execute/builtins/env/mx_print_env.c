#include "ush.h"

/*
 * Prints enviromental variables
 * Environ ==> global variable| in ush.h
 */
void mx_print_env() {
    int i = 0;

    while(environ[i]) {
        // If variables has value !(variable=)
        if (mx_char_index(environ[i], '=') != mx_strlen(environ[i]) - 1)
            printf("%s\n", environ[i]);
        i++;
    }
}

