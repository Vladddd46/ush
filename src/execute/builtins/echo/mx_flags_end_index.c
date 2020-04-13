#include "ush.h"

// return index of echo argument, which is not flag.
int mx_flags_end_index(char **cmd) {
    int walker = 1;
    
    while(cmd[walker]) {
        if (mx_valid_is_flag(cmd[walker]) == -1) {
            return walker;
        }
        walker++;
    }
    return walker;
}


