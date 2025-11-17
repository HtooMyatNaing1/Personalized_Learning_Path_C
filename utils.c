#include <string.h>
#include <stdio.h>
#include "utils.h"

void trim_newline(char *s) {
    size_t n = strlen(s);
    if (n==0) return;
    if (s[n-1]=='\n') s[n-1]='\0';
}

void clear_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}