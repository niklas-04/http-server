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

enum Status {
    NO_STATUS
};
typedef enum Status http_status;

struct request {
    version_t version;
    Path path;
    http_method method;
};

struct http_response {
    http_status status;
    version_t version; // maybe not needed?
    char *type;
    void *content;
};
