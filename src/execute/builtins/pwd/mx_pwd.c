#include "ush.h"

/*
 * Implementation of pwd builtin
 * flags: -L -P
 * L - logical path of cwd.
 * P - physical path of cwd.
 */

// Returns physical location of link or NULL if name not link
static char *is_link(char *name) {
    char *link_name;
    char buff[4026];
    int buff_size = readlink(name, buff, 4026);
    
    if (buff_size == -1)
        return NULL;
    link_name = mx_strnew(buff_size);
    for (int i = 0; i < buff_size; ++i) {
        link_name[i] = buff[i];
    }
    return link_name;
}

// Prints physical location of link
static void pwd_with_resolved_link(char *pwd, char *location) {
    char **pwd_arr = mx_str_to_arr(pwd, '/');

    for (int i = 0; pwd_arr[i + 1]; ++i)
        printf("%s%s", "/",pwd_arr[i]);
    printf("%s%s\n", "/",location);
    mx_arr_freesher(pwd_arr);
}

// Excecutes pwd with flags -L -P
static void flag_p(char *pwd) {
    char *link_location = is_link(pwd);

    if (link_location != NULL)
        pwd_with_resolved_link(pwd, link_location);
    else
        printf("%s\n", pwd);
}


void mx_pwd(char **cmd_expression, t_local_env **local_env) {
    char *pwd = mx_get_var_value(local_env, "PWD");
    char flag = '\0';

    if (mx_pwd_flag_determine(cmd_expression, &flag))
        return;
    
    if (flag == '.' || flag == 'L')
        printf("%s\n", pwd);
    else if (flag == 'P')
        flag_p(pwd);
}
