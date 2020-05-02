#include "ush.h"

// Returns value of secified var_name
char *mx_get_var_value(t_local_env **list, char *var_name) {
    t_local_env *tmp = *list;

    while(tmp) {
        if (strcmp(var_name, tmp->var_name) == 0) {
            return tmp->var_value;
        }
        tmp = tmp->next;
    }
    return NULL;
}


