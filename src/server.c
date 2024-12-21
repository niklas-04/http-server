#include "server.h"
#include "http_parser.h"

#define MAX_CLIENTS 10
#define MSG_MAX_LEN 1024

typedef enum Methods http_method;

enum Methods {
    NONE,
    GET
};

struct http_server {
  int port;
  int socket;                      // A fd to the socket
  int client_sockets[MAX_CLIENTS]; // Each client will have their own socket connection when accepting
  size_t amount_of_clients;
};

// Helpers
static void __exit(char *exit_msg) {
    perror(exit_msg);
    abort();
}

static int *get_client(http_server_t *server, size_t index) {
  if (index > server->amount_of_clients) { return NULL; }
  return &server->client_sockets[index];
}

static void handle_GET(http_server_t *server, size_t client_index, char *msg) {
    Path document_address = get_path(msg);
    FILE *document = fopen(document_address, "r");

    if (document == NULL) { __exit("handle_GET"); }

    char buffer[MSG_MAX_LEN] = { 0 };
    char c;
    for (int i = 0; i < MSG_MAX_LEN && (c = fgetc(document)) != EOF; i++) {
        buffer[i] = c;
    }

    http_send(server, client_index, buffer);
    fclose(document);
}

/* 
 * Get first word of message
 * Check if that word is GET
 */
static http_method check_method(char *msg) {
    http_method method = NONE;
    char first_word[MSG_MAX_LEN] = { 0 };
    for (int i = 0; msg[i] && msg[i] != ' '; i++) {
        first_word[i] = msg[i];
    }

    if (!strcmp(first_word, "GET")) {
        method = GET;
    }
    return method;
}

static void handle_method(http_server_t *server, size_t client_index, char *msg) {
    http_method method = check_method(msg);
    switch (method) {
        case NONE: printf("Not a valid request"); break;
        case GET: handle_GET(server, client_index, msg); break;
    }
}
// End of helpers

http_server_t *create_http_server(int port) {
  http_server_t *server = calloc(1, sizeof(http_server_t));
  if ((server->port = port) < 0) { __exit("invalid port"); }
  // Sets up a socket that uses IPv4, using TCP
  if ((server->socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) { __exit("socket failed"); }
  //server->client_sockets = calloc(MAX_CLIENTS, sizeof(int)); // Each client is represented as a pid (int)
  server->amount_of_clients = 0;
}

void close_http_server(http_server_t *server) {
    for (int i = 0; i < server->amount_of_clients; i++) {
        int current_client_socketfd = server->client_sockets[i];
        close(current_client_socketfd);
    }

    close(server->socket);
    free(server);
}

void http_accept_new_client(http_server_t *server) {
    // TODO: add check to see if server is full
    struct sockaddr_in address; // Description of a socket address
    address.sin_family = AF_INET; // TCP socket
    address.sin_addr.s_addr = INADDR_ANY; // Designate the IP to local
    address.sin_port = htons(server->port);

    int *current_slot = get_client(server, server->amount_of_clients);
    socklen_t addrlen = sizeof(address);

    // Binds the server socket to the socket address
    if (bind(server->socket, (struct sockaddr*) &address, sizeof(address)) < 0) { __exit("bind failed"); }
    // Listen and accept incoming requests, with a maximum queue of 5
    if (listen(server->socket, 5) < 0) { __exit("listen failed"); }
    if ((*current_slot = accept(server->socket, (struct sockaddr*) &address, &addrlen)) < 0) { __exit("accept failed"); }
    server->amount_of_clients++;
}

char *http_read(http_server_t *server, size_t client_index) {
    if (client_index > server->amount_of_clients) { return NULL; }
    int client_fd = *get_client(server, client_index);
    char buffer[MSG_MAX_LEN] = { 0 };

    // TODO: add checks for if server is setup
    // ssize_t allows for -1, indicating failure
    ssize_t bytes_read = read(client_fd, buffer, MSG_MAX_LEN - 1); // one byte reserved for null termination
    buffer[MSG_MAX_LEN] = '\0';

    if (bytes_read < 0) { __exit("read failed"); }

    handle_method(server, client_index, buffer);

    return strdup(buffer);
}

void http_send(http_server_t *server, size_t client_index, char *msg) {
    int client_fd = *get_client(server, client_index);
    if (client_index > server->amount_of_clients || !client_fd) { return; }
    if (send(client_fd, msg, strlen(msg), 0) < 0) { __exit("send failed"); }
}

 //int main(void) {
 //   Path p = "GET /home/niklas/Projekt/http_server/src/hello.txt";
 //   //handle_GET(p);
 //   p = "GET /home/niklas/Projekt/http_server/src/hello.html";
 //   //handle_GET(p);
 //}
