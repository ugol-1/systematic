cmake_minimum_required(VERSION 3.8)
project(systematic VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

# add targets
add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(
    DIRECTORY include/
    DESTINATION include/
)

# Install targets and generate an export target
install(TARGETS systematic
    EXPORT systematic-targets
)

install(EXPORT systematic-targets
    NAMESPACE systematic::
    DESTINATION share/systematic/cmake
)

# Generate and install the package configuration and version files
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/systematic-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/systematic-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/systematic-config.cmake"
    INSTALL_DESTINATION share/systematic/cmake
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/systematic-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/systematic-config-version.cmake"
    DESTINATION share/systematic/cmake
)
