#include "ush.h"

int mx_no_current_job_err(t_proc *proc) {
    char *msg;
    
    if (proc == NULL) {
        msg = "fg: no current job\n";
        write(2, msg, mx_strlen(msg));
        return 1;
    }
    else
        return 0;
}


