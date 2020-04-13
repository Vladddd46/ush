#include "ush.h"
/*
    * Implementation of export built-in function
    * Functional:
        // prints all enviromental variables.
        * >>> export
        // adds new variable with value into env.
        * >>> export new_var=value
        // adds new variable with empty (mx_strnew(1)) value.
          >>> export new_var or export new_var=
        // error
        * >>> export =some_text
*/

/*
    * walking throuth user`s input and setting specified variables
    * into env list if there is no error.
*/
static void exporting_var(char **cmd) {
    char **data;
    char *put;
    int walker = 1;

    while(cmd[walker]) {
        data = mx_splitter(cmd[walker]);
        if (!mx_not_valid_identifier_error(cmd[walker], data)) {
            if (mx_str_in_arr_index(environ, data[0]) == -1) {
                put = mx_three_join(data[0], "=", data[1]);
                putenv(put);
            }
            else
                setenv(data[0], data[1], 1);
        }
        walker++;
        mx_arr_freesher(data);
    }
}

void mx_export(char **cmd) {
    // prints all env. variables
    if (mx_strarr_size(cmd) == 1)
        mx_export_printer();
    // export variables
    else
        exporting_var(cmd); 
}


