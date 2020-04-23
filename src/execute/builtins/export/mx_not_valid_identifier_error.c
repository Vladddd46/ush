#include "ush.h"

/*
 * Prints error msg if data[0] == '='
 * or data[0] is digit.
 */

void not_valid_identifier_msg(char *str) {
    char *msg1 = "u$h: export: \'";
    char *msg2 = "\':not a valid identifier\n";

    write(2, msg1, mx_strlen(msg1));
    write(2, str,  mx_strlen(str));
    write(2, msg2, mx_strlen(msg2));
}

int mx_not_valid_identifier_error(char *str, char **data) {
    if (str[0] == '=') {
        not_valid_identifier_msg(str);
        return 1;
    }
    else if (mx_strcmp(data[0], "0") != 0 && atoi(data[0])) {
        not_valid_identifier_msg(str);
        return 1;
    }
    return 0;
}


