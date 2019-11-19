cmake_minimum_required(VERSION 3.5)

# options
option(BUILD_TESTS "build test cases for cxx_framework" ON)

# global settings
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# build project
project(cxx_framework CXX)

# CLI11
add_library(CLI11 INTERFACE)
target_include_directories(CLI11 INTERFACE ${PROJECT_SOURCE_DIR}/CLI11/include)

# easy profiler
add_subdirectory(easy_profiler)

# simple ini
add_subdirectory(SimpleIni)

# catch
add_library(catch INTERFACE)
target_include_directories(catch INTERFACE ${PROJECT_SOURCE_DIR}/catch)

# spdlog
add_subdirectory(spdlog)

# json
add_library(json INTERFACE)
target_include_directories(json INTERFACE ${PROJECT_SOURCE_DIR}/json)

# tinyxml2
add_subdirectory(tinyxml2)

# utils
add_subdirectory(utils)

# export library
include(Export.cmake)
add_library(${PROJECT_NAME}
${PROJECT_BINARY_DIR}/${export_cpp}
${PROJECT_BINARY_DIR}/${export_h}
${export_cpp}.in
${export_h}.in)
target_link_libraries(${PROJECT_NAME} PUBLIC
CLI11
easy_profiler
SimpleIni
catch
spdlog::spdlog
json
tinyxml2
framework::utils)
source_group(template FILES ${export_cpp}.in ${export_h}.in)

# build tests
if(BUILD_TESTS)
    add_subdirectory(tests)
endif(BUILD_TESTS)