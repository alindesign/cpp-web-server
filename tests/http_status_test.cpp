#include <cassert>

#include <src/lib/http_status.h>

int main() {
  constexpr auto code = HttpStatus::Code::OK;

  assert(HttpStatus::reason(code) == "OK");

  return 0;
}
