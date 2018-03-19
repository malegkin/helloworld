cmake_minimum_required(VERSION 3.2)

#get project version
SET(BUILD_NUMBER "999")

IF(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    SET(BUILD_NUMBER $ENV{TRAVIS_BUILD_NUMBER})
ENDIF()

file (STRINGS ".version" PROJECT_VERSION)

#init project
project (helloworld VERSION ${PROJECT_VERSION}.${BUILD_NUMBER})

#inclue cmake modules
SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

#find Boost unit_test_framework
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

# get TCLAP
find_package(TCLAP REQUIRED)
include_directories(${TCLAP_INCLUDE_DIR})

##version library
# configure a header file to pass some of the CMake settings
# to the source code
configure_file(
    ${CMAKE_SOURCE_DIR}/src/version.h.in 
    ${CMAKE_SOURCE_DIR}/src/version.h
)


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



