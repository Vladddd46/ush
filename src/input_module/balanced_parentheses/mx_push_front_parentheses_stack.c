#include "ush.h"

/*
    * Creates/Pushes node into t_braces_stack list
    * it is needed to check whether all parentheses 
      in user`s input are balanced.
    * brace - parenthese {",',\,(,{,),}}
    * index - index of braced in array below. this 
      array declared in calling func.

*/
static t_braces_stack *mx_create_stack_node(char brace, int index) {
    t_braces_stack *node = (t_braces_stack *)malloc(sizeof(t_braces_stack));

    node->brace = brace;
    node->index = index;
    node->next  = NULL;
    return node;
}

void mx_push_front_brace(t_braces_stack **list, char brace, int index) {
    t_braces_stack *new_node;
    t_braces_stack *last_node = *list;

    if (*list == NULL)
        *list = mx_create_stack_node(brace, index);
    else {
        while(last_node->next != NULL)
            last_node = last_node->next;
        new_node = mx_create_stack_node(brace, index);
        last_node->next = new_node;
    }
}



