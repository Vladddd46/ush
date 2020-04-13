#include "ush.h"

/*
    * creates and pushes back node 
      in linked list t_parsed_blocks **list
*/
void mx_prs_blocks_push_back(t_parsed_blocks **list, 
                            char **cmd_expr, 
                            char *separator,  
                            int  builtin) {
    int id = 0;
    if (*list != NULL) {
        t_parsed_blocks *tmp = *list;
        while (tmp -> next != NULL)
            tmp = tmp -> next;
        id = tmp -> id + 1;
    }
    
    t_parsed_blocks *node = mx_create_parsed_blocks_node(cmd_expr, separator,
                                                         builtin,  id);
    t_parsed_blocks *last_el;
    if (*list == NULL)
        *list = node;
    else {
        last_el = *list;
        while(last_el -> next != NULL)
            last_el = last_el -> next;
        last_el -> next = node;   
    }
}


