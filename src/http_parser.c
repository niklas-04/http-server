#include "http_parser.h"
#include <stdio.h>
#include <string.h>

Path get_path(char *request) {
    int word = 0;
    char buffer[1024] = { 0 };
    int j = 0;
   for (int i = 0; i < 1024 && *(request + i) && word < 2; i++) {
        if (*(request + i) == ' ') {
            word++;
        } else if (word == 1) {
            buffer[j] = *(request + i);
            j++;
        }
   }

    return strdup(buffer);
}
