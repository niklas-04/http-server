#include "http_parser.h"
#include <stdio.h>

Path get_path(char *request) {
    while (*request++ && *request != ' ');
    return ++request;
}
