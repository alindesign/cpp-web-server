#include "http_status.h"

std::string HttpStatus::reason(const Code code) {
  switch (code) {
    case Code::OK:
      return "OK";
    case Code::CREATED:
      return "Created";
    case Code::ACCEPTED:
      return "Accepted";
    case Code::NO_CONTENT:
      return "No Content";
    case Code::RESET_CONTENT:
      return "Reset Content";
    case Code::PARTIAL_CONTENT:
      return "Partial Content";
    case Code::MOVED_PERMANENTLY:
      return "Moved Permanently";
    case Code::FOUND:
      return "Found";
    case Code::NOT_MODIFIED:
      return "Not Modified";
    case Code::TEMPORARY_REDIRECT:
      return "Temporary Redirect";
    case Code::PERMANENT_REDIRECT:
      return "Permanent Redirect";
    case Code::BAD_REQUEST:
      return "Bad Request";
    case Code::UNAUTHORIZED:
      return "Unauthorized";
    case Code::FORBIDDEN:
      return "Forbidden";
    case Code::NOT_FOUND:
      return "Not Found";
    case Code::METHOD_NOT_ALLOWED:
      return "Method Not Allowed";
    case Code::UNPROCESSABLE_ENTITY:
      return "Unprocessable Entity";
    case Code::TOO_MANY_REQUESTS:
      return "Too Many Requests";
    case Code::INTERNAL_SERVER_ERROR:
      return "Internal Server Error";
    case Code::NOT_IMPLEMENTED:
      return "Not Implemented";
    case Code::BAD_GATEWAY:
      return "Bad Gateway";
    case Code::SERVICE_UNAVAILABLE:
      return "Service Unavailable";
    case Code::GATEWAY_TIMEOUT:
      return "Gateway Timeout";
    default:
      return "Unknown";
  }
}

int HttpStatus::to_int(Code code) {
  return static_cast<int>(code);
}
