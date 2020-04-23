#include "ush.h"

/*
 * Exits from ./ush
 * Executes when ctrl+d is pressed.
 */
void mx_ctrl_d(char buff, struct termios orig_termios) {
    if (buff == 4) {
        mx_disable_raw_mode(orig_termios);
        printf("\n%s\n", "process exited...");
        exit(0);
    }
}
