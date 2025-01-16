#include "common.h"
#include "response.h"

http_response_t *create_http_response() {
    http_response_t *response = calloc(1, sizeof(http_response_t));
    return response;
}

// TODO: remove hardcoded strings
char *response_tostring(http_response_t *response) {
    char response_buffer[1024] = { 0 };
    char temp_buffer[256] = { 0 };

    int current_len = snprintf(temp_buffer, 256, "Status Code: %d\n", response->status);
    strcat(response_buffer, temp_buffer);

    current_len += snprintf(temp_buffer, 256, "Status Message: OK\n", response->status);
    strcat(response_buffer, temp_buffer);

    current_len += snprintf(temp_buffer, 256, "Headers: %s\n", response->type);
    strcat(response_buffer, temp_buffer);

    current_len += snprintf(temp_buffer, 256, "Content: %s\n", response->content);
    strcat(response_buffer, temp_buffer);
    

    return strdup(response_buffer);
}
