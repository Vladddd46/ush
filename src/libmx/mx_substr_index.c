#include "ush.h"

/*
    * finds index of first char of sub in string
    * str = geHello sub = Hello
    * return 2  
*/
int mx_substr_index(char *str, char *sub) {
    for (int i = 0; i < mx_strlen(str); ++i) {
        if (str[i] == sub[0]) {
            int tmp_i = i;
            int sub_i = 0;
            while(str[tmp_i] == sub[sub_i] && str[tmp_i]) {
                tmp_i++;
                sub_i++;
            }
            if (tmp_i - i == sub_i) 
                return i;
        }
    }
    return -1;
}

