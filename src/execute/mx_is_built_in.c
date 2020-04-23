#include "ush.h"

// Checks, whether cmd is built_in
int mx_is_built_in(char *cmd) {
    char *built_ins[17] = { "export", "unset", "env", 
                            "pwd", "which", "echo", "fg", 
                            "exit", "jobs", "cd", "color", 
                            "bgcolor", NULL};
    int walker = 0;

    while(built_ins[walker]) {
        if (mx_strcmp(built_ins[walker], cmd) == 0)
            return 1;
        walker++;
    }
    return 0;
}

