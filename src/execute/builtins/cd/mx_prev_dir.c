#include "ush.h"

/*
 * Returns the previous dir.
 * Runs, when user specified ".." as argument
 * Example: 
 *   cwd == /Users/user_name/Desktop
 *   prev_dir() = /Users/user_name
 */
char *mx_prev_dir() {
    char *prev_dir   = NULL;
    char **split     = mx_str_to_arr(getenv("PWD"), '/');
    char *insert_str = NULL;

    if (mx_strcmp("/", getenv("PWD")) == 0 || mx_strarr_size(split) == 1) {
        mx_arr_freesher(split);
        return mx_string_copy("/");
    }
    for (int i = 0; i < mx_strarr_size(split) - 1; ++i) {
        if (split[i + 2] != NULL)
            insert_str = mx_strjoin(split[i], "/");
        else
            insert_str = mx_string_copy(split[i]);
        if (prev_dir) 
            prev_dir = mx_strjoin(prev_dir, insert_str);
        else
            prev_dir = mx_three_join("/", split[i], "/");
        free(insert_str);
    }
    mx_arr_freesher(split);
    return prev_dir;
}


