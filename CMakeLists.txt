cmake_minimum_required(VERSION 3.9)

#dependences
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

#Build Version Configuration
SET(BUILD_NUMBER "999")

IF(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    SET(BUILD_NUMBER $ENV{TRAVIS_BUILD_NUMBER})
ENDIF()


#main
project (helloworld VERSION 0.0.${BUILD_NUMBER})

##version library
configure_file(./src/version.h.in ./src/version.h)
add_library(version ./src/version.cpp)

#main app
add_executable(helloworld ./src/main.cpp)

#test app
add_executable(unit_test_1 ./src/test.cpp)


#etc
set_target_properties(helloworld unit_test_1 PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

set_target_properties(unit_test_1 PROPERTIES
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
  INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(helloworld version)

target_link_libraries(unit_test_1
  ${Boost_LIBRARIES}
  version
)


install(TARGETS helloworld RUNTIME DESTINATION bin)

enable_testing()

add_test(test_version_valid unit_test_1)


#Debian package
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_DEBIAN_PACKAGE_NAME "helloworld")

set(CPACK_PACKAGE_CONTACT malegkin@gmail.com)

include (CPack)



