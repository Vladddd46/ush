#include "ush.h"

// Prints all env variables in ascending order
void mx_export_printer() {
    char **env_copy = mx_arr_copy(environ);

    mx_quicksort_strarr(env_copy, 0, mx_strarr_size(env_copy) - 1);
    mx_print_strarr(env_copy);
    mx_arr_freesher(env_copy);
}
