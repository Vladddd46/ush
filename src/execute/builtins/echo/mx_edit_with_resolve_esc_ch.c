#include "ush.h"

/*
 * Edits old_arg in order to resolve escape characters.
 * Save result in edited_str[0]
 */
void mx_edit_with_resolve_esc_ch(char *old_arg, char **edited_str,
                                    int *i, int *index) {
    if (old_arg[*i] == '\\') {
        *i += 1;
    if (mx_escape_char_determiner(old_arg[*i]) != -1)
        edited_str[0][*index] = mx_escape_char_determiner(old_arg[*i]);
    else
        edited_str[0][*index] = old_arg[*i];
        *index += 1;
    }
    else {
        edited_str[0][*index] = old_arg[*i];
        *index += 1;
    }
}

