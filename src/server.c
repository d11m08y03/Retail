#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 6961
#define BUFFER_SIZE 2048

static int server_socket = 0;

void handle_sigint(int sig) {
  printf("\nCaught signal %d (SIGINT). Performing cleanup...\n", sig);

  if (close(server_socket) < 0) {
    puts("Error closing client socket");
    exit(EXIT_FAILURE);
  }

  puts("Server closed successfully.");

  exit(EXIT_SUCCESS);
}

void handle_request(int client_socket) {
  char buffer[BUFFER_SIZE] = {0};
  int bytes_read;
  const char *response_header =
      "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: ";
  char response_body[BUFFER_SIZE] = {0};
  char response[BUFFER_SIZE] = {0};

  // Read the request
  bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
  if (bytes_read < 0) {
    perror("read");
    close(client_socket);
    return;
  }
  buffer[bytes_read] = '\0';

  // Extract path from request
  char method[BUFFER_SIZE], path[BUFFER_SIZE], protocol[BUFFER_SIZE];
  sscanf(buffer, "%s %s %s", method, path, protocol);

  if (strcmp(path, "/") == 0) {
    snprintf(
        response_body, sizeof(response_body), "{\"message\": \"Hello World\"}");
  } else if (strcmp(path, "/balls") == 0) {
    snprintf(
        response_body, sizeof(response_body), "{\"message\": \"Hello Balls\"}");
  } else {
    snprintf(
        response_body,
        sizeof(response_body),
        "{\"error\": \"Route not found\"}");
  }

  // Prepare response
  snprintf(
      response,
      sizeof(response),
      "%s%d\r\n\r\n%s",
      response_header,
      (int)strlen(response_body),
      response_body);

  // Send response
  write(client_socket, response, strlen(response));

  close(client_socket);
}

int main(void) {
  // Signaction when server is stopped
  struct sigaction sa;
  sa.sa_handler = handle_sigint;
  sa.sa_flags = 0;
  sigemptyset(&sa.sa_mask);

  if (sigaction(SIGINT, &sa, NULL) == -1) {
    perror("Unable to set up signal handler");
    exit(EXIT_FAILURE);
  }

  int client_socket;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_addr_len = sizeof(client_addr);

  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0) {
    perror("Socket");
    exit(EXIT_FAILURE);
  }

  // Set SO_REUSEADDR to allow reuse of address
  int opt = 1;
  if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
    perror("setsockopt");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  int bind_result =
      bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (bind_result < 0) {
    perror("Bind");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  // Listen for incoming connections
  if (listen(server_socket, 10) < 0) {
    perror("Listen");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  printf("Server running on port %d. Press Ctrl-C to stop.\n", PORT);

  while (true) {
    client_socket = accept(
        server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket < 0) {
      perror("accept failed");
      close(server_socket);
      exit(EXIT_FAILURE);
    }

    handle_request(client_socket);
  }

  return EXIT_SUCCESS;
}
