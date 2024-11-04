project(
    'cpp-web-server',
    'cpp',
    version: '1.0.0',
    default_options: ['warning_level=3', 'cpp_std=c++23'],
)

sources = files(
  'src/lib/http_server.cpp',
  'src/lib/http_server.h',
  'src/lib/http_status.cpp',
  'src/lib/http_status.h',
  'src/lib/logger.h',
  'src/lib/request.cpp',
  'src/lib/request.h',
  'src/lib/response.cpp',
  'src/lib/response.h',
  'src/lib/view.cpp',
  'src/lib/view.h',
)

main = executable('main', 'src/main.cpp', sources: sources, install: true)

test(
  'http_status test',
  executable(
    'http_status_test',
    'tests/http_status_test.cpp',
    sources: sources,
  ),
)

test(
  'view test',
  executable(
    'view_test',
    'tests/view_test.cpp',
    sources: sources,
  ),
)
