#include "ush.h"
/*
 * Implementation of cd built-in
 * Flags: -s -P
 * - argument is also maintable.
 */

/*
 * Return link physical location. 
 * If <name> is not link => NULL is returned
 */
static char *is_link(char *name) {
    char *link_name;
    char buff[4026];
    int  buff_size  = readlink(name, buff, 4026);
    int  i          = 0;
    int  buff_index = 0;

    if (buff_size == -1)
        return NULL;
    link_name = mx_strnew(buff_size + 1);
    if (name[0] == '/') {
        link_name[0] = '/';
        i++;
    }
    for (; buff[buff_index]; ++i) {
        link_name[i] = buff[buff_index];
        buff_index++;
    }
    return link_name;
}

static int is_too_many_arguments(char **cmd_exp, int newcwd_index) {
    if (cmd_exp[newcwd_index + 1] != NULL && newcwd_index != 0) {
        mx_too_many_arguments_error("cd");
        return 1;
    }
    return 0;
}

/*
 * Returns pointer to wd, user specified.
 * If "cd [flags] -", path = OLDPWD
 * If "cd", path = HOME
 * If absolute path, returns copy of argument.
 * If relative path, joins cwd + / + user`s_input_argument and
 * returns it.
 */
static char *wd_from_user_preprocess(char **cmd_exp, int wd_from_user_indx, 
                                    t_local_env **local_env, char *cwd) {
    char *path;

    if (strcmp(cmd_exp[wd_from_user_indx], "-") == 0)
        path = mx_string_copy(mx_get_var_value(local_env, "OLDPWD"));
    else if (wd_from_user_indx == 0)
        path = mx_string_copy(getpwuid(getuid())->pw_dir);
    else {
        if (cmd_exp[wd_from_user_indx][0] == '/')
            path = mx_string_copy(cmd_exp[wd_from_user_indx]);
        else {
            if (strcmp(cwd, "/") != 0)
                path = mx_three_join(cwd, "/", cmd_exp[wd_from_user_indx]);
            else 
                path = mx_strjoin(cwd, cmd_exp[wd_from_user_indx]);
        }
    }
    return path;
}


static void flag_resolver(t_local_env **local_env, char *new_cwd, 
                            char *old_cwd, char flag) {
    char real_path[4026];
    char *link_name = is_link(new_cwd);
    char *resolved;

    if (flag == 's' && link_name != NULL)
        mx_flag_s_link_error(new_cwd);
    else if (flag == 'P') {
        realpath(new_cwd, real_path);
        mx_cwd_changer(local_env, mx_string_copy(real_path), old_cwd);
    }
    else {
        // CD do not resolve links, only dots.
        resolved = mx_dot_resolver(new_cwd);
        mx_cwd_changer(local_env, resolved, old_cwd);
        free(resolved);
    }
    free(link_name);
}


void mx_cd(char **cmd_exp, t_local_env **local_env) {
    char flag              = mx_cd_flag_retriever(cmd_exp);
    int  wd_from_user_indx = mx_wd_from_user_indx(cmd_exp);
    char *cwd              = mx_string_copy(mx_get_var_value(local_env, "PWD"));
    char *wd_from_user     = wd_from_user_preprocess(cmd_exp, wd_from_user_indx,
                                                    local_env, cwd);
    if (is_too_many_arguments(cmd_exp, wd_from_user_indx)){
        // do_nothing
    }
    else if (mx_access_errors(wd_from_user)) {
        // do_nothing
    }
    else
        flag_resolver(local_env, wd_from_user, cwd, flag);
    mx_free_strs(2, cwd, wd_from_user);
}




