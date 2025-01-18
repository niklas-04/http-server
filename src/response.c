#include "common.h"
#include "response.h"
#define HEADER_BYTES 1024

http_response_t *create_http_response() {
    http_response_t *response = calloc(1, sizeof(http_response_t));
    return response;
}

// TODO: remove hardcoded strings
char *response_tostring(http_response_t *response) {
    size_t buff_len = response->content_length + HEADER_BYTES;
    char *response_buffer = calloc(1, buff_len * sizeof(char));

    char *status_message = response->status < 400 ? "OK" : "Not Found";
    int current_len = snprintf(response_buffer, buff_len, "%s %d %s\n", response->version, response->status, status_message);

    //current_len += snprintf(response_buffer, buff_len, "Content-Type: %s\n", response->type);
    current_len += snprintf(response_buffer + current_len, buff_len, "Content-Type: text/html\n");

    current_len += snprintf(response_buffer + current_len, buff_len, "Content-Length %d\n\n", response->content_length);

    current_len += snprintf(response_buffer + current_len, buff_len,"%s", response->content);

    return response_buffer;
}

void destroy_response(http_response_t *response) {
    if (response->version) {
        free(response->version);
    }
    if (response->type) {
        free(response->type);
    }
    if (response->content) {
        free(response->content);
    }

    free(response);
}
