#include "ush.h"
/************************************
    * Implementation of cd built-in *
    * flags: -s -P and - argument   *
*************************************/

/*
    * return link physical location. 
    * if <name> is not link => NULL is returned
*/
static char *is_link(char *name) {
    char *link_name;
    char *buff      = mx_strnew(4026);
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

static char *getting_oldcwd() {
    char *oldcwd = getenv("OLDPWD");
    char *res;
    char *msg;

    if (oldcwd == NULL) {
        msg = "cd: OLDPWD variable is not set\n";
        write(2, msg, mx_strlen(msg));
        return NULL;
    }
    res = mx_string_copy(oldcwd);
    return res;
}

static void preprocessing(char *arg, char *flag, char *oldcwd) {
    char *newcwd;
    char *link = is_link(arg);

    if (flag == NULL)
        flag = "-";
    if (mx_strcmp(arg, "..") == 0)
        newcwd = mx_prev_dir();
    else if (link != NULL && mx_strcmp(flag, "-s") == 0) {
        mx_flag_s_link_error(arg);
        return;
    }
    else if (link != NULL && mx_strcmp(flag, "-P") == 0)
        newcwd = mx_new_cwd_maker(link);
    else if (link != NULL && mx_strcmp(flag, "-") == 0)
        newcwd = mx_new_cwd_maker(arg);
    else if (link == NULL && mx_strcmp(arg, "-") == 0)
        newcwd = getting_oldcwd();
    else
        newcwd = mx_new_cwd_maker(arg);
    mx_cwd_changer(newcwd, oldcwd);
    free(link);
}

void mx_cd(char **cmd_exp) {
    if (mx_pwd_var_error())
        return;
    char *flag = mx_flag_retriever(cmd_exp);
    char *oldcwd = mx_string_copy(getenv("PWD"));

    if (mx_too_many_args(cmd_exp, &flag, &oldcwd))
        return;
    // cd with no args (/Users/<username>)
    if (mx_strarr_size(cmd_exp) == 1 
        || (mx_strarr_size(cmd_exp) == 2 && flag != NULL))
        mx_cd_home(oldcwd);
    else {
        if (flag == NULL)
            preprocessing(cmd_exp[1], flag, oldcwd);
        else if (mx_strarr_size(cmd_exp) == 3)
            preprocessing(cmd_exp[2], flag, oldcwd);
    }
    free(flag);
    return;
}




