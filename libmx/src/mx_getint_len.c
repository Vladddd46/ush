#include "libmx.h"

int mx_getint_len (int num) {
    int count = 0;

    while(num > 0) {
        num /= 10;
        count++;
    }
    return count;
}


