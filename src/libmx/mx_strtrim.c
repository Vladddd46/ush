#include "ush.h"

/*
    * deletes whitespaces from the beginning and end of the str
*/

static int first_chr_index(const char *str) {
    int i = 0;

    while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
        i++;
    return i;
}

static int last_chr_index(const char *str, int len_str) {
    int j = len_str - 1;
    while (str[j] && ((str[j] >= 9 && str[j] <= 13) || str[j] == 32))
        j--;
    return j;
}

static int needed_mem_counter(int first_chr_index, int last_chr_index) {
    int mem = 0;
    int tmp = first_chr_index;

    for (; tmp <= last_chr_index; ++tmp)
        mem++;
    return mem;
}

char *mx_strtrim(const char *str) {
    if (str == NULL)
        return NULL;
    int len_str = mx_strlen(str);
    //i - first index of char in str (not whitespace)
    int i = first_chr_index(str);
    //j - last index of char in str (not whitespace)
    int j = last_chr_index(str, len_str);
    // mem for trimed str and mem allocation
    int needed_mem = needed_mem_counter(i, j);
    char *memory = mx_strnew(needed_mem);
    if (memory == NULL)
        return NULL;
    int q = 0;
    while (q < needed_mem){
        memory[q] = str[i];
        i++;
        q++;
    }
    return memory;
}

