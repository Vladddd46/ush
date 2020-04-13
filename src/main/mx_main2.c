#include "ush.h"

void mx_main2(char *cmd, t_proc **proc_list) {
    t_parsed_blocks *list = mx_expression_parse(cmd);
    t_parsed_blocks *tmp  = list;
    int            status = 1;
    
    /* this loop is needed to implement && and || */
    while(tmp) {
        mx_input_preprocessing(tmp->cmd_expr, proc_list);
        status = mx_execute(tmp->cmd_expr, &proc_list[0]);
        if (status == 1) {
            while(tmp) {
                if(tmp->separator) {
                    if (mx_strcmp(tmp->separator, "&&") == 0)
                        break;
                }
                tmp = tmp->next;
            }
        }
        if (tmp)
            tmp = tmp -> next;
    }
}


