#include "ush.h"
/*
    * implementation of which built in
*/

static void find(char *bin_name, char *path, char *flags) {
    char **pathes = mx_str_to_arr(path, ':');
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
                    printf("%s/%s\n", pathes[i], bin_name);
                    if (mx_is_in_arr(flags, 'a') != 1)
                        break;
                }      
            }
            closedir(dir);
        }
        i++;
    }
}

void mx_which(char **cmd) {
    if(mx_which_usage_err(cmd))
        return;
    int arg_index       = 1;
    char *flags         = mx_which_flags_determine(cmd, &arg_index);

    if (flags == NULL || getenv("PATH") == NULL) 
        return;
    while (cmd[arg_index]) {
        find(cmd[arg_index], getenv("PATH"), flags);
        arg_index++;
    }
    free(flags);
}





