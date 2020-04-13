#include "ush.h"

/*
    * retrieves flags from cmd expression;
    * returns flags = malloc(3);
      flags: {'-', '-', '-'}
      {'-', '-', 'n'} - user specified only -n flag.
      {'-', 'e', '-'} - user specified only -e flag.
      {'E', '-', '-'} - user specified only -E flag.
      {'E', 'e', 'n'} - user specified all flags.
*/

char *mx_flags_retriever(char **cmd) {
    int  flag_id;
    char *flags = mx_strnew(3);
    int walker = 1;
    flags[0] = '-';
    flags[1] = '-';
    flags[2] = '-';

    while(cmd[walker]) {
        flag_id = mx_valid_is_flag(cmd[walker]);
        if (flag_id == 2)
            flags[2] = 'n';
        else if (flag_id == 1)
            flags[1] = 'e';
        else if (flag_id == 0)
            flags[0] = 'E';
        else
            return flags;
        walker++;
    }
    return flags;
}
