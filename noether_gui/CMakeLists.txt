cmake_minimum_required(VERSION 3.5.1)

# Extract package name and version from package.xml
find_package(ros_industrial_cmake_boilerplate REQUIRED)
extract_package_metadata(pkg)

project(${pkg_extracted_name} VERSION ${pkg_extracted_version} LANGUAGES CXX)

find_package(noether_tpp REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

option(NOETHER_ENABLE_CLANG_TIDY "Enables compilation with clang-tidy" OFF)
option(NOETHER_ENABLE_TESTING "Enables compilation of unit tests" OFF)

include_directories(include ${CMAKE_CURRENT_BINARY_DIR})

# Install headers
install(DIRECTORY include/ DESTINATION include/)

# Package configuration
configure_package(NAMESPACE noether)
