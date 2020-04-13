#include "ush.h"

/*
    * pops node from end of t_braces_stack *list
*/
void mx_pop_back_brace_stack(t_braces_stack **list) {
    if (*list == NULL)
        return;
    else if (list[0]->next == NULL) {
         free(list[0]);
        *list = NULL;
        return;
    }

    t_braces_stack *prelast_node = *list;
    while(prelast_node->next->next != NULL)
        prelast_node = prelast_node->next;
    free(prelast_node->next);
    prelast_node->next = NULL;
}



