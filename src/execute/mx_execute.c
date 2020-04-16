#include "ush.h"
/*
    * checks whether cmd is built in or external and
      executes program.
*/

static char *proccess(char *str) {
    char *result;
    char *new_str = mx_strnew(mx_strlen(str));
    int omit = 0;
    int index = 0;

    for (int i = 0; str[i]; ++i) {
        if (str[i] == '\\' && omit == 0) {
            omit = 1;
            continue;
        }
        omit = 0;
        new_str[index] = str[i];
        index += 1;
    }
    result = mx_string_copy(new_str);
    free(new_str);
    return result;
}


static void slash_chars_handler(char **cmd) {
    int i = 1;
    char *proccessed_str;
    while(cmd[i]) {
        proccessed_str = proccess(cmd[i]);

        free(cmd[i]);
        cmd[i] = proccessed_str;
        i++;
    }   
}



int mx_execute(char **cmd_expression, t_proc **proc) {
    int status = 1;
    
    if (mx_is_built_in(cmd_expression[0]))
        mx_built_ins_launcher(cmd_expression, &proc[0]);
    else { 
    	slash_chars_handler(cmd_expression);
        status = mx_external(cmd_expression, &proc[0], getenv("PATH")); 
    }
    return status;
}


