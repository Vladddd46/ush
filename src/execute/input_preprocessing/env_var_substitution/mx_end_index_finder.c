#include "ush.h"

/*
    * returns ending index of last element is expression
      with dollar.
    * For Example:
      str = "abc${HOME}abc";
        dollar_indx = 3
        end_indx    = 9
      str = "abc$HOME."
        dollar_indx = 3
        end_indx    = 7
*/
int mx_end_index_finder(char *str, int dollar_indx) {
    int end_indx = dollar_indx + 1;

    if (str[end_indx] && str[end_indx] == '{') {
        while(str[end_indx] && str[end_indx + 1] != '}')
            end_indx++;
        end_indx++;
    }
    else if (str[end_indx] && mx_is_alphadigit(str[end_indx])) {
        while(str[end_indx] && mx_is_alphadigit(str[end_indx + 1]))
            end_indx++;
    }
    else if (str[end_indx] && str[end_indx] == '$') {
        return end_indx;
    }
    return end_indx;
}




