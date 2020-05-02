#include "ush.h"

/*
 * Local enviroment is needed to store additional data;
 * cwd, which gets from getcwd() func. when shell initialize.
 * "?=status" status value of last process.
 * alias defenitions.
 * and so on...
 * other_data is usually = NULL. It is used in need of writing
 * additional data.
 */


static t_local_env *create_node(char *var_name, char *var_value, 
                                char **other_data) {
    t_local_env *node = (t_local_env *)malloc(sizeof(t_local_env));

    node->var_name = var_name;
    node->var_value = var_value;
    node->other_data = other_data;
    node->next = NULL;
    return node;
}

void mx_push_front_local_env(t_local_env **list, char *var_name,
                            char *var_value, char **other_data) {
    t_local_env *node = create_node(var_name, var_value, other_data);

    if (*list == NULL)
        *list = node;
    else {
        node->next = *list;
        *list = node;
    }   
}

