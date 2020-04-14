#include "ush.h"

/*
    * Implementation of echo built in
    * Flags:
      -n
      -e
      -E
*/

// prints preproccessed cmd on stdout.
static void result_print(char **cmd, int arg_indx2, char *flags) {
    while(cmd[arg_indx2]) {
        write(1, cmd[arg_indx2], mx_strlen(cmd[arg_indx2]));
        if (cmd[arg_indx2 + 1])
            write(1, " ", 1);
        arg_indx2++;
    }
    if (flags[2] != 'n')
        write(1, "\n", 1);
}

void mx_echo(char **cmd) {
    char *flags   = mx_flags_retriever(cmd);
    int  arg_indx = mx_flags_end_index(cmd);
    int  arg_indx2 = arg_indx;
    char *edited_str;

    while(cmd[arg_indx]) {
        if (mx_is_quoted(cmd[arg_indx])) 
            edited_str = mx_quoted_str_editor(cmd[arg_indx], flags);
        else 
            edited_str = mx_not_quoted_str_editor(cmd[arg_indx]);
        free(cmd[arg_indx]);
        cmd[arg_indx] = edited_str;
        arg_indx++;
    }
    result_print(cmd, arg_indx2, flags);
}



