#include "ush.h"

/*
 * Return flags specified by user.
 * If no flag specified => NULL is returned. 
 */
char *mx_flag_retriever(char **cmd_exp) {
    char *flag = NULL;

    if (mx_strarr_size(cmd_exp) > 1) {
        if (mx_strcmp("-s", cmd_exp[1]) == 0) {
            flag = mx_strnew(2);
            flag[0] = '-';
            flag[1] = 's';
        }
        else if (mx_strcmp("-P", cmd_exp[1]) == 0) {
            flag = mx_strnew(2);
            flag[0] = '-';
            flag[1] = 'P';
        }
    }
    return flag;
}



