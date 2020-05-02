#include "ush.h"

// Frees mem of many strs
void mx_free_strs(int num, ...) {

   va_list valist;
   /* initialize valist for num number of arguments */
   va_start(valist, num);
   for (int i = 0; i < num; ++i)
       free(va_arg(valist, char *));
   /* clean memory reserved for valist */
   va_end(valist);
}

