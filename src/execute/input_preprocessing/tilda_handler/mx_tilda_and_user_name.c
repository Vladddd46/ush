#include "ush.h"
/*
    * case ~username/some_dir
*/

// checks wheather username exists in system user`s
static int user_exist_checker(char *username) {
    struct passwd *entry;

    while (1) {
        entry = getpwent();
        if (!entry)
            break;
        if (mx_strcmp(entry->pw_name, username) == 0) {
            endpwent();
            return 1;
        }
    }
    endpwent();
    return 0;
}

void mx_tilda_and_user_name(char **arg_splt) {
    char *user_name = mx_substr_retriever(arg_splt[0], 
                                          1, 
                                          mx_strlen(arg_splt[0]) - 1);
    int  user_exist = user_exist_checker(user_name);
    char *new_str = mx_string_copy("/Users/");

    if (user_exist) {
        new_str = mx_strjoin(new_str, user_name);
        free(arg_splt[0]);
        arg_splt[0] = new_str;
    }
    free(user_name);
}


