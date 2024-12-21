#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct http_server http_server_t;


http_server_t *create_http_server(int port);
void close_http_server(http_server_t *server);
void http_accept_new_client(http_server_t *server);
char *http_read(http_server_t *server, size_t client_index);
void http_send(http_server_t *server, size_t client_index, char *msg);
