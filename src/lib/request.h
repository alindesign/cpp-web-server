#ifndef REQUEST_H
#define REQUEST_H

#include <string>

#define STATUS_OK 200
#define STATUS_NOT_FOUND 404
#define STATUS_INTERNAL_SERVER_ERROR 500


namespace Request {
  enum Method {
    UNKNOWN,
    GET,
    POST,
  };

  class Req {
    std::string content;
    ssize_t content_length = 0;
    const u_int16_t buffer_size = 1024;
    int fd;

    void parse();

  public:
    Method method;
    std::string uri;

    explicit Req(const int fd) : fd(fd), method() {}

    void read_from_socket();
  }; // class Req

  void log_request(const Req &req);

  std::string method_str(const Method &method);

} // namespace Request

#endif // REQUEST_H
