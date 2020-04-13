#include "ush.h"
/*
    * - takes the name of user_inputed command (external_name)
    * - we already know, that this func. is not built_in.
    * - retrieves all pathes from env -> $PATH var.
    * - scans all pathes and tries to find file with external name
        * - if finds -> return /binary/path/external_name
        * Example: /bin/usr/ls (ls - external_name)
        * - else NULL;
    *** This module has no leaks! *** 
*/

static char *search(char **pathes, char *external_name) {
    char *found_path;
    struct dirent *entry;
    int walker = 0;
    DIR *dir;

    while(pathes[walker]) {
        dir = opendir(pathes[walker]);
        if (dir == NULL)
            free(dir);
        else {
            while((entry = readdir(dir)) != NULL) {
                if (mx_strcmp(external_name,  entry->d_name) == 0) {
                    found_path = mx_three_join(pathes[walker], "/", external_name);
                    closedir(dir);
                    return found_path;
                }      
            }
            closedir(dir);
        }
        walker++;
    }
    return NULL;
}


char *mx_find_external_storage_path(char *external_name, char *path) {
    char **pathes = mx_str_to_arr(path, ':');
    char *found_path;

    if (pathes == NULL) {
        mx_arr_freesher(pathes);
        return NULL;
    }

    found_path = search(pathes, external_name);
    mx_arr_freesher(pathes);
    return found_path;
}

