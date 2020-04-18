#include "ush.h"

/*
===================================================
This is implementation of mini-shell.
It contains:
    - user`s input
      > backspace
      > logic operators || && 
      > cmd separator ;
    - external binary executing
      > path/bin_name; ls; clear; mkdir; ./bin_name ... etc.
    - 9 built-ins:
      > export
      > unset
      > exit
      > env   [-i -P -u]
      > cd    [-s -P -]
      > pwd   [-L -P]
      > which [-a -s]
      > echo  [-n -e -E]
      > fg    [%n %str]
    - signals handling
      > Ctrl+D
      > Ctrl+Z
      > Ctrl+C
    - substitutions
      > ~; ~/dir_name; ~username/dirname; ~+/dirname; ~-/dirname
      > variable substitution ${VARNAME};$VARNAME
      > command substitution  `command`; $(command)
GitHub: Vladddd46
10.12.2020
PS. There are some functuons,
    which are little inadequate divided into smaller functions.
    This is done because of the code style I must stick to. 
    (each func. must be 20 or less line) 
===================================================
*/

static int continue_(char **arr) {
    if (arr == NULL) {
        if (!isatty(0))
            exit(2);
        write(1,"\n", 1);
        return 1;
    }
    if (isatty(0))
        mx_printstr("\n");
    return 0;
}

static void loop(t_proc *proc_list, char *user_input, char **splt_by_semicolon) {
    while (1) {
        user_input = mx_getting_input();
        if (mx_balanced_parentheses_checker(user_input) == -1) {
            free(user_input);
            if (!isatty(0))
                exit(2);
            continue;
        }
        splt_by_semicolon = mx_semicolon_divider(user_input);
        free(user_input);
        if (continue_(splt_by_semicolon)) {
            free(splt_by_semicolon);
            continue;
        }
        // processing each cmd from splt_by_semicolon
        for (int i = 0; splt_by_semicolon[i]; ++i)
            mx_main2(splt_by_semicolon[i], &proc_list);
        if (!isatty(0))
            exit(0);
        mx_arr_freesher(splt_by_semicolon);
    }
}

int main() {
    /*
        proc_list - list of processes, which are suspended by a signal.
        user_input - string, which represents user`s input.
        splt_by_semicolon - user`s input splited by ';'.
    */
    t_proc *proc_list          = NULL;
    char   *user_input         = NULL;
    char   **splt_by_semicolon = NULL;

    mx_signals_ignore();
    mx_shlvl_adder();
    // setting variable for exit status.
    putenv("?=0"); 
    loop(proc_list, user_input, splt_by_semicolon);
}




