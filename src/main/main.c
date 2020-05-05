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
      > color/bgcolor
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

/*
 * If user enterned not valid input such as
 * ;;;;;;;;;;;;;
 */
static int input_error(char **arr) {
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

/*
 * Returns 1 if:
 *  user_input == NULL.
 *  parenttheses in user_input are not balanced.
 *  else returns 0
 */
static int restart_loop(char **user_input) {
    int status = 0;

    if (user_input[0] == NULL){
       write(1,"\n", 1);
       status = 1;
    }
    else if (mx_balanced_parentheses_checker(user_input[0]) == -1) {
        free(user_input[0]);
        status = 1;
    }
    if (status) {
        if (!isatty(0))
            exit(2);
        return 1;
    }
    return 0;
}

static void loop(t_proc *proc_list, char *user_input, 
                char **splt_by_semicolon, t_local_env **local_env) {
    while (1) {
        user_input = mx_getting_input(local_env);
        if (restart_loop(&user_input))
            continue;
        splt_by_semicolon = mx_semicolon_divider(user_input);
        free(user_input);
        if (input_error(splt_by_semicolon))
            continue;
        // Processing each cmd from splt_by_semicolon
        for (int i = 0; splt_by_semicolon[i]; ++i)
            mx_main2(splt_by_semicolon[i], &proc_list, local_env);
        mx_arr_freesher(splt_by_semicolon);
        if (!isatty(0))
            exit(0);
    }
}

// Adds some vars into local shell enviroment.
static void local_env_init(t_local_env **local_env) {
  char pwd[4026];

  getcwd(pwd, 4026);
  mx_push_front_local_env(local_env, mx_string_copy("PWD"), 
                          mx_string_copy(pwd), NULL);
  mx_push_front_local_env(local_env, mx_string_copy("OLDPWD"), 
                          mx_string_copy(pwd), NULL);
  mx_push_front_local_env(local_env, mx_string_copy("?"), 
                          mx_string_copy("0"), NULL);
  mx_push_front_local_env(local_env, mx_string_copy("PROMPT"), 
                          mx_string_copy("u$h> "), NULL);
}

int main() {
    /*
     * proc_list - list of processes, which are suspended by a signal.
     * user_input - string, which represents user`s input.
     * splt_by_semicolon - user`s input splited by ';'.
     * local_env - list, which contains additional variables, such as ?
     */
    t_proc      *proc_list          = NULL;
    char        *user_input         = NULL;
    char        **splt_by_semicolon = NULL;
    t_local_env *local_env          = NULL;

    local_env_init(&local_env);
    mx_signals_ignore();
    mx_shlvl_adder();
    // Setting variable for exit status.
    loop(proc_list, user_input, splt_by_semicolon, &local_env);
}




