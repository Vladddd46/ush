#include "ush.h"

/*
    * returns 1 if char c is alpha or digit
    * otherwise returns 0
*/
int mx_is_alphadigit(char c) {
    int alpha = isalpha(c);
    int digit = isdigit(c);

    if (alpha != 0 || digit != 0)
        return 1;
    return 0;
}


