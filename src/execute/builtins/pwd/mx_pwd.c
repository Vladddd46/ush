#include "ush.h"

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
static void pwd_with_flags(char **cmd_expression) {
    char *link_location;
    char *logic_env = getenv("PWD");

    if (mx_strcmp(cmd_expression[1], "-L")      == 0)
        printf("%s\n", logic_env);
    else if (mx_strcmp(cmd_expression[1], "-P") == 0){
        link_location = is_link(logic_env);
        if (link_location != NULL)
            pwd_with_resolved_link(logic_env, link_location);
        else
            printf("%s\n", logic_env);
    }
}

static void pwd_not_set_err() {
    char *msg = "pwd: enviroment variable PWD is not set\n";

    write(2, msg, mx_strlen(msg));
}

void mx_pwd(char **cmd_expression) {
    if (mx_strarr_size(cmd_expression) > 2)
        mx_too_many_arguments_error("pwd");
    else if (getenv("PWD") == NULL) {
        pwd_not_set_err();
        return;
    }
    else if (mx_strarr_size(cmd_expression) == 1)
        printf("%s\n", getenv("PWD"));
    else if (mx_strarr_size(cmd_expression) == 2) {
        if (mx_strcmp(cmd_expression[1], "-L")    == 0 
            || mx_strcmp(cmd_expression[1], "-P") == 0)
            pwd_with_flags(cmd_expression);
        else
            mx_bad_option(cmd_expression[1]);
    }
}
