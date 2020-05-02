#include "ush.h"

// Implementation of exit() built in function

static void num_arg_required_err(char *str) {
    char *msg1 = "u$h> exit: ";
    char *msg2 = ": numeric argument required\n";
    write(2, msg1, mx_strlen(msg1));
    write(2, str, mx_strlen(str));
    write(2, msg2, mx_strlen(msg2));
}

void mx_exit(char **cmd_expression) {
    int arr_size = mx_strarr_size(cmd_expression);
    int code;

    if (arr_size > 2) {
        mx_too_many_arguments_error("exit");
        return;
    }
    else if (arr_size == 1)
        exit(0);
    code = atoi(cmd_expression[1]);
    if (code == 0 && mx_strcmp("0", cmd_expression[1]) != 0) 
        num_arg_required_err(cmd_expression[1]);
    else
        exit(code);
}


