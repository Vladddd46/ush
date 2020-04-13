#include "ush.h"

// Changes terminal`s mode to raw.
void mx_enable_raw_mode(struct termios orig_termios) {
    struct termios raw = orig_termios;

    tcgetattr(0, &orig_termios);
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSAFLUSH, &raw);
}
