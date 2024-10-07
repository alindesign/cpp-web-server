#include <csignal>
#include <cstdlib>
#include <iostream>
#include "arpa/inet.h"

#include "http_server.h"
#include "request.h"
#include "response.h"

HttpServer server(INADDR_ANY, 8080);

void graceful_shutdown(const int code) {
    std::cout << "Interrupt signal (" << code << ") received.\n";
    server.cleanup();
    exit(code);
}


int main() {
    signal(SIGINT, graceful_shutdown);
    signal(SIGKILL, graceful_shutdown);
    signal(SIGTERM, graceful_shutdown);

    server.handle([](const Request &req, Response &res) {
        if (req.method == GET) {
            res.write("OK");
        } else {
            res.write("Method not allowed");
        }
    });

    server.bootstrap();

    return 0;
}
