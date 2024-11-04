#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <netinet/in.h>

#include <cstdint>

#include "request.h"
#include "response.h"

class HttpServer {
  sockaddr_in addr{};

  const int workers = 32;

  int socket_fd{};

  int server_bind{};

  void (*request_handler)(const Request &req, Response &res){};

  void init_addr(uint32_t addr, uint16_t port);

  void init_socket();

  void init_bind();

  void init_listen() const;

  void handle_request() const;

  void accepting_connections() const;

public:
  HttpServer(uint32_t addr, uint16_t port);

  ~HttpServer();

  void cleanup() const;

  void bootstrap();

  void handle(void (*handler)(const Request &req, Response &res));
};

#endif // HTTP_SERVER_H
