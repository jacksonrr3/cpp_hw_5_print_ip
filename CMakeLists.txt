cmake_minimum_required(VERSION 3.2)

project(print_ip VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Threads REQUIRED)

set(SOURCES src/main.cpp)
set(SOURCES_LIB src/print_ip.h)

add_executable(print_ip ${SOURCES} ${SOURCES_LIB})

set_target_properties(print_ip PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT jacksonrr3@yandex.ru)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)


include(CPack)
