cmake_minimum_required(VERSION 3.9)

project (helloworld VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

add_executable(helloworld ./src/main.cpp)

install(TARGETS helloworld RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT malegkin@gmail.com)

include (CPack)

