#include "ush.h"
/*
 * Takes str and start/end index of $expression
 *     Example: "abc${HOME}...", start_indx = 3, end_indx = 9
 * Returns value associated with $expression.
 *     return getenv(HOME);
 *     if (getenv(HOME) == NULL)
 *       return mx_strnew(1);
 */

static char *mem_for_value_allocate(char *dirty_value) {
    char *new_str;

    if (dirty_value[0] == '{')
        new_str = mx_strnew(mx_strlen(dirty_value) - 2);
    else
        new_str = mx_strnew(mx_strlen(dirty_value));
    return new_str;
}

static char *value_retriever(char *str, int start_indx, int end_indx) {
    // start_indx + 1 becasue we omit $
    char *dirty_value = mx_substr_retriever(str, start_indx + 1, end_indx);
    char *new_str     = mem_for_value_allocate(dirty_value);
    int  index = 0;

    if (dirty_value[0] == '{') {
        for (int i = 1; i < mx_strlen(dirty_value) - 1; ++i) {
            new_str[index] = dirty_value[i];
            index++;
        }
    }
    else {
        for (int i = 0; dirty_value[i]; ++i)
            new_str[i] = dirty_value[i];
    }
    free(dirty_value);
    return new_str;
}

char *mx_env_value_get(char *str, int start_indx, int end_indx, 
                                    t_local_env **local_env) {
    char *value;
    char *env_value;

    // if $$ -> return pid
    if (end_indx - start_indx == 1 && str[end_indx] == '$')
        return mx_itoa((int)getpid());
    value = value_retriever(str, start_indx, end_indx);
    if (!strcmp(value, "?"))
        env_value = mx_get_var_value(local_env, "?");
    else
        env_value = getenv(value);
    if (env_value == NULL)
        env_value = mx_strnew(1);
    free(value);
    return env_value;
}








