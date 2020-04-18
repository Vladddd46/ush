#include "ush.h"
/*
    * substitutes variable expression with
      value from env
      Example ${USER}/$USER => username
*/
// determines, wheather next char should be omitted. 1 omitted.
static int is_omitted(int *omit, char c) {
    if (c == '\\' && *omit == 0)
        *omit  = 1;
    else if (*omit == 1) {
        *omit = 0;
        return 1;
    }
    return 0;
}

static void subst_loop(int *omit, int *i, int *j, int *end_indx, char **cmd) {
    char *value;
    char *edited_str;

    while(cmd[*i]) {
        *j = 0;
        while(cmd[*i][*j]) {
            if (is_omitted(omit, cmd[*i][*j]))
                continue;
            else if (cmd[*i][*j] == '$' && (mx_is_alphadigit(cmd[*i][*j + 1]) 
                    || mx_is_in_arr("$?", cmd[*i][*j + 1]) || cmd[*i][*j + 1] == '{')) {
                *end_indx   = mx_end_index_finder(cmd[*i], *j);
                value       = mx_env_value_get(cmd[*i], *j, *end_indx);
                edited_str  = mx_str_edit(cmd[*i], value, *j, *end_indx);
                free(cmd[*i]);
                cmd[*i] = edited_str;
                *j = -1;
            }
            *j += 1;
        }
        *i += 1;
    }
}

// i,j - walkers
void mx_variable_substitution(char **cmd) {
    int  omit = 0;
    int  i    = 0;
    int  j;
    int  end_indx;
    
    subst_loop(&omit, &i, &j, &end_indx, cmd);
}






