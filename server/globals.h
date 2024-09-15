#ifndef GLOBALS_H
#define GLOBALS_H

#define PORT 6961
#define BUFFER_SIZE 2048

#define HTTP_OK_RESPONSE_HEADER                                                \
  "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: "

#define HTTP_CREATED_RESPONSE_HEADER                                           \
  "HTTP/1.1 201 Created\r\nContent-Type: application/json\r\nContent-Length: "

#define HTTP_NOT_FOUND_RESPONSE_HEADER                                         \
  "HTTP/1.1 404 Not Found\r\nContent-Type: "                                   \
  "application/json\r\nContent-Length: "

#endif // !GLOBALS_H
