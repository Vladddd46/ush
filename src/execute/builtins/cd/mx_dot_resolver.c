#include "ush.h"

static void fill_array_with_null(char **array, int size) {
    for (int i = 0; i < size; ++i)
        array[i] = NULL;
}

static void dot_resolver(char **splt_wd, char **resolved_arr) {
    int index = 0;

    for (int i = 0; splt_wd[i]; ++i) {
        if (!strcmp(splt_wd[i], ".")) {
            // just skip .
        }
        else if (!strcmp(splt_wd[i], "..")) {
            if (index > 0) {
                index--;
                free(resolved_arr[index]);
                resolved_arr[index] = NULL;
            }
        }
        else {
            resolved_arr[index] = mx_string_copy(splt_wd[i]);
            index++;
        }
    }
}

static char *resolution(char **splt_wd) {
    char **resolved_arr = mx_new_strarr(mx_strarr_size(splt_wd));
    char *tmp = NULL;
    char *del;

    fill_array_with_null(resolved_arr, mx_strarr_size(splt_wd));
    dot_resolver(splt_wd, resolved_arr);
    int walk = 0;
    while(resolved_arr[walk]) {
        if (tmp == NULL)
            tmp = mx_strjoin("/",resolved_arr[walk]);
        else {
            del = tmp;
            tmp = mx_three_join(tmp, "/",resolved_arr[walk]);
            free(del);
        }
        walk++;
    }
    if (resolved_arr[0] == NULL)
        return mx_string_copy("/");
    return tmp;
}

char *mx_dot_resolver(char *not_resolved_wd) {
    // Split path by slash.
    char **splt_wd = mx_str_to_arr(not_resolved_wd, '/');
    char *result;

    // If path contains only slashes.
    if (*splt_wd == NULL || !splt_wd)
        result = mx_string_copy("/");
    else
        result = resolution(splt_wd);
    free(splt_wd);
    return result;
}









