#include <csignal>
#include <cstdlib>
#include <iostream>
#include "arpa/inet.h"

#include "lib/http_server.h"
#include "lib/view.h"

using namespace View;

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
      auto document = html(
          {
             {"lang", "en"},
          },
          {
              head({
                  title("Hello, World!"),
                  style("body { background-color: #f0f0f0; }"),
              }),
              body({
                  h1({text("Hello, World!")}),
                  p({text("This is a paragraph.")}),
              }),
          });

      res.write(document.render());
    } else {
      res.write("Method not allowed");
    }
  });

  server.bootstrap();
  return 0;
}
