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

    char *status_message = response->status < 400 ? "OK" : "Not Found";
    int current_len = snprintf(temp_buffer, 256, "%s %d %s\n", response->version, response->status, status_message);
    strcat(response_buffer, temp_buffer);

    //current_len += snprintf(temp_buffer, 256, "Content-Type: %s\n", response->type);
    current_len += snprintf(temp_buffer, 256, "Content-Type: text/html\n");
    strcat(response_buffer, temp_buffer);

    current_len += snprintf(temp_buffer, 256, "Content-Length: %d\n\n", response->content_length);
    strcat(response_buffer, temp_buffer);

    current_len += snprintf(temp_buffer, 256, "%s", (char *) response->content);
    strcat(response_buffer, temp_buffer);
    

    return strdup(response_buffer);
}
