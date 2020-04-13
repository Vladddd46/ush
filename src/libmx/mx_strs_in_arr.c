#include "ush.h"

/*
    * checks whether any element of **source occured in arr
    * if true -> returns index of first occurance
    * if no occurance -> return -1
    * Examples:

        1)
        {"+", "-"}  - source
        {"2", "*", "2", "+", "4"} - arr
        returns 3 ------/

        2)
        {"&&", "||}  - source
        {"2", "*", "2", "+", "4"} - arr
        returns -1
*/
int mx_strs_in_arr_index(char **source, char **arr) {
    
    for (int i = 0; i <  mx_strarr_size(arr); i++) {
        for (int j = 0; j < mx_strarr_size(source); j++) {
            if (mx_strcmp(arr[i], source[j]) == 0) 
                return i;
        }
    }
    return -1;
}



