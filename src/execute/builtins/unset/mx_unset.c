#include "ush.h"
/*
    Implementation of unset built-in function.
    * deletes specified var from env.
*/

// unsets variable
static void unsetter(char *expr) {
    char *var_name;
    int eq_index = mx_char_index(expr, '=');

    if (eq_index == -1)
        unsetenv(expr);
    else {
        var_name = mx_substr_retriever(expr, 0, eq_index - 1);
        unsetenv(var_name);
        free(var_name);
    }
}

static char *var_name_retriever(char *expr) {
    char *var_name;
    int eq_index = mx_char_index(expr, '=');

    if (eq_index == -1)
        var_name = mx_string_copy(expr);
    else
        var_name = mx_substr_retriever(expr, 0, eq_index - 1);
    return var_name;
}

static int variable_in_env(char *expr) {
    char *var_name = var_name_retriever(expr);
    char *env_var_name;
    int eq_index2;
    int is_in_env = 0;

    int i = 0;
    while(environ[i]) {
        eq_index2    = mx_char_index(environ[i], '=');
        env_var_name = mx_substr_retriever(environ[i], 0, eq_index2 - 1);
        if (mx_strcmp(env_var_name, var_name) == 0)
            is_in_env = 1;
        free(env_var_name);
        i++;
    }
    free(var_name);
    return is_in_env;
}

void mx_unset(char **cmd) {
    // "if >>>unset"
    if (mx_error_not_enough_args(cmd))
        return;

    int walker = 1;
    while(cmd[walker]) {
        if (cmd[walker][0] == '=' || variable_in_env(cmd[walker]) == 0)
            mx_no_such_var_msg(cmd[walker]);
        else
            unsetter(cmd[walker]);
        walker++;
    }
}


