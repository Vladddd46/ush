#include "ush.h"

/*
 * Changes shell prompt.
 */

 static void prompt_syntax() {
    char *msg = "prompt syntax: prompt new_prompt_name\n";
    write(2, msg, mx_strlen(msg));
 }

void mx_prompt(char **cmd_expr, t_local_env **local_env) {
    if (mx_strarr_size(cmd_expr) > 2)
        mx_too_many_arguments_error("prompt");
    else if (mx_strarr_size(cmd_expr) == 1)
        prompt_syntax();
    else
        mx_local_var_value_resetter(local_env, "PROMPT", 
                                    mx_string_copy(cmd_expr[1]));
}



