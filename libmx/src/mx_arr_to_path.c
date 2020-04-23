#include "libmx.h"

/*
 * Takes arr of strs and returns path_str
 * char *arr = {"a", "b", "c", NULL};
 * return "a/b/c"
 */
char *mx_arr_to_path(char **arr) {
    int walker = 1;
    char *newstr = mx_string_copy(arr[0]);
    char *tmp_str;

    while(arr[walker]) {
        tmp_str = mx_three_join(newstr, "/", arr[walker]);
        free(newstr);
        newstr = mx_string_copy(tmp_str);
        free(tmp_str);
        walker++;
    }
    return newstr;
}


