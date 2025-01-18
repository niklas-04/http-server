#pragma once
#include <stdlib.h>

typedef char* Path;
typedef struct http_response http_response_t;
typedef struct request http_request;


enum Methods {
    NONE,
    GET
};
typedef enum Methods http_method;


enum Status {
    NO_STATUS,
    STATUS_200 = 200,
    STATUS_404 = 404
};
typedef enum Status http_status;

struct request {
    char *version;
    Path path;
    http_method method;
};

struct http_response {
    http_status status;
    char *version; // maybe not needed?
    char *type;
    size_t content_length;
    void *content;
};
