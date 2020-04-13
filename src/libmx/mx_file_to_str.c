#include "ush.h"
/*
    * takes file_name as arguments
    * returns str with data from file
*/

static int needed_mem(const char *file) {
    char buff;
    int fd = open(file, O_RDONLY);
    int mem = 0;

    if (fd == -1)
        return -1;
    // count charackters in file
    while (read(fd, &buff, 1))
        mem++;
    close(fd);
    return mem;
}

char *mx_file_to_str(const char *file) {
    char buff;
    int mem = needed_mem(file);
    if (mem == -1)
        return NULL;
    // allocating mem for str, that contains file data
    char *str = mx_strnew(mem);
    int fd = open(file, O_RDONLY);
    // reading file and writing it`s data in str
    int i = 0;

    while(mem){
        read(fd, &buff, 1);
        str[i] = buff;
        i++;
        mem--;
    }
    return str;
}
