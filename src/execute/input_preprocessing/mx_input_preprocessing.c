#include "ush.h"

static void cmd_to_lowecase(char **cmd_expression) {
    char *low = mx_upper_to_lower(cmd_expression[0]);

    free(cmd_expression[0]);
    cmd_expression[0] = low;
}

void mx_input_preprocessing(char **cmd_expression, t_proc **proc) {
    // turns cmd name in lower case
    cmd_to_lowecase(cmd_expression);
    // replaces tilda where it`s needed 
    mx_tilda_handler(cmd_expression);
    // ${variable} $variable replacer 
    mx_variable_substitution(cmd_expression);
    // command substitution
    mx_cmd_substitution(cmd_expression, proc);
    // argument preprocessing   
    mx_arguments_preprocessor(cmd_expression);
}



