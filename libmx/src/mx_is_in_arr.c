#include "libmx.h"

// Checks if char <c> in str <s> 
int mx_is_in_arr(char *s, char c) {
    for (int i = 0; i < mx_strlen(s); ++i) {
        if (s[i] == c) {
            return 1;
        }
    }
    return 0;
}
