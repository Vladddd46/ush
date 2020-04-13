#include "ush.h"

void mx_input_preprocessing(char **cmd_expression, t_proc **proc) {
    // replaces tilda where it`s needed 
    mx_tilda_handler(cmd_expression);
    // ${variable} $variable replacer 
    mx_variable_substitution(cmd_expression);
    // command substitution
    mx_cmd_substitution(cmd_expression, proc);
}



