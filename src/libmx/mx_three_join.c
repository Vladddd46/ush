#include "ush.h"
/* 
    concatenates 3 strings in one 
*/

char *mx_three_join(char *str1, char *str2, char *str3) {
    char *str1_str2 = mx_strjoin(str1, str2);
    char *result = mx_strjoin(str1_str2, str3);

    free(str1_str2);
    return result;  
}
