#include "ush.h"

/*
 * Implementation of which built in
 */

static void was_found_actions(char *flags, char *path, 
                              char *bin_name, int *found) {
    if (flags[1] != 's')
        printf("%s/%s\n", path, bin_name);
    *found = 1;
}

static void find(char *bin_name, char **pathes, char *flags, int *found) {
    struct dirent *entry;
    DIR *dir;   
    int i = 0;

    while(pathes[i]) {
        dir = opendir(pathes[i]);
        if (dir == NULL)
            free(dir);
        else {
            while((entry = readdir(dir)) != NULL) {
                if (mx_strcmp(bin_name,  entry->d_name) == 0) {
                    was_found_actions(flags, pathes[i], bin_name, found);
                    if (mx_is_in_arr(flags, 'a') != 1)
                        break;
                }      
            }
            closedir(dir);
        }
        i++;
    }
}

static void is_builtin(char *name, int *found, char *flags) {
    char *builtins[12] = {"cd", "export", "env", "unset", 
                          "echo", "exit", "fg", "jobs", 
                          "pwd", "which", NULL};
    if (mx_str_in_arr_index(builtins, name) != -1) {
        *found = 1;
        if (mx_is_in_arr(flags, 's') != 1)
            printf("%s: shell built-in command\n", name);
    }
}

static void s_flag_resolver(char *flags, int found) {
    if (flags[1] == 's') {
        if (found)
            setenv("?", "0", 1);
        else
            setenv("?", "1", 1);
    }
    else
        setenv("?", "0", 1);
}

void mx_which(char **cmd) {
    if(mx_which_usage_err(cmd))
        return;
    int  arg_index       = 1;
    char *flags          = mx_which_flags_determine(cmd, &arg_index);
    int  found           = 0;
    char **pathes;

    if (flags == NULL || getenv("PATH") == NULL) 
        return;
    pathes = mx_str_to_arr(getenv("PATH"), ':');
    while (cmd[arg_index]) {
        if (mx_is_in_arr(flags, 'a') == 1)
            is_builtin(cmd[arg_index], &found, flags);
        find(cmd[arg_index], pathes, flags, &found);
        arg_index++;
    }
    s_flag_resolver(flags, found);
    free(flags);
    mx_arr_freesher(pathes);
}





