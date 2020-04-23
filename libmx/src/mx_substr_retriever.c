#include "libmx.h"
/*
 * Retrieves str[indx1:indx2] from src_str
 * Example:
 *       char *s = "HelloWorld"  // needed substr = "oWo"
 *       >>>mx_substr_retriever(s, 4, 6)
 *       return oWo
 */
char *mx_substr_retriever(char *src_str, int indx1, int indx2) {
    if (indx1 > indx2 || src_str == NULL)
        return NULL;
    char *sub = mx_strnew((indx2 + 1) - indx1);
    int index = 0;

    while(indx1 <= indx2) {
        sub[index] = src_str[indx1];
        indx1++;
        index++;
    }
    return sub;
}




