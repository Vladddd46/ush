#include "ush.h"

/*
    * creates new paths.
    * takes PWD value and adds /new_dir.
    * if PWD == '/', adds only new_dir.
*/
char *mx_new_cwd_maker(char *new_dir) {
    char *newcwd;
    char *PWD = getenv("PWD");

    if (mx_strcmp(".", new_dir) == 0)
        return  mx_string_copy(PWD);
    
    if (new_dir[0] != '/')
        if (mx_strcmp(PWD, "/") != 0)
            newcwd = mx_three_join(PWD, "/", new_dir);
        else
            newcwd = mx_strjoin(PWD, new_dir);
    else
        newcwd = mx_string_copy(new_dir);
    return newcwd;
}

