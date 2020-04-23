#include "libmx.h"

char *mx_strnew(int size) {
    int sized = size;
    char *memory = malloc(sized + 1);

    if (memory == NULL)
        return NULL;
    for (int i = 0; i < sized + 1; i++)
        memory[i] = '\0';
    return memory;
}
