#include "ush.h"

/*  
    * adds 1 to SHLVL in env. variables.
    * do nothing if there is no SHLVL arg.
*/
void mx_shlvl_adder() {
    char *shlvl = getenv("SHLVL");
    int  current_shlvl;
    char *new_shlvl;

    if (shlvl == NULL)
        return;
    current_shlvl = atoi(shlvl);
    new_shlvl     = mx_itoa(current_shlvl + 1);
    setenv("SHLVL", new_shlvl, 1);
    free(new_shlvl);
}

