#include "ush.h"

/*
 * Puts flag user specified in cd.
 * Flag are put depending on priority.
 * -s has greater priority than -P
 */
char mx_cd_flag_retriever(char **cmd_exp) {
    char flag = '-';
    
    for (int i = 1; cmd_exp[i]; ++i) {
        if (strcmp(cmd_exp[i], "-s") == 0)
            flag = 's';
        else if (strcmp(cmd_exp[i], "-P") == 0) {
            if (flag != 's')
                flag = 'P';
        }
    }
    return flag;
}



