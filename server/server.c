#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "db.h"
#include "globals.h"
#include "handlers.h"
#include "server.h"

static int server_socket = 0;

static void handle_sigint(int sig) {
  printf("\nCaught signal %d (SIGINT). Performing cleanup...\n", sig);

  if (close(server_socket) < 0) {
    puts("Error closing client socket.");
    exit(EXIT_FAILURE);
  }

  puts("Server closed successfully.");

  db_destroy();

  exit(EXIT_SUCCESS);
}

static void handle_requests(int client_socket) {
  char buffer[BUFFER_SIZE] = {0};
  int bytes_read;
  char response_body[BUFFER_SIZE] = {0};
  char response[BUFFER_SIZE * 2] = {0};

  // Read the request
  bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
  if (bytes_read < 0) {
    perror("Read.");
    close(client_socket);
    return;
  }
  buffer[bytes_read] = '\0';

  // Extract path from request
  char method[BUFFER_SIZE], path[BUFFER_SIZE], protocol[BUFFER_SIZE];
  sscanf(buffer, "%s %s %s", method, path, protocol);

  char *json_string;
  char *response_header;

  // Handle URL paths
  if (strcmp(path, "/api/create_user") == 0) {
    json_string = handle_create_user(buffer);
    response_header = HTTP_CREATED_RESPONSE_HEADER;

    printf(
        "[LOG | %s | %s] /api/create_user HIT. Payload: %s \n",
        __func__,
        __FILE__,
        json_string);

  } else if (strcmp(path, "/api/create_product") == 0) {
    json_string = handle_create_product(buffer);
    response_header = HTTP_CREATED_RESPONSE_HEADER;

    printf(
        "[LOG | %s | %s] /api/create_product HIT. Payload: %s \n",
        __func__,
        __FILE__,
        json_string);

  } else {
    json_string = "{\"error\": \"Route not found\"}";
    response_header = HTTP_NOT_FOUND_RESPONSE_HEADER;

    printf(
        "[LOG | %s | %s] %s 404 HIT. Payload: %s \n",
        __func__,
        __FILE__,
        path,
        json_string);
  }

  snprintf(response_body, sizeof(response_body), "%s", json_string);

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

int server_start(void) {
  // Sigaction when server is stopped
  struct sigaction sa;
  sa.sa_handler = handle_sigint;
  sa.sa_flags = 0;
  sigemptyset(&sa.sa_mask);

  if (sigaction(SIGINT, &sa, NULL) == -1) {
    perror("Unable to set up signal handler.");
    exit(EXIT_FAILURE);
  }

  int client_socket;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_addr_len = sizeof(client_addr);

  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0) {
    perror("Socket.");
    exit(EXIT_FAILURE);
  }

  // Set SO_REUSEADDR to allow reuse of address and port
  int opt = 1;
  if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
    perror("Setsockopt.");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  int bind_result =
      bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (bind_result < 0) {
    perror("Bind.");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  // Listen for incoming connections
  if (listen(server_socket, 10) < 0) {
    perror("Listen.");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  printf("Server running on port %d. Press Ctrl-C to stop.\n", PORT);

  while (true) {
    client_socket = accept(
        server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket < 0) {
      perror("Accept failed.");
      close(server_socket);
      exit(EXIT_FAILURE);
    }

    handle_requests(client_socket);
  }

  return EXIT_SUCCESS;
}
