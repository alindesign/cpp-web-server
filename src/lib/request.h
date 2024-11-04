#ifndef REQUEST_H
#define REQUEST_H

#include <string>

#define STATUS_OK 200
#define STATUS_NOT_FOUND 404
#define STATUS_INTERNAL_SERVER_ERROR 500

enum Method {
  UNKNOWN,
  GET,
  POST,
};

class Request {
  std::string content;
  ssize_t content_length = 0;
  const u_int16_t buffer_size = 1024;
  int fd;

  void parse();

public:
  Method method;

  explicit Request(const int fd) : fd(fd), method() {}

  void read_from_socket();
};

#endif // REQUEST_H
