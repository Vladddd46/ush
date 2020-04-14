#include "ush.h"

/*
    * Implementation of flag -i in env built-in
    * ignores env.variables/sets only specified variables 
    * and executes specified binary(unility).
*/

static void specified_vars_unset(char **cmd, int start) {
    char **name_value;
    int walker = start;

   while (cmd[walker]
         && mx_is_in_arr(cmd[walker], '=') 
         && cmd[walker][mx_strlen(cmd[walker])-1] != '=' 
         && cmd[walker][0] != '=') {
        name_value = mx_str_to_arr(cmd[walker], '=');
        unsetenv(name_value[0]);
        mx_arr_freesher(name_value);
        walker++;
    }
}

static void env_ignore() {
    int eq_index;
    char *var_name;

    int i = 0;
    while(environ[i]) {
        eq_index = mx_char_index(environ[i], '=');
        var_name = mx_substr_retriever(environ[i], 0, eq_index - 1);
        if (mx_strcmp("PATH", var_name) != 0)
            unsetenv(var_name);
        free(var_name);
        i++;
    }
}

static void env_restore(char **copy_env) {
    int walker = 0;

    while(copy_env[walker]) {
        putenv(copy_env[walker]);
        walker++;
    }
}

static void print_specified_vars(char **cmd) {
    int walker;

    walker = 2;
    while(cmd[walker]) {
        printf("%s\n", cmd[walker]);
        walker++;
    }
}

void mx_env_flag_i(char **cmd, t_proc **proc) {
    int binary_index;
    char **copy_env = mx_arr_copy(environ);

    if (mx_strarr_size(cmd) == 2)
        return;
    env_ignore();
    binary_index = mx_binary_index_finder(cmd, 2);
    if (cmd[binary_index]) {
        mx_specified_vars_setter(cmd, 2);
        mx_env_exe(cmd, binary_index, proc, getenv("PATH"));
        specified_vars_unset(cmd, 2);
    }
    else
        print_specified_vars(cmd);
    env_restore(copy_env);
}


