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

enum Version {
    NO_VERSION,
    V0_9,
    V1_0
};
typedef enum Version version_t;

struct request {
    version_t version;
    Path path;
    http_method method;
};

struct http_response {
    size_t status;
    version_t version;
    char *type;
    void *content;
};
