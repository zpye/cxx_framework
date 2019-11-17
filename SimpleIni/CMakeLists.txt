cmake_minimum_required(VERSION 3.5)

# build project
project(SimpleIni)

add_library(${PROJECT_NAME} SimpleIni.h ConvertUTF.c ConvertUTF.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})