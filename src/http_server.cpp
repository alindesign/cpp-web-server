#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <csignal>
#include <string>
#include <thread>
#include <vector>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "common.h"
#include "http_server.h"
#include "request.h"
#include "response.h"

HttpServer::HttpServer(const uint32_t addr, const uint16_t port) {
    init_addr(addr, port);
}

HttpServer::~HttpServer() {
    cleanup();
}

void HttpServer::cleanup() const {
    if (socket_fd > 0) {
        printf("Closing socket:%d\n", socket_fd);
        close(socket_fd);
    }

    if (server_bind > 0) {
        printf("Unlink bind%d\n", server_bind);
        close(server_bind);
    }
}

void HttpServer::init_addr(const uint32_t addr, const uint16_t port) {
    this->addr.sin_family = AF_INET;
    this->addr.sin_addr.s_addr = addr;
    this->addr.sin_port = htons(port);
    memset(this->addr.sin_zero, '\0', sizeof this->addr.sin_zero);
}

void HttpServer::init_socket() {
    printf("Setting up socket\n");
    if (socket_fd = socket(AF_INET, SOCK_STREAM, 0); socket_fd < 0) {
        errorf("error: unable to create socket got (%d)\n", socket_fd);
        panic(socket_fd);
    }

    constexpr int enable = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        errorf("setsockopt(SO_REUSEADDR) failed");
        panic(EXIT_FAILURE);
    }
}

void HttpServer::init_bind() {
    printf("Binding socket\n");
    if (server_bind = bind(socket_fd, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)); server_bind < 0) {
        errorf("error: unable to bind socket got (%d)\n", server_bind);
        panic(server_bind);
    }
}

void HttpServer::init_listen() const {
    printf("Listening on socket\n");
    if (const int result = listen(socket_fd, 10); result < 0) {
        errorf("error: unable to listen on socket got (%d)\n", result);
        panic(result);
    }
}

void HttpServer::handle_request() const {
    sockaddr_in client_addr{};
    socklen_t client_addr_len = sizeof(client_addr);

    const int client_fd = accept(socket_fd, reinterpret_cast<sockaddr *>(&client_addr), &client_addr_len);
    if (client_fd < 0) {
        errorf("error: unable to accept connection got (%d)\n", client_fd);
        panic(EXIT_FAILURE);
    }

    Request req(client_fd);
    Response res(client_fd);

    try {
        req.read_from_socket();
        res.status_code(STATUS_OK);
        request_handler(req, res);
    } catch (const std::exception &e) {
        res.status_code(STATUS_INTERNAL_SERVER_ERROR);
        res.writeln(R"(Error)");
    }

    res.send();
    close(client_fd);
}

void HttpServer::accepting_connections() const {
    printf("Accepting connections\n");
    std::vector<std::thread> threads;
    threads.reserve(workers);

    for (int i = 0; i < workers; i++) {
        threads.emplace_back([this] {
            while (true) {
                handle_request();
            }
        });
    }

    for (auto &thread: threads) {
        thread.join();
    }
}

void HttpServer::bootstrap() {
    printf("Trying to listen on http://%s:%d\n",
           inet_ntoa(addr.sin_addr),
           ntohs(addr.sin_port));

    init_socket();
    init_bind();
    init_listen();
    accepting_connections();
}

void HttpServer::handle(void (*handler)(const Request &req, Response &res)) {
    request_handler = handler;
}
