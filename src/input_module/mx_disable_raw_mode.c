#include "ush.h"

// Changes terminal`s mode to original.
void mx_disable_raw_mode(struct termios orig_termios) {
    tcsetattr(0, TCSAFLUSH, &orig_termios);
}

