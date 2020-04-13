#include "ush.h"
/* 
    * Creates t_parsed_blocks list node
    * cmd_expr - command user specified
    * separator = &&/&/|/||/>>/>/<</<
*/
t_parsed_blocks *mx_create_parsed_blocks_node(char **cmd_expr,
                                            char *separator, 
                                            int builtin, int id) {
    t_parsed_blocks *node = (t_parsed_blocks *)malloc(sizeof(t_parsed_blocks));
    char **newarr = mx_new_strarr(mx_strarr_size(cmd_expr));

    for (int i = 0; cmd_expr[i]; i++)
        newarr[i] = mx_string_copy(cmd_expr[i]);
    node -> id = id;
    node -> cmd_expr = newarr;
    node -> separator = separator;
    node -> builtin = builtin;
    node -> next = NULL;
    return node;
}




