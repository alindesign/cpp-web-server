#include <cassert>
#include <src/lib/view.h>

using namespace View;

int main() {
  auto document = html(
      {
          std::make_pair("lang", "en"),
      },
      {
          head({
              title("Hello, World!"),
              style("body { background-color: #f0f0f0; }"),
          }),
          body({{"bgcolor", "#f0f0f0"}},
               {
                   h1({text("Hello, World!")}),
                   p({text("This is a paragraph.")}),
               }),
      });

  assert(document.render() ==
         "<!doctype html><html lang=\"en\"><head><title>Hello, "
         "World!</title><style>body { background-color: #f0f0f0; "
         "}</style></head><body bgcolor=\"#f0f0f0\"><h1>Hello, "
         "World!</h1><p>This is a paragraph.</p></body></html>");

  return 0;
}
