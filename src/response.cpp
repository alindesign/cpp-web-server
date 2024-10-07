#include <string>
#include <unistd.h>
#include <sstream>
#include <iomanip>
#include <chrono>

#include "response.h"

std::string Response::nl = "\r\n";

void Response::write_header(const std::string &string, const std::string &str) {
    std::stringstream header_stream;
    header_stream << string << ": " << str << nl;
    write(header_stream.str());
}

void Response::send() {
    begin();
    write_headers();
    write(nl);
    write(buff);
}

void Response::status_code(const uint16_t i) {
    status = i;
}

std::string status_text_of(const uint16_t status) {
    if (status == 200) {
        return "OK";
    }

    if (status == 404) {
        return "Not Found";
    }

    if (status == 500) {
        return "Internal Server Error";
    }

    return "Unknown";
}

void Response::write_headers() {
    std::stringstream date_stream;
    const auto now = std::chrono::system_clock::now();
    const auto in_time_t = std::chrono::system_clock::to_time_t(now);
    date_stream << std::put_time(std::gmtime(&in_time_t), "%a, %d %b %Y %T %Z");

    write_header("Date", date_stream.str());
    write_header("Server", "passm");
    write_header("Connection", "close");
}

void Response::begin() {
    started = true;
    std::stringstream init_stream;
    init_stream << "HTTP/1.1 " << status << " " << status_text_of(status) << nl;
    write(init_stream.str());
}

void Response::writeln(const std::string &str) {
    write(str);
    writeln();
}

void Response::write(const std::string &str) {
    if (!started) {
        buff += str;
    } else {
        ::write(fd, str.c_str(), str.size());
    }
}

void Response::writeln() {
    write(nl);
}
