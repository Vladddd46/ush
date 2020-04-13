#include "ush.h"

void mx_controlling_terminal_change(pid_t proc_id) {
    tcsetpgrp(0, proc_id);
    tcsetpgrp(1, proc_id);
}

