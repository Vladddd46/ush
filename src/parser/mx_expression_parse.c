#include "ush.h"
/*
    * takes expression as an argument (f.e "echo 123 || pwd && ls >> file")
    * return list of command nodes:
        char            *command;
        char            *separator;
        t_parsed_blocks *next;
*/  
t_parsed_blocks *mx_expression_parse(char *expression) {
    char *separators[9]       = {"&&", "||", "|", ">", ">>", "<", "<<", NULL};
    char *prettier_expression = mx_space_prettier(expression);
    char **exp_div_by_space   = mx_divide_by_space(prettier_expression);
    free(prettier_expression);
    if (mx_parse_error(exp_div_by_space))
        return NULL; 
    /*
        * creates list of secified by user commands.
        * Node:
            command;
            separator;
    */
    t_parsed_blocks *list = mx_list_creator(separators, exp_div_by_space);
    mx_arr_freesher(exp_div_by_space);
    return list;
}

