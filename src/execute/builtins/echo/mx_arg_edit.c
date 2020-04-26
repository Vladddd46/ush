#include "ush.h"

/*
 * Edits argument of echo 
 * depending on flags and quotes
 * specified by user.
 */

static void is_in_quotes(int *is_quoted, int *i, char *old_arg) {
    if (old_arg[*i] == '\'' || old_arg[*i] == '\"') {
        if (*is_quoted == 0)
            *is_quoted = 1;
        else
            *is_quoted = 0;
        *i += 1;
    }
}

static void ch_not_in_quotes(int *i, int *index, 
                            char *old_arg, char **edited_str) {
    if (old_arg[*i] == '\\')
        *i += 1;
    edited_str[0][*index] = old_arg[*i];
    *index += 1;
}

static void edit_without_resolve_esc_ch(char **edited_str, char *old_arg,
                                        int *index, int *i) {
    edited_str[0][*index] = old_arg[*i];
    *index += 1;
}

static int big_e_flag(char *flags) {
    if (mx_is_in_arr(flags, 'E') && mx_is_in_arr(flags, 'e') == 0)
        return 1; 
    return 0;
}

char *mx_arg_edit(char *old_arg, char *flags) {
    char *edited_str = mx_strnew(mx_strlen(old_arg));
    char *result;
    int index = 0;
    int is_quoted = 0;

    for (int i = 0; old_arg[i]; ++i) {
        is_in_quotes(&is_quoted, &i, old_arg);
        if (is_quoted == 0)
            ch_not_in_quotes(&i, &index, old_arg, &edited_str);
        else if (is_quoted) {
            if (big_e_flag(flags))
                edit_without_resolve_esc_ch(&edited_str, old_arg, &index, &i);
            else
                mx_edit_with_resolve_esc_ch(old_arg, &edited_str, &i, &index);
        }
    }
    result = mx_string_copy(edited_str);
    free(edited_str);
    return result;
}


