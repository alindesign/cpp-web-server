#include "request.h"

#include <sys/socket.h>

#include <string>

#include "logger.h"

void Request::read_from_socket() {
  ssize_t bytes_read;
  do {
    content.resize(content_length + buffer_size);
    bytes_read = read(fd, content.data() + content_length, buffer_size);
    if (bytes_read < 0) {
      errorf("error: unable to read from socket got (%ld)\n", bytes_read);
      panic(EXIT_FAILURE);
    }

    content_length += bytes_read;
  } while (bytes_read == buffer_size);

  content.resize(content_length);

  parse();
}

void Request::parse() {
  const auto method_end = content.find(' ');
  if (method_end == std::string::npos) {
    method = UNKNOWN;
    return;
  }

  const std::string method_str = content.substr(0, method_end);
  if (method_str == "GET")
    method = GET;
  else if (method_str == "POST")
    method = POST;
  else
    method = UNKNOWN;
}
