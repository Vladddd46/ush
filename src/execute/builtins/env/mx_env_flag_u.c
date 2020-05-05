#include "ush.h"

// Implementation of flag -u in env built-in

// Prints all env variables except var_name
static void print_env_without_var(char *var_name) {
    int  eq_indx;
    char *env_var_name;
    int  walker = 0;

    while (environ[walker]) {
        eq_indx      = mx_char_index(environ[walker], '=');
        env_var_name = mx_substr_retriever(environ[walker], 0, eq_indx - 1);
        if (mx_strcmp(var_name, env_var_name) != 0)
            printf("%s\n", environ[walker]);
        free(env_var_name);
        walker++;
    }
}

void mx_env_flag_u(char **cmd, t_proc **proc, t_local_env **local_env) {
    char *unset_var;
    char *unset_var_value;

    if (mx_strarr_size(cmd) == 2)
        mx_option_requires_an_argument("u");
    else if (mx_strarr_size(cmd) == 3)
        print_env_without_var(cmd[2]);
    else if (mx_strarr_size(cmd) > 3) {
        unset_var = getenv(cmd[2]);
        if (unset_var == NULL)
            mx_env_exe(cmd, 3, proc, getenv("PATH"), local_env);
        else  {
            unset_var_value = mx_three_join(cmd[2], "=", unset_var);
            unsetenv(cmd[2]);
            mx_env_exe(cmd, 3, proc, getenv("PATH"), local_env);
            putenv(unset_var_value);
            free(unset_var_value);
        }
    }
}


