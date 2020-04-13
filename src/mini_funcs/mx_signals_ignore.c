#include "ush.h"

/*
    * make programm ignore signals:
        ctrl+c
        ctrl+z 
*/

void mx_signals_ignore() {
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGINT , SIG_IGN);
}
