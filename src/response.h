#ifndef RESPONSE_H
#define RESPONSE_H
#include <cstdint>
#include <string>

const char *status_text_of();

class Response {
    bool started;
    uint16_t status;
    const int fd;
    std::string buff;

    void write_headers();

    void begin();

public:
    static std::string nl;

    explicit Response(const int fd): started(false), status(0), fd(fd) {
    }

    void write(const std::string &str);

    void writeln();

    void writeln(const std::string &str);

    void write_header(const std::string &string, const std::string &str);

    void send();

    void status_code(u_int16_t i);
};

#endif //RESPONSE_H
