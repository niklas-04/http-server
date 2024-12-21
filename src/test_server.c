#include "server.h"
#include <stdio.h>


int main() { 
    http_server_t *server = create_http_server(8080);
    printf("server created\n");
    http_accept_new_client(server);
    printf("client accepted\n");
    char *str = http_read(server, 0);
    printf("%s", str);
    http_send(server, 0, "hej tillbaka");
    printf("sent string");
    close_http_server(server);
}
