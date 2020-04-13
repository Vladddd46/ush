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

/*
    * returns the previous dir.
    * runs, when user specified ".." as argument
    * Example: 
        cwd == /Users/user_name/Desktop
        prev_dir() = /Users/user_name
*/
static char *prev_dir() {
    char *prev_dir   = NULL;
    char **split     = mx_str_to_arr(getenv("PWD"), '/');
    char *insert_str = NULL;

    if (mx_strcmp("/", getenv("PWD")) == 0 || mx_strarr_size(split) == 1) {
        mx_arr_freesher(split);
        return mx_string_copy("/");
    }
    for (int i = 0; i < mx_strarr_size(split) - 1; ++i) {
        if (split[i + 2] != NULL)
            insert_str = mx_strjoin(split[i], "/");
        else
            insert_str = mx_string_copy(split[i]);
        if (prev_dir) 
            prev_dir = mx_strjoin(prev_dir, insert_str);
        else
            prev_dir = mx_three_join("/", split[i], "/");
        free(insert_str);
    }
    mx_arr_freesher(split);
    return prev_dir;
}

// makes new cwd. returns string of new cwd
static char *new_cwd_maker(char *new_dir) {
    char *newcwd;
    char *PWD = getenv("PWD");

    if (mx_strcmp(".", new_dir) == 0)
        return  mx_string_copy(PWD);
    
    if (new_dir[0] != '/')
        if (mx_strcmp(PWD, "/") != 0)
            newcwd = mx_three_join(PWD, "/", new_dir);
        else
            newcwd = mx_strjoin(PWD, new_dir);
    else
        newcwd = mx_string_copy(new_dir);
    return newcwd;
}

// prints error if -s as flag and <link> as argument specified. 
static void flag_s_link_error(char *arg) {
    char *msg = "cd: not a directory: ";
    write(2, msg, mx_strlen(msg));
    write(2, arg, mx_strlen(arg));
    write(2, "\n", 1);
}

static void preprocessing(char *arg, char *flag, char *oldcwd) {
    char *newcwd;
    char *link = is_link(arg);

    if (flag == NULL)
        flag = "-";
    if (mx_strcmp(arg, "..") == 0)
        newcwd = prev_dir();
    else if (link != NULL && mx_strcmp(flag, "-s") == 0) {
        flag_s_link_error(arg);
        return;
    }
    else if (link != NULL && mx_strcmp(flag, "-P") == 0)
        newcwd = new_cwd_maker(link);
    else if (link != NULL && mx_strcmp(flag, "-") == 0)
        newcwd = new_cwd_maker(arg);
    else if (link == NULL && mx_strcmp(arg, "-") == 0)
        newcwd = mx_string_copy(getenv("OLDPWD"));
    else
        newcwd = new_cwd_maker(arg);
    mx_cwd_changer(newcwd, oldcwd);
    free(link);
}


void mx_cd(char **cmd_exp) {
    char *flag = mx_flag_retriever(cmd_exp);
    char *newcwd;
    char *oldcwd = mx_string_copy(getenv("PWD"));

    // too many arg error
    if (mx_too_many_args(cmd_exp, flag)) {
        free(flag);
        free(oldcwd);
        return;
    }
    // cd with no args (/Users/<username>)
    if (mx_strarr_size(cmd_exp) == 1 
        || (mx_strarr_size(cmd_exp) == 2 && flag != NULL)) {
        newcwd = mx_string_copy(getenv("HOME"));
        mx_cwd_changer(newcwd, oldcwd);
    }
    else {
        if (flag == NULL)
            preprocessing(cmd_exp[1], flag, oldcwd);
        else if (mx_strarr_size(cmd_exp) == 3)
            preprocessing(cmd_exp[2], flag, oldcwd);
    }
    free(flag);
    return;
}




