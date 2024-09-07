#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8888
#define BUFFER_SIZE 2048

void handle_request(int client_socket) {
  char buffer[BUFFER_SIZE] = {0};
  int bytes_read;
  const char *response_header =
      "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: ";
  const char *response_body = "{\"message\": \"Hello World\"}";
  char response[BUFFER_SIZE] = {0};

  // Read the request
  bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
  if (bytes_read < 0) {
    perror("read");
    close(client_socket);
    return;
  }
  buffer[bytes_read] = '\0';

  // Prepare response
  snprintf(response, sizeof(response), "%s%d\r\n\r\n%s", response_header,
           (int)strlen(response_body), response_body);

  // Send response
  write(client_socket, response, strlen(response));

  close(client_socket);
}

int main(void) {
  int server_socket, client_socket;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_addr_len = sizeof(client_addr);

  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  int bind_result =
      bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

  if (bind_result < 0) {
    perror("bind");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  // Listen for incoming connections
  if (listen(server_socket, 10) < 0) {
    perror("listen");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  printf("Server running on port %d\n", PORT);

  client_socket =
      accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);

  while (client_socket >= 0) {
    handle_request(client_socket);
  }

  close(server_socket);

  return EXIT_SUCCESS;
}
