cmake_minimum_required(VERSION 3.5)

# build project
project(utils)

# find dependent libs
find_package(Threads REQUIRED)

set(utils_files
WaitKey.cpp
WaitKey.h
)

add_library(${PROJECT_NAME} ${utils_files})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)
add_library(framework::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
