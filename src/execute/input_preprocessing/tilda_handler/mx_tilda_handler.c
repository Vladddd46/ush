#include "ush.h"
/*
 * Replaces tilda, where it`s needed
 * in user`s input.
 */
static void tilda_replacer(char **arg_splt) {
    if (arg_splt[0] == NULL)
        return;
    if (mx_strcmp(arg_splt[0], "~") == 0)
        mx_home_replace(arg_splt);
    else if (mx_strcmp(arg_splt[0], "~+") == 0)
        mx_pwd_replace(arg_splt);
    else if (mx_strcmp(arg_splt[0], "~-") == 0)
        mx_oldpwd_replace(arg_splt);
    else if (arg_splt[0][0] == '~')
        mx_tilda_and_user_name(arg_splt);

}  

void mx_tilda_handler(char **cmd) {
    char **arg_splt_by_slash;
    int walker = 0;

    while(cmd[walker]) {
        if (cmd[walker][0] == '~') {
            arg_splt_by_slash = mx_str_to_arr(cmd[walker], '/');
            tilda_replacer(arg_splt_by_slash);
            free(cmd[walker]);
            cmd[walker] = mx_arr_to_path(arg_splt_by_slash);
            mx_arr_freesher(arg_splt_by_slash);
        }
        walker++;
    }
}

