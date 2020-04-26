#include "ush.h"

// Returns ASCII code of esc character depending on letter.
char mx_escape_char_determiner(char c) {
    if (c == 'a') 
        return '\a';
    else if (c == 'b')
        return '\b';
    else if (c == 'f')
        return '\f';
    else if (c == 'n')
        return '\n'; 
    else if (c == 'r')
        return '\r';
    else if (c == 't')
        return '\t';
    else if (c == 'v') 
        return '\v';
    return -1;
}

