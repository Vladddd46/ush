#include "ush.h"

/*
 * Returns index of new pwd user specified in cd.
 * In case of no specified path (<cd> or <cd -s>),
 * 0 is returned.
 */
int mx_wd_from_user_indx(char **cmd_exp) {
    if (mx_strarr_size(cmd_exp) == 1)
        return 0;

    int i = 1;
    for (; cmd_exp[i]; ++i) {
        if (strcmp(cmd_exp[i], "-P") != 0 && strcmp(cmd_exp[i], "-s") != 0)
            break;
    }
    if (cmd_exp[i])
        return i;
    else
        return 0;
}

