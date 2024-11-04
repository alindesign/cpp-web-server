#ifndef RESPONSE_H
#define RESPONSE_H
#include <string>

#include "http_status.h"

const char *status_text_of();

class Response {
  bool started;
  const int fd;
  HttpStatus::Code status;
  std::string buff;

  void write_headers();

  void begin();

public:
  static std::string nl;

  explicit Response(const int fd) :
      started(false), fd(fd), status(HttpStatus::Code::OK) {}

  void write(const std::string &str);

  void writeln();

  void writeln(const std::string &str);

  void write_header(const std::string &string, const std::string &str);

  void send();

  void status_code(HttpStatus::Code code);
};

#endif // RESPONSE_H
