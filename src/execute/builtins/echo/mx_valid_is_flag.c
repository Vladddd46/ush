#include "ush.h"

/*
    * returns flag identifier if flag is valid.
      also flag combinations are considered.
      id '-n' (and combinations) = 2
      id '-e' (and combinations) = 1
      id '-E' (and combinations) = 0
*/
int mx_valid_is_flag(char *flag) {
    char *n_combinations[12] = {"-n","-ne","-nE", "-En", "-en", "-neE", 
                             "-nEe", "-enE", "-Ene", "-Een", "-eEn",NULL};
    char *big_e_combinations[12] = {"-E","-Ee","-En", "-nE", "-eE", "-Een", 
                             "-Ene", "-eEn", "-nEe", "-neE", "-enE",NULL};
    char *e_combinations[12] = {"-e","-en","-eE", "-Ee", "-ne", "-enE", 
                             "-eEn", "-neE", "-Een", "-Ene", "-nEe",NULL};  

    if (mx_str_in_arr_index(n_combinations, flag) != -1)
        return 2;
    if (mx_str_in_arr_index(e_combinations, flag) != -1)
        return 1;
    if (mx_str_in_arr_index(big_e_combinations, flag) != -1)
        return 0;
    return -1;
}


