#include "ush.h"
/*
 * Takes expression as an argument (f.e "echo 123 || pwd && ls >> file")
 * Return list of command nodes:
 *       char            *command;
 *       char            *separator;
 *       t_parsed_blocks *next;
 */  
t_parsed_blocks *mx_expression_parse(char *expression) {
    char *separators[9]       = {"&&", "||", "|", ">", ">>", "<", "<<", NULL};
    char *prettier_expression = mx_space_prettier(expression);
    char **exp_div_by_space   = mx_divide_by_space(prettier_expression);
    t_parsed_blocks *list;

    free(prettier_expression);
    if (mx_parse_error(exp_div_by_space)) {
        mx_arr_freesher(exp_div_by_space);
        return NULL; 
    }
    /*
     * Creates list of secified by user commands.
     * Node:
     *       command;
     *       separator;
     */
    list = mx_list_creator(separators, exp_div_by_space);
    mx_arr_freesher(exp_div_by_space);
    return list;
}

