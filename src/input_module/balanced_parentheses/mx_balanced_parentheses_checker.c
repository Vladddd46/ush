#include "ush.h"

/*
 * Checks wheather user`s input 
 * has balanced number of parentheses.
 */

// Returns the braces_stack->index of last element
static char last_elem_index_in_stack(t_braces_stack *braces_stack) {
    t_braces_stack *tmp;

    if (braces_stack == NULL)
        return -1;
    tmp = braces_stack;
    while(tmp->next != NULL)
        tmp = tmp->next;
    return tmp->index;
}

// Checks wheather brace should be omitted ("(" - ( omitted))
static int brace_should_be_omited(int last_elem_index, int i, char *input) {
    if (last_elem_index == 0 && input[i] != '\\' && input[i] != '\'')
        return 1;
    else if (last_elem_index == 1 && input[i] != '\\' && input[i] != '\"')
        return 1;
    return 0;
}

// Algorightm, that checks braces balance.
static int alg(char *inp, char *o_brace, char *c_brace, t_braces_stack **stack) {
    int last_elem_index;
    int op_index;
    int cl_index;

    for (int i = 0; inp[i]; i++) {
        last_elem_index = last_elem_index_in_stack(*stack);
        op_index = mx_char_index(o_brace,  inp[i]);
        cl_index = mx_char_index(c_brace,  inp[i]);
        if (brace_should_be_omited(last_elem_index, i, inp))
            continue;
        if (op_index != -1 && cl_index != -1 && last_elem_index == cl_index)
            mx_pop_back_brace_stack(stack);
        else if (last_elem_index == 4)
            mx_pop_back_brace_stack(stack);
        else if (op_index != -1)
            mx_push_front_brace(stack, inp[i], op_index);
        else if (cl_index != -1) {
            if (cl_index == last_elem_index)
                mx_pop_back_brace_stack(stack);
            else 
                return cl_index;
        }
    }
    return 1;
}

static void matching_error(char brace) {
    if (isatty(0))
        write(2, "\n", 1);
    char *msg1 = "u$h: mathching error near ";

    write(2, msg1, mx_strlen(msg1));
    write(2, &brace, 1);
    write(2, "\n", 1);
}

int mx_balanced_parentheses_checker(char *input) {
    char *open_braces  = "\'\"({\\`";
    char *close_braces = "\'\")}\\`";
    t_braces_stack *braces_stack = NULL;
    int status = alg(input, open_braces, close_braces, &braces_stack);

    if (braces_stack == NULL && status == 1)
        return 1;
    if (status != 1)
        matching_error(close_braces[status]);
    // freeing stack and writing error message.
    t_braces_stack *del;
    t_braces_stack *tmp = braces_stack;
    while (tmp) {
        if (tmp->next == NULL)
            matching_error(tmp->brace);
        del = tmp;
        tmp = tmp->next;
        free(del);
    } 
    return -1;
}











