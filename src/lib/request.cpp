#include <chrono>
#include <string>
#include <sys/socket.h>

#include <iostream>
#include "logger.h"
#include "request.h"

void Request::Req::read_from_socket() {
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

void Request::Req::parse() {
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

void Request::log_request(const Request::Req &req) {
  std::stringstream log_stream;
  const auto now = std::chrono::system_clock::now();
  const auto in_time_t = std::chrono::system_clock::to_time_t(now);
  log_stream << std::put_time(std::gmtime(&in_time_t),
                              "[%d/%b/%Y:%H:%M:%S %z]");
  log_stream << " " << Request::method_str(req.method) << " " << req.uri;

  std::cerr << log_stream.str() << std::endl;
}

std::string Request::method_str(const Method &method) {
  switch (method) {
    case GET:
      return "GET";
    case POST:
      return "POST";
    default:
      return "UNKNOWN";
  }
}
