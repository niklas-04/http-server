#pragma once
#include <string.h>
#include <stdio.h>

http_response_t *create_http_response();
char *response_tostring(http_response_t *response);
void destroy_response(http_response_t *response);
