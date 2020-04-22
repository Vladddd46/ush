#include "ush.h"


t_parsed_blocks *mx_list_creator(char **separators, char **exp_div_by_space) {
    t_parsed_blocks *list = NULL;
    char **cmd_expr;
    int command_index = 0;
    int walker = 0;

    while(exp_div_by_space[walker]) {
        // if exp_div_by_space[walker] == separator
        if (mx_str_in_arr_index(separators, exp_div_by_space[walker]) != -1) {
            cmd_expr = mx_divide_arr_by_index(exp_div_by_space, command_index, walker - 1);
            mx_prs_blocks_push_back(&list, cmd_expr, mx_string_copy(exp_div_by_space[walker]), 0);
            command_index = walker + 1;
            free(cmd_expr);
        }
        else if (exp_div_by_space[walker + 1] == NULL) { // if last element
            cmd_expr = mx_divide_arr_by_index(exp_div_by_space, command_index, walker);
            mx_prs_blocks_push_back(&list, cmd_expr, NULL, 0);
            free(cmd_expr);
       }
        walker++;
    }
    return list;
}

