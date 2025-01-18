#include "http_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MSG_MAX_LEN 1024

char *get_word_at_index(char *str, size_t index) {
    int word = 0;
    char buffer[MSG_MAX_LEN] = { 0 };
    int j = 0;
   for (int i = 0; i < 1024 && *(str + i) && word < index + 1; i++) {
        char current_char = *(str + i);
        if (current_char == ' ' || current_char == '\r') {
            word++;
        } else if (current_char != '\n' && word == index) {
            buffer[j] = *(str + i);
            j++;
        }
   }

    if (word <= index) {
        return NULL;
    }
    return strdup(buffer);
}

http_method check_method(char *msg) {
    http_method method = NONE;
    char *first_word =  get_word_at_index(msg, 0);

    if (!first_word) {
        return method;
    }

    if (!strcmp(first_word, "GET")) {
        method = GET;
    }
    free(first_word);
    return method;
}

Path get_path(char *request) {
    return get_word_at_index(request, 1);
}

char *get_version(char *request) {
    return get_word_at_index(request, 2);
}

char *get_response_type(char *request) {
    Path path = get_path(request);
    // TODO: implement

    free(path);
}
