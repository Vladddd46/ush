#include "ush.h"

// Restores signals, that were ignored in main()
void mx_signals_restore() {
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGINT, SIG_DFL);
}



