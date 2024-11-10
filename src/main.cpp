#include <csignal>
#include <cstdlib>
#include <iostream>
#include "arpa/inet.h"

#include "lib/http_server.h"
#include "lib/view.h"

using namespace View;
using namespace Request;

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

  server.handle([](const Req &req, Response &res) {
    if (req.method == GET) {
      auto document = html(
          {
              prop("lang", "en"),
          },
          {
              head({
                  title("Hello, World!"),
                  style(R"(
                    body {
                      background-color: #111;
                      color: #fff;
                    }
                  )"),
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
