#include "ush.h"

// Changes value of specified variable in local_env 

void mx_local_var_value_resetter(t_local_env **local_env, 
                            char *var_name, char *new_value) {
    t_local_env *tmp = *local_env;

    while(tmp) {
        if (strcmp(var_name, tmp->var_name) == 0) {
            free(tmp->var_value);
            tmp->var_value = new_value;
            break;
        }
        tmp = tmp->next;
    }
}


