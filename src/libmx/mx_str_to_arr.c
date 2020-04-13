#include "ush.h"
/* 
    * Counts number of words, which appears,
    after dividing str by delim;
    * Example:
        "Hello World YES!"
        return 3
*/
static int word_count(char *str, char delim) {
    int counter = 0;
    int index = 0;

    while (str[index]) {
    
        if (str[index] != delim) {
            counter++;
            while(str[index] && str[index] != delim)
                index++;
        }
        else 
            index++;
    }
    return counter;
}

/*
    * determines the last index of char of the word
    * Example:
        - str = "Hello world"
        - start_index = 0 ('H')
        - delim = ' '
    returns 4 (as 'o' has 4th index in str)                        
*/
static int index_of_last_char(char *str, int start_indx, char delim) {
    int len = mx_strlen(str);
    int tmp_index = start_indx;

    while(tmp_index < len) {
        if (str[tmp_index + 1] == delim || str[tmp_index + 1] == '\0') {
            return tmp_index;
        }
        tmp_index++;
    }
    return -1;
}

/*
    * Skipps char (if it is delim) until char is not delim
*/
static int index_of_first_char(char *str, char delim) {
    int index = 0;

    while (str[index] == delim)
        index++;
    return index;
}

/* 
    * devide str by delim and return arr of words
    * Example:
        mx_str_to_arr(" Hello World ", ' ')
        return arr = {"Hello", "World"}
*/
char **mx_str_to_arr(char *str, char delim) {
    int words = word_count(str, delim);
    char **arr = mx_new_strarr(words);
    int start_indx = index_of_first_char(str, delim);
    int index = 0;
    int last_indx;
    char *substr;
    
    while (str[start_indx]) {
        last_indx = index_of_last_char(str, start_indx, delim);
        substr = mx_substr_retriever(str, start_indx, last_indx);
        arr[index] = substr;
        index++;
        last_indx++;

        while (str[last_indx] == delim)
            last_indx++;
        start_indx = last_indx;
    }
    return arr;
}














