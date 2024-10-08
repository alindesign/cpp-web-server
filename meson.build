project('cpp-web-server', 'cpp',
        version : '1.0.0',
        default_options : ['warning_level=3', 'cpp_std=c++20'])

cppWebServer = executable('cpp-web-server',
                   'src/common.h',
                   'src/http_server.h',
                   'src/http_server.cpp',
                   'src/request.h',
                   'src/request.cpp',
                   'src/response.h',
                   'src/response.cpp',
                   'src/main.cpp',
                   install : true)

test('test', cppWebServer)
