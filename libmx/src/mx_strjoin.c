#include "libmx.h"

/* 
 * Function joins two strings
 * "Hello" "World" => "HelloWorld"
 * If first argument(s1) = NULL, func. returns second argument(s2)
 * If second arg.(s2) = NULL, func returns first arg.(s1)
 */
static char *mx_strjoin_null_checker(char *s1, char *s2) {
    int len;
    char *result;

    if(s1 == NULL && s2 != NULL) {
        len = mx_strlen(s2);
        result = mx_strnew(len);

        result = mx_strcpy(result ,s2);
        return result;
    }
    else if(s1 != NULL && s2 == NULL) {
        len = mx_strlen(s1);
        result = mx_strnew(len);

        result = mx_strcpy(result, s1);
        return result;
    }
    else
        return NULL;
}

char *mx_strjoin(char *s1, char *s2) {
    char *null_checker = mx_strjoin_null_checker(s1, s2);
    int len_s1;
    int len_s2;
    char *new_str;
    if (null_checker != NULL)
        return null_checker;
    len_s1 = mx_strlen(s1);
    len_s2 = mx_strlen(s2);
    new_str = mx_strnew(len_s1 + len_s2);

    for(int i = 0; i < len_s1; i++)
        new_str[i] = s1[i];
    for(int i = len_s1; i < len_s1 + len_s2; i++)
        new_str[i] = s2[i - len_s1];
    return new_str;
}
